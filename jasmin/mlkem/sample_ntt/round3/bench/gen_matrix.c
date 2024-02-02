#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "common/cpucycles.c"
#include "randombytes.c"

#ifndef RUNS
#define RUNS 10
#endif

#ifndef TIMINGS
#define TIMINGS 10001
#endif

#ifndef GEN_MATRIX_SIZE
#define GEN_MATRIX_SIZE 2304
#endif

extern uint64_t gen_matrix(uint16_t matrix_ptr[GEN_MATRIX_SIZE], uint8_t seed_ptr[32], uint64_t transposed);

void bench_gen_matrix_setup1(void)
{
  unsigned long timings[TIMINGS];
  uint64_t median;
  double mean, sd, tr_mean;

  uint8_t *seed;
  uint8_t *seed_ptr;
  uint16_t *matrix;

  seed = aligned_alloc(16, sizeof(uint8_t) * 32 * TIMINGS);
  assert(seed != NULL);

  matrix = aligned_alloc(16, sizeof(uint16_t) * GEN_MATRIX_SIZE);
  assert(matrix != NULL);

  for(size_t run=0; run<RUNS; run++)
  { 
    randombytes(seed, sizeof(uint8_t) * 32 * TIMINGS);
    seed_ptr = seed;

    for(size_t t=0; t<TIMINGS; t++)
    {
      timings[t] = gen_matrix(matrix, seed_ptr, 0);
      seed_ptr += 32;
    }

    cpucycles_sort(timings, TIMINGS);

    median  = stats_median(timings, TIMINGS);
    mean    = stats_mean(timings, TIMINGS);
    sd      = stats_sd(timings, TIMINGS);
    tr_mean = stats_trimmed_mean(timings, TIMINGS, 0.05);

    printf("%" PRIu64 ", %.2lf, %.2lf, %.2lf\n", median, mean, sd, tr_mean);
  }

  free(seed);
}

int main()
{
  bench_gen_matrix_setup1();
  return 0;
}
