
#include <newNTL/ctools.h>

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

   cout << "\n\n";
   cout << "Basic Configuration Options:\n";


#ifdef newNTL_STD_CXX
   cout << "newNTL_STD_CXX\n";
#endif

#ifdef newNTL_PSTD_NNS
   cout << "newNTL_PSTD_NNS\n";
#endif

#ifdef newNTL_PSTD_NHF
   cout << "newNTL_PSTD_NHF\n";
#endif

#ifdef newNTL_PSTD_NTN
   cout << "newNTL_PSTD_NTN\n";
#endif

#ifdef newNTL_GMP_LIP
   cout << "newNTL_GMP_LIP\n";
#endif

#ifdef newNTL_GMP_HACK
   cout << "newNTL_GMP_HACK\n";
#endif

#ifdef newNTL_GF2X_LIB
   cout << "newNTL_GF2X_LIB\n";
#endif

#ifdef newNTL_LONG_LONG_TYPE
   cout << "newNTL_LONG_LONG_TYPE: ";
   cout << make_string(newNTL_LONG_LONG_TYPE) << "\n";
#endif

#ifdef newNTL_UNSIGNED_LONG_LONG_TYPE
   cout << "newNTL_UNSIGNED_LONG_LONG_TYPE: ";
   cout << make_string(newNTL_UNSIGNED_LONG_LONG_TYPE) << "\n";
#endif

#ifdef newNTL_CXX_ONLY
   cout << "newNTL_CXX_ONLY\n";
#endif


#ifdef newNTL_X86_FIX
   cout << "newNTL_X86_FIX\n";
#endif

#ifdef newNTL_NO_X86_FIX
   cout << "newNTL_NO_X86_FIX\n";
#endif

#ifdef newNTL_NO_INIT_TRANS
   cout << "newNTL_NO_INIT_TRANS\n";
#endif

#ifdef newNTL_CLEAN_INT
   cout << "newNTL_CLEAN_INT\n";
#endif

#ifdef newNTL_CLEAN_PTR
   cout << "newNTL_CLEAN_PTR\n";
#endif

#ifdef newNTL_RANGE_CHECK
   cout << "newNTL_RANGE_CHECK\n";
#endif


cout << "\n";
cout << "Resolution of double-word types:\n";
cout << make_string(newNTL_LL_TYPE) << "\n";
cout << make_string(newNTL_ULL_TYPE) << "\n";


cout << "\n";
cout << "Performance Options:\n";

#ifdef newNTL_LONG_LONG
   cout << "newNTL_LONG_LONG\n";
#endif

#ifdef newNTL_AVOID_FLOAT
   cout << "newNTL_AVOID_FLOAT\n";
#endif

#ifdef newNTL_SPMM_UL
   cout << "newNTL_SPMM_UL\n";
#endif


#ifdef newNTL_SPMM_ULL
   cout << "newNTL_SPMM_ULL\n";
#endif


#ifdef newNTL_SPMM_ASM
   cout << "newNTL_SPMM_ASM\n";
#endif




#ifdef newNTL_AVOID_BRANCHING
   cout << "newNTL_AVOID_BRANCHING\n";
#endif



#ifdef newNTL_TBL_REM
   cout << "newNTL_TBL_REM\n";
#endif


#ifdef newNTL_GF2X_ALTCODE
   cout << "newNTL_GF2X_ALTCODE\n";
#endif


#ifdef newNTL_GF2X_ALTCODE1
   cout << "newNTL_GF2X_ALTCODE1\n";
#endif


#ifdef newNTL_GF2X_NOINLINE
   cout << "newNTL_GF2X_NOINLINE\n";
#endif

   cout << "\n\n";

   return 0;
}
