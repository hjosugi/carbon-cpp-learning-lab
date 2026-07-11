#pragma once

#include <utility>
#include <version>

#if !defined(LOGLENS_FORCE_RESULT_FALLBACK) && defined(__cpp_lib_expected) &&  \
    __cpp_lib_expected >= 202202L
#include <expected>

namespace loglens {

template <typename Value, typename Error>
using Result = std::expected<Value, Error>;

template <typename Error> [[nodiscard]] auto unexpected(Error error) {
  return std::unexpected<Error>(std::move(error));
}

} // namespace loglens

#else

#include <variant>

namespace loglens {

template <typename Error> struct Unexpected {
  Error error;
};

template <typename Error>
[[nodiscard]] auto unexpected(Error error) -> Unexpected<Error> {
  return Unexpected<Error>{std::move(error)};
}

// Compatibility adapter for standard libraries that don't expose C++23
// std::expected yet. The project API stays identical and dependency-free.
template <typename Value, typename Error> class Result {
public:
  Result(Value value) : storage_(std::in_place_index<0>, std::move(value)) {}
  Result(Unexpected<Error> error)
      : storage_(std::in_place_index<1>, std::move(error.error)) {}

  [[nodiscard]] auto has_value() const noexcept -> bool {
    return storage_.index() == 0;
  }
  explicit operator bool() const noexcept { return has_value(); }

  [[nodiscard]] auto operator*() & -> Value & { return std::get<0>(storage_); }
  [[nodiscard]] auto operator*() const & -> const Value & {
    return std::get<0>(storage_);
  }
  [[nodiscard]] auto operator->() -> Value * { return &std::get<0>(storage_); }
  [[nodiscard]] auto operator->() const -> const Value * {
    return &std::get<0>(storage_);
  }
  [[nodiscard]] auto error() & -> Error & { return std::get<1>(storage_); }
  [[nodiscard]] auto error() const & -> const Error & {
    return std::get<1>(storage_);
  }

private:
  std::variant<Value, Error> storage_;
};

} // namespace loglens

#endif
