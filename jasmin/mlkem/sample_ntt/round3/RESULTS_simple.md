# alder-lake i7-1260P

| implementation dir                      | impl. name            | cycles (median) | as -o size in bytes | stack size | sct | cpu extensions (from xed)                        | mean     | sd     | trimmed mean | checksum         |
|-------------------                      |------------           |-----------------|---------------------|------------|-----|---------------------------                       |------    |----    |--------------|----------        |
| src/gen_matrix/mlkem768/pqcrystals_ref  | gen_matrix_bmi1       | 75113           | 9096                |            | no  | BASE,BMI1,LONGMODE,SSE,SSE2                      |  75439.31| 2460.53| 75247.90     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/ref_sct         | gen_matrix_bmi1       | 83440           | 4344                | 5152       | yes | BASE,BMI1,MMX,SSE2                               |  83584.11| 1704.51| 83497.28     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/pqcrystals_avx2 | gen_matrix_bmi1_table | 27621           | 26184               |            | no  | AVX,AVX2,AVX2GATHER,BASE,BMI1,BMI2,LONGMODE,SSE4 |  27871.20| 1099.87| 27707.90     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/avx2_opt1_sct   | gen_matrix_bmi1       | 28839           | 12936               | 9288       | yes | AVX,AVX2,BASE,BMI1,MMX,SSE2,SSE4                 |  28967.47| 610.27 | 28885.72     | 0x20ad092986f73c |
| src/gen_matrix/mlkem768/avx2_opt2_sct   | gen_matrix_avx2       | 28074           | 15560               | 8648       | yes | AVX,AVX2,BASE,MMX,SSE2,SSE4                      |  28233.79| 691.16 | 28129.06     | 0x20ad092986f73c |
