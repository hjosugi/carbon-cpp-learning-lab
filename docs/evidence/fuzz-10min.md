# Parser fuzz 10-minute evidence

検証日: 2026-07-12

## Environment

```text
clang version 22.1.8
Linux 7.1.2-3-cachyos x86_64 GNU/Linux
```

## Command

```bash
make -C product/loglens CXX=clang++ FUZZ_SECONDS=600 fuzz-long
```

`parse_line`をlibFuzzer + AddressSanitizer + UndefinedBehaviorSanitizerで実行しました。

## Result

```text
#109738844 DONE cov: 173 ft: 452 corp: 164/8068b lim: 4096 exec/s: 182593 rss: 489Mb
Done 109738844 runs in 601 second(s)
```

- crash / leak / OOM / timeout artifact: 0
- sanitizer finding: 0
- 実行後corpus files: 168
- corpus SHA-256 aggregate: `56afd244b96979b5fd85ec05250398471c49106def1e136325d8962551d09d02`

aggregateは次のcommandで、path順を固定した個別SHA-256一覧から計算しました。

```bash
find product/loglens/build/fuzz/corpus -type f -print0 |
  sort -z | xargs -0 sha256sum | sha256sum
```

GitHubの週次/manual `fuzz-long` workflowも同じ10分設定を使い、実行後corpusと個別SHA-256一覧を14日間artifactに保存します。
