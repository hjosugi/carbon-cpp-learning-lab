# C++/Carbon differential testを作る

Labels: `area/interop`, `type/test`, `priority/p0`, `risk/toolchain`

Depends on: #021

## Tasks

- [ ] shared vector file formatを定義する
- [ ] deterministic random vectorsを生成する
- [ ] C++/Carbon outputをbyte compareする
- [ ] mismatchをminimal reproductionへ縮小する

## Acceptance criteria

10,000 vectorsで一致し、nightly更新時に自動実行できる。

## Evidence

seed、vector hash、compare logを保存する。
