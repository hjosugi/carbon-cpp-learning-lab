# resource limitsを実装する

Labels: `area/product`, `type/feature`, `priority/p0`

Depends on: #016

## Tasks

- [ ] max line bytesを設定可能にする
- [ ] max unique servicesを設定可能にする
- [ ] limit超過時のfail/aggregate-other policyを決める
- [ ] disk/full pipe/broken pipe behaviorをtestする

## Acceptance criteria

attacker-controlled cardinality/line sizeでunbounded memoryにならず、limit eventがobservableである。

## Evidence

adversarial testのpeak RSSとexit behaviorを保存する。
