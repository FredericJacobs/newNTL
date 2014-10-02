
#ifndef newNTL_vec_ZZ_p__H
#define newNTL_vec_ZZ_p__H

#include <newNTL/ZZ_p.h>
#include <newNTL/vec_ZZ.h>

newNTL_OPEN_NNS

newNTL_vector_decl(ZZ_p,vec_ZZ_p)

newNTL_io_vector_decl(ZZ_p,vec_ZZ_p)

newNTL_eq_vector_decl(ZZ_p,vec_ZZ_p)

void conv(vec_ZZ_p& x, const vec_ZZ& a);
template<> inline vec_ZZ_p to<vec_ZZ_p>(const vec_ZZ& a)
   { vec_ZZ_p x; conv(x, a); newNTL_OPT_RETURN(vec_ZZ_p, x); }


void conv(vec_ZZ& x, const vec_ZZ_p& a);
template<> inline vec_ZZ to<vec_ZZ>(const vec_ZZ_p& a)
   { vec_ZZ x; conv(x, a); newNTL_OPT_RETURN(vec_ZZ, x); }


void mul(vec_ZZ_p& x, const vec_ZZ_p& a, const ZZ_p& b);
inline void mul(vec_ZZ_p& x, const ZZ_p& a, const vec_ZZ_p& b)
   { mul(x, b, a); }

void mul(vec_ZZ_p& x, const vec_ZZ_p& a, long b);
inline void mul(vec_ZZ_p& x, long a, const vec_ZZ_p& b)
   { mul(x, b, a); }

void add(vec_ZZ_p& x, const vec_ZZ_p& a, const vec_ZZ_p& b);

void sub(vec_ZZ_p& x, const vec_ZZ_p& a, const vec_ZZ_p& b);
void clear(vec_ZZ_p& x);
void negate(vec_ZZ_p& x, const vec_ZZ_p& a);




void InnerProduct(ZZ_p& x, const vec_ZZ_p& a, const vec_ZZ_p& b);
void InnerProduct(ZZ_p& x, const vec_ZZ_p& a, const vec_ZZ_p& b,
                  long offset);

long IsZero(const vec_ZZ_p& a);

void VectorCopy(vec_ZZ_p& x, const vec_ZZ_p& a, long n);
inline vec_ZZ_p VectorCopy(const vec_ZZ_p& a, long n)
   { vec_ZZ_p x; VectorCopy(x, a, n); newNTL_OPT_RETURN(vec_ZZ_p, x); }

vec_ZZ_p operator+(const vec_ZZ_p& a, const vec_ZZ_p& b);
vec_ZZ_p operator-(const vec_ZZ_p& a, const vec_ZZ_p& b);
vec_ZZ_p operator-(const vec_ZZ_p& a);

inline vec_ZZ_p operator*(const vec_ZZ_p& a, const ZZ_p& b)
   { vec_ZZ_p x; mul(x, a, b); newNTL_OPT_RETURN(vec_ZZ_p, x); }

inline vec_ZZ_p operator*(const vec_ZZ_p& a, long b)
   { vec_ZZ_p x; mul(x, a, b); newNTL_OPT_RETURN(vec_ZZ_p, x); }

inline vec_ZZ_p operator*(const ZZ_p& a, const vec_ZZ_p& b)
   { vec_ZZ_p x; mul(x, a, b); newNTL_OPT_RETURN(vec_ZZ_p, x); }

inline vec_ZZ_p operator*(long a, const vec_ZZ_p& b)
   { vec_ZZ_p x; mul(x, a, b); newNTL_OPT_RETURN(vec_ZZ_p, x); }

ZZ_p operator*(const vec_ZZ_p& a, const vec_ZZ_p& b);



// assignment operator notation:

inline vec_ZZ_p& operator+=(vec_ZZ_p& x, const vec_ZZ_p& a)
{ 
   add(x, x, a);
   return x;
}

inline vec_ZZ_p& operator-=(vec_ZZ_p& x, const vec_ZZ_p& a)
{ 
   sub(x, x, a);
   return x;
}

inline vec_ZZ_p& operator*=(vec_ZZ_p& x, const ZZ_p& a)
{ 
   mul(x, x, a);
   return x;
}

inline vec_ZZ_p& operator*=(vec_ZZ_p& x, long a)
{ 
   mul(x, x, a);
   return x;
}


newNTL_CLOSE_NNS


#endif
