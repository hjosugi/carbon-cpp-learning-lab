# LogLens report schema contract

## Version 1

top-level `schema_version`は整数`1`です。Version 1 consumerは未知fieldを無視し、必須fieldの型を検証します。

| Field | JSON type | Contract |
| --- | --- | --- |
| `schema_version` | number (integer) | `1` |
| `accepted` | number (integer) | accepted records、unsigned 64-bit range |
| `malformed` | number (integer) | rejected records、unsigned 64-bit range |
| `services` | array | `service`昇順 |
| `service` | string | parser allowlistを通過したASCII name |
| `count` | number (integer) | service records、unsigned 64-bit range |
| `error_rate` | number | `(4xx + 5xx) / count`、`0..1` |
| `latency_avg_ms` | number | latency sum / count |
| `latency_max_ms` | number (integer) | exact maximum、unsigned 32-bit range |
| `latency_p95_upper_ms` | number (integer) | p95を含むpower-of-two bucket上限 |
| `latency_sum_saturated` | boolean | averageのsumが64-bit上限へ到達したことを示す |

## Number precision

- integer fieldはscientific notationを使わずdecimal integerとして出力する。
- 値は最大unsigned 64-bitであり、JavaScript `Number`のsafe integerを超え得る。consumerは64-bit integerまたはarbitrary-precision parserを使う。
- ratio/averageはIEEE 754 `double`で計算し、round-trip可能な`max_digits10`精度で出力する。
- NaN/Infinityは出力しない。count 0のservice entryは生成されない。
- `latency_sum_saturated=true`の場合、averageはsaturated sumに基づくためexactではない。

## Compatibility rules

- Version 1へのoptional field追加はbackward-compatible。consumerは未知fieldを無視する。
- field削除、型変更、意味変更、必須化はbreaking changeで、`schema_version`を増やす。
- service array orderはAPI contractであり、同一入力のbyte-identical outputを保証する。
- whitespace変更はsemantic compatibilityを保つが、golden test更新を必要とする。

## Golden evidence

`product/loglens/tests/golden/`にzero records、one service、many servicesを固定し、debug/releaseの両binaryでbyte compareします。各outputは`jq`でもJSON/type validationします。
