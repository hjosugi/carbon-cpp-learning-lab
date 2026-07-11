#!/usr/bin/env bash
set -euo pipefail

root_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
version="${1:-$(<"${root_dir}/VERSION")}"
package_name="loglens-${version}-linux-x86_64"
dist_dir="${root_dir}/dist"
stage_dir="${dist_dir}/${package_name}"

if [[ ! "${version}" =~ ^[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
  echo "Version must use X.Y.Z format: ${version}" >&2
  exit 2
fi
if [[ "$(uname -s)-$(uname -m)" != "Linux-x86_64" ]]; then
  echo "Binary packaging currently supports Linux x86_64 only." >&2
  exit 2
fi

make -C "${root_dir}/product/loglens" clean warnings test release
rm -rf "${dist_dir}"
mkdir -p "${stage_dir}/bin" "${stage_dir}/share/loglens"
install -m 0755 "${root_dir}/product/loglens/build/release/loglens" \
  "${stage_dir}/bin/loglens"
install -m 0644 "${root_dir}/product/loglens/README.md" \
  "${stage_dir}/share/loglens/README.md"
install -m 0644 "${root_dir}/product/loglens/samples/access.log" \
  "${stage_dir}/share/loglens/access.log"
install -m 0644 "${root_dir}/LICENSE" "${stage_dir}/LICENSE"

compiler="$(${CXX:-g++} --version | head -n 1)"
binary_sha="$(sha256sum "${stage_dir}/bin/loglens" | cut -d' ' -f1)"
source_sha="$(find "${root_dir}/product/loglens" -type f \
  ! -path '*/build/*' -print0 | sort -z | xargs -0 sha256sum | sha256sum | cut -d' ' -f1)"
cat >"${stage_dir}/share/loglens/PROVENANCE.txt" <<EOF
artifact=${package_name}.tar.gz
version=${version}
source_tree_sha256=${source_sha}
binary_sha256=${binary_sha}
compiler=${compiler}
flags=-std=c++23 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -O3 -DNDEBUG
platform=$(uname -s)-$(uname -m)
EOF

created="$(date -u +%Y-%m-%dT%H:%M:%SZ)"
cat >"${dist_dir}/${package_name}.spdx.json" <<EOF
{
  "spdxVersion": "SPDX-2.3",
  "dataLicense": "CC0-1.0",
  "SPDXID": "SPDXRef-DOCUMENT",
  "name": "${package_name}",
  "documentNamespace": "https://github.com/hjosugi/carbon-cpp-learning-lab/releases/tag/v${version}#sbom",
  "creationInfo": {
    "created": "${created}",
    "creators": ["Tool: carbon-cpp-learning-lab/package-release.sh"]
  },
  "packages": [{
    "name": "LogLens",
    "SPDXID": "SPDXRef-Package-LogLens",
    "versionInfo": "${version}",
    "downloadLocation": "NOASSERTION",
    "filesAnalyzed": false,
    "licenseConcluded": "MIT",
    "licenseDeclared": "MIT",
    "copyrightText": "NOASSERTION"
  }],
  "relationships": [{
    "spdxElementId": "SPDXRef-DOCUMENT",
    "relationshipType": "DESCRIBES",
    "relatedSpdxElement": "SPDXRef-Package-LogLens"
  }]
}
EOF

tar --sort=name --mtime='UTC 2026-07-12' --owner=0 --group=0 --numeric-owner \
  -czf "${dist_dir}/${package_name}.tar.gz" -C "${dist_dir}" "${package_name}"
cp "${stage_dir}/share/loglens/PROVENANCE.txt" \
  "${dist_dir}/${package_name}.provenance.txt"
(
  cd "${dist_dir}"
  sha256sum "${package_name}.tar.gz" "${package_name}.spdx.json" \
    "${package_name}.provenance.txt" >SHA256SUMS
)

"${stage_dir}/bin/loglens" --version
"${stage_dir}/bin/loglens" --input "${stage_dir}/share/loglens/access.log" \
  | jq -e '.schema_version == 1 and .accepted == 5' >/dev/null
echo "Created release artifacts in ${dist_dir}"
