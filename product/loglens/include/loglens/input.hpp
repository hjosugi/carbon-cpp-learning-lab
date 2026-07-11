#pragma once

#include <cstddef>
#include <istream>
#include <string>

namespace loglens {

enum class ReadLineResult { line, end, too_long, error };

// Reads at most max_bytes into line. An oversized line is drained so the
// caller can either report it or stop without retaining attacker-sized input.
[[nodiscard]] auto read_bounded_line(std::istream& input, std::string& line,
                                     std::size_t max_bytes)
    -> ReadLineResult;

}  // namespace loglens
