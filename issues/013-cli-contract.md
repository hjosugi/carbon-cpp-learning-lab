# CLI/exit-code contractを完成する

Labels: `area/product`, `type/feature`, `priority/p1`

Depends on: #010

## Tasks

- [ ] `--input -`でstdinを読む
- [ ] duplicate option policyを決める
- [ ] `--help`とversion outputを追加する
- [ ] exit codes 0/2/3/4をintegration testする

## Acceptance criteria

stdoutにreport以外を出さず、diagnosticはstderr、全exit codeがREADMEと一致する。

## Evidence

shell integration test outputを保存する。
