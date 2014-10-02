
#ifndef newNTL_new__H
#define newNTL_new__H

#include <newNTL/config.h>

#if (defined(newNTL_STD_CXX) || defined(newNTL_PSTD_NTN))

// We use <new> and std::nothrow, even if neither newNTL_STD_CXX nor  
// newNTL_PSTD_NHF are set.  This appears to be somewhat more compatible
// with current compilers.

#include <new>

#define newNTL_NEW_OP new (std::nothrow)


#else

#define newNTL_NEW_OP new

#endif

#endif
