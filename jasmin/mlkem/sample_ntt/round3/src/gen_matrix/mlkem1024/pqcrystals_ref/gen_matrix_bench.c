#define gen_matrix gen_matrix_internal

#include "gen_matrix.c"

#undef gen_matrix

static inline uint64_t cycles(void)
{
  uint64_t counter;
  __asm__ volatile ("rdtsc; shlq $32,%%rdx; orq %%rdx,%%rax" : "=a" (counter) : : "%rdx");
  return counter;
}

uint64_t gen_matrix(polyvec *a, const uint8_t seed[KYBER_SYMBYTES], int transposed)
{
  uint64_t begin, end;

  begin = cycles();
  gen_matrix_internal(a, seed, transposed);
  end = cycles();
  return end-begin;
}
