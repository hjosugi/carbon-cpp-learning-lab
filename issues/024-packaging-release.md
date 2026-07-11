# packaging/release/SBOMを作る

Labels: `area/product`, `type/feature`, `priority/p1`

Depends on: #018

## Tasks

- [ ] Linux x86_64 release archiveを作る
- [ ] SHA-256 checksumを生成する
- [ ] SPDXまたはCycloneDX SBOMを生成する
- [ ] provenanceとcompiler flagsを記録する
- [ ] install/uninstall instructionsをtestする

## Acceptance criteria

clean containerでarchiveを展開し、sample inputを処理でき、checksum/SBOMがreleaseに含まれる。

## Evidence

artifact名、checksum、clean-install logを保存する。
