#include <cstddef>
#include <cstdint>
#include <string_view>

#include "loglens/parser.hpp"

extern "C" auto LLVMFuzzerTestOneInput(const std::uint8_t* data,
                                       std::size_t size) -> int {
  const auto input = std::string_view(reinterpret_cast<const char*>(data), size);
  static_cast<void>(loglens::parse_line(input));
  return 0;
}
