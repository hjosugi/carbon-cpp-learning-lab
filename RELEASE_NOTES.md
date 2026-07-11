# v1.0.0 — Carbon × Modern C++ hands-on lab

2026-07-12時点の公式Carbon nightlyと設計文書に基づく、実行可能な学習bundleの初回stable releaseです。

## Highlights

- SHA-256を固定したCarbon nightly bootstrapと、compile/link/run検証済みの4 labs
- class、struct、choice、pattern matching、checked generics、C++ interopのdesign labs
- 公式status、memory safety、toolchain architecture、Modern C++23比較を含む11章
- 製品レベルのC++23 streaming log analytics CLI「LogLens 1.0.0」
- RFC 3339 parse、bounded input/cardinality、stable JSON schema/exit codes、C ABI seam
- GCC/Clang、unit/integration、ASan/UBSan、libFuzzer、benchmark、CMake/Make
- Linux x86_64 binary、SHA256SUMS、provenance、SPDX 2.3 SBOM
- acceptance criteriaとevidenceを持つ27件のguided GitHub Issues

## Important status

Carbonはpre-0.1の実験的プロジェクトで、本番利用向けではありません。製品baselineは実行検証済みのC++23版で、Carbonコードはnightly smokeと段階移植experimentに分離しています。
