
#include <newNTL/vec_long.h>

#include <newNTL/new.h>

newNTL_START_IMPL

static inline 
void BlockConstruct(long *, long, const long&) { }

static inline 
void BlockDestroy(long *, long) { }

newNTL_io_vector_impl(long,vec_long)

newNTL_eq_vector_impl(long,vec_long)

newNTL_END_IMPL

