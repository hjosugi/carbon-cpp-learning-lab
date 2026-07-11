# Carbon baselineを固定する

Labels: `area/carbon`, `type/docs`, `priority/p0`, `risk/toolchain`

## Goal

調査日、公式status、nightly version、既知の未実装領域を1つのbaselineとして固定する。

## Tasks

- [ ] README、roadmap、latest releaseを公式sourceで確認する
- [ ] `.carbon-version`と実在release tagを照合する
- [ ] `:!`/`:?`など旧syntaxを教材から検索する
- [ ] design-onlyとtoolchain-supportedの境界を記録する

## Acceptance criteria

- `docs/00-status.md`に調査日とsource URLがある
- pinned nightly assetがGitHub Releasesに存在する
- `rg ':!|:\?' --glob '*.carbon'`が0件

## Evidence

release URL、tag、確認日、`rg`出力をissue commentへ保存する。
