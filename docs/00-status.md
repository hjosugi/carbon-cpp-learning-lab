# 2026年7月時点のCarbon

## 結論

Carbonは「C++後継を目指す実験」であり、現在の本番言語ではありません。一方で、compiler/linkerを含むnightly toolchainは毎日公開され、単純なCarbonコードはcompile/link/runできます。

## 事実と判断

| 項目 | 2026-07-12時点 | この教材での扱い |
| --- | --- | --- |
| project status | experimental | 本番依存禁止 |
| version | `0.0.0-0.nightly.*`、`0.1`未到達 | 日付でpin |
| toolchain | compiler/linkerのnightlyあり | smoke labで使用 |
| platform | recent Ubuntu系を公式例で案内 | Ubuntu/WSL2を推奨 |
| C++ interop | 設計・実装が進行中、TODOも残る | 小さな境界で実験 |
| memory safety | strict/permissive modes等の設計あり | 将来設計と現在実装を分離 |
| production | 公式もearly/experimentalと明記 | C++23版を製品実装にする |

## 重要な最新変更

2026-07-11 nightlyの変更には、旧`:`記号ベースのphase binding syntaxをkeyword/contextual defaultへ置き換える変更が含まれます。古い記事にある`:!`や`:?`を新規教材の基準にしません。

## Carbonが狙う位置

Carbonの差別化は次の組み合わせです。

- performance-critical software
- C++との双方向interopと段階移行
- definition-checked generics
- 大規模な言語・software evolution
- 将来的なmemory-safe mode

Rustの代替としてゼロからecosystemを作るというより、巨大なC++資産を少しずつ移行できることが中心です。安全な汎用library ecosystemについてはRustとのinteropを活用する方向も公式設計に記載されています。

## 学習時のルール

1. `docs/design`は設計、nightlyで動いたコードは実装事実として分ける。
2. 構文を覚えるより、C++の何を改善しようとしているかを説明する。
3. nightly更新は自動追従せず、CIで検証してからpinを更新する。
4. C++相互運用境界は小さくし、ownership、ABI、error contractを文書化する。
5. Carbonのみでproduction-readyと表現しない。

## 公式根拠

- https://github.com/carbon-language/carbon-lang
- https://github.com/carbon-language/carbon-lang/releases
- https://docs.carbon-lang.dev/docs/project/roadmap.html
- https://docs.carbon-lang.dev/docs/design/safety/
- https://docs.carbon-lang.dev/docs/design/interoperability/
