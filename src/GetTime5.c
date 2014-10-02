#include <newNTL/config.h>

#if (defined(newNTL_CXX_ONLY) && !defined(__cplusplus))
#error "CXX_ONLY flag set...must use C++ compiler"
#endif


#if (defined(__cplusplus) && !defined(newNTL_CXX_ONLY))
extern "C" double _newntl_GetTime();
#endif


double _newntl_GetTime(void)
{
   return 0;
}
