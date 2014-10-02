#ifndef newNTL_xdouble__H
#define newNTL_xdouble__H

#include <newNTL/ZZ.h>

newNTL_OPEN_NNS

// newNTL_XD_HBOUND = 2^{max(newNTL_DOUBLE_PRECISION,newNTL_BITS_PER_LONG)+4}

#if (newNTL_DOUBLE_PRECISION > newNTL_BITS_PER_LONG)

#define newNTL_XD_HBOUND (newNTL_FDOUBLE_PRECISION*32.0)
#define newNTL_XD_HBOUND_LOG (newNTL_DOUBLE_PRECISION+4)

#else

#define newNTL_XD_HBOUND (double(1L << (newNTL_BITS_PER_LONG - 2))*64.0)
#define newNTL_XD_HBOUND_LOG (newNTL_BITS_PER_LONG+4)

#endif

#define newNTL_XD_HBOUND_INV (double(1)/newNTL_XD_HBOUND)

#define newNTL_XD_BOUND (newNTL_XD_HBOUND*newNTL_XD_HBOUND)
#define newNTL_XD_BOUND_INV (double(1)/newNTL_XD_BOUND)


class xdouble {

public:

double x;
long e;

xdouble() : x(0), e(0) { }

inline xdouble& operator=(double a);

~xdouble() { }

void normalize();

static long oprec;
static void SetOutputPrecision(long p);
static long OutputPrecision() { return oprec; }

double mantissa() const { return x; }
long exponent() const { return e; }

xdouble(double xx, long ee) : x(xx), e(ee) { } // internal use only

};

template<> inline xdouble to<xdouble>(int a) { return xdouble(a, 0); }
template<> inline xdouble to<xdouble>(long a) { return xdouble(a, 0); }
template<> inline xdouble to<xdouble>(unsigned int a) { return xdouble(a, 0); }
template<> inline xdouble to<xdouble>(unsigned long a) { return xdouble(a, 0); }

template<> xdouble to<xdouble>(double a);
template<> inline xdouble to<xdouble>(float a) { return to_xdouble(double(a)); }
template<> xdouble to<xdouble>(const char *a);


inline xdouble& xdouble::operator=(double a)
   { *this = to_xdouble(a); return *this; }

xdouble operator+(const xdouble& a, const xdouble& b);
inline xdouble operator+(const xdouble& a, double b)
   { return a + to_xdouble(b); }
inline xdouble operator+(double a, const xdouble& b)
   { return to_xdouble(a) + b; }

xdouble operator-(const xdouble& a, const xdouble& b);
inline xdouble operator-(const xdouble& a, double b)
   { return a - to_xdouble(b); }
inline xdouble operator-(double a, const xdouble& b)
   { return to_xdouble(a) - b; }

xdouble operator*(const xdouble& a, const xdouble& b);
inline xdouble operator*(const xdouble& a, double b)
   { return a * to_xdouble(b); }
inline xdouble operator*(double a, const xdouble& b)
   { return to_xdouble(a) * b; }

xdouble operator/(const xdouble& a, const xdouble& b);
inline xdouble operator/(const xdouble& a, double b)
   { return a / to_xdouble(b); }
inline xdouble operator/(double a, const xdouble& b)
   { return to_xdouble(a) / b; }

xdouble operator-(const xdouble& a);



inline xdouble& operator+=(xdouble& a, const xdouble& b) 
   { a = a + b; return a; }
inline xdouble& operator+=(xdouble& a, double b)
   { a = a + b; return a; }

inline xdouble& operator-=(xdouble& a, const xdouble& b) 
   { a = a - b; return a; }
inline xdouble& operator-=(xdouble& a, double b) 
   { a = a - b; return a; }

inline xdouble& operator*=(xdouble& a, const xdouble& b) 
   { a = a * b; return a; }
inline xdouble& operator*=(xdouble& a, double b) 
   { a = a * b; return a; }

inline xdouble& operator/=(xdouble& a, const xdouble& b) 
   { a = a / b; return a; }
inline xdouble& operator/=(xdouble& a, double b) 
   { a = a / b; return a; }

inline xdouble& operator++(xdouble& a) { a = a + to_xdouble(1); return a; }
inline xdouble& operator--(xdouble& a) { a = a - to_xdouble(1); return a; }

inline void operator++(xdouble& a, int) { a = a + to_xdouble(1); }
inline void operator--(xdouble& a, int) { a = a - to_xdouble(1); }

long compare(const xdouble& a, const xdouble& b);
inline long compare(const xdouble& a, double b)
   { return compare(a, to_xdouble(b)); }
inline long compare(double a, const xdouble& b)
   { return compare(to_xdouble(a), b); }

long sign(const xdouble& a);

inline long operator==(const xdouble& a, const xdouble& b) 
   { return compare(a, b) == 0; }
inline long operator!=(const xdouble& a, const xdouble& b) 
   { return compare(a, b) != 0; }
inline long operator<=(const xdouble& a, const xdouble& b) 
   { return compare(a, b) <= 0; }
inline long operator>=(const xdouble& a, const xdouble& b) 
   { return compare(a, b) >= 0; }
inline long operator <(const xdouble& a, const xdouble& b) 
   { return compare(a, b)  < 0; }
inline long operator >(const xdouble& a, const xdouble& b) 
   { return compare(a, b)  > 0; }

inline long operator==(const xdouble& a, double b) 
   { return compare(a, b) == 0; }
inline long operator!=(const xdouble& a, double b) 
   { return compare(a, b) != 0; }
inline long operator<=(const xdouble& a, double b) 
   { return compare(a, b) <= 0; }
inline long operator>=(const xdouble& a, double b) 
   { return compare(a, b) >= 0; }
inline long operator <(const xdouble& a, double b) 
   { return compare(a, b)  < 0; }
inline long operator >(const xdouble& a, double b) 
   { return compare(a, b)  > 0; }

inline long operator==(double a, const xdouble& b) 
   { return compare(a, b) == 0; }
inline long operator!=(double a, const xdouble& b) 
   { return compare(a, b) != 0; }
inline long operator<=(double a, const xdouble& b) 
   { return compare(a, b) <= 0; }
inline long operator>=(double a, const xdouble& b) 
   { return compare(a, b) >= 0; }
inline long operator <(double a, const xdouble& b) 
   { return compare(a, b)  < 0; }
inline long operator >(double a, const xdouble& b) 
   { return compare(a, b)  > 0; }


void conv(ZZ& x, const xdouble& a);
// x = floor(a);

template<> inline ZZ to<ZZ>(const xdouble& a)
   { ZZ x; conv(x, a); newNTL_OPT_RETURN(ZZ, x); }



template<> xdouble to<xdouble>(const ZZ& a);
inline void conv(xdouble& z, const ZZ& a)
   { z = to_xdouble(a); }

void conv(double& x, const xdouble& a);
template<> inline double to<double>(const xdouble& a)
   { double z; conv(z, a); return z; }

inline void conv(float& x, const xdouble& a) 
   { double t; conv(t, a); x = float(t); }
template<> inline float to<float>(const xdouble& a)
   { float z; conv(z, a); return z; }


inline void conv(long& x, const xdouble& a)
   { double z; conv(z, a); x = long(newNTL_SNS floor(z)); }
template<> inline long to<long>(const xdouble& a)
   { long z; conv(z, a); return z; }




inline void conv(int& x, const xdouble& a)
   { double z; conv(z, a); x = int(newNTL_SNS floor(z)); }
template<> inline int to<int>(const xdouble& a)
   { int z; conv(z, a); return z; }

inline void conv(xdouble& x, const xdouble& a)
   { x = a; }
template<> inline xdouble to<xdouble>(const xdouble& a)
   { return a; }


inline void conv(xdouble& x, int a) { x = to_xdouble(a); }
inline void conv(xdouble& x, long a) { x = to_xdouble(a); }

inline void conv(xdouble& x, unsigned int a) { x = to_xdouble(a); }
inline void conv(xdouble& x, unsigned long a) { x = to_xdouble(a); }

inline void conv(xdouble& x, float a) { x = to_xdouble(a); }
inline void conv(xdouble& x, double a) { x = to_xdouble(a); }
inline void conv(xdouble& x, const char *a) { x = to_xdouble(a); }

newNTL_SNS ostream& operator<<(newNTL_SNS ostream& s, const xdouble& a);

newNTL_SNS istream& operator>>(newNTL_SNS istream& s, xdouble& x);

xdouble trunc(const xdouble& a);
xdouble floor(const xdouble& a);
xdouble ceil(const xdouble& a);
xdouble fabs(const xdouble& a);
xdouble sqrt(const xdouble& a);

void power(xdouble& z, const xdouble& a, const ZZ& e);
inline xdouble power(const xdouble& a, const ZZ& e)
   { xdouble z; power(z, a, e); return z; }

void power(xdouble& z, const xdouble& a, long e);
inline xdouble power(const xdouble& a, long e)
   { xdouble z; power(z, a, e); return z; }

void power2(xdouble& z, long e);
inline xdouble power2_xdouble(long e)
   { xdouble z; power2(z, e); return z; }


void MulAdd(xdouble& z, const xdouble& a, const xdouble& b, const xdouble& c);
inline xdouble MulAdd(const xdouble& a, const xdouble& b, 
                            const xdouble& c)
   { xdouble z; MulAdd(z, a, b, c); return z; }


void MulSub(xdouble& z, const xdouble& a, const xdouble& b, const xdouble& c);
inline xdouble MulSub(const xdouble& a, const xdouble& b, 
                            const xdouble& c)
   { xdouble z; MulSub(z, a, b, c); return z; }

double log(const xdouble& a);
xdouble xexp(double x);

newNTL_CLOSE_NNS

#endif
