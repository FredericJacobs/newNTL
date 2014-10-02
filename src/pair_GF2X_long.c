
#include <newNTL/pair_GF2X_long.h>

#include <newNTL/new.h>

newNTL_START_IMPL

newNTL_pair_impl(GF2X,long,pair_GF2X_long)
newNTL_pair_io_impl(GF2X,long,pair_GF2X_long)
newNTL_pair_eq_impl(GF2X,long,pair_GF2X_long)

newNTL_vector_impl(pair_GF2X_long,vec_pair_GF2X_long)
newNTL_io_vector_impl(pair_GF2X_long,vec_pair_GF2X_long)
newNTL_eq_vector_impl(pair_GF2X_long,vec_pair_GF2X_long)

newNTL_END_IMPL
