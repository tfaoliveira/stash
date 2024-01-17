// adapted from an internal project yet to be released

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <gsl/gsl_statistics_ulong.h>

static inline uint64_t cpucycles_counter(void)
{
  uint64_t counter;
  __asm__ volatile ("rdtsc; shlq $32,%%rdx; orq %%rdx,%%rax" : "=a" (counter) : : "%rdx");
  return counter;
}

static inline uint64_t cpucycles_begin(void)
{
  return cpucycles_counter();
}

static inline uint64_t cpucycles_end(uint64_t begin)
{
  return (cpucycles_counter() - begin);
}

static inline int cpucycles_compare(const void *a, const void *b)
{
  if(*(uint64_t *)a < *(uint64_t *)b){ return -1; }
  if(*(uint64_t *)a > *(uint64_t *)b){ return  1; }
  return 0;
}

static inline void cpucycles_sort(uint64_t *data, size_t length)
{
  qsort(data, length, sizeof(uint64_t), cpucycles_compare);
}

// 

static uint64_t stats_median(uint64_t *data, size_t length)
{
  uint64_t median;
  size_t base_index;

  base_index = length >> 1;

  if((length & 1) == 1) // odd
  { median = data[base_index]; }
  else // even
  { median = (data[base_index - 1] + data[base_index]) >> 1; }

  return median;
}

static double stats_mean(uint64_t *data, size_t length)
{
  double mean;

  mean = gsl_stats_ulong_mean(data, 1, length);
  if(isnan(mean) != 0)
  { mean = gsl_stats_ulong_mean(data, 1, length); }

  return mean;
}

static double stats_sd(uint64_t *data, size_t length)
{
  double sd;
  sd = gsl_stats_ulong_sd(data, 1, length);
  if(isnan(sd) != 0)
  { sd = gsl_stats_ulong_sd(data, 1, length); }

  return sd;
}

static double stats_trimmed_mean(uint64_t *data, size_t length, double cut_percentage)
{
  double trimmed_mean;
  trimmed_mean = gsl_stats_ulong_trmean_from_sorted_data(cut_percentage, data, 1, length);
  if(isnan(trimmed_mean) != 0)
  { trimmed_mean = gsl_stats_ulong_trmean_from_sorted_data(cut_percentage, data, 1, length); }

  return trimmed_mean;
}

//

