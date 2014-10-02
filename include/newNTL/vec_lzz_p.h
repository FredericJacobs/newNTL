
#ifndef newNTL_vec_zz_p__H
#define newNTL_vec_zz_p__H

#include <newNTL/vec_ZZ.h>
#include <newNTL/lzz_p.h>

newNTL_OPEN_NNS

newNTL_vector_decl(zz_p,vec_zz_p)

newNTL_io_vector_decl(zz_p,vec_zz_p)

newNTL_eq_vector_decl(zz_p,vec_zz_p)

void conv(vec_zz_p& x, const vec_ZZ& a);
template<> inline vec_zz_p to<vec_zz_p>(const vec_ZZ& a)
   { vec_zz_p x; conv(x, a); newNTL_OPT_RETURN(vec_zz_p, x); }

void conv(vec_ZZ& x, const vec_zz_p& a);
template<> inline vec_ZZ to<vec_ZZ>(const vec_zz_p& a)
   { vec_ZZ x; conv(x, a); newNTL_OPT_RETURN(vec_ZZ, x); }



long CRT(vec_ZZ& g, ZZ& a, const vec_zz_p& G);

void add(vec_zz_p& x, const vec_zz_p& a, const vec_zz_p& b);

void sub(vec_zz_p& x, const vec_zz_p& a, const vec_zz_p& b);
void clear(vec_zz_p& x);
void negate(vec_zz_p& x, const vec_zz_p& a);



void InnerProduct(zz_p& x, const vec_zz_p& a, const vec_zz_p& b);
void InnerProduct(zz_p& x, const vec_zz_p& a, const vec_zz_p& b,
                  long offset);



void mul(vec_zz_p& x, const vec_zz_p& a, zz_p b);
inline void mul(vec_zz_p& x, zz_p a, const vec_zz_p& b)
   { mul(x, b, a); }

void mul(vec_zz_p& x, const vec_zz_p& a, long b);
inline void mul(vec_zz_p& x, long a, const vec_zz_p& b)
   { mul(x, b, a); }


long IsZero(const vec_zz_p& a);

void VectorCopy(vec_zz_p& x, const vec_zz_p& a, long n);
inline vec_zz_p VectorCopy(const vec_zz_p& a, long n)
   { vec_zz_p x; VectorCopy(x, a, n); newNTL_OPT_RETURN(vec_zz_p, x); }



vec_zz_p operator+(const vec_zz_p& a, const vec_zz_p& b);
vec_zz_p operator-(const vec_zz_p& a, const vec_zz_p& b);
vec_zz_p operator-(const vec_zz_p& a);
zz_p operator*(const vec_zz_p& a, const vec_zz_p& b);

inline vec_zz_p operator*(const vec_zz_p& a, zz_p b)
   { vec_zz_p x; mul(x, a, b); newNTL_OPT_RETURN(vec_zz_p, x); }

inline vec_zz_p operator*(const vec_zz_p& a, long b)
   { vec_zz_p x; mul(x, a, b); newNTL_OPT_RETURN(vec_zz_p, x); }

inline vec_zz_p operator*(zz_p a, const vec_zz_p& b)
   { vec_zz_p x; mul(x, a, b); newNTL_OPT_RETURN(vec_zz_p, x); }

inline vec_zz_p operator*(long a, const vec_zz_p& b)
   { vec_zz_p x; mul(x, a, b); newNTL_OPT_RETURN(vec_zz_p, x); }







// assignment operator notation:

inline vec_zz_p& operator+=(vec_zz_p& x, const vec_zz_p& a)
{ 
   add(x, x, a);
   return x;
}

inline vec_zz_p& operator-=(vec_zz_p& x, const vec_zz_p& a)
{ 
   sub(x, x, a);
   return x;
}

inline vec_zz_p& operator*=(vec_zz_p& x, zz_p a)
{ 
   mul(x, x, a);
   return x;
}

inline vec_zz_p& operator*=(vec_zz_p& x, long a)
{
   mul(x, x, a);
   return x;
}


newNTL_CLOSE_NNS


#endif