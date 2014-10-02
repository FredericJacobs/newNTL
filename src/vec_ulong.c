
#include <newNTL/vec_ulong.h>

#include <newNTL/new.h>

newNTL_START_IMPL

static inline 
void BlockConstruct(_newntl_ulong *, long) { }

static inline 
void BlockDestroy(_newntl_ulong *, long) { }

newNTL_io_vector_impl(_newntl_ulong,vec_ulong)

newNTL_eq_vector_impl(_newntl_ulong,vec_ulong)

newNTL_END_IMPL

