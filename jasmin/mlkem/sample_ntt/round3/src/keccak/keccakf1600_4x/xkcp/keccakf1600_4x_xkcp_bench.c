#include "KeccakP-1600-times4-SIMD256.c"

static inline uint64_t cycles(void)
{
  uint64_t counter;
  __asm__ volatile ("rdtsc; shlq $32,%%rdx; orq %%rdx,%%rax" : "=a" (counter) : : "%rdx");
  return counter;
}

uint64_t keccakf1600_4x(uint8_t state_ptr[25*8*4])
{
  uint64_t begin, end;

  begin = cycles();
  KeccakP1600times4_PermuteAll_24rounds(state_ptr);
  end = cycles();
  return end-begin;
}

