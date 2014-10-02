
#ifndef newNTL_FacVec__H
#define newNTL_FacVec__H

#include <newNTL/vector.h>

newNTL_OPEN_NNS

struct IntFactor {
   IntFactor() { }
   ~IntFactor() { }

   long q;
   long a;
   long val;
   long link;
};


newNTL_vector_decl(IntFactor,vec_IntFactor)
typedef vec_IntFactor FacVec;

void FactorInt(FacVec& fvec, long n);

newNTL_CLOSE_NNS

#endif
