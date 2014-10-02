
#include <newNTL/ZZ_pX.h>
#include <newNTL/lzz_pX.h>
#include <newNTL/GF2X.h>

#include <newNTL/version.h>

newNTL_CLIENT


#define make_string_aux(x) #x
#define make_string(x) make_string_aux(x)

int SmallModulusTest(long p, long n)
{
   zz_pBak bak;

   bak.save();


   zz_p::init(p);

   zz_pX a, b, c, cc;

   random(a, n);
   random(b, n);
   PlainMul(c, a, b);
   FFTMul(cc, a, b);

   int res;
   res = (c != cc);

   bak.restore();

   return res;
}


int GF2X_test()
{
   GF2X a, b, c, c1;

   long n;

#ifdef newNTL_GF2X_LIB
   for (n = 32; n <= (1L << 18); n = n << 1) {
      random(a, n);
      random(b, n);
      OldMul(c, a, b);
      mul(c1, a, b);
      if (c1 != c) return 1;
   }
#endif

   return 0;
}

void GF2X_time()
{
   long n = 1000000L;
   long iter;

   GF2X a, b, c;

   double t;
   long i;

   random(a, n);
   random(b, n);

   mul(c, a, b);

   iter = 0;
   do {
      iter = iter ? (2*iter) : 1;
      t = GetTime();
      for (i = 0; i < iter; i++)
         mul(c, a, b);
      t = GetTime() - t;
   } while (t < 0.5);

   cerr << "time to multiply polynomials over GF(2) \n   of degree < 1000000: "
        << (t/iter) << "s\n";

#ifdef newNTL_GF2X_LIB
   OldMul(c, a, b);

   iter = 0;
   do {
      iter = iter ? (2*iter) : 1;
      t = GetTime();
      for (i = 0; i < iter; i++)
         OldMul(c, a, b);
      t = GetTime() - t;
   } while (t < 0.5);

   cerr << "   **** using old code: "  << (t/iter) << "s\n";
#endif

}


int main()
{


   cerr << "This is newNTL version " << newNTL_VERSION << "\n"; 

   cerr << "Basic Configuration Options:\n";


#ifdef newNTL_STD_CXX
   cerr << "newNTL_STD_CXX\n";
#endif

#ifdef newNTL_PSTD_NNS
   cerr << "newNTL_PSTD_NNS\n";
#endif

#ifdef newNTL_PSTD_NHF
   cerr << "newNTL_PSTD_NHF\n";
#endif

#ifdef newNTL_PSTD_NTN
   cerr << "newNTL_PSTD_NTN\n";
#endif

#ifdef newNTL_GMP_LIP
   cerr << "newNTL_GMP_LIP\n";
#endif

#ifdef newNTL_GMP_HACK
   cerr << "newNTL_GMP_HACK\n";
#endif

#ifdef newNTL_GF2X_LIB
   cerr << "newNTL_GF2X_LIB\n";
#endif


#ifdef newNTL_LONG_LONG_TYPE
   cerr << "newNTL_LONG_LONG_TYPE: ";
   cerr << make_string(newNTL_LONG_LONG_TYPE) << "\n";
#endif

#ifdef newNTL_UNSIGNED_LONG_LONG_TYPE
   cerr << "newNTL_UNSIGNED_LONG_LONG_TYPE: ";
   cerr << make_string(newNTL_UNSIGNED_LONG_LONG_TYPE) << "\n";
#endif

#ifdef newNTL_CXX_ONLY
   cerr << "newNTL_CXX_ONLY\n";
#endif


#ifdef newNTL_X86_FIX
   cerr << "newNTL_X86_FIX\n";
#endif

#ifdef newNTL_NO_X86_FIX
   cerr << "newNTL_NO_X86_FIX\n";
#endif

#ifdef newNTL_NO_INIT_TRANS
   cerr << "newNTL_NO_INIT_TRANS\n";
#endif

#ifdef newNTL_CLEAN_INT
   cerr << "newNTL_CLEAN_INT\n";
#endif

#ifdef newNTL_CLEAN_PTR
   cerr << "newNTL_CLEAN_PTR\n";
#endif

#ifdef newNTL_RANGE_CHECK
   cerr << "newNTL_RANGE_CHECK\n";
#endif


cerr << "\n";
cerr << "Resolution of double-word types:\n";
cerr << make_string(newNTL_LL_TYPE) << "\n";
cerr << make_string(newNTL_ULL_TYPE) << "\n";


cerr << "\n";
cerr << "Performance Options:\n";

#ifdef newNTL_LONG_LONG
   cerr << "newNTL_LONG_LONG\n";
#endif

#ifdef newNTL_AVOID_FLOAT
   cerr << "newNTL_AVOID_FLOAT\n";
#endif

#ifdef newNTL_SPMM_UL
   cerr << "newNTL_SPMM_UL\n";
#endif


#ifdef newNTL_SPMM_ULL
   cerr << "newNTL_SPMM_ULL\n";
#endif


#ifdef newNTL_SPMM_ASM
   cerr << "newNTL_SPMM_ASM\n";
#endif




#ifdef newNTL_AVOID_BRANCHING
   cerr << "newNTL_AVOID_BRANCHING\n";
#endif



#ifdef newNTL_TBL_REM
   cerr << "newNTL_TBL_REM\n";
#endif


#ifdef newNTL_GF2X_ALTCODE
   cerr << "newNTL_GF2X_ALTCODE\n";
#endif

#ifdef newNTL_GF2X_ALTCODE1
   cerr << "newNTL_GF2X_ALTCODE1\n";
#endif


#ifdef newNTL_GF2X_NOINLINE
   cerr << "newNTL_GF2X_NOINLINE\n";
#endif

   cerr << "\n\n";

   if (_newntl_gmp_hack)
      cerr << "using GMP hack\n\n";

   cerr << "running tests...";

   long n, k;

   n = 200;
   k = 10*newNTL_ZZ_NBITS;

   ZZ p;

   GenPrime(p, k);


   ZZ_p::init(p);         // initialization

   ZZ_pX f, g, h, r1, r2, r3;

   random(g, n);    // g = random polynomial of degree < n
   random(h, n);    // h =             "   "
   random(f, n);    // f =             "   "

   // SetCoeff(f, n);  // Sets coefficient of X^n to 1
   
   ZZ_p lc;

   do {
      random(lc);
   } while (IsZero(lc));

   SetCoeff(f, n, lc);


   // For doing arithmetic mod f quickly, one must pre-compute
   // some information.

   ZZ_pXModulus F;
   build(F, f);

   PlainMul(r1, g, h);  // this uses classical arithmetic
   PlainRem(r1, r1, f);

   MulMod(r2, g, h, F);  // this uses the FFT

   MulMod(r3, g, h, f);  // uses FFT, but slower

   // compare the results...

   if (r1 != r2) {
      cerr << "r1 != r2!!\n";
      return 1;
   }
   else if (r1 != r3) {
      cerr << "r1 != r3!!\n";
      return 1;
   }


   // small prime tests...I've made some changes in v5.3
   // that should be checked on various platforms, so 
   // we might as well check them here.

   if (SmallModulusTest(17, 1000)) {
      cerr << "first SmallModulusTest failed!!\n";
      return 1;
   }

   if (SmallModulusTest((1L << (newNTL_SP_NBITS))-1, 1000)) {
      cerr << "second SmallModulusTest failed!!\n";
      return 1;
   }

   // Test gf2x code....

   if (GF2X_test()) {
      cerr << "GF2X test failed!\n";
      return 1;
   }
   

   cerr << "OK\n";

   ZZ x1, x2, x3, x4;
   double t;
   long i;

   RandomLen(x1, 1024);
   RandomBnd(x2, x1);
   RandomBnd(x3, x1);

   mul(x4, x2, x3);

   t = GetTime();
   for (i = 0; i < 100000; i++)
      mul(x4, x2, x3);
   t = GetTime()-t;

   cerr << "time for 1024-bit mul: " << t*10 << "us";

   if (_newntl_gmp_hack) {
      _newntl_gmp_hack = 0;
      mul(x4, x2, x3);

      t = GetTime();
      for (i = 0; i < 100000; i++)
         mul(x4, x2, x3);
      t = GetTime()-t;

      cerr << " (" << (t*10) << "us without GMP)"; 

      _newntl_gmp_hack = 1;
   }

   cerr << "\n";

   rem(x2, x4, x1);

   t = GetTime();
   for (i = 0; i < 100000; i++)
      rem(x2, x4, x1);
   t = GetTime()-t;

   cerr << "time for 2048/1024-bit rem: " << t*10 << "us";

   if (_newntl_gmp_hack) {
      _newntl_gmp_hack = 0;
      rem(x2, x4, x1);
   
      t = GetTime();
      for (i = 0; i < 100000; i++)
         rem(x2, x4, x1);
      t = GetTime()-t;
      cerr << " (" << (t*10) << "us without GMP)"; 

      _newntl_gmp_hack = 1;
   }

   cerr << "\n";
   

   GenPrime(p, 1024);
   RandomBnd(x1, p);
   if (IsZero(x1)) set(x1);

   InvMod(x2, x1, p);

   t = GetTime();
   for (i = 0; i < 1000; i++)
      InvMod(x2, x1, p);
   t = GetTime()-t;

   cerr << "time for 1024-bit modular inverse: " << t*1000 << "us";

   if (_newntl_gmp_hack) {
      _newntl_gmp_hack = 0;
      InvMod(x2, x1, p);
   
      t = GetTime();
      for (i = 0; i < 1000; i++)
         InvMod(x2, x1, p);
      t = GetTime()-t;
         cerr << " (" << (t*1000) << "us without GMP)"; 

      _newntl_gmp_hack = 1;
   }

   cerr << "\n";



   // test modulus switching
   
   n = 1024;
   k = 1024;
   RandomLen(p, k);

   ZZ_p::init(p);
   ZZ_pInfo->check();

   ZZ_pX j1, j2, j3;

   random(j1, n);
   random(j2, n);

   t = GetTime();
   for (i = 0; i < 20; i++) mul(j3, j1, j2);
   t = GetTime()-t;

   cerr << "time to multiply degree 1023 polynomials\n   modulo a 1024-bit number: ";
   cerr << (t/20) << "s";

   if (_newntl_gmp_hack) {
      _newntl_gmp_hack = 0;

      ZZ_p::init(p);
      ZZ_pInfo->check();

      t = GetTime();
      for (i = 0; i < 20; i++) mul(j3, j1, j2);
      t = GetTime()-t;

      cerr << " (" << (t/20) << "s without GMP)";
      _newntl_gmp_hack = 1;
   }

   cerr << "\n";

   GF2X_time();

   return 0;
}
