#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
parent_dir="$(dirname "${root_dir}")"
archive_name="carbon-cpp-learning-lab-2026-07-12.zip"
archive_path="${parent_dir}/${archive_name}"

rm -f "${archive_path}"
(
  cd "${parent_dir}"
  zip -q -r "${archive_path}" "$(basename "${root_dir}")" \
    -x '*/.git/*' '*/.tools/*' '*/build/*' '*/dist/*'
)
unzip -tq "${archive_path}" >/dev/null
sha256sum "${archive_path}" >"${archive_path}.sha256"
echo "Created ${archive_path}"
