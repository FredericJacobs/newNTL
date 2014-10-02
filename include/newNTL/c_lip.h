

typedef long * _newntl_verylong;

#if (defined(newNTL_SINGLE_MUL))

#if (defined(newNTL_AVOID_FLOAT) || defined(newNTL_LONG_LONG))
#error "at most one of newNTL_SINGLE_MUL newNTL_AVOID_FLOAT newNTL_LONG_LONG allowed"
#endif

#elif (defined(newNTL_AVOID_FLOAT) && defined(newNTL_LONG_LONG))
#error "at most one of newNTL_SINGLE_MUL newNTL_AVOID_FLOAT newNTL_LONG_LONG allowed"
#endif

#if (defined(newNTL_SINGLE_MUL))

#if (!newNTL_SINGLE_MUL_OK)
#error "newNTL_SINGLE_MUL not supported on this platform"
#endif

#if (defined(newNTL_CLEAN_INT))
#error "newNTL_SINGLE_MUL not allowed with newNTL_CLEAN_INT"
#endif


#define newNTL_NBITS (26)

#else

#define newNTL_NBITS newNTL_NBITS_MAX

#endif


#define newNTL_RADIX           (1L<<newNTL_NBITS)
#define newNTL_NBITSH          (newNTL_NBITS>>1)
#define newNTL_RADIXM          (newNTL_RADIX-1)
#define newNTL_RADIXROOT       (1L<<newNTL_NBITSH)
#define newNTL_RADIXROOTM      (newNTL_RADIXROOT-1)

#define newNTL_FRADIX ((double) newNTL_RADIX)
#define newNTL_FRADIX_INV  (((double) 1.0)/((double) newNTL_RADIX))



#define newNTL_ZZ_NBITS newNTL_NBITS
#define newNTL_ZZ_FRADIX ((double) (1L << newNTL_NBITS))

#define newNTL_SP_NBITS newNTL_NBITS
#define newNTL_SP_BOUND (1L << newNTL_SP_NBITS)
#define newNTL_SP_FBOUND ((double) newNTL_SP_BOUND)

#define newNTL_WSP_NBITS newNTL_ZZ_NBITS
#define newNTL_WSP_BOUND (1L << newNTL_WSP_NBITS)



#if (defined(newNTL_SINGLE_MUL) && !newNTL_SINGLE_MUL_OK)
#undef newNTL_SINGLE_MUL
#endif

#if (defined(newNTL_SINGLE_MUL))


/****************************************************************

The following macros extract the two words of a double,
getting around the type system.
This is only used in the newNTL_SINGLE_MUL strategy.

*****************************************************************/

#if (newNTL_DOUBLES_LOW_HIGH)
#define newNTL_LO_WD 0
#define newNTL_HI_WD 1
#else
#define newNTL_LO_WD 1
#define newNTL_HI_WD 0
#endif


typedef union { double d; unsigned long rep[2]; } _newntl_d_or_rep;

#define newNTL_FetchHiLo(hi,lo,x) \
do { \
   _newntl_d_or_rep ll_xx; \
   ll_xx.d = (x); \
   hi = ll_xx.rep[newNTL_HI_WD]; \
   lo = ll_xx.rep[newNTL_LO_WD]; \
} while (0)


#define newNTL_FetchLo(lo,x)  \
do {  \
   _newntl_d_or_rep ll_xx;  \
   ll_xx.d = x;  \
   lo = ll_xx.rep[newNTL_LO_WD];  \
} while (0) 

#endif


/**********************************************************************

   A multiprecision integer is represented as a pointer to long.
   Let x be such a pointer.
   x = 0 represents 0.
   Otherwise, let n = abs(x[0]) and s = sign(x[0]);
   the integer represented is then:

      s*(x[1] + x[2]*newNTL_RADIX + ... + x[n]*newNTL_RADIX^{n-1}),

   where x[n] != 0, unless n = s = 1.
   Notice that the number zero can be represented in precisely 2 ways,
   either as a null pointer, or as x[0] = 1 and x[1] = 0.

   Storage is generally managed via _newntl_zsetlength and _newntl_zfree.
   x[-1] = (k << 1) | b, where k is the maximum value of n allocated,
   and b is a bit that is set is the space is managed by some
   mechanism other than _newntl_zsetlength and _newntl_zfree.

************************************************************************/



#if (defined(__cplusplus) && !defined(newNTL_CXX_ONLY))
extern "C" {
#endif


/***********************************************************************

   Basic Functions

***********************************************************************/
    


    void _newntl_zsadd(_newntl_verylong a, long d, _newntl_verylong *b);
       /* *b = a + d */

    void _newntl_zadd(_newntl_verylong a, _newntl_verylong b, _newntl_verylong *c);
       /*  *c = a + b */

    void _newntl_zsub(_newntl_verylong a, _newntl_verylong b, _newntl_verylong *c);
       /* *c = a - b */

    void _newntl_zsubpos(_newntl_verylong a, _newntl_verylong b, _newntl_verylong *c);
       /* *c = a - b; assumes a >= b >= 0 */

    void _newntl_zsmul(_newntl_verylong a, long d, _newntl_verylong *b);
       /* *b = d * a */

    void _newntl_zmul(_newntl_verylong a, _newntl_verylong b, _newntl_verylong *c);
       /* *c = a * b */

    void _newntl_zsq(_newntl_verylong a, _newntl_verylong *c);
       /* *c = a * a */

    long _newntl_zsdiv(_newntl_verylong a, long b, _newntl_verylong *q);
       /* (*q) = floor(a/b) and a - floor(a/b)*(*q) is returned;
          error is raised if b == 0;
          if b does not divide a, then sign(*q) == sign(b) */

    void _newntl_zdiv(_newntl_verylong a, _newntl_verylong b, _newntl_verylong *q, _newntl_verylong *r);
       /* (*q) = floor(a/b) and (*r) = a - floor(a/b)*(*q);
          error is raised if b == 0;
          if b does not divide a, then sign(*q) == sign(b) */

    void _newntl_zmultirem(_newntl_verylong a, long n, long* dd, long* rr);
    void _newntl_zmultirem2(_newntl_verylong a, long n, long* dd, double **tbl, long* rr);
       /* rr[i] = a % dd[i], i = 0..n-1;
          assumes a >= 0, 0 < dd[i] < newNTL_RADIX
          _newntl_zmultirem2 takes an extra argument, tbl, which contains
          pre-computed residues of powers of RADIX */
    void _newntl_zmultirem3(_newntl_verylong a, long n, long* dd, long **tbl, long* rr);
       /* same as above, but tbl has different type */

    long _newntl_zsfastrem(_newntl_verylong a, long d);
       /* return a % d;
          assumes a >= 0, 0 < d < newNTL_RADIX */
        

    void _newntl_zmod(_newntl_verylong a, _newntl_verylong b, _newntl_verylong *r);
       /* same as _newntl_zdiv, but only remainder is computed */

    long _newntl_zsmod(_newntl_verylong a, long d);
       /* same as _newntl_zsdiv, but only remainder is computed */

    void _newntl_zquickmod(_newntl_verylong *r, _newntl_verylong b);
       /* *r = *r % b;
	  assumes b > 0 and *r >= 0;
	  The division is performed in place (but may sometimes
          cause *r to grow by one digit) */

    void _newntl_zsaddmul(_newntl_verylong x, long y,  _newntl_verylong *ww);
      /* *ww += x*y */

    void _newntl_zaddmul(_newntl_verylong x, _newntl_verylong y,  _newntl_verylong *ww);
      /* *ww += x*y */

    void _newntl_zssubmul(_newntl_verylong x, long y,  _newntl_verylong *ww);
      /* *ww -= x*y */

    void _newntl_zsubmul(_newntl_verylong x, _newntl_verylong y,  _newntl_verylong *ww);
      /* *ww -= x*y */


/********************************************************************

   Shifting and bit manipulation

*********************************************************************/

    void _newntl_z2mul(_newntl_verylong n, _newntl_verylong *a);
       /* *a = 2 * n */

    long _newntl_z2div(_newntl_verylong n, _newntl_verylong *a);
       /* *a = sign(n) * (|n|/2) */ 

    void _newntl_zlshift(_newntl_verylong n, long k, _newntl_verylong *a);
       /* *a = sign(n) * (|n| << k);
          shift is in reverse direction for negative k */

    void _newntl_zrshift(_newntl_verylong n, long k, _newntl_verylong *a);
       /* *a = sign(n) * (|n| >> k);
          shift is in reverse direction for negative k */
    
    long _newntl_zmakeodd(_newntl_verylong *n);
       /*
          if (n != 0)
              *n = m;
              return (k such that n == 2 ^ k * m with m odd);
          else
              return (0); 
        */

    long _newntl_znumtwos(_newntl_verylong n);
        /* return largest e such that 2^e divides n, or zero if n is zero */



    long _newntl_zodd(_newntl_verylong a);
       /* returns 1 if n is odd and 0 if it is even */

    long _newntl_zbit(_newntl_verylong a, long p);
       /* returns p-th bit of a, where the low order bit is indexed by 0;
          p out of range returns 0 */

    long _newntl_zsetbit(_newntl_verylong *a, long p);
       /* returns original value of p-th bit of |a|, and replaces
          p-th bit of a by 1 if it was zero;
          error if p < 0 */

    long _newntl_zswitchbit(_newntl_verylong *a, long p);
       /* returns original value of p-th bit of |a|, and switches
          the value of p-th bit of a;
          p starts counting at 0;
          error if p < 0 */


     void _newntl_zlowbits(_newntl_verylong a, long k, _newntl_verylong *b);
        /* places k low order bits of |a| in b */ 

     long _newntl_zslowbits(_newntl_verylong a, long k);
        /* returns k low order bits of |a| */

    long _newntl_zweights(long a);
        /* returns Hamming weight of |a| */

    long _newntl_zweight(_newntl_verylong a);
        /* returns Hamming weight of |a| */

    void _newntl_zand(_newntl_verylong a, _newntl_verylong b, _newntl_verylong *c);
        /* c gets bit pattern `bits of |a|` and `bits of |b|` */

    void _newntl_zor(_newntl_verylong a, _newntl_verylong b, _newntl_verylong *c);
        /* c gets bit pattern `bits of |a|` inclusive or `bits of |b|` */

    void _newntl_zxor(_newntl_verylong a, _newntl_verylong b, _newntl_verylong *c);
        /* c gets bit pattern `bits of |a|` exclusive or `bits of |b|` */




/************************************************************************

   Comparison

*************************************************************************/

    long _newntl_zcompare(_newntl_verylong a, _newntl_verylong b);
       /*
          if (a > b)
              return (1);
          if (a == b)
              return (0);
          if (a < b)
              return (-1);
         */

    long _newntl_zscompare(_newntl_verylong a, long b);
       /* single-precision version of the above */

    long _newntl_ziszero (_newntl_verylong a);
       /* test for 0 */


    long _newntl_zsign(_newntl_verylong a);
       /* 
          if (a > 0)
              return (1);
          if (a == 0)
              return (0);
          if (a < 0)
              return (-1);
        */

    void _newntl_zabs(_newntl_verylong *a);
       /* *a = |a| */

    void _newntl_znegate(_newntl_verylong *a);
       /* *a = -a */

    void _newntl_zcopy(_newntl_verylong a, _newntl_verylong *b);
       /* *b = a;  space is allocated  */

    void _newntl_zcopy1(_newntl_verylong a, _newntl_verylong *b);
       /* *b = a;  space not necessarily allocated  */

    void _newntl_zswap(_newntl_verylong *a, _newntl_verylong *b);
       /* swap a and b (by swaping pointers) */

    long _newntl_z2log(_newntl_verylong a);
       /* number of bits in |a|; returns 0 if a = 0 */

    long _newntl_z2logs(long a);
        /* single-precision version of the above */


/********************************************************************

   Conversion

*********************************************************************/
        
    void _newntl_zzero(_newntl_verylong *a);
       /* *a = 0;  space is allocated */

    void _newntl_zzero1(_newntl_verylong *a);
       /* *a = 0;  space not necessarily allocated */

    void _newntl_zone(_newntl_verylong *a);
       /* *a = 1 */

    void _newntl_zintoz(long d, _newntl_verylong *a);
       /* *a = d;  space is allocated  */

    void _newntl_zintoz1(long d, _newntl_verylong *a);
       /* *a = d;  space not necessarily allocated  */

    void _newntl_zuintoz(unsigned long d, _newntl_verylong *a);
       /* *a = d;  space is allocated  */

    long _newntl_ztoint(_newntl_verylong a);
       /* converts a to a long;  overflow results in value
          mod 2^{newNTL_BITS_PER_LONG}. */

    unsigned long _newntl_ztouint(_newntl_verylong a);
       /* converts a to a long;  overflow results in value
          mod 2^{newNTL_BITS_PER_LONG}. */


    double _newntl_zdoub(_newntl_verylong n);
       /* converts a to a double;  no overflow check */

    long _newntl_zround_correction(_newntl_verylong a, long k, long residual);
       /* k >= 1, |a| >= 2^k, and residual is 0, 1, or -1.
          The result is what we should add to (a >> k) to round
          x = a/2^k to the nearest integer using IEEE-like rounding rules
          (i.e., round to nearest, and round to even to break ties).
          The result is either 0 or sign(a).
          If residual is not zero, it is as if x were replaced by
          x' = x + residual*2^{-(k+1)}.
          This can be used to break ties when x is exactly
          half way between two integers. */

    double _newntl_zlog(_newntl_verylong a);
       /* computes log(a), protecting against overflow */
      

    void _newntl_zdoubtoz(double a, _newntl_verylong *x);
       /* x = floor(a); */  
    



/************************************************************************

   Square roots

*************************************************************************/


    long _newntl_zsqrts(long n);
       /* return floor(sqrt(n));  error raised in n < 0 */

    void _newntl_zsqrt(_newntl_verylong n, _newntl_verylong *r);
       /* *r =  floor(sqrt(n));  error raised in n < 0 */

/*********************************************************************
 
    Exponentiation
 
**********************************************************************/

   void _newntl_zexp(_newntl_verylong a, long e, _newntl_verylong *b);
       /* *b = a^e;  error raised if e < 0 */

   void _newntl_zexps(long a, long e, _newntl_verylong *b);
       /* *b = a^e;  error raised if e < 0 */
       

/*********************************************************************

   Modular Arithmetic

   Addition, subtraction, multiplication, squaring division, inversion,
   and exponentiation modulo a positive modulus n, where all operands
   (except for the exponent in exponentiation) and results are in the
   range [0, n-1].   

***********************************************************************/

    void _newntl_zaddmod(_newntl_verylong a, _newntl_verylong b, _newntl_verylong n, _newntl_verylong *c);
       /* *c = (a + b) % n */

    void _newntl_zsubmod(_newntl_verylong a, _newntl_verylong b, _newntl_verylong n, _newntl_verylong *c);
       /* *c = (a - b) % n */

    void _newntl_zsmulmod(_newntl_verylong a, long b, _newntl_verylong n, _newntl_verylong *c);
       /* *c = (a * b) % n */

    void _newntl_zmulmod(_newntl_verylong a, _newntl_verylong b, _newntl_verylong n, _newntl_verylong *c);
       /* *c = (a * b) % n */

    void _newntl_zsqmod(_newntl_verylong a, _newntl_verylong n, _newntl_verylong *c);
       /* *c = (a ^ 2) % n */

    void _newntl_zinvmod(_newntl_verylong a, _newntl_verylong n, _newntl_verylong *c);
       /* *c = (1 / a) % n; error raised if gcd(b, n) != 1 */

    void _newntl_zpowermod(_newntl_verylong g, _newntl_verylong e, _newntl_verylong F,
                        _newntl_verylong *h);

       /* *b = (a ^ e) % n;  */



/**************************************************************************

   Euclidean Algorithms

***************************************************************************/
    void _newntl_zgcd(_newntl_verylong m1, _newntl_verylong m2, _newntl_verylong *r);
       /* *r = greatest common divisor of m1 and m2; 
          uses binary gcd algorithm */


    void _newntl_zexteucl(_newntl_verylong a, _newntl_verylong *xa,
                 _newntl_verylong b, _newntl_verylong *xb,
                 _newntl_verylong *d);
       /*
          *d = a * *xa + b * *xb = gcd(a, b);
          sets *d, *xa and *xb given a and b;
          uses Lehmer`s trick
        */


    long _newntl_zinv(_newntl_verylong a, _newntl_verylong b, _newntl_verylong *c);
       /*
          if (a and b coprime)
          {
              *c = inv; 
              return(0);
          }
          else
          {
              *c = gcd(a, b);
              return(1);
          }
          
          where inv is such that (inv * a)  == 1 mod b;
          error raised if b <= 1 or a < 0 or a >= b
        */

     long _newntl_zxxratrecon(_newntl_verylong x, _newntl_verylong m,  
                      _newntl_verylong a_bound, _newntl_verylong b_bound,
                      _newntl_verylong *a, _newntl_verylong *b);

        /* rational reconstruction: see doc in ZZ.txt */


        
/**********************************************************************

    Storage Allocation

    These routines use malloc and free.

***********************************************************************/


    void _newntl_zsetlength(_newntl_verylong *v, long len);
       /* Allocates enough space to hold a len-digit number,
          where each digit has newNTL_NBITS bits.
          If space must be allocated, space for one extra digit
          is always allocated. */

    void _newntl_zfree(_newntl_verylong *x);
       /* Free's space held by x, and sets x back to 0. */


/*******************************************************************

    Special routines

********************************************************************/



long _newntl_zsize(_newntl_verylong n);
long _newntl_zisone(_newntl_verylong n);
long _newntl_zdigit(_newntl_verylong a, long i);

long _newntl_zsptest(_newntl_verylong a);
long _newntl_zwsptest(_newntl_verylong a);

long _newntl_zcrtinrange(_newntl_verylong g, _newntl_verylong a);

void _newntl_zfrombytes(_newntl_verylong *x, const unsigned char *p, long n);
void _newntl_zbytesfromz(unsigned char *p, _newntl_verylong a, long nn);

long _newntl_zblock_construct_alloc(_newntl_verylong *x, long d, long n);
void _newntl_zblock_construct_set(_newntl_verylong x, _newntl_verylong *y, long i);
long _newntl_zblock_destroy(_newntl_verylong x);
long _newntl_zblock_storage(long d);



void _newntl_crt_struct_init(void **crt_struct, long n, _newntl_verylong p,
                          const long *primes);
void _newntl_crt_struct_insert(void *crt_struct, long i, _newntl_verylong m);
void _newntl_crt_struct_free(void *crt_struct);
void _newntl_crt_struct_eval(void *crt_struct, _newntl_verylong *t, const long *a);
long _newntl_crt_struct_special(void *crt_struct);

void _newntl_rem_struct_init(void **rem_struct, long n, _newntl_verylong p, 
                          const long *primes);
void _newntl_rem_struct_free(void *rem_struct);
void _newntl_rem_struct_eval(void *rem_struct, long *x, _newntl_verylong a);



#if (defined(__cplusplus) && !defined(newNTL_CXX_ONLY))
}
#endif


extern int _newntl_gmp_hack;

#define newNTL_crt_struct_eval _newntl_crt_struct_eval
#define newNTL_crt_struct_free _newntl_crt_struct_free
#define newNTL_crt_struct_init _newntl_crt_struct_init
#define newNTL_crt_struct_insert _newntl_crt_struct_insert
#define newNTL_crt_struct_special _newntl_crt_struct_special
#define newNTL_rem_struct_eval _newntl_rem_struct_eval
#define newNTL_rem_struct_free _newntl_rem_struct_free
#define newNTL_rem_struct_init _newntl_rem_struct_init
#define newNTL_verylong _newntl_verylong
#define newNTL_z2log _newntl_z2log
#define newNTL_zabs _newntl_zabs
#define newNTL_zadd _newntl_zadd
#define newNTL_zaddmod _newntl_zaddmod
#define newNTL_zand _newntl_zand
#define newNTL_zbit _newntl_zbit
#define newNTL_zblock_construct_alloc _newntl_zblock_construct_alloc
#define newNTL_zblock_construct_set _newntl_zblock_construct_set
#define newNTL_zblock_destroy _newntl_zblock_destroy
#define newNTL_zblock_storage _newntl_zblock_storage
#define newNTL_zbytesfromz _newntl_zbytesfromz
#define newNTL_zcompare _newntl_zcompare
#define newNTL_zcopy _newntl_zcopy1
#define newNTL_zcrtinrange _newntl_zcrtinrange
#define newNTL_zdigit _newntl_zdigit
#define newNTL_zdiv _newntl_zdiv
#define newNTL_zdoub _newntl_zdoub
#define newNTL_zdoubtoz _newntl_zdoubtoz
#define newNTL_zexp _newntl_zexp
#define newNTL_zexps _newntl_zexps
#define newNTL_zexteucl _newntl_zexteucl
#define newNTL_zfree _newntl_zfree
#define newNTL_zfrombytes _newntl_zfrombytes
#define newNTL_zgcd _newntl_zgcd
#define newNTL_zintoz _newntl_zintoz1
#define newNTL_zinv _newntl_zinv
#define newNTL_zinvmod _newntl_zinvmod
#define newNTL_zisone _newntl_zisone
#define newNTL_ziszero _newntl_ziszero
#define newNTL_zlog _newntl_zlog
#define newNTL_zlowbits _newntl_zlowbits
#define newNTL_zlshift _newntl_zlshift
#define newNTL_zmakeodd _newntl_zmakeodd
#define newNTL_zmod _newntl_zmod
#define newNTL_zmul _newntl_zmul
#define newNTL_zmulmod _newntl_zmulmod
#define newNTL_znegate _newntl_znegate
#define newNTL_znumtwos _newntl_znumtwos
#define newNTL_zodd _newntl_zodd
#define newNTL_zone _newntl_zone
#define newNTL_zor _newntl_zor
#define newNTL_zpowermod _newntl_zpowermod
#define newNTL_zquickmod _newntl_zquickmod
#define newNTL_zround_correction _newntl_zround_correction
#define newNTL_zrshift _newntl_zrshift
#define newNTL_zsadd _newntl_zsadd
#define newNTL_zscompare _newntl_zscompare
#define newNTL_zsdiv _newntl_zsdiv
#define newNTL_zsetbit _newntl_zsetbit
#define newNTL_zsetlength _newntl_zsetlength
#define newNTL_zsign _newntl_zsign
#define newNTL_zsize _newntl_zsize
#define newNTL_zslowbits _newntl_zslowbits
#define newNTL_zsmod _newntl_zsmod
#define newNTL_zsmul _newntl_zsmul
#define newNTL_zsmulmod _newntl_zsmulmod
#define newNTL_zsptest _newntl_zsptest
#define newNTL_zsq _newntl_zsq
#define newNTL_zsqmod _newntl_zsqmod
#define newNTL_zsqrt _newntl_zsqrt
#define newNTL_zsqrts _newntl_zsqrts
#define newNTL_zsub _newntl_zsub
#define newNTL_zsubmod _newntl_zsubmod
#define newNTL_zsubpos _newntl_zsubpos
#define newNTL_zswap _newntl_zswap
#define newNTL_zswitchbit _newntl_zswitchbit
#define newNTL_ztoint _newntl_ztoint
#define newNTL_ztouint _newntl_ztouint
#define newNTL_zuintoz _newntl_zuintoz
#define newNTL_zweight _newntl_zweight
#define newNTL_zweights _newntl_zweights
#define newNTL_zwsptest _newntl_zwsptest
#define newNTL_zxor _newntl_zxor
#define newNTL_zxxratrecon _newntl_zxxratrecon
#define newNTL_zzero _newntl_zzero1

#define newNTL_zsaddmul _newntl_zsaddmul
#define newNTL_zaddmul _newntl_zaddmul
#define newNTL_zssubmul _newntl_zssubmul
#define newNTL_zsubmul _newntl_zsubmul

