#pragma once

#include <expected>
#include <string_view>

#include "loglens/model.hpp"

namespace loglens {

using ParseResult = std::expected<Record, ParseError>;

[[nodiscard]] auto parse_line(std::string_view line) noexcept -> ParseResult;

}  // namespace loglens
