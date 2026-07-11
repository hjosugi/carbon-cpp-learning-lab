#!/usr/bin/env bash
set -euo pipefail

binary="${1:?usage: integration.sh BINARY}"
tmp_dir="$(mktemp -d)"
trap 'rm -rf "${tmp_dir}"' EXIT

valid='2026-07-12T01:00:00Z INFO api 17 200'
printf '%s\n' "${valid}" | "${binary}" --input - >"${tmp_dir}/stdin.json"
jq -e '.schema_version == 1 and .accepted == 1 and .malformed == 0' \
  "${tmp_dir}/stdin.json" >/dev/null

"${binary}" --version | grep -qx 'loglens 1.0.0'
"${binary}" --help >/dev/null

expect_exit() {
  local expected="$1"
  shift
  set +e
  "$@" >"${tmp_dir}/stdout" 2>"${tmp_dir}/stderr"
  local actual=$?
  set -e
  if [[ "${actual}" -ne "${expected}" ]]; then
    echo "expected exit ${expected}, got ${actual}: $*" >&2
    return 1
  fi
}

expect_exit 2 "${binary}" --input - --input -
expect_exit 3 "${binary}" --input "${tmp_dir}/missing"
printf '%s\n' bad | expect_exit 4 "${binary}" --input - --strict
printf '%s\n' "${valid}" | expect_exit 5 "${binary}" --input - --max-line-bytes 8
printf '%s\n%s\n' "${valid}" \
  '2026-07-12T01:00:01Z INFO worker 18 200' |
  expect_exit 5 "${binary}" --input - --max-services 1

printf 'integration tests passed\n'
