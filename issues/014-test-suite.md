# unit/integration testsを拡充する

Labels: `area/product`, `type/test`, `priority/p0`

Depends on: #010, #011, #012, #013

## Tasks

- [ ] parser table tests
- [ ] histogram property tests
- [ ] aggregator overflow tests
- [ ] CLI golden/integration tests
- [ ] deterministic repeated-run test

## Acceptance criteria

testsがnetworkやclockに依存せず、release/debugの両buildで再現する。

## Evidence

test listとCI linkを保存する。
