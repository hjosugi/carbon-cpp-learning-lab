#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
lines="${1:-1000000}"
services="${2:-1000}"
report="${3:-${root_dir}/build/benchmark/resource-${lines}-${services}.txt}"

if [[ ! "${lines}" =~ ^[1-9][0-9]*$ || ! "${services}" =~ ^[1-9][0-9]*$ ]]; then
  echo "lines and services must be positive integers" >&2
  exit 2
fi
if [[ ! -x /usr/bin/time ]]; then
  echo "/usr/bin/time is required for peak RSS evidence" >&2
  exit 2
fi

make -C "${root_dir}" build/benchmark/generate release >/dev/null
mkdir -p "$(dirname "${report}")"

/usr/bin/time -v -o "${report}" \
  sh -c '"$1" "$2" "$3" | "$4" --input - >/dev/null' \
  resource-report "${root_dir}/build/benchmark/generate" "${lines}" \
  "${services}" "${root_dir}/build/release/loglens"

{
  echo "lines=${lines}"
  echo "services=${services}"
  grep -E 'Elapsed \(wall clock\)|Maximum resident set size|Exit status' "${report}"
} | tee "${report}.summary"
