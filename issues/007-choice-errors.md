# choiceとerrors-as-valuesを比較する

Labels: `area/carbon`, `area/cpp`, `type/learning`, `priority/p1`

Depends on: #004

## Tasks

- [ ] Carbon `choice ParseResult`を設計する
- [ ] `match`で全alternativeを処理する
- [ ] C++ `std::expected`版と`std::variant`版を比較する
- [ ] exceptionを使わない理由と使う場合を文書化する

## Acceptance criteria

invalid inputが通常eventであるparserのerror contractが明示され、追加alternative時の影響を説明できる。

## Evidence

test casesとdesign noteを保存する。
