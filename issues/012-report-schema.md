# report schemaをversion化する

Labels: `area/product`, `type/feature`, `priority/p1`

Depends on: #011

## Tasks

- [ ] top-level `schema_version`を追加する
- [ ] JSON number precision policyを決める
- [ ] deterministic service orderをtestする
- [ ] zero records/one service/many servicesのgolden filesを作る

## Acceptance criteria

outputがvalid JSONで、schema変更規則とbackward compatibility policyが文書化される。

## Evidence

golden JSONとJSON parser validation logを保存する。
