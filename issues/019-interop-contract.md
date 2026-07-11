# interop boundary contractを固定する

Labels: `area/interop`, `area/carbon`, `area/cpp`, `type/docs`, `priority/p0`

Depends on: #008, #011

## Tasks

- [ ] fixed-width typesだけのC ABIを定義する
- [ ] ownership/nullability/threadingを明記する
- [ ] exceptionをboundary外へ出さない
- [ ] ABI versionとsymbol policyを決める

## Acceptance criteria

headerだけでcaller contractが理解でき、layout/width static assertionsがある。

## Evidence

API review checklistとapproved headerを保存する。
