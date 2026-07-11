#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#define LOGLENS_NOEXCEPT noexcept
#else
#define LOGLENS_NOEXCEPT
#endif

// Stable C ABI seam for the Carbon interop lab. No allocation or ownership is
// transferred. Values >= 32 saturate at UINT32_MAX.
uint64_t loglens_bucket_upper(uint32_t bucket) LOGLENS_NOEXCEPT;

#ifdef __cplusplus
}
#endif

#undef LOGLENS_NOEXCEPT
