# LogLens v1.0.0 Product Readiness Review

判定日: 2026-07-12

## Decision

| Component | Decision | Scope |
| --- | --- | --- |
| LogLens C++23 CLI | **GO** | Linux x86_64 release |
| Carbon nightly smoke labs | **GO for learning** | pinned nightlyのみ |
| Carbon production dependency | **NO-GO** | Carbon 0.1未到達のため |

## Requirements vs actual behavior

| Requirement | Evidence | Result |
| --- | --- | --- |
| streaming processing | bounded line reader + per-record aggregation | Pass |
| untrusted input | RFC 3339、integer、service allowlist | Pass |
| bounded resources | line bytesとunique servicesをCLIで制限 | Pass |
| deterministic JSON | schema version 1 + sorted services | Pass |
| stable CLI failures | integration testsでexit 0/2/3/4/5 | Pass |
| memory/UB checks | ASan、UBSan、10,000-case fuzz smoke | Pass |
| compiler portability | GCC、Clang、`Result<T, E>` compatibility path | Pass |
| supply-chain evidence | SHA-256、provenance、SPDX 2.3 SBOM | Pass |
| clean packaging | staged archiveからversion/sample実行 | Pass |

## Security, reliability, and performance

- parserはlocale非依存で、partial integer parseを拒否する。
- oversized lineは保持せずdrainし、service cardinality超過はfail closedする。
- percentileはserviceごとに固定33 bucketsを使い、入力行数に対してboundedである。
- latency sumはoverflow時にsaturateし、reportへflagを出す。
- malformed recordsは通常modeでcount、strict modeでexit 4とする。
- exact percentile、Windows binary、long-duration soakの保証はrelease scope外とする。

## Carbon isolation

Carbon toolchainは公式asset SHA-256で固定し、C++製品のbuild/runtime dependencyにはしない。nightly drift時はcurrent pinへrollbackでき、design labsはcompile保証対象から分離する。

## Versioning, support, and rollback

- JSON `schema_version`のbreaking changeはmajor releaseで扱う。
- binary rollbackはGitHub Releaseの直前versionへ戻す。
- Carbon rollbackは`.carbon-version`と`.carbon-sha256`を同時に戻す。
- security reportはpublic IssueではなくGitHub private security advisoryを使う。
- release artifactsは`SHA256SUMS`検証後に利用する。

## Release blockers

v1.0.0に対する未解決P0 release blockerはありません。GitHub IssuesのP0表記には、完成baselineを学習者が自分で再現するguided exerciseが含まれ、製品欠陥のseverityとは分離しています。
