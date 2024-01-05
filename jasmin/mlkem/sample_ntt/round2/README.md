# Overview

`gen_matrix` implementation study for MLKEM 768, reference and avx2.

## Implementation Overview

* 

## Raw data

### i7-1260P - Alder Lake

| Implementation dir             | Impl. name                 | as -o size in bytes | stack size | median cycles | mean     | sd     | trimmed mean | checksum         |
|-------------------             |------------                |---------------------|------------|---------------|------    |----    |--------------|----------        |
| src/gen_matrix/pqcrystals_ref  | gen_matrix                 | 9288                |            | 84807         | 85228.93 | 3217.50| 85066.14     | 0x20ad092986f73c |
| src/gen_matrix/hakyber_ref     | gen_matrix                 | 13072               | 5824       | 158553        | 158995.17| 3280.37| 158820.78    | 0x20ad092986f73c |
| src/gen_matrix/ref             | gen_matrix                 | 4136                | 5152       | 79663         | 79833.19 | 1994.34| 79736.66     | 0x20ad092986f73c |
|-------------------             |------------                |---------------------|------------|---------------|------    |----    |--------------|----------        |
| src/gen_matrix/pqcrystals_avx2 | gen_matrix                 | 26376               |            | 26281         | 26533.63 | 3136.41| 26374.76     | 0x20ad092986f73c |
| src/gen_matrix/hakyber_avx2    | gen_matrix                 | 73512               | 8424       | 29833         | 30145.31 | 1137.19| 29986.73     | 0x20ad092986f73c |
| src/gen_matrix/avx2            | gen_matrix                 | 11232               | 8552       | 33100         | 33232.45 | 903.56 | 33145.75     | 0x20ad092986f73c |
|-------------------             |------------                |---------------------|------------|---------------|------    |----    |--------------|----------        |
| src/keccak/keccakf1600         | keccakf1600_hakyber        | 3160                | 432        | 3983          | 3984.51  | 150.40 | 3983.44      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600         | keccakf1600_nobmi1_compact | 2680                | 488        | 1733          | 1736.07  | 102.27 | 1733.99      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600         | keccakf1600_bmi1_compact   | 2584                | 488        | 1483          | 1483.77  | 90.21  | 1482.63      | 0x47d4d25a50f5d7 |
|-------------------             |------------                |---------------------|------------|---------------|------    |----    |--------------|----------        |
| src/keccak/keccakf1600_4x/xkcp | keccakf1600_4x_xkcp        | 10032               |            | 2709          | 2712.14  | 129.62 | 2709.37      | 0x8aa6ef973c5e3a |
| src/keccak/keccakf1600_4x      | keccakf1600_4x_hakyber     | 38248               | 1640       | 2894          | 2910.77  | 2753.17| 2894.17      | 0x8aa6ef973c5e3a |
| src/keccak/keccakf1600_4x      | keccakf1600_4x_compact     | 4016                | 1648       | 3076          | 3078.96  | 122.96 | 3076.06      | 0x8aa6ef973c5e3a |


### i5-6300U - Skylake

| Implementation dir             | Impl. name                 | as -o size in bytes | stack size | median cycles | mean     | sd     | trimmed mean | checksum         |
|-------------------             |------------                |---------------------|------------|---------------|------    |----    |--------------|----------        |
| src/gen_matrix/pqcrystals_ref  | gen_matrix                 | 9288                |            | 89212         | 89438.41 | 1910.89| 89284.07     | 0x20ad092986f73c |
| src/gen_matrix/hakyber_ref     | gen_matrix                 | 13072               | 5824       | 155380        | 155843.45| 2741.21| 155555.75    | 0x20ad092986f73c |
| src/gen_matrix/ref             | gen_matrix                 | 4136                | 5152       | 79016         | 79228.26 | 4671.30| 79074.76     | 0x20ad092986f73c |
|-------------------             |------------                |---------------------|------------|---------------|------    |----     |--------------|----------        |
| src/gen_matrix/pqcrystals_avx2 | gen_matrix                 | 26376               |            | 20464         | 20645.95 | 988.73 | 20526.65     | 0x20ad092986f73c |
| src/gen_matrix/hakyber_avx2    | gen_matrix                 | 73512               | 8424       | 29438         | 29649.89 | 1016.83| 29508.58     | 0x20ad092986f73c |
| src/gen_matrix/avx2            | gen_matrix                 | 11232               | 8552       | 27168         | 27303.45 | 724.75 | 27216.28     | 0x20ad092986f73c |
|-------------------             |------------                |---------------------|------------|---------------|------    |----     |--------------|----------        |
| src/keccak/keccakf1600         | keccakf1600_hakyber        | 3160                | 432        | 3932          | 3935.45  | 183.52 | 3931.56      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600         | keccakf1600_nobmi1_compact | 2680                | 488        | 1786          | 1788.11  | 117.48 | 1786.13      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600         | keccakf1600_bmi1_compact   | 2584                | 488        | 1546          | 1549.74  | 163.31 | 1547.17      | 0x47d4d25a50f5d7 |
|-------------------             |------------                |---------------------|------------|---------------|------    |----     |--------------|----------        |
| src/keccak/keccakf1600_4x/xkcp | keccakf1600_4x_xkcp        | 10032               |            | 1802          | 1794.24  | 140.15 | 1793.34      | 0x8aa6ef973c5e3a |
| src/keccak/keccakf1600_4x      | keccakf1600_4x_hakyber     | 38248               | 1640       | 2440          | 2442.62  | 148.65 | 2439.73      | 0x8aa6ef973c5e3a |
| src/keccak/keccakf1600_4x      | keccakf1600_4x_compact     | 4016                | 1648       | 2046          | 2054.58  | 141.54 | 2052.37      | 0x8aa6ef973c5e3a |

