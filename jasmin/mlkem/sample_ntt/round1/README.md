# Overview

`gen_matrix` implementation study for MLKEM 768, reference and avx2.

## Implementation Overview

* `src/gen_matrix/hakyber_ref` - formosa-crypto/hakyber reference implementation
* `src/gen_matrix/hakyber_avx2` - formosa-crypto/hakyber avx2 implementation
* `src/gen_matrix/ref` - simple reference implementation that closely follows the EasyCrypt specification
* `src/gen_matrix/ref_sct0` - starting from `ref`, protect against spectre v1 in a dummy way (just lfences; baseline for comparison)
* `src/gen_matrix/ref_sct1` - starting from `ref`, protect against spectre v1 in a more elaborate way
* `src/gen_matrix/ref_opt1` - intermediate step between ref and avx2; still scalar code; samples 3 xof blocks and improves the filtering
* `src/gen_matrix/ref_opt1_sct0` - starting from ref_opt1, dummy protection against spectre v1
* `src/gen_matrix/ref_opt1_sct1` - starting from ref_opt1, efficient protection against spectre v1
* `src/gen_matrix/avx2` - simple avx2 implementation: just keccak_4x
* `src/gen_matrix/avx2_opt1` - uses avx2 rejection sampling
* `src/gen_matrix/avx2_opt2` - improves `avx2_opt1`

## Raw data

### i7-1260P - Alder Lake

| Implementation dir           | Impl. name                 | as -o size in bytes | stack size | median cycles | mean    | sd    | trimmed mean | checksum         |
|-------------------           |------------                |---------------------|------------|---------------|------   |----   |--------------|----------        |
| src/gen_matrix/hakyber_ref   | gen_matrix                 | 13072               | 5824       | 54019         | 54099.94| 816.32| 54058.71     | 0x20ad092986f73c |
| src/gen_matrix/hakyber_avx2  | gen_matrix                 | 73512               | 8424       | 10144         | 10295.65| 543.32| 10220.11     | 0x20ad092986f73c |
| src/gen_matrix/ref           | gen_matrix                 | 4088                | 5144       | 27249         | 27317.82| 721.31| 27268.42     | 0x20ad092986f73c |
| src/gen_matrix/ref_sct0      | gen_matrix                 | 4024                | 5144       | 41181         | 41286.59| 964.68| 41207.36     | 0x20ad092986f73c |
| src/gen_matrix/ref_sct1      | gen_matrix                 | 4304                | 5144       | 29430         | 29524.64| 960.86| 29455.20     | 0x20ad092986f73c |
| src/gen_matrix/ref_opt1      | gen_matrix                 | 6960                | 5656       | 24600         | 24856.38| 986.05| 24752.81     | 0x20ad092986f73c |
| src/gen_matrix/ref_opt1_sct0 | gen_matrix                 | 7088                | 5656       | 32152         | 32196.30| 636.44| 32169.34     | 0x20ad092986f73c |
| src/gen_matrix/ref_opt1_sct1 | gen_matrix                 | 8928                | 5656       | 26053         | 26123.09| 662.34| 26073.94     | 0x20ad092986f73c |
| src/gen_matrix/avx2          | gen_matrix                 | 11168               | 8624       | 23595         | 23656.31| 656.00| 23622.31     | 0x20ad092986f73c |
| src/gen_matrix/avx2_opt1     | gen_matrix                 | 14312               | 8656       | 16926         | 16987.46| 512.35| 16951.72     | 0x20ad092986f73c |
| src/gen_matrix/avx2_opt2     | gen_matrix                 | 14312               | 8656       | 15511         | 15558.46| 428.71| 15528.40     | 0x20ad092986f73c |
| src/keccak/keccakf1600       | keccakf1600_hakyber        | 3160                | 432        | 1922          | 1894.44 | 118.88| 1906.18      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600       | keccakf1600_nobmi1         | 3384                | 480        | 794           | 794.11  | 47.39 | 793.49       | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600       | keccakf1600_nobmi1_compact | 2680                | 488        | 839           | 838.56  | 40.80 | 838.17       | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600       | keccakf1600_bmi1_compact   | 2584                | 488        | 721           | 720.59  | 42.02 | 720.17       | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600       | keccakf1600_bmi1           | 3224                | 480        | 654           | 655.23  | 123.77| 653.83       | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600_4x    | keccakf1600_4x_hakyber     | 38248               | 1640       | 1361          | 1362.92 | 55.41 | 1361.81      | 0x8aa6ef973c5e3a |
| src/keccak/keccakf1600_4x    | keccakf1600_4x             | 5224                | 1640       | 1505          | 1507.19 | 67.62 | 1504.67      | 0x8aa6ef973c5e3a |
| src/keccak/keccakf1600_4x    | keccakf1600_4x_compact     | 4016                | 1648       | 1406          | 1409.09 | 52.49 | 1405.98      | 0x8aa6ef973c5e3a |


### i5-6300U - Skylake
| Implementation dir           | Impl. name                 | as -o size in bytes | stack size | median cycles | mean     | sd     | trimmed mean | checksum         |
|-------------------           |------------                |---------------------|------------|---------------|------    |----    |--------------|----------        |
| src/gen_matrix/hakyber_ref   | gen_matrix                 | 13072               | 5824       | 155452        | 157096.88| 9653.84| 155695.13    | 0x20ad092986f73c |
| src/gen_matrix/hakyber_avx2  | gen_matrix                 | 73512               | 8424       | 29434         | 29627.18 | 852.66 | 29495.61     | 0x20ad092986f73c |
| src/gen_matrix/ref           | gen_matrix                 | 4088                | 5144       | 81780         | 81951.78 | 1658.43| 81830.73     | 0x20ad092986f73c |
| src/gen_matrix/ref_sct0      | gen_matrix                 | 4024                | 5144       | 99156         | 99387.71 | 2340.89| 99223.32     | 0x20ad092986f73c |
| src/gen_matrix/ref_sct1      | gen_matrix                 | 4304                | 5144       | 85948         | 86140.76 | 1621.90| 86039.66     | 0x20ad092986f73c |
| src/gen_matrix/ref_opt1      | gen_matrix                 | 6960                | 5656       | 68660         | 68822.26 | 1346.59| 68713.80     | 0x20ad092986f73c |
| src/gen_matrix/ref_opt1_sct0 | gen_matrix                 | 7088                | 5656       | 87836         | 88039.01 | 2572.54| 87896.58     | 0x20ad092986f73c |
| src/gen_matrix/ref_opt1_sct1 | gen_matrix                 | 8928                | 5656       | 74388         | 74552.10 | 1373.23| 74448.74     | 0x20ad092986f73c |
| src/gen_matrix/avx2          | gen_matrix                 | 11168               | 8624       | 53102         | 53258.81 | 1317.21| 53157.36     | 0x20ad092986f73c |
| src/gen_matrix/avx2_opt1     | gen_matrix                 | 14312               | 8656       | 33854         | 33996.02 | 1079.33| 33905.31     | 0x20ad092986f73c |
| src/gen_matrix/avx2_opt2     | gen_matrix                 | 14312               | 8656       | 30234         | 30352.45 | 899.36 | 30279.30     | 0x20ad092986f73c |
| src/keccak/keccakf1600       | keccakf1600_hakyber        | 3160                | 432        | 3932          | 3929.46  | 207.85 | 3931.73      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600       | keccakf1600_nobmi1         | 3384                | 480        | 3672          | 3681.44  | 395.66 | 3672.70      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600       | keccakf1600_nobmi1_compact | 2680                | 488        | 1862          | 1869.97  | 374.96 | 1862.24      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600       | keccakf1600_bmi1_compact   | 2584                | 488        | 3376          | 3440.31  | 726.48 | 3378.24      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600       | keccakf1600_bmi1           | 3224                | 480        | 3006          | 3010.51  | 339.14 | 3005.51      | 0x47d4d25a50f5d7 |
| src/keccak/keccakf1600_4x    | keccakf1600_4x_hakyber     | 38248               | 1640       | 3252          | 3218.90  | 680.94 | 3184.88      | 0x8aa6ef973c5e3a |
| src/keccak/keccakf1600_4x    | keccakf1600_4x             | 5224                | 1640       | 4594          | 4608.31  | 537.94 | 4592.92      | 0x8aa6ef973c5e3a |
| src/keccak/keccakf1600_4x    | keccakf1600_4x_compact     | 4016                | 1648       | 2610          | 2910.28  | 688.15 | 2879.92      | 0x8aa6ef973c5e3a |


## Some TODOs that come to mind

* measure `gen_matrix` with/without bmi1 keccak implementations / extend comparisons
* cleanup and document avx2 implementations
* avx2 sct
* improve ref_opt1 with same idea from avx2_opt2






