# histogram coreをCarbonへportする

Labels: `area/carbon`, `area/interop`, `type/feature`, `priority/p1`, `risk/toolchain`

Depends on: #003, #020

## Tasks

- [ ] bucket selection pure functionをportする
- [ ] bucket upper pure functionをportする
- [ ] overflow/shift boundaryを定義する
- [ ] unsupported library featureを最小化する

## Acceptance criteria

Carbon版がpinned nightlyでcompileし、C++版と全32-bit boundary casesで一致する。

## Evidence

source、toolchain version、comparison outputを保存する。
