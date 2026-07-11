# product readiness reviewを行う

Labels: `area/product`, `type/docs`, `priority/p0`

Depends on: #017, #018, #022, #024

## Tasks

- [ ] requirementsとactual behaviorを照合する
- [ ] security/performance/reliability risksをreviewする
- [ ] Carbon componentをoptional/experimentalと確認する
- [ ] rollback、support、versioningを確認する
- [ ] go/no-goを記録する

## Acceptance criteria

C++製品のrelease判断とCarbon実験の判断が別々に記録され、未解決P0が0件である。

## Evidence

signed checklist、known limitations、release decisionを保存する。
