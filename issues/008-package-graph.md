# package/library graphを設計する

Labels: `area/carbon`, `type/docs`, `priority/p1`

Depends on: #005, #006, #007

## Tasks

- [ ] LogLensをParsing/Aggregation/Reportingへ分割する
- [ ] API fileとimplementation fileを定義する
- [ ] public/private entityを分類する
- [ ] transitive importsとcycleを確認する

## Acceptance criteria

dependency graphにcycleがなく、各libraryのpublic contractとcompile dependencyが文書化される。

## Evidence

Mermaid diagramとAPI skeletonを保存する。
