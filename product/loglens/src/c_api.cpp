#include "loglens/c_api.h"

#include <cstdint>

#include "loglens/aggregator.hpp"

static_assert(sizeof(std::uint32_t) == 4);
static_assert(sizeof(std::uint64_t) == 8);

extern "C" auto loglens_bucket_upper(std::uint32_t bucket) noexcept
    -> std::uint64_t {
  return loglens::LatencyHistogram::bucket_upper(bucket);
}
