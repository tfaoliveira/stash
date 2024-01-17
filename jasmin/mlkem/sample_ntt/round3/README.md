# Overview

`gen_matrix` - Jasmin implementation study for MLKEM 512 / 768 / 1024, reference and avx2 (with and without Spectre v1 protections: suffix `_sct`)

## List of properties to consider

* performance difference from 26K to 33K 
* 512 / 768 / 1024
* bmi vs non-bmi analysis

## Implementation Overview

* 

## Raw data

### i7-1260P - Alder Lake

### i7-1260P - Alder Lake

| implementation dir                       | impl. name                 | cycles (median) | as -o size in bytes | stack size | cpu extensions (from xed)                        | mean      | sd      | trimmed mean | checksum         |
|-------------------                       |------------                |-----------------|---------------------|------------|---------------------------                       |------     |----     |--------------|----------        |
| src/gen_matrix/mlkem1024/pqcrystals_ref  | gen_matrix_nobmi1          | 157664          | 9288                |            | BASE,LONGMODE,SSE,SSE2                           |  160948.32| 14149.19| 159605.85    | 0xe6ea86200be211 |
| src/gen_matrix/mlkem1024/pqcrystals_ref  | gen_matrix_bmi1            | 132870          | 9096                |            | BASE,BMI1,LONGMODE,SSE,SSE2                      |  133632.74| 8026.79 | 133196.51    | 0xe6ea86200be211 |
| src/gen_matrix/mlkem1024/ref             | gen_matrix_nobmi1          | 146139          | 4200                | 8736       | BASE,MMX                                         |  146614.76| 18323.23| 146222.15    | 0xe6ea86200be211 |
| src/gen_matrix/mlkem1024/ref             | gen_matrix_bmi1            | 134895          | 4136                | 8736       | BASE,BMI1,MMX                                    |  135101.70| 2505.02 | 134982.10    | 0xe6ea86200be211 |
| src/gen_matrix/mlkem1024/pqcrystals_avx2 | gen_matrix_nobmi1_notable  | 41916           | 16360               |            | AVX,AVX2,AVX2GATHER,BASE,BMI2,LONGMODE,SSE4      |  42317.73 | 1461.52 | 42140.22     | 0xe6ea86200be211 |
| src/gen_matrix/mlkem1024/pqcrystals_avx2 | gen_matrix_nobmi1_table    | 44915           | 18256               |            | AVX,AVX2,AVX2GATHER,BASE,BMI2,LONGMODE,SSE4      |  46642.69 | 7519.69 | 45334.82     | 0xe6ea86200be211 |
| src/gen_matrix/mlkem1024/pqcrystals_avx2 | gen_matrix_bmi1_notable    | 42020           | 16360               |            | AVX,AVX2,AVX2GATHER,BASE,BMI2,LONGMODE,SSE4      |  42392.01 | 1246.91 | 42240.94     | 0xe6ea86200be211 |
| src/gen_matrix/mlkem1024/pqcrystals_avx2 | gen_matrix_bmi1_table      | 39678           | 18256               |            | AVX,AVX2,AVX2GATHER,BASE,BMI2,LONGMODE,SSE4      |  40078.86 | 1285.88 | 39924.98     | 0xe6ea86200be211 |
| src/gen_matrix/mlkem1024/avx2            | gen_matrix_nobmi1          | 45339           | 11032               | 12136      | AVX,AVX2,BASE,MMX,SSE4                           |  45547.32 | 1035.73 | 45448.99     | 0xe6ea86200be211 |
| src/gen_matrix/mlkem1024/avx2            | gen_matrix_bmi1            | 45317           | 10936               | 12136      | AVX,AVX2,BASE,BMI1,MMX,SSE4                      |  45615.23 | 9606.02 | 45409.20     | 0xe6ea86200be211 |


| implementation dir                       | impl. name                 | cycles (median) | as -o size in bytes | stack size | cpu extensions (from xed)                        | mean      | sd      | trimmed mean | checksum         |
|-------------------                       |------------                |-----------------|---------------------|------------|---------------------------                       |------     |----     |--------------|----------        |
| src/gen_matrix/mlkem768/pqcrystals_ref   | gen_matrix_nobmi1          | 82751           | 9288                |            | BASE,LONGMODE,SSE,SSE2                           |  83171.98 | 2650.92 | 82953.84     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/pqcrystals_ref   | gen_matrix_bmi1            | 74912           | 9096                |            | BASE,BMI1,LONGMODE,SSE,SSE2                      |  75170.46 | 2367.03 | 75002.60     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/ref              | gen_matrix_nobmi1          | 81950           | 4200                | 5152       | BASE,MMX                                         |  82261.41 | 2631.25 | 82038.82     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/ref              | gen_matrix_bmi1            | 75905           | 4136                | 5152       | BASE,BMI1,MMX                                    |  76237.96 | 2773.97 | 75988.31     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/pqcrystals_avx2  | gen_matrix_nobmi1_notable  | 27450           | 24464               |            | AVX,AVX2,AVX2GATHER,BASE,BMI2,LONGMODE,SSE4      |  27668.08 | 1037.13 | 27527.21     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/pqcrystals_avx2  | gen_matrix_nobmi1_table    | 26353           | 26376               |            | AVX,AVX2,AVX2GATHER,BASE,BMI2,LONGMODE,SSE4      |  26547.16 | 1095.43 | 26412.34     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/pqcrystals_avx2  | gen_matrix_bmi1_notable    | 26248           | 24272               |            | AVX,AVX2,AVX2GATHER,BASE,BMI1,BMI2,LONGMODE,SSE4 |  26488.50 | 1021.81 | 26342.21     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/pqcrystals_avx2  | gen_matrix_bmi1_table      | 25110           | 26184               |            | AVX,AVX2,AVX2GATHER,BASE,BMI1,BMI2,LONGMODE,SSE4 |  25326.83 | 940.13  | 25189.90     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/avx2             | gen_matrix_nobmi1          | 31918           | 11488               | 8552       | AVX,AVX2,BASE,MMX,SSE4                           |  33902.75 | 9013.03 | 32437.01     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/avx2             | gen_matrix_bmi1            | 31109           | 11392               | 8552       | AVX,AVX2,BASE,BMI1,MMX,SSE4                      |  31225.14 | 858.03  | 31152.91     | 0x20ad092986f73c |

| implementation dir                       | impl. name                 | cycles (median) | as -o size in bytes | stack size | cpu extensions (from xed)                        | mean      | sd      | trimmed mean | checksum         |
|-------------------                       |------------                |-----------------|---------------------|------------|---------------------------                       |------     |----     |--------------|----------        |
| src/gen_matrix/mlkem512/pqcrystals_ref   | gen_matrix_nobmi1          | 37078           | 9320                |            | BASE,LONGMODE,SSE,SSE2                           |  39638.76 | 10627.51| 38117.45     | 0xa2c8edb4cf1224 |
| src/gen_matrix/mlkem512/pqcrystals_ref   | gen_matrix_bmi1            | 33296           | 9128                |            | BASE,BMI1,LONGMODE,SSE,SSE2                      |  33453.70 | 1346.83 | 33347.69     | 0xa2c8edb4cf1224 |
| src/gen_matrix/mlkem512/ref              | gen_matrix_nobmi1          | 36572           | 4200                | 2592       | BASE,MMX                                         |  36669.68 | 1084.50 | 36604.86     | 0xa2c8edb4cf1224 |
| src/gen_matrix/mlkem512/ref              | gen_matrix_bmi1            | 33808           | 4136                | 2592       | BASE,BMI1,MMX                                    |  33973.07 | 5682.90 | 33826.41     | 0xa2c8edb4cf1224 |
| src/gen_matrix/mlkem512/pqcrystals_avx2  | gen_matrix_nobmi1_notable  | 10532           | 16168               |            | AVX,AVX2,AVX2GATHER,BASE,BMI2,LONGMODE,SSE4      |  10646.80 | 647.01  | 10545.05     | 0xa2c8edb4cf1224 |
| src/gen_matrix/mlkem512/pqcrystals_avx2  | gen_matrix_nobmi1_table    | 9902            | 18064               |            | AVX,AVX2,AVX2GATHER,BASE,BMI2,LONGMODE,SSE4      |  10023.60 | 709.52  | 9912.61      | 0xa2c8edb4cf1224 |
| src/gen_matrix/mlkem512/pqcrystals_avx2  | gen_matrix_bmi1_notable    | 10496           | 16168               |            | AVX,AVX2,AVX2GATHER,BASE,BMI2,LONGMODE,SSE4      |  10621.94 | 750.67  | 10511.35     | 0xa2c8edb4cf1224 |
| src/gen_matrix/mlkem512/pqcrystals_avx2  | gen_matrix_bmi1_table      | 9915            | 18064               |            | AVX,AVX2,AVX2GATHER,BASE,BMI2,LONGMODE,SSE4      |  10033.14 | 710.92  | 9926.25      | 0xa2c8edb4cf1224 |
| src/gen_matrix/mlkem512/avx2             | gen_matrix_nobmi1          | 11310           | 10984               | 5992       | AVX,AVX2,BASE,MMX,SSE4                           |  11381.02 | 462.62  | 11322.19     | 0xa2c8edb4cf1224 |
| src/gen_matrix/mlkem512/avx2             | gen_matrix_bmi1            | 11350           | 10888               | 5992       | AVX,AVX2,BASE,BMI1,MMX,SSE4                      |  11415.49 | 460.73  | 11364.01     | 0xa2c8edb4cf1224 |

| implementation dir                       | impl. name                 | cycles (median) | as -o size in bytes | stack size | cpu extensions (from xed)                        | mean      | sd      | trimmed mean | checksum         |
|-------------------                       |------------                |-----------------|---------------------|------------|---------------------------                       |------     |----     |--------------|----------        |
| src/keccak/keccakf1600_4x/xkcp           | keccakf1600_4x_xkcp        | 2795            | 10032               |            | AVX,AVX2,BASE                                    |  2800.37  | 196.13  | 2796.01      | 0x8aa6ef973c5e3a |
| src/keccak/keccakf1600_4x                | keccakf1600_4x_compact     | 3118            | 4016                | 1648       | AVX,AVX2,BASE,MMX                                |  3124.50  | 308.63  | 3117.69      | 0x8aa6ef973c5e3a |
| src/keccak/keccakf1600                   | keccakf1600_nobmi1_compact | 1838            | 2680                | 488        | BASE,MMX                                         |  1834.84  | 117.54  | 1832.47      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600                   | keccakf1600_bmi1_compact   | 1570            | 2584                | 488        | BASE,BMI1,MMX                                    |  1569.75  | 102.58  | 1568.62      | 0x47d4d25a50f5d7 |


### i5-6300U - Skylake

