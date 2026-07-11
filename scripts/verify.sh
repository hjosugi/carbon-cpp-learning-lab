#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

for script in "${root_dir}"/scripts/*.sh; do
  bash -n "${script}"
done

make -C "${root_dir}/product/loglens" warnings
make -C "${root_dir}/product/loglens" test
make -C "${root_dir}/product/loglens" release
make -C "${root_dir}/product/loglens" sanitize

output="${root_dir}/product/loglens/build/verification-output.json"
"${root_dir}/product/loglens/build/release/loglens" \
  --input "${root_dir}/product/loglens/samples/access.log" >"${output}"

jq -e '.schema_version == 1 and .accepted == 5 and .malformed == 1' \
  "${output}" >/dev/null
echo "Local verification passed."
