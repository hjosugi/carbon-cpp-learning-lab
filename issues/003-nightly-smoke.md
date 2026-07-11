# nightly smoke labsを完了する

Labels: `area/carbon`, `type/learning`, `priority/p0`

Depends on: #002

## Tasks

- [ ] 4つの`.carbon`をcompileする
- [ ] objectをlinkする
- [ ] executable outputを確認する
- [ ] intentional compile errorを1つ作りdiagnosticを読む

## Acceptance criteria

```bash
./scripts/run-carbon-smoke.sh
```

がexit 0で、各labのcompile/link/runを順番に表示する。

## Evidence

toolchain version、command、output、失敗時diagnosticを保存する。
