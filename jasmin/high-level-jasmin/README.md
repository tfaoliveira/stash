# High-level Jasmin, some notes, 20231107, Formosa retreat Bochum

## Curve25519

* Idea: what if we could implement the montgomery ladder using a `fold`? Would it simplify proofs?
* The following link contains a Curve25519 specification in EasyCrypt where a `fold` is used:
  * https://github.com/tfaoliveira/libjc/blob/x25519/proof/crypto_scalarmult/curve25519/Curve25519_Spec.ec
* Goal: being able to deal with the proof quickly:
  * Formally verified version of `fold` is provided by a Jasmin stdlib (some information down bellow);
  * Function given to `fold`, in this particular instance, can be proven correct with CryptoLine;
  * Note: it seems to be the case that even in the case where the EC specification is imperative (`while` instead of `fold`), using `fold` in Jasmin might be advantageous (assuming that there are EC theories that enable the developers to quickly relate the Jasmin `fold` to EC `whiles`).

## Sphincs+

### Templates

* Problem: in Jasmin, array lengths must be known during compiling time
* Consequences: Implies having different functions for different files; difficult to develop/maintain
* Solution: templates (in fact, a possible solution from the set viable solutions; another one, for the long term, would be to have support for unknown array lengths in internal functions)
* `Jasmin preprocessor`: [https://github.com/ruipedro16/jasmin-preprocessor/](https://github.com/ruipedro16/jasmin-preprocessor/)
* Simple example: `thash` from Sphincs+
  * https://github.com/tfaoliveira/sphincsplus-jasmin/blob/ref-jasmin/ref/thash_shake_robust.c
  * https://github.com/tfaoliveira/sphincsplus-jasmin/blob/ref-jasmin/ref-jasmin/thash/thash_shake_robust.jtmpl

### Functions as arguments and abstract inline structs
* What about functions as parameters and abstract types/abstract structs?
* Example: `treehashx1` from Sphincs+
* Solution: 
  * Step 1: allow for **inline** (first step) **functions** to be passed **as arguments** -- if they comply with the expected API (necessary but not sufficient, see next)
  * Step 2: support **inline structs** -- similar to typedef struct from C, but fields would be expanded (note to self: I still need to write notes about this and push them to the Jasmin TODO list -- result from Sophia-202310);
  * Step 3: allow for **abstract inline structs**

* Previous solution allows to implement the following function in a very clean way (simplifies proof and reduces development/maintenance effort)
  * https://github.com/tfaoliveira/sphincsplus-jasmin/blob/ref-jasmin/ref/utilsx1.c#L23

### Jasmin preprocessor approach 

* Motivated by Sphincs+ 
* Many other applications
* Prototyping new features: https://github.com/ruipedro16/jasmin-preprocessor/
* Goal: have native support in the Jasmin compiler


## Dilithium-Arm

* The same pattern is used frequently: what about replacing `while` with `map`?
  * [reduce32](https://github.com/PQClean/PQClean/blob/d3f62d23f651cc87810bac71ab5197a160f6b494/crypto_sign/dilithium3/clean/reduce.c#L33)
  * [poly_reduce](https://github.com/PQClean/PQClean/blob/d3f62d23f651cc87810bac71ab5197a160f6b494/crypto_sign/dilithium3/clean/poly.c#L20C6-L20C42)

* The previous code can be implemented as follows in (high-level) Jasmin -- requires [jasmin-preprocessor](https://github.com/ruipedro16/jasmin-preprocessor/):

```
inline fn __reduce32_8380417(reg u32 a) -> reg u32
{
  reg u32 t t_x511 t_x523265 t_x4286586879 res;

  t = a + (1 << 22); // 1<<22 == 4194304
  t = t >>s 23; // we have that: t = (a + (1 << 22)) >> 23;

  t_x511 = #RSB(t, (t << 9)); // t * 2**9 - t
  t_x523265 = t + (t_x511 << 10);
  t_x4286586879 = #RSB(t, (t_x523265 << 13)); // ((t * 523265) * 2**13) - t
  
  // we have that: t_x4286586879 == t * -Q 

  res = a + t_x4286586879;

  res = res;
  return res;
}

inline fn __poly_reduce(reg ptr u32[N] a) -> reg ptr u32[N]
{
  a = __map1<N,1>[__reduce32_8380417;u32](a);
  return a;
}
```

* Where `__map1` is defined as follows:

```
inline fn __map1<N, ITER>[F;A](reg ptr A[N] a) -> reg ptr A[N]
{
  reg u32 i; // ideally: reg size i; // similar to size_t
  inline int j;
  reg A elem;

  i = 0;
  while(i < (N / ITER) * ITER)
  {
    for j=0 to ITER
    {
      elem = a[(int) i];
      elem = F(elem);
      a[(int) i] = elem;
      i += 1;
    }
  }

  for j=0 to (N % ITER)
  {
    elem = a[(int) i];
    elem = F(elem);
    a[(int) i] = elem;
    i += 1;
  }

  return a;
}//<>

```

## Formosa Demos - Proof of Concept - The EasyCrypt side of things

* W.r.t. map and the interaction with EasyCrypt, there is a proof of concept in the following link:
  * https://github.com/formosa-crypto/formosa-demos/tree/main/high-level-jasmin/maps


## Jasmin Standard Library for high-level constructions (but not only):

* Jasmin library (jstdlib?) that provides generic functions **(map, fold, filter, ...)** with EC proofs
* Goal: speed up development and correctness proofs
* Generic **conditions library**:
  * https://github.com/tfaoliveira/sphincsplus-jasmin/blob/ref-jasmin/ref-jasmin/generic/conditions.jinc
  * Example:
```
// cond = a < b && a < c
inline fn __cond_u64_a_below_b_and_a_below_c(reg u64 a b c) -> reg bool
{
  reg bool c1 c2 c3;
  reg u8 bc1 bc2;

  ?{ "<u" = c1 } = #CMP_64(a, b);
  // if(c1) <=> if(a <u b)
  bc1 = #SETcc(c1);

  ?{ "<u" = c2 } = #CMP_64(a, c);
  // if(c2) <=> if(a <u c)
  bc2 = #SETcc(c2);

  // zf == 1 => bc1 & bc2 == 0 => cond = false
  // zf == 0 => bc1 & bc2 == 1 => cond = true
  ?{ "!=" = c3 } = #TEST_8(bc1, bc2); 

  return c3;
}
```

## Polymorphism
* The previous example, `__cond_u64_a_below_b_and_a_below_c(reg u64 a b c)`, is a nice motivation for polymorphism in Jasmin:
  * Currently we need to implement the same function for `u64`, `u32`, `u16`, and `u8`
  * Even though the code is essentially the same
  * `inline fn __cond_u64_a_below_b_and_a_below_c<type>(reg type a b c) -> reg bool` ? 

