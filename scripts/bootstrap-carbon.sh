#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
version="${CARBON_VERSION:-$(<"${root_dir}/.carbon-version")}"
expected_sha="${CARBON_SHA256:-$(<"${root_dir}/.carbon-sha256")}"
toolchain_name="carbon_toolchain-${version}"
install_dir="${root_dir}/.tools/${toolchain_name}"
archive="${root_dir}/.tools/${toolchain_name}.tar.gz"
url="https://github.com/carbon-language/carbon-lang/releases/download/v${version}/${toolchain_name}.tar.gz"

if [[ "$(uname -s)" != "Linux" ]]; then
  echo "Carbon nightly bootstrap currently expects Linux (Ubuntu/WSL2)." >&2
  exit 2
fi

if [[ -x "${install_dir}/bin/carbon" ]]; then
  echo "Carbon toolchain is already installed: ${install_dir}"
  exit 0
fi

mkdir -p "${root_dir}/.tools"
echo "Downloading pinned Carbon nightly ${version}"
curl --proto '=https' --tlsv1.2 --fail --location --retry 3 \
  --output "${archive}.partial" "${url}"
mv "${archive}.partial" "${archive}"

actual_sha="$(sha256sum "${archive}" | cut -d' ' -f1)"
if [[ "${actual_sha}" != "${expected_sha}" ]]; then
  rm -f "${archive}"
  echo "Carbon archive checksum mismatch." >&2
  exit 3
fi

while IFS= read -r entry; do
  case "${entry}" in
    /*|../*|*/../*)
      echo "Unsafe archive path: ${entry}" >&2
      exit 4
      ;;
  esac
done < <(tar -tzf "${archive}")

tar -xzf "${archive}" -C "${root_dir}/.tools"
if [[ ! -x "${install_dir}/bin/carbon" ]]; then
  echo "Carbon executable was not found after extraction." >&2
  exit 5
fi

echo "Installed: ${install_dir}/bin/carbon"
