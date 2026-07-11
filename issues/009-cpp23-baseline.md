# Modern C++23 baselineを固める

Labels: `area/cpp`, `type/learning`, `priority/p0`

Depends on: #001

## Tasks

- [ ] GCC 13+またはClang 17+でbuildする
- [ ] `span`, `string_view`, `expected`, `from_chars`, RAIIを復習する
- [ ] warnings-as-errorsをpassする
- [ ] owning raw pointerがないことを確認する

## Acceptance criteria

```bash
make -C product/loglens warnings test release
```

が成功する。

## Evidence

compiler versionとcommand outputを保存する。
