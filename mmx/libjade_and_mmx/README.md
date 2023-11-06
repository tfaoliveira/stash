# Overview

TODO: write an overview for this experiment.

Notes:
* kyber768 reference: generally faster, (-0.95% overhead to -1.72%), just pointer spilling
* scalarmult: slower, replaces stack by xmm in a couple of functions (only uses 4 mm registers)
* sha256/sha512/chacha20: pointer spilling, no practical difference 
* shake*: roughly the same (keccak)

# Results

## Machine info

Intel(R) Core(TM) i7-10700K CPU @ 3.80GHz

Linux debian 5.10.0-21-amd64 #1 SMP Debian 5.10.162-1 x86_64 GNU/Linux

gcc version 10.2.1 20210110 (Debian 10.2.1-6)
-Wall -Wno-unused-function -march=native -O3 -fomit-frame-pointer -fwrapv -fPIC -fPIE

## Kem and Scalarmult 
| Implementation | Cycles Baseline / Cycles MMX | Difference | Overhead | Stdev Baseline / Stdev MMX |
|----------------|------------------------------|------------|----------|----------------------------|
| jade_kem_kyber_kyber768_amd64_ref_enc_derand     | 349554 / 346200 | 3354  | -0,96 %| 54,00 / 73,00 |
| jade_kem_kyber_kyber768_amd64_ref_keypair_derand | 298561 / 293420 | 5141  | -1,72 %| 28,00 / 15,00 |
| jade_kem_kyber_kyber768_amd64_ref_keypair        | 298880 / 293804 | 5076  | -1,70 %| 41,00 / 13,00 |
| jade_kem_kyber_kyber768_amd64_ref_enc            | 349755 / 346447 | 3308  | -0,95 %| 85,00 / 40,00 |
| jade_kem_kyber_kyber768_amd64_ref_dec            | 438874 / 432959 | 5915  | -1,35 %| 61,00 / 54,00 |
| jade_scalarmult_curve25519_amd64_mulx_base       | 98268 / 100306  | -2038 | 2,07 % | 29,00 / 39,00 |
| jade_scalarmult_curve25519_amd64_mulx            | 98336 / 100340  | -2004 | 2,04 % | 18,00 / 42,00 |



## Hash, Stream, Onetimeauth, and Secretbox
### Input length: 16384
| Implementation | Cycles Baseline / Cycles MMX | Difference | Overhead | Stdev Baseline / Stdev MMX |
|----------------|------------------------------|------------|----------|----------------------------|
| jade_hash_sha256_amd64_ref                | 274080 / 274948 | -868 | 0,32 % | 37,00 / 103,00 |
| jade_hash_sha512_amd64_ref                | 176984 / 176962 | 22   | -0,01 %| 19,00 / 15,00  |
| jade_stream_chacha_chacha20_amd64_ref_xor | 95272 / 95273   | -1   | 0,00 % | 1,00 / 1,00    |
| jade_stream_chacha_chacha20_amd64_ref     | 94740 / 94733   | 7    | -0,01 %| 3,00 / 3,00    |



## Xof 
### Output length: 32
### Input length: 16384
| Implementation | Cycles Baseline / Cycles MMX | Difference | Overhead | Stdev Baseline / Stdev MMX |
|----------------|------------------------------|------------|----------|----------------------------|
| jade_xof_shake128_amd64_ref1 | 148891 / 148246 | 645   | -0,43 %| 6,00 / 7,00    |
| jade_xof_shake128_amd64_ref  | 148681 / 146649 | 2032  | -1,37 %| 27,00 / 5,00   |
| jade_xof_shake128_amd64_bmi1 | 123841 / 123241 | 600   | -0,48 %| 87,00 / 56,00  |
| jade_xof_shake256_amd64_ref1 | 182232 / 182422 | -190  | 0,10 % | 25,00 / 34,00  |
| jade_xof_shake256_amd64_ref  | 180888 / 180236 | 652   | -0,36 %| 126,00 / 14,00 |
| jade_xof_shake256_amd64_bmi1 | 152151 / 153570 | -1419 | 0,93 % | 116,00 / 2,00  |

