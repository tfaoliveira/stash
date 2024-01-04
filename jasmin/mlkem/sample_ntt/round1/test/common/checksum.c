// adapted from SUPERCOP

#include <stdint.h>

#define FOR(i,n) for (i = 0;i < n;++i)

static uint32_t L32(uint32_t x, int c) { return (x << c) | ((x&0xffffffff) >> (32 - c)); }

static uint32_t ld32(const uint8_t *x)
{
  uint32_t u = x[3];
  u = (u<<8)|x[2];
  u = (u<<8)|x[1];
  return (u<<8)|x[0];
}

static void st32(uint8_t *x, uint32_t u)
{
  int i;
  FOR(i,4) { x[i] = u; u >>= 8; }
}

static const uint8_t sigma_checksum[17] = "expand 32-byte k";

static void core(uint8_t *out, const uint8_t *in, const uint8_t *k)
{
  uint32_t w[16], x[16], y[16], t[4];
  int i, j, m;

  FOR(i,4) {
    x[5*i] = ld32(sigma_checksum+4*i);
    x[1+i] = ld32(k+4*i);
    x[6+i] = ld32(in+4*i);
    x[11+i] = ld32(k+16+4*i);
  }

  FOR(i,16) y[i] = x[i];

  FOR(i,20) {
    FOR(j,4) {
      FOR(m,4) t[m] = x[(5*j+4*m)%16];
      t[1] ^= L32(t[0]+t[3], 7);
      t[2] ^= L32(t[1]+t[0], 9);
      t[3] ^= L32(t[2]+t[1],13);
      t[0] ^= L32(t[3]+t[2],18);
      FOR(m,4) w[4*j+(j+m)%4] = t[m];
    }
    FOR(m,16) x[m] = w[m];
  }

  FOR(i,16) st32(out + 4 * i,x[i] + y[i]);
}

// /////////////////////////////////////////////////////////////////////////////

void checksum(uint8_t *checksum_state, uint8_t *x, uint64_t xlen)
{
  uint8_t block[16];
  uint64_t i;

  while (xlen >= 16)
  { core(checksum_state, x, checksum_state);
    x += 16;
    xlen -= 16;
  }
  FOR(i,16) block[i] = 0;
  FOR(i,xlen) block[i] = x[i];
  block[xlen] = 1;
  checksum_state[0] ^= 1;
  core(checksum_state,block,checksum_state);
}


