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

extern void keccakf1600_4x(uint8_t state_ptr[25*8*4]);

void bench_keccakf1600_4x_setup1(void)
{
  uint64_t timings[TIMINGS];
  uint64_t start;
  uint64_t median;
  double mean, sd, tr_mean;

  uint8_t *state_ptr;

  state_ptr = aligned_alloc(16, sizeof(uint8_t) * 25 * 8 * 4);
  assert(state_ptr != NULL);

  for(size_t run=0; run<RUNS; run++)
  { 
    randombytes(state_ptr, sizeof(uint8_t) * 25 * 8 * 4);

    for(size_t t=0; t<TIMINGS; t++)
    {
      start = cpucycles_begin();

      keccakf1600_4x(state_ptr);

      timings[t] = cpucycles_end(start);    
    }

    cpucycles_sort(timings, TIMINGS);

    median  = stats_median(timings, TIMINGS);
    mean    = stats_mean(timings, TIMINGS);
    sd      = stats_sd(timings, TIMINGS);
    tr_mean = stats_trimmed_mean(timings, TIMINGS, 0.05);

    printf("%" PRIu64 ", %.2lf, %.2lf, %.2lf\n", median, mean, sd, tr_mean);
  }

  free(state_ptr);
}

int main()
{
  bench_keccakf1600_4x_setup1();
  return 0;
}
