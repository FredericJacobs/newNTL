
#include <newNTL/pair_lzz_pEX_long.h>

#include <newNTL/new.h>

newNTL_START_IMPL

newNTL_pair_impl(zz_pEX,long,pair_zz_pEX_long)
newNTL_pair_io_impl(zz_pEX,long,pair_zz_pEX_long)
newNTL_pair_eq_impl(zz_pEX,long,pair_zz_pEX_long)

newNTL_vector_impl(pair_zz_pEX_long,vec_pair_zz_pEX_long)
newNTL_io_vector_impl(pair_zz_pEX_long,vec_pair_zz_pEX_long)
newNTL_eq_vector_impl(pair_zz_pEX_long,vec_pair_zz_pEX_long)

newNTL_END_IMPL
