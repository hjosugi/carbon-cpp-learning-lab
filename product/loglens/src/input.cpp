#include "loglens/input.hpp"

#include <algorithm>

namespace loglens {

auto read_bounded_line(std::istream& input, std::string& line,
                       std::size_t max_bytes) -> ReadLineResult {
  line.clear();
  line.reserve(std::min<std::size_t>(max_bytes, 4096));
  bool oversized = false;
  bool read_any = false;

  for (;;) {
    const auto next = input.get();
    if (next == std::char_traits<char>::eof()) {
      if (input.bad()) return ReadLineResult::error;
      if (!read_any) return ReadLineResult::end;
      break;
    }
    read_any = true;
    const auto character = static_cast<char>(next);
    if (character == '\n') break;
    if (!oversized && line.size() < max_bytes) {
      line.push_back(character);
    } else {
      oversized = true;
    }
  }

  if (oversized) {
    line.clear();
    return ReadLineResult::too_long;
  }
  if (!line.empty() && line.back() == '\r') line.pop_back();
  return ReadLineResult::line;
}

}  // namespace loglens
