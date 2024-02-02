#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>

#include "common/checksum.c"
#include "common/randombytes.c" // not randombytes 
#include "common/print.c"

#ifndef GEN_MATRIX_RANDOM_TESTS
#define GEN_MATRIX_RANDOM_TESTS 1000
#endif

#ifndef GEN_MATRIX_SIZE
#define GEN_MATRIX_SIZE 2304
#endif

extern void gen_matrix(uint16_t matrix_ptr[GEN_MATRIX_SIZE], uint8_t seed_ptr[32], uint64_t transposed);

void test_gen_matrix_simple(void)
{
  uint16_t *matrix_ptr;
  uint8_t *seed_ptr;

  matrix_ptr = calloc(sizeof(uint16_t), GEN_MATRIX_SIZE);
  assert(matrix_ptr != NULL);

  seed_ptr = calloc(sizeof(uint8_t), 32);
  assert(seed_ptr != NULL);

  randombytes(seed_ptr, 32);
  print_u8c(seed_ptr, 32);

  gen_matrix(matrix_ptr, seed_ptr, 0);

  print_u16(matrix_ptr, GEN_MATRIX_SIZE);

  free(matrix_ptr);
  free(seed_ptr);
}

void test_gen_matrix_seed1()
{
  // note: enters scalar code for (1,1)
  uint8_t seed[] =
  {
    0x03, 0x4e, 0x9e, 0x83, 0xe5, 0x8a, 0x01, 0x3a, 
    0xf0, 0xe7, 0x35, 0x2f, 0xb7, 0x90, 0x85, 0x14, 
    0xe3, 0xb3, 0xd1, 0x04, 0x0d, 0x0b, 0xb9, 0x63, 
    0xb3, 0x95, 0x4b, 0x63, 0x6b, 0x5f, 0xd4, 0xbf
  };

  uint16_t *matrix_ptr;

  matrix_ptr = calloc(sizeof(uint16_t), GEN_MATRIX_SIZE);
  assert(matrix_ptr != NULL);

  gen_matrix(matrix_ptr, seed, 0);

  print_u16(matrix_ptr, GEN_MATRIX_SIZE);

  free(matrix_ptr);
}

void test_gen_matrix_checksum()
{
  uint8_t checksum_state[64];
  uint16_t *matrix_ptr;
  uint8_t *seed_ptr;

  matrix_ptr = calloc(sizeof(uint16_t), GEN_MATRIX_SIZE);
  assert(matrix_ptr != NULL);

  seed_ptr = calloc(sizeof(uint8_t), 32);
  assert(seed_ptr != NULL);

  memset(checksum_state, 0, 64);

  for(uint64_t transposed=0; transposed<=1; transposed++)
  {
    for(size_t t=0; t < GEN_MATRIX_RANDOM_TESTS; t++)
    {
      randombytes(seed_ptr, sizeof(uint8_t)*32);
      memset(matrix_ptr, 0, sizeof(uint16_t)*GEN_MATRIX_SIZE);

      gen_matrix(matrix_ptr, seed_ptr, transposed);

      checksum(checksum_state, (uint8_t*) matrix_ptr, sizeof(uint16_t)*GEN_MATRIX_SIZE);

        //print_u8(seed_ptr, 32);
        //print_u8c(checksum_state, 64);
    }
  }

  print_u8c(checksum_state, 64);

  free(matrix_ptr);
  free(seed_ptr);
}


int main(void)
{
//  test_gen_matrix_simple();
//  test_gen_matrix_seed1();
  test_gen_matrix_checksum();
  return 0;
}
