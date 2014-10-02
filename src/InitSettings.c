
#include <newNTL/config.h>

#if (defined(newNTL_STD_CXX) || defined(newNTL_PSTD_NHF))
#include <iostream>
using namespace std;
#else
#include <iostream.h>
#endif

#define make_string_aux(x) #x
#define make_string(x) make_string_aux(x)



int main()
{

#ifdef newNTL_STD_CXX
   cout << "newNTL_STD_CXX=1\n";
#else
   cout << "newNTL_STD_CXX=0\n";
#endif

#ifdef newNTL_PSTD_NNS
   cout << "newNTL_PSTD_NNS=1\n";
#else
   cout << "newNTL_PSTD_NNS=0\n";
#endif

#ifdef newNTL_PSTD_NHF
   cout << "newNTL_PSTD_NHF=1\n";
#else
   cout << "newNTL_PSTD_NHF=0\n";
#endif

#ifdef newNTL_PSTD_NTN
   cout << "newNTL_PSTD_NTN=1\n";
#else
   cout << "newNTL_PSTD_NTN=0\n";
#endif

#ifdef newNTL_GMP_LIP
   cout << "newNTL_GMP_LIP=1\n";
#else
   cout << "newNTL_GMP_LIP=0\n";
#endif

#ifdef newNTL_GMP_HACK
   cout << "newNTL_GMP_HACK=1\n";
#else
   cout << "newNTL_GMP_HACK=0\n";
#endif

#ifdef newNTL_GF2X_LIB
   cout << "newNTL_GF2X_LIB=1\n";
#else
   cout << "newNTL_GF2X_LIB=0\n";
#endif

#ifdef newNTL_LONG_LONG_TYPE
   cout << "FLAG_LONG_LONG_TYPE=1\n";
   cout << "newNTL_LONG_LONG_TYPE=" make_string(newNTL_LONG_LONG_TYPE) "\n";
#else
   cout << "FLAG_LONG_LONG_TYPE=0\n";
   cout << "newNTL_LONG_LONG_TYPE=long long\n";
#endif


#ifdef newNTL_UNSIGNED_LONG_LONG_TYPE
   cout << "FLAG_UNSIGNED_LONG_LONG_TYPE=1\n";
   cout << "newNTL_UNSIGNED_LONG_LONG_TYPE=" make_string(newNTL_UNSIGNED_LONG_LONG_TYPE) "\n";
#else
   cout << "FLAG_UNSIGNED_LONG_LONG_TYPE=0\n";
   cout << "newNTL_UNSIGNED_LONG_LONG_TYPE=unsigned long long\n";
#endif

#ifdef newNTL_CXX_ONLY
   cout << "newNTL_CXX_ONLY=1\n";
#else
   cout << "newNTL_CXX_ONLY=0\n";
#endif


#ifdef newNTL_X86_FIX
   cout << "newNTL_X86_FIX=1\n";
#else
   cout << "newNTL_X86_FIX=0\n";
#endif

#ifdef newNTL_NO_X86_FIX
   cout << "newNTL_NO_X86_FIX=1\n";
#else
   cout << "newNTL_NO_X86_FIX=0\n";
#endif


#ifdef newNTL_NO_INIT_TRANS
   cout << "newNTL_NO_INIT_TRANS=1\n";
#else
   cout << "newNTL_NO_INIT_TRANS=0\n";
#endif

#ifdef newNTL_CLEAN_INT
   cout << "newNTL_CLEAN_INT=1\n";
#else
   cout << "newNTL_CLEAN_INT=0\n";
#endif

#ifdef newNTL_CLEAN_PTR
   cout << "newNTL_CLEAN_PTR=1\n";
#else
   cout << "newNTL_CLEAN_PTR=0\n";
#endif

#ifdef newNTL_RANGE_CHECK
   cout << "newNTL_RANGE_CHECK=1\n";
#else
   cout << "newNTL_RANGE_CHECK=0\n";
#endif


   return 0;
}
