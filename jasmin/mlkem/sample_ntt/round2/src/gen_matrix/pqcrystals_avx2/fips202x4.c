#include <stddef.h>
#include <stdint.h>
#include <immintrin.h>
#include <string.h>
#include "fips202.h"
#include "fips202x4.h"

#include "keccakf1600_4x_xkcp.c"

#define KeccakF1600_StatePermute4x KeccakP1600times4_PermuteAll_24rounds

/* Use implementation from the Keccak Code Package */
/*void KeccakF1600_StatePermute4x(__m256i *s);*/

static void keccakx4_absorb_once(__m256i s[25],
                                 unsigned int r,
                                 const uint8_t *in0,
                                 const uint8_t *in1,
                                 const uint8_t *in2,
                                 const uint8_t *in3,
                                 size_t inlen,
                                 uint8_t p)
{
  size_t i;
  uint64_t pos = 0;
  __m256i t, idx;

  for(i = 0; i < 25; ++i)
    s[i] = _mm256_setzero_si256();

  idx = _mm256_set_epi64x((long long)in3, (long long)in2, (long long)in1, (long long)in0);
  while(inlen >= r) {
    for(i = 0; i < r/8; ++i) {
      t = _mm256_i64gather_epi64((long long *)pos, idx, 1);
      s[i] = _mm256_xor_si256(s[i], t);
      pos += 8;
    }
    inlen -= r;

    KeccakF1600_StatePermute4x(s);
  }

  for(i = 0; i < inlen/8; ++i) {
    t = _mm256_i64gather_epi64((long long *)pos, idx, 1);
    s[i] = _mm256_xor_si256(s[i], t);
    pos += 8;
  }
  inlen -= 8*i;

  if(inlen) {
    t = _mm256_i64gather_epi64((long long *)pos, idx, 1);
    idx = _mm256_set1_epi64x((1ULL << (8*inlen)) - 1);
    t = _mm256_and_si256(t, idx);
    s[i] = _mm256_xor_si256(s[i], t);
  }

  t = _mm256_set1_epi64x((uint64_t)p << 8*inlen);
  s[i] = _mm256_xor_si256(s[i], t);
  t = _mm256_set1_epi64x(1ULL << 63);
  s[r/8 - 1] = _mm256_xor_si256(s[r/8 - 1], t);
}

static void keccakx4_squeezeblocks(uint8_t *out0,
                                   uint8_t *out1,
                                   uint8_t *out2,
                                   uint8_t *out3,
                                   size_t nblocks,
                                   unsigned int r,
                                   __m256i s[25])
{
  unsigned int i;
  __m128d t;

  while(nblocks > 0) {
    KeccakF1600_StatePermute4x(s);
    for(i=0; i < r/8; ++i) {
      t = _mm_castsi128_pd(_mm256_castsi256_si128(s[i]));
      _mm_storel_pd((__attribute__((__may_alias__)) double *)&out0[8*i], t);
      _mm_storeh_pd((__attribute__((__may_alias__)) double *)&out1[8*i], t);
      t = _mm_castsi128_pd(_mm256_extracti128_si256(s[i],1));
      _mm_storel_pd((__attribute__((__may_alias__)) double *)&out2[8*i], t);
      _mm_storeh_pd((__attribute__((__may_alias__)) double *)&out3[8*i], t);
    }

    out0 += r;
    out1 += r;
    out2 += r;
    out3 += r;
    --nblocks;
  }
}

void shake128x4_absorb_once(keccakx4_state *state,
                            const uint8_t *in0,
                            const uint8_t *in1,
                            const uint8_t *in2,
                            const uint8_t *in3,
                            size_t inlen)
{
  keccakx4_absorb_once(state->s, SHAKE128_RATE, in0, in1, in2, in3, inlen, 0x1F);
}

void shake128x4_squeezeblocks(uint8_t *out0,
                              uint8_t *out1,
                              uint8_t *out2,
                              uint8_t *out3,
                              size_t nblocks,
                              keccakx4_state *state)
{
  keccakx4_squeezeblocks(out0, out1, out2, out3, nblocks, SHAKE128_RATE, state->s);
}
