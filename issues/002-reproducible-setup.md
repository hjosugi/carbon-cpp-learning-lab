# Ubuntu/WSL2環境を再現する

Labels: `area/carbon`, `type/feature`, `priority/p0`

Depends on: #001

## Tasks

- [ ] clean Ubuntu 24.04/WSL2でprerequisitesを導入する
- [ ] `./scripts/bootstrap-carbon.sh`を実行する
- [ ] 2回目がidempotentであることを確認する
- [ ] invalid versionでnon-zeroになることを確認する

## Acceptance criteria

- toolchainが`.tools/`だけに展開される
- partial downloadを完成assetとして扱わない
- unsupported OSは明示的に失敗する

## Evidence

`uname -a`、toolchain path、first/second run logを保存する。secretやhome pathは除く。
