#include "KeccakP-1600-times4-SIMD256.c"

void keccakf1600_4x(uint8_t state_ptr[25*8*4])
{
  KeccakP1600times4_PermuteAll_24rounds(state_ptr);
}

