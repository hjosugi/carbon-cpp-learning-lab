# 8週間学習プラン

1日60〜90分、週5日を想定します。

| Week | Theme | Deliverable |
| --- | --- | --- |
| 1 | setup、nightly、basic syntax | smoke labs完了 |
| 2 | tuple、struct、class、value semantics | C++比較ノート |
| 3 | interface、checked generics、templates | generic設計説明 |
| 4 | package/library、errors、choice | mini library設計 |
| 5 | C++23 parserとRAII | LogLens parser拡張 |
| 6 | streaming aggregation、histogram | benchmarkとtest |
| 7 | C++ interop boundary | pure function experiment |
| 8 | toolchain design/contribution | small upstream issue/PR候補 |

## 毎日の型

1. 10分: 前日のコードを見ずに再現
2. 20分: 公式design docを1節読む
3. 30分: labまたはproduct issueを実装
4. 10分: C++との違いを英語3文で説明
5. 10分: test/diagnosticを保存

## 週末レビュー

- 実装済みとdesign-onlyを区別できたか。
- old syntaxを公式trunkで再確認したか。
- API contract、complexity、failureを説明できるか。
- testなしで「動く」と判断していないか。
- 次週のissueを1〜3個だけ`in progress`にしたか。

## Google面接への接続

- checked generics: abstraction、contract、compile-time tradeoff
- package graph: build scalability、dependency management
- LogLens: streaming、bounded memory、approximation
- interop: migration strategy、failure isolation、rollback
- safety modes: product migrationとideal designのtradeoff
