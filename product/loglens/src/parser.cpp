#include "loglens/parser.hpp"

#include <array>
#include <charconv>
#include <cstdint>
#include <string_view>

namespace loglens {
namespace {

constexpr std::size_t kFieldCount = 5;

auto split_fields(std::string_view line,
                  std::array<std::string_view, kFieldCount>& fields) noexcept
    -> bool {
  std::size_t field_index = 0;
  std::size_t position = 0;

  while (position < line.size()) {
    while (position < line.size() && line[position] == ' ') {
      ++position;
    }
    if (position == line.size()) {
      break;
    }
    if (field_index == fields.size()) {
      return false;
    }
    const auto start = position;
    while (position < line.size() && line[position] != ' ') {
      ++position;
    }
    fields[field_index++] = line.substr(start, position - start);
  }
  return field_index == fields.size();
}

auto parse_level(std::string_view value) noexcept -> std::expected<Level, ParseError> {
  if (value == "TRACE") return Level::trace;
  if (value == "DEBUG") return Level::debug;
  if (value == "INFO") return Level::info;
  if (value == "WARN") return Level::warn;
  if (value == "ERROR") return Level::error;
  if (value == "FATAL") return Level::fatal;
  return std::unexpected(
      ParseError{ParseErrorCode::invalid_level, "invalid level"});
}

auto decimal(std::string_view value, std::size_t offset,
             std::size_t length) noexcept -> int {
  int result = 0;
  for (std::size_t index = offset; index < offset + length; ++index) {
    const auto character = value[index];
    if (character < '0' || character > '9') return -1;
    result = result * 10 + (character - '0');
  }
  return result;
}

auto is_leap_year(int year) noexcept -> bool {
  return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

auto valid_timestamp(std::string_view value) noexcept -> bool {
  // RFC 3339 UTC subset: YYYY-MM-DDTHH:MM:SS[.fraction]Z. Leap seconds are
  // intentionally rejected because LogLens has no leap-second time model.
  if (value.size() < 20 || value[4] != '-' || value[7] != '-' ||
      value[10] != 'T' || value[13] != ':' || value[16] != ':' ||
      value.back() != 'Z') {
    return false;
  }
  if (value.size() > 20) {
    if (value[19] != '.' || value.size() == 21) return false;
    for (std::size_t index = 20; index + 1 < value.size(); ++index) {
      if (value[index] < '0' || value[index] > '9') return false;
    }
  }

  const int year = decimal(value, 0, 4);
  const int month = decimal(value, 5, 2);
  const int day = decimal(value, 8, 2);
  const int hour = decimal(value, 11, 2);
  const int minute = decimal(value, 14, 2);
  const int second = decimal(value, 17, 2);
  if (year < 0 || month < 1 || month > 12 || hour < 0 || hour > 23 ||
      minute < 0 || minute > 59 || second < 0 || second > 59) {
    return false;
  }
  constexpr std::array<int, 12> kDaysPerMonth{
      31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int days = kDaysPerMonth[static_cast<std::size_t>(month - 1)];
  if (month == 2 && is_leap_year(year)) ++days;
  return day >= 1 && day <= days;
}

auto valid_service(std::string_view value) noexcept -> bool {
  if (value.empty() || value.size() > 128) return false;
  for (const char character : value) {
    const bool ascii_alphanumeric =
        (character >= 'a' && character <= 'z') ||
        (character >= 'A' && character <= 'Z') ||
        (character >= '0' && character <= '9');
    if (!(ascii_alphanumeric || character == '_' || character == '-' ||
          character == '.')) {
      return false;
    }
  }
  return true;
}

template <typename Integer>
auto parse_integer(std::string_view value) noexcept -> std::expected<Integer, ParseError> {
  Integer result{};
  const auto* begin = value.data();
  const auto* end = begin + value.size();
  const auto parsed = std::from_chars(begin, end, result);
  if (parsed.ec != std::errc{} || parsed.ptr != end) {
    return std::unexpected(
        ParseError{ParseErrorCode::invalid_latency, "invalid integer"});
  }
  return result;
}

}  // namespace

auto parse_line(std::string_view line) noexcept -> ParseResult {
  std::array<std::string_view, kFieldCount> fields{};
  if (!split_fields(line, fields)) {
    return std::unexpected(ParseError{ParseErrorCode::wrong_field_count,
                                      "expected exactly five fields"});
  }
  if (!valid_timestamp(fields[0])) {
    return std::unexpected(ParseError{ParseErrorCode::invalid_timestamp,
                                      "invalid UTC timestamp envelope"});
  }

  const auto level = parse_level(fields[1]);
  if (!level) return std::unexpected(level.error());

  if (!valid_service(fields[2])) {
    return std::unexpected(ParseError{ParseErrorCode::invalid_service,
                                      "invalid service name"});
  }

  const auto latency = parse_integer<std::uint32_t>(fields[3]);
  if (!latency) {
    return std::unexpected(ParseError{ParseErrorCode::invalid_latency,
                                      "invalid latency"});
  }

  const auto status = parse_integer<std::uint16_t>(fields[4]);
  if (!status || *status < 100 || *status > 599) {
    return std::unexpected(
        ParseError{ParseErrorCode::invalid_status, "status must be 100..599"});
  }

  return Record{fields[0], *level, fields[2], *latency, *status};
}

}  // namespace loglens
