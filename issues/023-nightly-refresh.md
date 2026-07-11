# Carbon nightly更新手順を自動化する

Labels: `area/carbon`, `type/feature`, `priority/p1`, `risk/toolchain`

Depends on: #022

## Tasks

- [ ] latest release discoveryとasset存在確認を分ける
- [ ] proposed `.carbon-version` updateをPR化する
- [ ] smoke/differential testsを必須にする
- [ ] syntax change release notesをsummaryする

## Acceptance criteria

自動jobはmergeせず、検証済みPRだけを作る。failed nightlyはcurrent pinを壊さない。

## Evidence

成功/失敗run URLとrollback手順を保存する。
