
#include <newNTL/vec_double.h>

#include <newNTL/new.h>

newNTL_START_IMPL

static inline 
void BlockConstruct(double *, double) { }

static inline 
void BlockDestroy(double *, double) { }

newNTL_io_vector_impl(double,vec_double)

newNTL_eq_vector_impl(double,vec_double)

newNTL_END_IMPL

