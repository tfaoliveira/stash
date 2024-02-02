#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>

#include "common/checksum.c"
#include "common/randombytes.c" // not randombytes 
#include "common/print.c"

#ifndef KECCAKF1600_4X_RANDOM_TESTS
#define KECCAKF1600_4X_RANDOM_TESTS 100000
#endif

extern int keccakf1600_4x(uint8_t state_ptr[25*8*4]);
extern int pack_4x(uint8_t state_ptr[25*8*4]);
extern int unpack_4x(uint8_t state_ptr[25*8*4]);

void print_st4x(const uint64_t *ptr) {
  size_t i;

  if(ptr == NULL) { return; }

  printf("{\n");
  for(i=0; i<25; i++) {
    printf("0x%016" PRIx64 " 0x%016" PRIx64 " 0x%016" PRIx64 " 0x%016" PRIx64 "\n"
	   , ptr[i*4+0], ptr[i*4+1], ptr[i*4+2], ptr[i*4+3]);
  }
  printf("}\n");
}

#if 0
void test_keccakf1600_4x_pack_unpack()
{
  int i, j;
  uint64_t *state_ptr;

  posix_memalign((void**)&state_ptr, 16, sizeof(uint8_t) * 25 * 8 * 4);
  assert(state_ptr != NULL);

  for (j=0; j<4; j++)
    for (i=0; i<25; i++) {
      state_ptr[25*j+i] = 256*256*(j+1) + i;
    }
  print_st4x(state_ptr);
  pack_4x((uint8_t*)state_ptr);
  print_st4x(state_ptr);
  unpack_4x((uint8_t*)state_ptr);
  print_st4x(state_ptr);
  pack_4x((uint8_t*)state_ptr);
  print_st4x(state_ptr);

  free(state_ptr);
}
#endif

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

void test_keccakf1600_00000()
{
  uint8_t *state_ptr;

  posix_memalign((void**)&state_ptr, 16, sizeof(uint8_t) * 25 * 8);
  assert(state_ptr != NULL);

  memset(state_ptr, 0, sizeof(uint8_t) * 25 * 8);

  keccakf1600_4x(state_ptr);

  print_u64_5x5((uint64_t*) state_ptr);

  free(state_ptr);
}

void test_keccakf1600_4x_checksum()
{
  uint8_t checksum_state[64];
  uint8_t *state_ptr;
  int b;

  posix_memalign((void**)&state_ptr, 16, sizeof(uint8_t) * 25 * 8);
  assert(state_ptr != NULL);

  memset(checksum_state, 0, 64);

  for(size_t t=0; t < KECCAKF1600_4X_RANDOM_TESTS; t++)
  {
    randombytes(state_ptr, sizeof(uint8_t) * 25 * 8);

    b = keccakf1600_4x(state_ptr);

    if (1 || b)
      checksum(checksum_state, state_ptr, sizeof(uint8_t) * 25 * 8);
  }

  print_u8c(checksum_state, 64);

  free(state_ptr);
}


int main(void)
{
  test_keccakf1600_4x_checksum();
//  test_keccakf1600_00000();
//  test_keccakf1600_4x_pack_unpack();
  return 0;
}
