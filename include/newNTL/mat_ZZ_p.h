
#ifndef newNTL_mat_ZZ_p__H
#define newNTL_mat_ZZ_p__H

#include <newNTL/tools.h>
#include <newNTL/matrix.h>
#include <newNTL/vec_vec_ZZ_p.h>

newNTL_OPEN_NNS

newNTL_matrix_decl(ZZ_p,vec_ZZ_p,vec_vec_ZZ_p,mat_ZZ_p)
newNTL_io_matrix_decl(ZZ_p,vec_ZZ_p,vec_vec_ZZ_p,mat_ZZ_p)
newNTL_eq_matrix_decl(ZZ_p,vec_ZZ_p,vec_vec_ZZ_p,mat_ZZ_p)

void add(mat_ZZ_p& X, const mat_ZZ_p& A, const mat_ZZ_p& B); 
void sub(mat_ZZ_p& X, const mat_ZZ_p& A, const mat_ZZ_p& B); 
void negate(mat_ZZ_p& X, const mat_ZZ_p& A); 
void mul(mat_ZZ_p& X, const mat_ZZ_p& A, const mat_ZZ_p& B); 
void mul(vec_ZZ_p& x, const mat_ZZ_p& A, const vec_ZZ_p& b); 
void mul(vec_ZZ_p& x, const vec_ZZ_p& a, const mat_ZZ_p& B); 

void mul(mat_ZZ_p& X, const mat_ZZ_p& A, const ZZ_p& b);
void mul(mat_ZZ_p& X, const mat_ZZ_p& A, long b);

inline void mul(mat_ZZ_p& X, const ZZ_p& a, const mat_ZZ_p& B)
   { mul(X, B, a); }

inline void mul(mat_ZZ_p& X, long a, const mat_ZZ_p& B)
   { mul(X, B, a); }

void ident(mat_ZZ_p& X, long n); 
inline mat_ZZ_p ident_mat_ZZ_p(long n)
   { mat_ZZ_p X; ident(X, n); newNTL_OPT_RETURN(mat_ZZ_p, X); }



void determinant(ZZ_p& d, const mat_ZZ_p& A);
long IsIdent(const mat_ZZ_p& A, long n);
void transpose(mat_ZZ_p& X, const mat_ZZ_p& A);
void solve(ZZ_p& d, vec_ZZ_p& X,
           const mat_ZZ_p& A, const vec_ZZ_p& b);
void inv(ZZ_p& d, mat_ZZ_p& X, const mat_ZZ_p& A);

inline void sqr(mat_ZZ_p& X, const mat_ZZ_p& A)
   { mul(X, A, A); }

inline mat_ZZ_p sqr(const mat_ZZ_p& A)
   { mat_ZZ_p X; sqr(X, A); newNTL_OPT_RETURN(mat_ZZ_p, X); }

void inv(mat_ZZ_p& X, const mat_ZZ_p& A);

inline mat_ZZ_p inv(const mat_ZZ_p& A)
   { mat_ZZ_p X; inv(X, A); newNTL_OPT_RETURN(mat_ZZ_p, X); }

void power(mat_ZZ_p& X, const mat_ZZ_p& A, const ZZ& e);
inline mat_ZZ_p power(const mat_ZZ_p& A, const ZZ& e)
   { mat_ZZ_p X; power(X, A, e); newNTL_OPT_RETURN(mat_ZZ_p, X); }

inline void power(mat_ZZ_p& X, const mat_ZZ_p& A, long e)
   { power(X, A, ZZ_expo(e)); }
inline mat_ZZ_p power(const mat_ZZ_p& A, long e)
   { mat_ZZ_p X; power(X, A, e); newNTL_OPT_RETURN(mat_ZZ_p, X); }


void diag(mat_ZZ_p& X, long n, const ZZ_p& d);
inline mat_ZZ_p diag(long n, const ZZ_p& d)
   { mat_ZZ_p X; diag(X, n, d); newNTL_OPT_RETURN(mat_ZZ_p, X); }

long IsDiag(const mat_ZZ_p& A, long n, const ZZ_p& d);


long gauss(mat_ZZ_p& M);
long gauss(mat_ZZ_p& M, long w);
void image(mat_ZZ_p& X, const mat_ZZ_p& A);
void kernel(mat_ZZ_p& X, const mat_ZZ_p& A);




inline ZZ_p determinant(const mat_ZZ_p& a)
   { ZZ_p x; determinant(x, a); return x; }
// functional variant of determinant

inline mat_ZZ_p transpose(const mat_ZZ_p & a)
   { mat_ZZ_p x; transpose(x, a); newNTL_OPT_RETURN(mat_ZZ_p, x); }

void clear(mat_ZZ_p& a);
// x = 0 (dimension unchanged)

long IsZero(const mat_ZZ_p& a);
// test if a is the zero matrix (any dimension)


// operator notation:

mat_ZZ_p operator+(const mat_ZZ_p& a, const mat_ZZ_p& b);
mat_ZZ_p operator-(const mat_ZZ_p& a, const mat_ZZ_p& b);
mat_ZZ_p operator*(const mat_ZZ_p& a, const mat_ZZ_p& b);

mat_ZZ_p operator-(const mat_ZZ_p& a);


// matrix/scalar multiplication:

inline mat_ZZ_p operator*(const mat_ZZ_p& a, const ZZ_p& b)
   { mat_ZZ_p x; mul(x, a, b); newNTL_OPT_RETURN(mat_ZZ_p, x); }

inline mat_ZZ_p operator*(const mat_ZZ_p& a, long b)
   { mat_ZZ_p x; mul(x, a, b); newNTL_OPT_RETURN(mat_ZZ_p, x); }

inline mat_ZZ_p operator*(const ZZ_p& a, const mat_ZZ_p& b)
   { mat_ZZ_p x; mul(x, a, b); newNTL_OPT_RETURN(mat_ZZ_p, x); }

inline mat_ZZ_p operator*(long a, const mat_ZZ_p& b)
   { mat_ZZ_p x; mul(x, a, b); newNTL_OPT_RETURN(mat_ZZ_p, x); }

// matrix/vector multiplication:

vec_ZZ_p operator*(const mat_ZZ_p& a, const vec_ZZ_p& b);

vec_ZZ_p operator*(const vec_ZZ_p& a, const mat_ZZ_p& b);




// assignment operator notation:

inline mat_ZZ_p& operator+=(mat_ZZ_p& x, const mat_ZZ_p& a)
{
   add(x, x, a);
   return x;
}   

inline mat_ZZ_p& operator-=(mat_ZZ_p& x, const mat_ZZ_p& a)
{
   sub(x, x, a);
   return x;
}   


inline mat_ZZ_p& operator*=(mat_ZZ_p& x, const mat_ZZ_p& a)
{
   mul(x, x, a);
   return x;
}   

inline mat_ZZ_p& operator*=(mat_ZZ_p& x, const ZZ_p& a)
{
   mul(x, x, a);
   return x;
}   

inline mat_ZZ_p& operator*=(mat_ZZ_p& x, long a)
{
   mul(x, x, a);
   return x;
}   
   

inline vec_ZZ_p& operator*=(vec_ZZ_p& x, const mat_ZZ_p& a)
{
   mul(x, x, a);
   return x;
}   

newNTL_CLOSE_NNS



#endif