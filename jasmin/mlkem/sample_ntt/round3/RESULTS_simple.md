# alder-lake i7-1260P

| implementation dir                      | impl. name            | cycles (median) | as -o size in bytes | stack size | sct | cpu extensions (from xed)                        | mean     | sd     | trimmed mean | checksum         |
|-------------------                      |------------           |-----------------|---------------------|------------|-----|---------------------------                       |------    |----    |--------------|----------        |
| src/gen_matrix/mlkem768/pqcrystals_ref  | gen_matrix_bmi1       | 75113           | 9096                |            | no  | BASE,BMI1,LONGMODE,SSE,SSE2                      |  75439.31| 2460.53| 75247.90     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/ref_sct         | gen_matrix_bmi1       | 83440           | 4344                | 5152       | yes | BASE,BMI1,MMX,SSE2                               |  83584.11| 1704.51| 83497.28     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/pqcrystals_avx2 | gen_matrix_bmi1_table | 27621           | 26184               |            | no  | AVX,AVX2,AVX2GATHER,BASE,BMI1,BMI2,LONGMODE,SSE4 |  27871.20| 1099.87| 27707.90     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/avx2_opt1_sct   | gen_matrix_bmi1       | 28839           | 12936               | 9288       | yes | AVX,AVX2,BASE,BMI1,MMX,SSE2,SSE4                 |  28967.47| 610.27 | 28885.72     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/avx2_opt2_sct   | gen_matrix_avx2       | 28074           | 15560               | 8648       | yes | AVX,AVX2,BASE,MMX,SSE2,SSE4                      |  28233.79| 691.16 | 28129.06     | 0x20ad092986f73c |

# i7 11700K
| implementation dir                      | impl. name            | cycles (median) | as -o size in bytes | stack size | sct | cpu extensions (from xed) | mean     | sd     | trimmed mean | checksum         |
|-------------------                      |------------           |-----------------|---------------------|------------|-----|---------------------------|------    |----    |--------------|----------        |
| src/gen_matrix/mlkem768/pqcrystals_ref  | gen_matrix_bmi1       | 54518           | 9096                |            | no  |                           |  54616.01| 1037.62| 54559.12     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/ref_sct         | gen_matrix_bmi1       | 63450           | 4344                | 5152       | yes |                           |  63582.10| 1657.18| 63497.11     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/pqcrystals_avx2 | gen_matrix_bmi1_table | 17122           | 26184               |            | no  |                           |  17290.74| 1740.71| 17167.33     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/avx2_opt1_sct   | gen_matrix_bmi1       | 17148           | 12936               | 9288       | yes |                           |  17251.25| 472.02 | 17184.16     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/avx2_opt2_sct   | gen_matrix_avx2       | 16890           | 15560               | 8648       | yes |                           |  16985.67| 464.97 | 16920.94     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/avx2_opt3_sct   | gen_matrix_bmi1       | 16844           | 15104               | 9288       | yes |                           |  16950.02| 486.22 | 16881.74     | 0x20ad092986f73c |

