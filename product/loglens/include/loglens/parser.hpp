#pragma once

#include <string_view>

#include "loglens/model.hpp"
#include "loglens/result.hpp"

namespace loglens {

using ParseResult = Result<Record, ParseError>;

[[nodiscard]] auto parse_line(std::string_view line) noexcept -> ParseResult;

} // namespace loglens
