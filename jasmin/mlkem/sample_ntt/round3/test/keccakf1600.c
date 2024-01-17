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
  test_keccakf1600_checksum();
  return 0;
}
