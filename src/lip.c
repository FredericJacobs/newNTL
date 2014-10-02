
#include <newNTL/config.h>

#if (defined(newNTL_CXX_ONLY) && !defined(__cplusplus))
#error "CXX_ONLY flag set...must use C++ compiler"
#endif

#ifdef newNTL_GMP_LIP

#include "g_lip_impl.h"

#else

#include "c_lip_impl.h"

#endif
