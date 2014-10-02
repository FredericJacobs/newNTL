
#ifndef newNTL_quad_float__H
#define newNTL_quad_float__H


/*
Copyright (C) 1997, 1998, 1999, 2000 Victor Shoup

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*****************************************************

The quad_float package is derived from the doubledouble package of
Keith Briggs.  However, the version employed in newNTL has been extensively 
modified.  Below, I attach the copyright notice from the original
doubledouble package, which is currently available at 

   http://www.labs.bt.com/people/briggsk2

*****************************************************

Copyright (C) 1997 Keith Martin Briggs

Except where otherwise indicated,
this program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <newNTL/ZZ.h>

newNTL_OPEN_NNS


class quad_float {
public:
  double hi, lo;

  // Constructors
  quad_float() : hi(0), lo(0)  {}

  inline quad_float& operator=(double x);

  static long oprec;
  static void SetOutputPrecision(long p);
  static long OutputPrecision() { return oprec; }

  quad_float(double x, double y) : hi(x), lo(y) { } // internal use only

  ~quad_float() {}

};  // end class quad_float

#if (newNTL_BITS_PER_LONG < newNTL_DOUBLE_PRECISION)

template<> inline quad_float to<quad_float>(long n) { return quad_float(n, 0); }
template<> inline quad_float to<quad_float>(unsigned long n) { return quad_float(n, 0); }

#else

template<> quad_float to<quad_float>(long n);
template<> quad_float to<quad_float>(unsigned long n);

#endif

#if (newNTL_BITS_PER_INT < newNTL_DOUBLE_PRECISION)

template<> inline quad_float to<quad_float>(int n) { return quad_float(n, 0); }
template<> inline quad_float to<quad_float>(unsigned int n) { return quad_float(n, 0); }
 
#else

template<> inline quad_float to<quad_float>(int n) 
   { return to_quad_float(long(n)); }
template<> inline quad_float to<quad_float>(unsigned int n) 
   { return to_quad_float((unsigned long) n); }

#endif



template<> inline quad_float to<quad_float>(double x) { return quad_float(x, 0); }
// On platforms with extended doubles, this may result in an
// improper quad_float object, but it should be converted to a proper
// one when passed by reference to any of the arithmetic routines,
// at which time x will be forced to memory.

template<> inline quad_float to<quad_float>(float x) 
   { return to_quad_float(double(x)); }

inline quad_float& quad_float::operator=(double x) 
   { *this = to_quad_float(x); return *this; }

quad_float operator+(const quad_float&, const quad_float& );

inline quad_float operator+(const quad_float& x, double y )
   { return x + to_quad_float(y); }

inline quad_float operator+(double x, const quad_float& y)
   { return to_quad_float(x) + y; }

quad_float operator-(const quad_float&, const quad_float& );

inline quad_float operator-(const quad_float& x, double y )
   { return x - to_quad_float(y); }

inline quad_float operator-(double x, const quad_float& y)
   { return to_quad_float(x) - y; }

quad_float operator*(const quad_float&, const quad_float& );

inline quad_float operator*(const quad_float& x, double y )
   { return x * to_quad_float(y); }

inline quad_float operator*(double x, const quad_float& y)
   { return to_quad_float(x) * y; }

quad_float operator/(const quad_float&, const quad_float& );

inline quad_float operator/(const quad_float& x, double y )
   { return x / to_quad_float(y); }

inline quad_float operator/(double x, const quad_float& y)
   { return to_quad_float(x) / y; }

quad_float operator-(const quad_float& x);

quad_float& operator+= (quad_float& x, const quad_float& y);
inline quad_float& operator += (quad_float& x, double y)
   { x += to_quad_float(y); return x; }

quad_float& operator-= (quad_float& x, const quad_float& y);
inline quad_float& operator-= (quad_float& x, double y)
   { x -= to_quad_float(y); return x; }

quad_float& operator*= (quad_float& x, const quad_float& y);
inline quad_float& operator*= (quad_float& x, double y)
   { x *= to_quad_float(y); return x; }

quad_float& operator/= (quad_float& x, const quad_float& y);
inline quad_float& operator/= (quad_float& x, double y)
   { x /= to_quad_float(y); return x; }

inline quad_float& operator++(quad_float& a) { a += 1.0; return a; }
inline void operator++(quad_float& a, int) { a += 1.0; }

inline quad_float& operator--(quad_float& a) { a -= 1.0; return a; }
inline void operator--(quad_float& a, int) { a -= 1.0; }


long operator> (const quad_float& x, const quad_float& y);
long operator>=(const quad_float& x, const quad_float& y);
long operator< (const quad_float& x, const quad_float& y);
long operator<=(const quad_float& x, const quad_float& y);
long operator==(const quad_float& x, const quad_float& y);
long operator!=(const quad_float& x, const quad_float& y);

inline long operator> (const quad_float& x, double y) 
   { return x > to_quad_float(y); }
inline long operator> (double x, const quad_float& y)
   { return to_quad_float(x) > y; }

inline long operator>=(const quad_float& x, double y) 
   { return x >= to_quad_float(y); }
inline long operator>=(double x, const quad_float& y)
   { return to_quad_float(x) >= y; }

inline long operator< (const quad_float& x, double y) 
   { return x < to_quad_float(y); }
inline long operator< (double x, const quad_float& y)
   { return to_quad_float(x) < y; }

inline long operator<=(const quad_float& x, double y) 
   { return x <= to_quad_float(y); }
inline long operator<=(double x, const quad_float& y)
   { return to_quad_float(x) <= y; }

inline long operator!=(const quad_float& x, double y) 
   { return x != to_quad_float(y); }
inline long operator!=(double x, const quad_float& y)
   { return to_quad_float(x) != y; }

inline long operator==(const quad_float& x, double y) 
   { return x == to_quad_float(y); }
inline long operator==(double x, const quad_float& y)
   { return to_quad_float(x) == y; }


inline long sign(const quad_float& x){
  if (x.hi>0.0) return 1; else if (x.hi<0.0) return -1; else return 0;
}

long compare(const quad_float&, const quad_float&);

inline long compare(const quad_float& x, double y)
   { return compare(x, to_quad_float(y)); }

inline long compare(double x, const quad_float& y)
   { return compare(to_quad_float(x), y); }



newNTL_SNS istream& operator >> (newNTL_SNS istream&, quad_float&);
newNTL_SNS ostream& operator << (newNTL_SNS ostream&, const quad_float&);


quad_float sqrt(const quad_float&);
quad_float floor(const quad_float&);
quad_float ceil(const quad_float&);
quad_float trunc(const quad_float&);
quad_float fabs(const quad_float&);

void power(quad_float&, const quad_float&, long);
inline quad_float power(const quad_float& x, long e)
   { quad_float z; power(z, x, e); return z; }

void power2(quad_float&, long);
inline quad_float power2_quad_float(long e)
   { quad_float z; power2(z, e); return z; }


template<> long to<long>(const quad_float&);
template<> inline int to<int>(const quad_float& x) { return to_int(to_long(x)); }

template<> inline double to<double>(const quad_float& x) { return x.hi; }

template<> inline float to<float>(const quad_float& x) { return float(x.hi); }


inline void conv(quad_float& x, int a) { x = to_quad_float(a); }
inline void conv(quad_float& x, long a) { x = to_quad_float(a); }

inline void conv(quad_float& x, unsigned int a) { x = to_quad_float(a); }
inline void conv(quad_float& x, unsigned long a) { x = to_quad_float(a); }

inline void conv(quad_float& x, float a) { x = to_quad_float(a); }
inline void conv(quad_float& x, double a) { x = to_quad_float(a); }


inline void conv(long& x, const quad_float& a) { x = to_long(a); }
inline void conv(int& x, const quad_float& a) { x = to_int(a); }
inline void conv(double& x, const quad_float& a) { x = to_double(a); }
inline void conv(float& x, const quad_float& a) { x = to_float(a); }

void conv(quad_float&, const ZZ&);
template<> inline quad_float to<quad_float>(const ZZ& x)
   { quad_float z; conv(z, x); return z; }

void conv(ZZ&, const quad_float&);
template<> inline ZZ to<ZZ>(const quad_float& a)
   { ZZ x; conv(x, a); newNTL_OPT_RETURN(ZZ, x); }

inline void conv(quad_float& x, const quad_float& a)
   { x = a; }
template<> inline quad_float to<quad_float>(const quad_float& a)
   { return a; }

template<> quad_float to<quad_float>(const char *s);
inline void conv(quad_float& x, const char *s)
   { x = to_quad_float(s); }

long IsFinite(quad_float *x);

long PrecisionOK();

quad_float ldexp(const quad_float& x, long exp);

quad_float exp(const quad_float& x);
quad_float log(const quad_float& x);

void random(quad_float& x);
quad_float random_quad_float();


newNTL_CLOSE_NNS

#endif
