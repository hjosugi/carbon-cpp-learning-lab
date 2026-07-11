# bounded-memory aggregationを検証する

Labels: `area/product`, `area/cpp`, `type/test`, `priority/p0`

Depends on: #010

## Tasks

- [ ] histogram bucket boundaryを全てtestする
- [ ] p50/p95/p99のerror boundを測る
- [ ] latency sum overflow policyをtestする
- [ ] exact percentile版と比較する

## Acceptance criteria

memory complexityが`O(services × buckets)`で、approximation semanticsがreport field名に現れる。

## Evidence

boundary test、error table、peak RSSを保存する。
