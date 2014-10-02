

#ifdef newNTL_SINGLE_MUL
#error "do not set newNTL_SINGLE_MUL when newNTL_GMP_LIP is set"
#endif

#if 1

typedef void *_newntl_gbigint;

#else

/*
 * This way of defining the bigint handle type is a bit non-standard,
 * but better for debugging.
 */

struct _newntl_gbigint_is_opaque { int _x_; };
typedef struct _newntl_gbigint_is_opaque * _newntl_gbigint;

#endif

#define newNTL_SP_NBITS newNTL_NBITS_MAX
#define newNTL_SP_BOUND (1L << newNTL_SP_NBITS)
#define newNTL_SP_FBOUND ((double) newNTL_SP_BOUND)

#define newNTL_WSP_NBITS (newNTL_BITS_PER_LONG-2)
#define newNTL_WSP_BOUND (1L << newNTL_WSP_NBITS)

/* define the following so an error is raised */

#define newNTL_RADIX ......
#define newNTL_NBITSH ......
#define newNTL_RADIXM ......
#define newNTL_RADIXROOT ......
#define newNTL_RADIXROOTM ......
#define newNTL_FRADIX_INV ......




#if (defined(__cplusplus) && !defined(newNTL_CXX_ONLY))
extern "C" {
#endif


/***********************************************************************

   Basic Functions

***********************************************************************/
    


    void _newntl_gsadd(_newntl_gbigint a, long d, _newntl_gbigint *b);
       /* *b = a + d */

    void _newntl_gadd(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint *c);
       /*  *c = a + b */

    void _newntl_gsub(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint *c);
       /* *c = a - b */

    void _newntl_gsubpos(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint *c);
       /* *c = a - b; assumes a >= b >= 0 */

    void _newntl_gsmul(_newntl_gbigint a, long d, _newntl_gbigint *b);
       /* *b = d * a */

    void _newntl_gmul(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint *c);
       /* *c = a * b */

    void _newntl_gsq(_newntl_gbigint a, _newntl_gbigint *c);
       /* *c = a * a */

    long _newntl_gsdiv(_newntl_gbigint a, long b, _newntl_gbigint *q);
       /* (*q) = floor(a/b) and a - floor(a/b)*(*q) is returned;
          error is raised if b == 0;
          if b does not divide a, then sign(*q) == sign(b) */

    void _newntl_gdiv(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint *q, _newntl_gbigint *r);
       /* (*q) = floor(a/b) and (*r) = a - floor(a/b)*(*q);
          error is raised if b == 0;
          if b does not divide a, then sign(*q) == sign(b) */

    void _newntl_gmod(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint *r);
       /* same as _newntl_gdiv, but only remainder is computed */

    long _newntl_gsmod(_newntl_gbigint a, long d);
       /* same as _newntl_gsdiv, but only remainder is computed */

    void _newntl_gquickmod(_newntl_gbigint *r, _newntl_gbigint b);
       /* *r = *r % b; 
	  The division is performed in place (but may sometimes
	  assumes b > 0 and *r >= 0;
          cause *r to grow by one digit) */

    void _newntl_gsaddmul(_newntl_gbigint x, long y,  _newntl_gbigint *ww);
      /* *ww += x*y */

    void _newntl_gaddmul(_newntl_gbigint x, _newntl_gbigint y,  _newntl_gbigint *ww);
      /* *ww += x*y */

    void _newntl_gssubmul(_newntl_gbigint x, long y,  _newntl_gbigint *ww);
      /* *ww -= x*y */

    void _newntl_gsubmul(_newntl_gbigint x, _newntl_gbigint y,  _newntl_gbigint *ww);
      /* *ww -= x*y */


/********************************************************************

   Shifting and bit manipulation

*********************************************************************/


    void _newntl_glshift(_newntl_gbigint n, long k, _newntl_gbigint *a);
       /* *a = sign(n) * (|n| << k);
          shift is in reverse direction for negative k */

    void _newntl_grshift(_newntl_gbigint n, long k, _newntl_gbigint *a);
       /* *a = sign(n) * (|n| >> k);
          shift is in reverse direction for negative k */
    
    long _newntl_gmakeodd(_newntl_gbigint *n);
       /*
          if (n != 0)
              *n = m;
              return (k such that n == 2 ^ k * m with m odd);
          else
              return (0); 
        */

    long _newntl_gnumtwos(_newntl_gbigint n);
        /* return largest e such that 2^e divides n, or zero if n is zero */

    long _newntl_godd(_newntl_gbigint a);
       /* returns 1 if n is odd and 0 if it is even */

    long _newntl_gbit(_newntl_gbigint a, long p);
       /* returns p-th bit of a, where the low order bit is indexed by 0;
          p out of range returns 0 */

    long _newntl_gsetbit(_newntl_gbigint *a, long p);
       /* returns original value of p-th bit of |a|, and replaces
          p-th bit of a by 1 if it was zero;
          error if p < 0 */

    long _newntl_gswitchbit(_newntl_gbigint *a, long p);
       /* returns original value of p-th bit of |a|, and switches
          the value of p-th bit of a;
          p starts counting at 0;
          error if p < 0 */


     void _newntl_glowbits(_newntl_gbigint a, long k, _newntl_gbigint *b);
        /* places k low order bits of |a| in b */ 

     long _newntl_gslowbits(_newntl_gbigint a, long k);
        /* returns k low order bits of |a| */

    long _newntl_gweights(long a);
        /* returns Hamming weight of |a| */

    long _newntl_gweight(_newntl_gbigint a);
        /* returns Hamming weight of |a| */

    void _newntl_gand(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint *c);
        /* c gets bit pattern `bits of |a|` and `bits of |b|` */

    void _newntl_gor(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint *c);
        /* c gets bit pattern `bits of |a|` inclusive or `bits of |b|` */

    void _newntl_gxor(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint *c);
        /* c gets bit pattern `bits of |a|` exclusive or `bits of |b|` */




/************************************************************************

   Comparison

*************************************************************************/

    long _newntl_gcompare(_newntl_gbigint a, _newntl_gbigint b);
       /*
          if (a > b)
              return (1);
          if (a == b)
              return (0);
          if (a < b)
              return (-1);
         */

    long _newntl_gscompare(_newntl_gbigint a, long b);
       /* single-precision version of the above */

    long _newntl_giszero (_newntl_gbigint a);
       /* test for 0 */


    long _newntl_gsign(_newntl_gbigint a);
       /* 
          if (a > 0)
              return (1);
          if (a == 0)
              return (0);
          if (a < 0)
              return (-1);
        */

    void _newntl_gabs(_newntl_gbigint *a);
       /* *a = |a| */

    void _newntl_gnegate(_newntl_gbigint *a);
       /* *a = -a */

    void _newntl_gcopy(_newntl_gbigint a, _newntl_gbigint *b);
       /* *b = a;  */

    void _newntl_gswap(_newntl_gbigint *a, _newntl_gbigint *b);
       /* swap a and b (by swaping pointers) */

    long _newntl_g2log(_newntl_gbigint a);
       /* number of bits in |a|; returns 0 if a = 0 */

    long _newntl_g2logs(long a);
        /* single-precision version of the above */


/********************************************************************

   Conversion

*********************************************************************/
        
    void _newntl_gzero(_newntl_gbigint *a);
       /* *a = 0;  */

    void _newntl_gone(_newntl_gbigint *a);
       /* *a = 1 */

    void _newntl_gintoz(long d, _newntl_gbigint *a);
       /* *a = d;  */


    void _newntl_guintoz(unsigned long d, _newntl_gbigint *a);
       /* *a = d;  space is allocated  */

    long _newntl_gtoint(_newntl_gbigint a);
       /* converts a to a long;  overflow results in value
          mod 2^{newNTL_BITS_PER_LONG}. */

    unsigned long _newntl_gtouint(_newntl_gbigint a);
       /* converts a to a long;  overflow results in value
          mod 2^{newNTL_BITS_PER_LONG}. */

   


    double _newntl_gdoub(_newntl_gbigint n);
       /* converts a to a double;  no overflow check */

    long _newntl_ground_correction(_newntl_gbigint a, long k, long residual);
       /* k >= 1, |a| >= 2^k, and residual is 0, 1, or -1.
          The result is what we should add to (a >> k) to round
          x = a/2^k to the nearest integer using IEEE-like rounding rules
          (i.e., round to nearest, and round to even to break ties).
          The result is either 0 or sign(a).
          If residual is not zero, it is as if x were replaced by
          x' = x + residual*2^{-(k+1)}.
          This can be used to break ties when x is exactly
          half way between two integers. */

    double _newntl_glog(_newntl_gbigint a);
       /* computes log(a), protecting against overflow */

    void _newntl_gdoubtoz(double a, _newntl_gbigint *x);
       /* x = floor(a);  */
    



/************************************************************************

   Square roots

*************************************************************************/


    long _newntl_gsqrts(long n);
       /* return floor(sqrt(n));  error raised in n < 0 */

    void _newntl_gsqrt(_newntl_gbigint n, _newntl_gbigint *r);
       /* *r =  floor(sqrt(n));  error raised in n < 0 */

/*********************************************************************
 
    Exponentiation
 
**********************************************************************/

   void _newntl_gexp(_newntl_gbigint a, long e, _newntl_gbigint *b);
       /* *b = a^e;  error raised if e < 0 */

   void _newntl_gexps(long a, long e, _newntl_gbigint *b);
       /* *b = a^e;  error raised if e < 0 */
       

/*********************************************************************

   Modular Arithmetic

   Addition, subtraction, multiplication, squaring division, inversion,
   and exponentiation modulo a positive modulus n, where all operands
   (except for the exponent in exponentiation) and results are in the
   range [0, n-1].   

   ALIAS RESTRICTION:  output parameters should not alias n

***********************************************************************/

    void _newntl_gaddmod(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint n, _newntl_gbigint *c);
       /* *c = (a + b) % n */

    void _newntl_gsubmod(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint n, _newntl_gbigint *c);
       /* *c = (a - b) % n */

    void _newntl_gsmulmod(_newntl_gbigint a, long b, _newntl_gbigint n, _newntl_gbigint *c);
       /* *c = (a * b) % n */

    void _newntl_gmulmod(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint n, _newntl_gbigint *c);
       /* *c = (a * b) % n */

    void _newntl_gsqmod(_newntl_gbigint a, _newntl_gbigint n, _newntl_gbigint *c);
       /* *c = (a ^ 2) % n */

    void _newntl_ginvmod(_newntl_gbigint a, _newntl_gbigint n, _newntl_gbigint *c);
       /* *c = (1 / a) % n; error raised if gcd(b, n) != 1 */

    void _newntl_gpowermod(_newntl_gbigint g, _newntl_gbigint e, _newntl_gbigint F,
                        _newntl_gbigint *h);

       /* *b = (a ^ e) % n; */




/**************************************************************************

   Euclidean Algorithms

***************************************************************************/
    void _newntl_ggcd(_newntl_gbigint m1, _newntl_gbigint m2, _newntl_gbigint *r);
       /* *r = greatest common divisor of m1 and m2; 
          uses binary gcd algorithm */


    void _newntl_gexteucl(_newntl_gbigint a, _newntl_gbigint *xa,
                 _newntl_gbigint b, _newntl_gbigint *xb,
                 _newntl_gbigint *d);
       /*
          *d = a * *xa + b * *xb = gcd(a, b);
          sets *d, *xa and *xb given a and b;
          uses Lehmer`s trick
        */


    long _newntl_ginv(_newntl_gbigint a, _newntl_gbigint b, _newntl_gbigint *c);
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
          error raised if a < 0 or b <= 0
        */

     long _newntl_gxxratrecon(_newntl_gbigint x, _newntl_gbigint m,  
                      _newntl_gbigint a_bound, _newntl_gbigint b_bound,
                      _newntl_gbigint *a, _newntl_gbigint *b);

        /* rational reconstruction: see doc in ZZ.txt */


        
/**********************************************************************

    Storage Allocation

    These routines use malloc and free.

***********************************************************************/


    void _newntl_gsetlength(_newntl_gbigint *v, long len);
       /* Allocates enough space to hold a len-digit number,
          where each digit has newNTL_NBITS bits.
          If space must be allocated, space for one extra digit
          is always allocated. */

    void _newntl_gfree(_newntl_gbigint *x);
       /* Free's space held by x, and sets x back to 0. */


/*******************************************************************

    Special routines

********************************************************************/

long _newntl_gsize(_newntl_gbigint n);
long _newntl_gisone(_newntl_gbigint n);

long _newntl_gsptest(_newntl_gbigint a);
long _newntl_gwsptest(_newntl_gbigint a);
long _newntl_gcrtinrange(_newntl_gbigint g, _newntl_gbigint a);

void _newntl_gfrombytes(_newntl_gbigint *x, const unsigned char *p, long n);
void _newntl_gbytesfromz(unsigned char *p, _newntl_gbigint a, long nn);


long _newntl_gblock_construct_alloc(_newntl_gbigint *x, long d, long n);
void _newntl_gblock_construct_set(_newntl_gbigint x, _newntl_gbigint *y, long i);
long _newntl_gblock_destroy(_newntl_gbigint x);
long _newntl_gblock_storage(long d);


void _newntl_gcrt_struct_init(void **crt_struct, long n, _newntl_gbigint p,
                          const long *primes);
void _newntl_gcrt_struct_insert(void *crt_struct, long i, _newntl_gbigint m);
void _newntl_gcrt_struct_free(void *crt_struct);
void _newntl_gcrt_struct_eval(void *crt_struct, _newntl_gbigint *t, const long *a);
long _newntl_gcrt_struct_special(void *crt_struct);

void _newntl_grem_struct_init(void **rem_struct, long n, _newntl_gbigint p,
                          const long *primes);
void _newntl_grem_struct_free(void *rem_struct);
void _newntl_grem_struct_eval(void *rem_struct, long *x, _newntl_gbigint a);




#if (defined(__cplusplus) && !defined(newNTL_CXX_ONLY))
}
#endif


extern int _newntl_gmp_hack;

#define newNTL_crt_struct_eval _newntl_gcrt_struct_eval
#define newNTL_crt_struct_free _newntl_gcrt_struct_free
#define newNTL_crt_struct_init _newntl_gcrt_struct_init
#define newNTL_crt_struct_insert _newntl_gcrt_struct_insert
#define newNTL_crt_struct_special _newntl_gcrt_struct_special
#define newNTL_rem_struct_eval _newntl_grem_struct_eval
#define newNTL_rem_struct_free _newntl_grem_struct_free
#define newNTL_rem_struct_init _newntl_grem_struct_init
#define newNTL_verylong _newntl_gbigint
#define newNTL_z2log _newntl_g2log
#define newNTL_zabs _newntl_gabs
#define newNTL_zadd _newntl_gadd
#define newNTL_zaddmod _newntl_gaddmod
#define newNTL_zand _newntl_gand
#define newNTL_zbit _newntl_gbit
#define newNTL_zblock_construct_alloc _newntl_gblock_construct_alloc
#define newNTL_zblock_construct_set _newntl_gblock_construct_set
#define newNTL_zblock_destroy _newntl_gblock_destroy
#define newNTL_zblock_storage _newntl_gblock_storage
#define newNTL_zbytesfromz _newntl_gbytesfromz
#define newNTL_zcompare _newntl_gcompare
#define newNTL_zcopy _newntl_gcopy
#define newNTL_zcrtinrange _newntl_gcrtinrange
#define newNTL_zdiv _newntl_gdiv
#define newNTL_zdoub _newntl_gdoub
#define newNTL_zdoubtoz _newntl_gdoubtoz
#define newNTL_zexp _newntl_gexp
#define newNTL_zexps _newntl_gexps
#define newNTL_zexteucl _newntl_gexteucl
#define newNTL_zfree _newntl_gfree
#define newNTL_zfrombytes _newntl_gfrombytes
#define newNTL_zgcd _newntl_ggcd
#define newNTL_zintoz _newntl_gintoz
#define newNTL_zinv _newntl_ginv
#define newNTL_zinvmod _newntl_ginvmod
#define newNTL_zisone _newntl_gisone
#define newNTL_ziszero _newntl_giszero
#define newNTL_zlog _newntl_glog
#define newNTL_zlowbits _newntl_glowbits
#define newNTL_zlshift _newntl_glshift
#define newNTL_zmakeodd _newntl_gmakeodd
#define newNTL_zmod _newntl_gmod
#define newNTL_zmul _newntl_gmul
#define newNTL_zmulmod _newntl_gmulmod
#define newNTL_znegate _newntl_gnegate
#define newNTL_znumtwos _newntl_gnumtwos
#define newNTL_zodd _newntl_godd
#define newNTL_zone _newntl_gone
#define newNTL_zor _newntl_gor
#define newNTL_zpowermod _newntl_gpowermod
#define newNTL_zquickmod _newntl_gquickmod
#define newNTL_zround_correction _newntl_ground_correction
#define newNTL_zrshift _newntl_grshift
#define newNTL_zsadd _newntl_gsadd
#define newNTL_zscompare _newntl_gscompare
#define newNTL_zsdiv _newntl_gsdiv
#define newNTL_zsetbit _newntl_gsetbit
#define newNTL_zsetlength _newntl_gsetlength
#define newNTL_zsign _newntl_gsign
#define newNTL_zsize _newntl_gsize
#define newNTL_zslowbits _newntl_gslowbits
#define newNTL_zsmod _newntl_gsmod
#define newNTL_zsmul _newntl_gsmul
#define newNTL_zsmulmod _newntl_gsmulmod
#define newNTL_zsptest _newntl_gsptest
#define newNTL_zsq _newntl_gsq
#define newNTL_zsqmod _newntl_gsqmod
#define newNTL_zsqrt _newntl_gsqrt
#define newNTL_zsqrts _newntl_gsqrts
#define newNTL_zsub _newntl_gsub
#define newNTL_zsubmod _newntl_gsubmod
#define newNTL_zsubpos _newntl_gsubpos
#define newNTL_zswap _newntl_gswap
#define newNTL_zswitchbit _newntl_gswitchbit
#define newNTL_ztoint _newntl_gtoint
#define newNTL_ztouint _newntl_gtouint
#define newNTL_zuintoz _newntl_guintoz
#define newNTL_zweight _newntl_gweight
#define newNTL_zweights _newntl_gweights
#define newNTL_zwsptest _newntl_gwsptest
#define newNTL_zxor _newntl_gxor
#define newNTL_zxxratrecon _newntl_gxxratrecon
#define newNTL_zzero _newntl_gzero

#define newNTL_zsaddmul _newntl_gsaddmul
#define newNTL_zaddmul _newntl_gaddmul
#define newNTL_zssubmul _newntl_gssubmul
#define newNTL_zsubmul _newntl_gsubmul

#define newNTL_GMP_LIP

