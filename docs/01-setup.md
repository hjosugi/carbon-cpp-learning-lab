# 環境構築

## 推奨環境

- Ubuntu 24.04 x86_64、またはWindows上のWSL2 Ubuntu
- `bash`, `curl`, `tar`, `g++`, `make`
- C++23: GCC 13+またはClang 17+

`std::expected`の実装はcompiler frontendだけでなくC++ standard libraryにも依存します。CIのClang jobは対応版`libc++`を`-stdlib=libc++`で明示します。

Carbon nightlyは限定platform向けです。native Windows用の安定版toolchainがある前提にはしません。

## Carbon nightly

```bash
./scripts/bootstrap-carbon.sh
./scripts/run-carbon-smoke.sh
```

scriptは`.carbon-version`と`.carbon-sha256`を使い、checksum検証後に`.tools/`配下へ展開します。別nightlyを試す場合はversionと公式asset digestを両方指定します:

```bash
CARBON_VERSION=0.0.0-0.nightly.2026.07.11 \
CARBON_SHA256=8cd43d622f9f954b2470426e030514cfa8e9aad3ae07be308ea0f1106dc8d2ce \
  ./scripts/bootstrap-carbon.sh
```

公式CLIの基本形:

```bash
carbon compile --output=hello.o hello.carbon
carbon link --output=hello hello.o
./hello
```

link時にsystem libraryが不足する場合は、公式READMEに従いUbuntu側へGCC runtime development packageを入れます。package名はOS releaseごとに確認してください。

## C++製品

```bash
cd product/loglens
make test
make release
./build/release/loglens --input samples/access.log
```

追加検証:

```bash
make sanitize
make warnings
```

## Compiler Explorer

local installで詰まった場合でも、公式のCarbon Compiler Explorerで最小コードを試せます。

https://carbon.compiler-explorer.com/

## よくある失敗

### nightly URLが404

当日分が未生成、またはasset名が変わった可能性があります。GitHub Releasesで実在するversionを確認し、`CARBON_VERSION`に指定します。

### 古い構文例がcompileできない

Carbonはpre-0.1です。古いExplorer interpreter向け記事を使わず、公式`trunk` docsとpinned nightlyを揃えます。

### `carbon link`がsystem libraryを見つけない

GCC runtime development libraryの有無を確認します。compile成功とlink成功を分けて診断してください。

### macOS/Windows nativeで動かない

まずCompiler ExplorerかUbuntu/WSL2で学びます。toolchainを自前buildする作業は別issueに分離します。
