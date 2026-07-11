#include <charconv>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string_view>

namespace {

auto parse_size(std::string_view value, std::size_t fallback) -> std::size_t {
  std::size_t result{};
  const auto parsed = std::from_chars(value.data(), value.data() + value.size(), result);
  return parsed.ec == std::errc{} && parsed.ptr == value.data() + value.size() &&
                 result > 0
             ? result
             : fallback;
}

}  // namespace

auto main(int argc, char** argv) -> int {
  const auto lines = argc > 1 ? parse_size(argv[1], 1'000'000) : 1'000'000;
  const auto services = argc > 2 ? parse_size(argv[2], 1'000) : 1'000;
  std::uint64_t state = 0x9e3779b97f4a7c15ULL;
  for (std::size_t index = 0; index < lines; ++index) {
    state ^= state << 13;
    state ^= state >> 7;
    state ^= state << 17;
    std::cout << "2026-07-12T01:00:00Z INFO service-" << index % services
              << ' ' << state % 10'000 << ' '
              << (state % 20 == 0 ? 500 : 200) << '\n';
  }
  return std::cout ? 0 : 1;
}
