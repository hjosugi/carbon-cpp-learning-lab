# Security policy

## Supported code

C++ LogLens baselineのみsecurity fix対象です。Carbon examplesとinterop experimentsは学習用であり、production support対象ではありません。

## Threat model

Log inputはuntrustedとみなします。主なriskはmalformed input、integer overflow、extreme line length、unique-service cardinalityによるmemory exhaustion、terminal/JSON injectionです。

Current mitigations:

- `from_chars`によるbounded integer parse
- service character/length allowlist
- fixed-size latency histogram
- saturating latency sum
- bounded line reader（oversized inputを保持せずdrain）
- configurable unique-service limit
- ASan/UBSanとparser fuzz target
- stdout/stderr separation

既定値は1行1 MiB、10,000 servicesです。用途に合わせてCLIでより小さく設定できます。
exact resource budgetと長時間soak testはIssues 016/017で継続追跡します。

## Reporting

Public issueへexploit detailを投稿せず、repository ownerへprivate security advisoryで報告してください。
