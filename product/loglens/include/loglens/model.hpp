#pragma once

#include <cstdint>
#include <string_view>

namespace loglens {

enum class Level : std::uint8_t { trace, debug, info, warn, error, fatal };

struct Record {
  std::string_view timestamp;
  Level level;
  std::string_view service;
  std::uint32_t latency_ms;
  std::uint16_t status;
};

enum class ParseErrorCode : std::uint8_t {
  wrong_field_count,
  invalid_timestamp,
  invalid_level,
  invalid_service,
  invalid_latency,
  invalid_status,
};

struct ParseError {
  ParseErrorCode code;
  std::string_view message;
};

[[nodiscard]] constexpr auto level_name(Level level) noexcept
    -> std::string_view {
  switch (level) {
    case Level::trace:
      return "TRACE";
    case Level::debug:
      return "DEBUG";
    case Level::info:
      return "INFO";
    case Level::warn:
      return "WARN";
    case Level::error:
      return "ERROR";
    case Level::fatal:
      return "FATAL";
  }
  return "UNKNOWN";
}

}  // namespace loglens
