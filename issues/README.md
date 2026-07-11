# GitHub Issues backlog

すべてのissueは単独でGitHubへ転記でき、完了条件と証跡を含みます。番号は推奨実行順です。

これらはv1.0.0の未完成一覧ではなく、完成済みbaselineを自分で再現・拡張するためのguided hands-on backlogです。各自のfork/branchでcheckboxを進め、証跡をcommentへ残します。

| ID | Title | Depends on | Milestone |
| --- | --- | --- | --- |
| 001 | Carbon baselineを固定する | - | M0 |
| 002 | Ubuntu/WSL2環境を再現する | 001 | M0 |
| 003 | nightly smoke labsを完了する | 002 | M1 |
| 004 | basic syntax katasを実装する | 003 | M1 |
| 005 | class/value semanticsを比較する | 004 | M1 |
| 006 | checked genericsを比較する | 004 | M1 |
| 007 | choice/errors-as-valuesを比較する | 004 | M1 |
| 008 | package/library graphを設計する | 005,006,007 | M2 |
| 009 | Modern C++23 baselineを固める | 001 | M2 |
| 010 | LogLens parserをhardeningする | 009 | M3 |
| 011 | bounded-memory aggregationを検証する | 010 | M3 |
| 012 | report schemaをversion化する | 011 | M3 |
| 013 | CLI/exit-code contractを完成する | 010 | M3 |
| 014 | unit/integration testsを拡充する | 010-013 | M3 |
| 015 | sanitizer/fuzzを導入する | 014 | M4 |
| 016 | benchmark/soak testを作る | 011,014 | M4 |
| 017 | resource limitsを実装する | 016 | M4 |
| 018 | CI quality gatesを完成する | 014,015 | M4 |
| 019 | interop boundary contractを固定する | 008,011 | M5 |
| 020 | C ABI experimentを実装する | 019 | M5 |
| 021 | histogram coreをCarbonへportする | 003,020 | M5 |
| 022 | C++/Carbon differential testを作る | 021 | M5 |
| 023 | Carbon nightly更新手順を自動化する | 022 | M6 |
| 024 | packaging/release/SBOMを作る | 018 | M6 |
| 025 | product readiness reviewを行う | 017,18,22,24 | M6 |
| 026 | Carbon upstream contributionを行う | 023,025 | M7 |
| 027 | Carbon toolchain pipelineを追跡する | 003 | M2 |

## Milestones

- M0 Reproducible setup
- M1 Language foundations
- M2 Design and C++ bridge
- M3 Working product
- M4 Product hardening
- M5 Carbon interop experiment
- M6 Release readiness
- M7 Upstream contribution

## 推奨labels

`area/carbon`, `area/cpp`, `area/product`, `area/interop`, `type/learning`, `type/feature`, `type/test`, `type/docs`, `risk/toolchain`, `priority/p0`, `priority/p1`, `priority/p2`

## Issue作成例

```bash
gh issue create \
  --title "$(sed -n '1s/^# //p' issues/001-carbon-baseline.md)" \
  --body-file issues/001-carbon-baseline.md \
  --label 'area/carbon,type/docs,priority/p0'
```

外部repoへ作成する前にtitle、label、milestoneを確認してください。
