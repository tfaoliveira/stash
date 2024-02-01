#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>

#include "common/checksum.c"
#include "common/randombytes.c" // not randombytes 
#include "common/print.c"

#ifndef KECCAKF1600_RANDOM_TESTS
#define KECCAKF1600_RANDOM_TESTS 100000
#endif

extern void keccakf1600(uint8_t state_ptr[25*8]);
extern void pack(uint64_t state_ptr[28]);
extern void unpack(uint64_t state_ptr[28]);

void print_u64_5x5(const uint64_t *ptr)
{
  size_t i;

  if(ptr == NULL) { return; }

  printf("{\n  ");
  for(i=0; i<24; i++)
  { printf("0x%016" PRIx64 ", ", ptr[i]);

    if((i+1)%5 == 0)
    { printf("\n  "); }

    if((i+1)%25 == 0)
    { printf("\n  "); }
  }

  printf("0x%016" PRIx64 "\n};\n", ptr[i]);
  return;
}

void print_u64_5x5_p_3(const uint64_t *ptr)
{
  size_t i;

  if(ptr == NULL) { return; }

  printf("{\n  ");
  for(i=0; i<24; i++)
  { printf("0x%016" PRIx64 ", ", ptr[i]);

    if((i+1)%5 == 0)
    { printf("\n  "); }

    if((i+1)%25 == 0)
    { printf("\n  "); }
  }

  printf("0x%016" PRIx64 "\n",     ptr[i]);
  printf("0x%016" PRIx64 ", ",     ptr[i+1]);
  printf("0x%016" PRIx64 ", ",     ptr[i+2]);
  printf("0x%016" PRIx64 "\n};\n", ptr[i+3]);
  return;
}

void test_keccakf1600_avx2_pack_unpack()
{
  uint64_t *state_ptr;

  state_ptr = malloc(sizeof(uint8_t) * (25+3) * 8);
  assert(state_ptr != NULL);

  for(uint64_t i=0; i<25; i++)
  { state_ptr[i] = i+1; }
  state_ptr[25] = -1;
  state_ptr[26] = -1;
  state_ptr[27] = -1;

  pack(state_ptr);
  print_u64_5x5_p_3((uint64_t*) state_ptr);

  unpack(state_ptr);
  print_u64_5x5_p_3((uint64_t*) state_ptr);

  free(state_ptr);
}


void test_keccakf1600_00000()
{
  uint8_t *state_ptr;

  state_ptr = aligned_alloc(16, sizeof(uint8_t) * 25 * 8);
  assert(state_ptr != NULL);

  memset(state_ptr, 0, sizeof(uint8_t) * 25 * 8);

  keccakf1600(state_ptr);

  print_u64_5x5((uint64_t*) state_ptr);

  free(state_ptr);
}

void test_keccakf1600_01234()
{
  uint8_t *state_ptr;

  state_ptr = aligned_alloc(16, sizeof(uint8_t) * 25 * 8);
  assert(state_ptr != NULL);

  for(uint64_t i=0; i<25; i++)
  { ((uint64_t*)state_ptr)[i] = i; } 

  keccakf1600(state_ptr);

  print_u64_5x5((uint64_t*) state_ptr);

  free(state_ptr);
}

void test_keccakf1600_checksum()
{
  uint8_t checksum_state[64];
  uint8_t *state_ptr;

  state_ptr = aligned_alloc(16, sizeof(uint8_t) * 25 * 8);
  assert(state_ptr != NULL);

  memset(checksum_state, 0, 64);

  for(size_t t=0; t < KECCAKF1600_RANDOM_TESTS; t++)
  {
    randombytes(state_ptr, sizeof(uint8_t) * 25 * 8);

    keccakf1600(state_ptr);

    checksum(checksum_state, state_ptr, sizeof(uint8_t) * 25 * 8);
  }

  print_u8c(checksum_state, 64);

  free(state_ptr);
}


int main(void)
{
  //test_keccakf1600_00000();
  test_keccakf1600_01234();
  //test_keccakf1600_checksum();
  //test_keccakf1600_avx2_pack_unpack();
  return 0;
}
