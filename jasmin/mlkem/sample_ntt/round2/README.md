# Overview

`gen_matrix` implementation study for MLKEM 768, reference and avx2.

## Implementation Overview

* 

## Raw data

### i7-1260P - Alder Lake

| Implementation dir            | Impl. name                 | as -o size in bytes | stack size | median cycles | mean     | sd     | trimmed mean | checksum         |
|-------------------            |------------                |---------------------|------------|---------------|------    |----    |--------------|----------        |
| src/gen_matrix/pqcrystals_ref | gen_matrix                 | 9288                |            | 83229         | 84692.02 | 7284.38| 83714.69     | 0x20ad092986f73c |
| src/gen_matrix/hakyber_ref    | gen_matrix                 | 13072               | 5824       | 158611        | 159000.15| 3039.86| 158803.35    | 0x20ad092986f73c |
| src/gen_matrix/ref            | gen_matrix                 | 4136                | 5152       | 79784         | 79927.04 | 1681.98| 79853.18     | 0x20ad092986f73c |
|-------------------            |------------                |---------------------|------------|---------------|------    |----    |--------------|----------        |
| src/gen_matrix/hakyber_avx2   | gen_matrix                 | 73512               | 8424       | 29814         | 30176.77 | 1344.38| 29989.83     | 0x20ad092986f73c |
| src/gen_matrix/avx2           | gen_matrix                 | 11232               | 8552       | 33106         | 33239.66 | 1136.04| 33142.92     | 0x20ad092986f73c |
|-------------------            |------------                |---------------------|------------|---------------|------    |----    |--------------|----------        |
| src/keccak/keccakf1600        | keccakf1600_hakyber        | 3160                | 432        | 3991          | 3937.55  | 288.71 | 3959.90      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600        | keccakf1600_nobmi1_compact | 2680                | 488        | 1749          | 1760.48  | 138.88 | 1757.16      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600        | keccakf1600_bmi1_compact   | 2584                | 488        | 1485          | 1485.81  | 85.76  | 1484.30      | 0x47d4d25a50f5d7 |
|-------------------            |------------                |---------------------|------------|---------------|------    |----    |--------------|----------        |
| src/keccak/keccakf1600_4x     | keccakf1600_4x_hakyber     | 38248               | 1640       | 2893          | 2895.74  | 117.34 | 2893.62      | 0x8aa6ef973c5e3a |
| src/keccak/keccakf1600_4x     | keccakf1600_4x_compact     | 4016                | 1648       | 3076          | 3085.69  | 124.43 | 3076.53      | 0x8aa6ef973c5e3a |

