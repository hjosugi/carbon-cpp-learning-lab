# CI quality gatesを完成する

Labels: `area/product`, `type/feature`, `priority/p0`

Depends on: #014, #015

## Tasks

- [ ] GCCとClang matrixを追加する
- [ ] warnings/test/sanitizerを分離する
- [ ] cacheなしでも再現する
- [ ] artifactへsample outputとtest logを保存する

## Acceptance criteria

pull requestで必須checksがpassしない限りmergeできないbranch rule案がある。

## Evidence

workflow run URLとrequired check namesを保存する。
