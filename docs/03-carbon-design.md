# Carbonの設計を読む

## 1. Successor strategy

Carbonの中心課題は「優れた新言語を作る」だけではなく、「既存の巨大なC++ codebaseを段階的に移せるか」です。このため、pure designだけでなくABI、toolchain、header import、C++ type mappingが言語設計を制約します。

## 2. Interop-first

CarbonからC++ headerを読む構文は次です。

```carbon
import Cpp library "circle.h";
```

importしたentityは`Cpp.Circle`、`Cpp.putchar`のように`Cpp` package下へ入ります。originが明示され、Carbon名とのcollisionを避けます。

設計目標はsimple C++ APIをcustom bridgeやruntime overheadなしで使うことですが、2026年7月時点の公式interop文書にもconstructor、member access、type mappingなどのTODOが残っています。目標と現在の完成度を混同しないでください。

## 3. Checked generics

C++ templateは通常、具体的な型でinstantiateした時にbodyの誤りが表面化します。Carbon checked genericはinterfaceでrequirementsを宣言し、definition自体をtype-checkします。

期待される利点:

- call site diagnosticがcontract違反を指しやすい
- definitionの再checkを減らせる
- accidental dependencyを抑える
- specializationも表現できる

代償:

- interface/impl/coherenceの設計が複雑
- C++ template interopのためchecked genericsだけでは完結しない
- compile-time/runtime phaseの理解が必要

## 4. Library boundary

packageはnamespaceとdistributionの単位、libraryはAPIとcompile dependencyの単位です。implementation file同士は直接importせず、APIを通じて依存します。

設計レビューでは次を見ます。

- public APIに不要なtypeが漏れていないか
- API fileのtransitive importが大きすぎないか
- library cycleがないか
- C++ typeがCarbon API全体へpervasiveに広がっていないか

## 5. Errors are values

Carbonは「errors are values」をproject principleに持ちます。結果をsum typeで表し、call siteがmatchする設計は、exceptionのhidden control flowを減らします。

ただし、具体的なstandard error APIが固定済みだと決めつけないでください。教材ではconceptを学び、C++製品版では明示的な`ParseResult`を使います。

## 6. Safety migration

公式設計はstrict Carbonとpermissive Carbonを分けます。

- strict: unsafe operationは`unsafe`で明示し、memory-safe language要件を狙う
- permissive: C++ interopとmechanical migrationを優先し、一部unsafeを低摩擦にする

将来のmemory safety modelはRustに近い高水準を狙いつつ、initializationではautomatic initializationやdynamic optional semanticsも使う方向です。2026年7月時点で細部やsyntaxにfuture workが残ります。

## 7. ABI stabilityを絶対目標にしない

Carbonは全言語・libraryに対するstable ABIを明示的non-goalにしています。長期evolutionを可能にするためです。C++との境界ではC++ ABI互換を扱いますが、Carbon全体を永久固定する意味ではありません。

## Design review questions

1. このfeatureはCarbon固有の価値か、C++ interopのためのcostか。
2. compile-time contractはどこにあるか。
3. safe/unsafe boundaryはlocalに監査できるか。
4. ownershipとlifetimeは言語間で誰が持つか。
5. failureはvalue、termination、exceptionのどれか。
6. ABIを固定せず、どのversioning contractを提供するか。
