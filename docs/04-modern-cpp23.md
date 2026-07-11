# Carbon学習者向けModern C++23

Carbonを理解するには、比較対象を古いC++にしないことが重要です。

## この教材のC++ルール

- owning raw pointerを使わない。
- non-owning sequenceは`std::span`、text viewは`std::string_view`。
- parseは`std::from_chars`でlocaleとallocationを避ける。
- expected failureはexceptionではなくresult typeで返す。
- RAIIでresource lifetimeをscopeへ結びつける。
- `const`, `[[nodiscard]]`, `noexcept`をcontractとして使う。
- enumは`enum class`。
- hot pathで不要なallocationを避ける。
- warningsとsanitizerをCI contractにする。

## 対応表

| 問題 | C++23 | Carbon design |
| --- | --- | --- |
| immutable binding | `const` object | `let` |
| mutable binding | ordinary variable | `var` |
| borrowed sequence | `std::span<T>` | `slice(T)` design |
| sum type | `std::variant`, `std::optional`, `std::expected` | `choice` |
| generic constraint | concepts/requires | interface + checked generic |
| module boundary | modules/header | package + library API file |
| error value | `std::expected`等 | errors-as-values principle |
| unsafe operation | convention/tooling中心 | narrow `unsafe` syntax direction |

## なぜLogLensはC++23で完成させるか

現在のCarbonでCLI、filesystem、stable packaging、cross-platform CIまで本番品質に揃えるのは現実的ではありません。そこで、language-independentな仕様とarchitectureを定義し、C++23で完成させます。Carbon側はpure aggregation coreからportし、toolchain成熟に合わせて境界を広げます。

## 面接で説明する短い要点

Carbon should be compared with modern C++, not C++98. Modern C++ already has RAII, concepts, ranges, span, and expected. Carbon's main advantage is not one syntax feature. It is a coherent language and toolchain designed for evolution, checked generics, safety, and gradual C++ migration.
