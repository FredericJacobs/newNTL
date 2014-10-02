
#ifndef newNTL_tools__H
#define newNTL_tools__H

#include <newNTL/ctools.h>

#if (defined(newNTL_STD_CXX) || defined(newNTL_PSTD_NHF))

// new header files

#include <cstdlib>
#include <cmath>
#include <iostream>

#else

// old header files

#include <stdlib.h>
#include <math.h>
#include <iostream.h>

#endif

#if (defined(newNTL_STD_CXX) || defined(newNTL_PSTD_NHF))

#define newNTL_SNS std ::
#define newNTL_USE_SNS using namespace std;

#elif (defined(newNTL_PSTD_NNS))

#define newNTL_SNS ::
#define newNTL_USE_SNS 

#else

#define newNTL_SNS 
#define newNTL_USE_SNS 

#endif

#if (defined(newNTL_STD_CXX) || defined(newNTL_PSTD_NNS))

#define newNTL_NAMESPACE newNTL
#define newNTL_OPEN_NNS namespace newNTL_NAMESPACE {
#define newNTL_CLOSE_NNS  }
#define newNTL_USE_NNS using namespace newNTL_NAMESPACE;
#define newNTL_NNS newNTL_NAMESPACE ::

// To make things work, we have to apply using declarations of all std
// functions that are both overloaded by newNTL and are used in
// the implementation of newNTL.

#define newNTL_START_IMPL newNTL_USE_SNS newNTL_OPEN_NNS \
   using newNTL_SNS abs; \
   using newNTL_SNS ceil; \
   using newNTL_SNS exp; \
   using newNTL_SNS fabs; \
   using newNTL_SNS floor; \
   using newNTL_SNS ldexp; \
   using newNTL_SNS log; \
   using newNTL_SNS sqrt; 

#define newNTL_END_IMPL newNTL_CLOSE_NNS

#else

#define newNTL_NAMESPACE 
#define newNTL_OPEN_NNS 
#define newNTL_CLOSE_NNS 
#define newNTL_USE_NNS 
#define newNTL_NNS 

#define newNTL_START_IMPL
#define newNTL_END_IMPL

#endif

#define newNTL_CLIENT newNTL_USE_SNS newNTL_USE_NNS



#if 0

// This is for debugging purposes only.

namespace foo_bar {

class ostream;
class istream;

typedef unsigned int size_t;

double floor(double);
float floor(float);

}
#endif



#if (!defined(newNTL_CXX_ONLY)) 
extern "C"
#endif
double _newntl_GetTime();

typedef unsigned long _newntl_ulong;
typedef _newntl_ulong *_newntl_ulong_ptr;
// I made these have "obscure" names to avoid conflict with
// (non-standard but common) definitions in standard headers.
// Putting u_long inside namespace newNTL only tends to creates ambiguities,
// for no good reason.



newNTL_OPEN_NNS

extern void (*ErrorCallback)();

struct INIT_SIZE_STRUCT { };
const INIT_SIZE_STRUCT INIT_SIZE = INIT_SIZE_STRUCT();
typedef const INIT_SIZE_STRUCT& INIT_SIZE_TYPE;

struct INIT_VAL_STRUCT { };
const INIT_VAL_STRUCT INIT_VAL = INIT_VAL_STRUCT();
typedef const INIT_VAL_STRUCT& INIT_VAL_TYPE;

struct INIT_TRANS_STRUCT { };
const INIT_TRANS_STRUCT INIT_TRANS = INIT_TRANS_STRUCT();
typedef const INIT_TRANS_STRUCT& INIT_TRANS_TYPE;


struct INIT_LOOP_HOLE_STRUCT { };
const INIT_LOOP_HOLE_STRUCT INIT_LOOP_HOLE = INIT_LOOP_HOLE_STRUCT();
typedef const INIT_LOOP_HOLE_STRUCT& INIT_LOOP_HOLE_TYPE;

struct INIT_FFT_STRUCT { };
const INIT_FFT_STRUCT INIT_FFT = INIT_FFT_STRUCT();
typedef const INIT_FFT_STRUCT& INIT_FFT_TYPE;


#ifdef newNTL_NO_INIT_TRANS
#define newNTL_OPT_RETURN(t, x) return x
#else
#define newNTL_OPT_RETURN(t, x) return t(x, INIT_TRANS)
#endif


#ifndef newNTL_NO_MIN_MAX

inline int min(int a, int b) { return (a < b) ?  a : b; } 
inline int max(int a, int b) { return (a < b) ? b : a; }

inline long min(long a, long b) { return (a < b) ?  a : b; } 
inline long max(long a, long b) { return (a < b) ? b : a; }

inline long min(int a, long b) { return (a < b) ?  long(a) : b; } 
inline long max(int a, long b) { return (a < b) ? b : long(a); }

inline long min(long a, int b) { return (a < b) ?  a : long(b); } 
inline long max(long a, int b) { return (a < b) ? long(b) : a; }

#endif


inline void swap(long& a, long& b)  {  long t;  t = a; a = b; b = t; }
inline void swap(int& a, int& b)  {  int t;  t = a; a = b; b = t; }
inline void swap(double& a, double& b)  {  double t;  t = a; a = b; b = t; }
inline void swap(float& a, float& b)  {  float t;  t = a; a = b; b = t; }


//the expression: 
//  ifAneqBthenT<A,B,T>::type 
//is equal to T if and only if the types A and B differ
//else, it is undefined (and allows to discard templates)
template <typename A, typename B, typename T>
struct ifAneqBthenT {
  typedef T type;
};

template <typename A, typename T>
struct ifAneqBthenT<A, A, T> {};

//conversion templates
template <typename T,typename U> inline T to(const U& x);
template <typename T> inline T to(const char* x);
template <typename T> inline T to(double x);
template <typename T> inline T to(float x);
template <typename T> inline T to(int x);
template <typename T> inline T to(long x);
template <typename T> inline T to(unsigned int x);
template <typename T> inline T to(unsigned long x);

#define to_double to<double>
#define to_float to<float>
#define to_int to<int>
#define to_long to<long>
#define to_mat_zz_p to<mat_zz_p>
#define to_mat_ZZ_p to<mat_ZZ_p>
#define to_quad_float to<quad_float>
#define to_RR to<RR>
#define to_uint to<unsigned int>
#define to_ulong to<unsigned long>
#define to_vec_ZZ to<vec_ZZ>
#define to_vec_zz_p to<vec_zz_p>
#define to_vec_ZZ_p to<vec_ZZ_p>
#define to_xdouble to<xdouble>
#define to_ZZ to<ZZ>
#define to_zz_p to<zz_p>
#define to_ZZ_p to<ZZ_p>
#define to_zz_pE to<zz_pE>
#define to_ZZ_pE to<ZZ_pE>
#define to_zz_pEX to<zz_pEX>
#define to_ZZ_pEX to<ZZ_pEX>
#define to_zz_pX to<zz_pX>
#define to_ZZ_pX to<ZZ_pX>
#define to_ZZX to<ZZX>


inline void conv(int& x, int a) { x = a; }
inline void conv(int& x, long a) 
   { unsigned y = (unsigned) a;  x = newNTL_UINT_TO_INT(y); }
inline void conv(int& x, float a) { x = int(newNTL_SNS floor(double(a))); }
inline void conv(int& x, double a) { x = int(newNTL_SNS floor(a)); }

inline void conv(int& x, unsigned a) 
   { x = newNTL_UINT_TO_INT(a); }

inline void conv(int& x, unsigned long a)
   { unsigned y = (unsigned) a;  x = newNTL_UINT_TO_INT(y); }

template<> inline int to_int(int a) { return a; }
template<> inline int to_int(long a) 
   { unsigned y = (unsigned) a;  return newNTL_UINT_TO_INT(y); }
template<> inline int to_int(float a) { return int(newNTL_SNS floor(double(a))); }
template<> inline int to_int(double a) { return int(newNTL_SNS floor(a)); }

template<> inline int to_int(unsigned a) 
   { return newNTL_UINT_TO_INT(a); }

template<> inline int to_int(unsigned long a) 
   { unsigned y = (unsigned) a;  return newNTL_UINT_TO_INT(y); }


inline void conv(long& x, int a) { x = a; }
inline void conv(long& x, long a) { x = a; }
inline void conv(long& x, float a) { x = long(newNTL_SNS floor(double(a))); }
inline void conv(long& x, double a) { x = long(newNTL_SNS floor(a)); }

inline void conv(long& x, unsigned a)
   { unsigned long y = a;  x = newNTL_ULONG_TO_LONG(y); }

inline void conv(long& x, unsigned long a)
   { x = newNTL_ULONG_TO_LONG(a); }

template<> inline long to_long(int a) { return a; }
template<> inline long to_long(long a) { return a; }
template<> inline long to_long(float a) { return long(newNTL_SNS floor(double(a))); }
template<> inline long to_long(double a) { return long(newNTL_SNS floor(a)); }

template<> inline long to_long(unsigned a)
   { unsigned long y = a;  return newNTL_ULONG_TO_LONG(y); }

template<> inline long to_long(unsigned long a)
   { return newNTL_ULONG_TO_LONG(a); }

inline void conv(float& x, int a) { x = float(a); }
inline void conv(float& x, long a) { x = float(a); }
inline void conv(float& x, unsigned a) { x = float(a); }
inline void conv(float& x, unsigned long a) { x = float(a); }
inline void conv(float& x, float a) { x = a; }
inline void conv(float& x, double a) { x = float(a); }

template<> inline float to_float(int a) { return float(a); }
template<> inline float to_float(long a) { return float(a); }
template<> inline float to_float(unsigned a) { return float(a); }
template<> inline float to_float(unsigned long a) { return float(a); }
template<> inline float to_float(float a) { return a; }
template<> inline float to_float(double a) { return float(a); }

inline void conv(double& x, int a) { x = double(a); }
inline void conv(double& x, long a) { x = double(a); }
inline void conv(double& x, unsigned a) { x = double(a); }
inline void conv(double& x, unsigned long a) { x = double(a); }
inline void conv(double& x, float a) { x = double(a); }
inline void conv(double& x, double a) { x = a; }

template<> inline double to_double(int a) { return double(a); }
template<> inline double to_double(long a) { return double(a); }
template<> inline double to_double(unsigned a) { return double(a); }
template<> inline double to_double(unsigned long a) { return double(a); }
template<> inline double to_double(float a) { return double(a); }
template<> inline double to_double(double a) { return a; }

#define BASE_FLOAT_ARITHMETIC(FLOAT) \
inline void add(FLOAT& x,FLOAT y,FLOAT z) {x=y+z;} \
inline void mul(FLOAT& x,FLOAT y,FLOAT z) {x=y*z;} \
inline void sub(FLOAT& x,FLOAT y,FLOAT z) {x=y-z;} \
inline void div(FLOAT& x,FLOAT y,FLOAT z) {x=y/z;} \
inline void negate(FLOAT& x,FLOAT y) {x=-y;} \
inline void clear(FLOAT& d) {d=0.;} \
inline bool IsZero(FLOAT d) {return (d==0. || d==-0.);}

#define BASE_INT_ARITHMETIC(INTEGER) \
inline void add(INTEGER& x,INTEGER y,INTEGER z) {x=y+z;} \
inline void mul(INTEGER& x,INTEGER y,INTEGER z) {x=y*z;} \
inline void sub(INTEGER& x,INTEGER y,INTEGER z) {x=y-z;} \
inline void div(INTEGER& x,INTEGER y,INTEGER z) {x=y/z;} \
inline void negate(INTEGER& x,INTEGER y) {x=-y;} \
inline void clear(INTEGER& d) {d=0;} \
inline bool IsZero(INTEGER d) {return d==0;}

BASE_INT_ARITHMETIC(long);
BASE_INT_ARITHMETIC(int);
BASE_INT_ARITHMETIC(unsigned);
BASE_INT_ARITHMETIC(unsigned long);
BASE_FLOAT_ARITHMETIC(float);
BASE_FLOAT_ARITHMETIC(double);    


long SkipWhiteSpace(newNTL_SNS istream& s);
long IsWhiteSpace(long c);
long IsEOFChar(long c);

long CharToIntVal(long c);
char IntValToChar(long a);



void Error(const char *s);
void failwith(const char *s);
#define newNTL_assert assert


inline double GetTime() { return _newntl_GetTime(); }

inline long IsFinite(double *p) { return _newntl_IsFinite(p); }


#if (newNTL_EXT_DOUBLE)

inline void ForceToMem(double *p) { _newntl_ForceToMem(p); }

#else

inline void ForceToMem(double *p) { }

#endif



void PrintTime(newNTL_SNS ostream& s, double t);

newNTL_CLOSE_NNS


#endif

