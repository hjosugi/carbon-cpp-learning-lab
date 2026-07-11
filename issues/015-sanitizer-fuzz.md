# sanitizerとfuzzingを導入する

Labels: `area/product`, `type/test`, `priority/p0`

Depends on: #014

## Tasks

- [ ] ASan/UBSan testをCIで実行する
- [ ] leak detection可能環境ではLSanを有効化する
- [ ] `parse_line` fuzz targetを作る
- [ ] seed corpusへvalid/invalid/huge inputを入れる

## Acceptance criteria

10分fuzzでcrash/UBがなく、発見inputをregression corpusへ保存するworkflowがある。

## Evidence

sanitizer log、fuzz duration、corpus hashを保存する。
