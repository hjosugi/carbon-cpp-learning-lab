# LogLens parserをhardeningする

Labels: `area/product`, `area/cpp`, `type/feature`, `priority/p0`

Depends on: #009

## Tasks

- [ ] full RFC3339 UTC validationの要否を決める
- [ ] CRLF、empty line、huge lineをtestする
- [ ] latency/status overflowをtestする
- [ ] service length/character policyをtestする

## Acceptance criteria

malformed inputでcrash、UB、partial parseがなく、各failure codeがstableである。

## Evidence

unit test名、coverage対象、sample errorsを保存する。
