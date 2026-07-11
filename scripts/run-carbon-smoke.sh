#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
version="${CARBON_VERSION:-$(<"${root_dir}/.carbon-version")}"
carbon="${root_dir}/.tools/carbon_toolchain-${version}/bin/carbon"
source_dir="${root_dir}/hands-on/carbon/nightly-smoke"
build_dir="${root_dir}/build/carbon-smoke"

if [[ ! -x "${carbon}" ]]; then
  echo "Carbon toolchain is missing. Run ./scripts/bootstrap-carbon.sh first." >&2
  exit 2
fi

rm -rf "${build_dir}"
mkdir -p "${build_dir}"

for source in "${source_dir}"/*.carbon; do
  name="$(basename "${source}" .carbon)"
  object="${build_dir}/${name}.o"
  executable="${build_dir}/${name}"
  echo "==> ${name}"
  "${carbon}" compile --output-last-input-only --output="${object}" "${source}"
  "${carbon}" link --output="${executable}" "${object}"
  "${executable}"
done

echo "Carbon smoke labs passed."
