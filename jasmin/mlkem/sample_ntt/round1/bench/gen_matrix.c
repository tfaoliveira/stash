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

extern void gen_matrix(uint16_t matrix_ptr[2304], uint8_t seed_ptr[32], uint64_t transposed);

void bench_gen_matrix_setup1(void)
{
  uint64_t timings[TIMINGS];
  uint64_t start;
  uint64_t median;
  double mean, sd, tr_mean;

  uint8_t *seed;
  uint8_t *seed_ptr;
  uint16_t *matrix;

  seed = aligned_alloc(16, sizeof(uint8_t) * 32 * TIMINGS);
  assert(seed != NULL);

  matrix = aligned_alloc(16, sizeof(uint16_t) * 2304);
  assert(matrix != NULL);

  for(size_t run=0; run<RUNS; run++)
  { 
    randombytes(seed, sizeof(uint8_t) * 32 * TIMINGS);
    seed_ptr = seed;

    for(size_t t=0; t<TIMINGS; t++)
    {
      start = cpucycles_begin();

      gen_matrix(matrix, seed_ptr, 0);

      timings[t] = cpucycles_end(start);    

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
