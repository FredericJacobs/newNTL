#ifndef newNTL_RR__H
#define newNTL_RR__H

#include <newNTL/ZZ.h>
#include <newNTL/xdouble.h>
#include <newNTL/quad_float.h>
#include <mpfr.h>

newNTL_OPEN_NNS


class RR {
  public:
    mpfr_t* rep;


  private:
    static int initialize_prec_150();
    static int default_precision_initialized; 
    
    inline void init_nan() {
      rep = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init(*rep);
    }
    inline void init_copy(const RR& a) {
      rep = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init2(*rep, mpfr_get_prec(*a.rep));
      mpfr_set(*rep,*a.rep,MPFR_RNDN);
    }
    inline void init_0() {
      rep = (mpfr_t*) malloc(sizeof(mpfr_t));
      mpfr_init_set_si(*rep,0,MPFR_RNDN);
    }
    inline void destroy() {
      if (rep) 
      {
        mpfr_clear(*rep);
        free(rep);
      }
    }
  public:

//ZZ x;
//long e;

RR() {  init_0(); }

inline RR(INIT_VAL_TYPE, const ZZ& a);
inline RR(INIT_VAL_TYPE, int a);
inline RR(INIT_VAL_TYPE, long a);
inline RR(INIT_VAL_TYPE, unsigned int a);
inline RR(INIT_VAL_TYPE, unsigned long a);
inline RR(INIT_VAL_TYPE, float a);
inline RR(INIT_VAL_TYPE, double a);
inline RR(INIT_VAL_TYPE, const xdouble& a);
inline RR(INIT_VAL_TYPE, const quad_float& a);
inline RR(INIT_VAL_TYPE, const char *a);  // read from string
inline RR(INIT_VAL_TYPE, const RR& a);

inline RR(const ZZ& a);
inline RR(int a);
inline RR(long a);
inline RR(unsigned int a);
inline RR(unsigned long a);
inline RR(float a);
inline RR(double a);
inline RR(const xdouble& a);
inline RR(const quad_float& a);
inline RR(const char *a);  // read from string
inline RR(const RR& a);


inline RR& operator=(double a);
inline RR& operator=(const RR& a);

inline RR(RR& z, INIT_TRANS_TYPE) { rep = z.rep; z.rep = 0; }
inline ~RR() { destroy(); }

//const ZZ& mantissa() const { return x; }
//long exponent() const { return e; }

static inline void SetPrecision(long p) {mpfr_set_default_prec(p);}
static inline long precision() { return mpfr_get_default_prec(); }

static long oprec;
static void SetOutputPrecision(long p);
static inline long OutputPrecision() { return oprec; }

};


inline long IsZero(const RR& a) { return mpfr_zero_p(*a.rep); }
inline long IsOne(const RR& a) { return mpfr_cmp_si(*a.rep,1)==0; }
inline long sign(const RR& a) { return mpfr_sgn(*a.rep); }
inline void clear(RR& z) { mpfr_set_prec(*z.rep,mpfr_get_default_prec()); mpfr_set_si(*z.rep,0, MPFR_RNDN); }
inline void set(RR& z) { mpfr_set_prec(*z.rep,mpfr_get_default_prec()); mpfr_set_si(*z.rep,1, MPFR_RNDN); }
inline void swap(RR& a, RR& b) { mpfr_t* tmp = a.rep; a.rep=b.rep; b.rep=tmp; }

inline void add(RR& z, const RR& a, const RR& b) { mpfr_add(*z.rep, *a.rep, *b.rep, MPFR_RNDN); }

inline void add(RR& z, const RR& a, double b) {mpfr_add_d(*z.rep, *a.rep, b, MPFR_RNDN); }
inline void add(RR& z, double a, const RR& b) { add(z, b, a); }



inline void sub(RR& z, const RR& a, const RR& b) { mpfr_sub(*z.rep, *a.rep, *b.rep, MPFR_RNDN); }
inline void sub(RR& z, const RR& a, double b) { mpfr_sub_d(*z.rep, *a.rep, b, MPFR_RNDN); }
inline void sub(RR& z, double a, const RR& b) { mpfr_d_sub(*z.rep, a, *b.rep, MPFR_RNDN); }

inline void negate(RR& z, const RR& a) { mpfr_neg(*z.rep, *a.rep, MPFR_RNDN); }

inline void abs(RR& z, const RR& a) { mpfr_abs(*z.rep, *a.rep, MPFR_RNDN); }
inline RR abs(const RR& a) { RR z; abs(z, a); newNTL_OPT_RETURN(RR, z); }
inline RR fabs(const RR& a) { RR z; abs(z, a); newNTL_OPT_RETURN(RR, z); }

inline void mul(RR& z, const RR& a, const RR& b) { mpfr_mul(*z.rep, *a.rep, *b.rep, MPFR_RNDN); }
inline void mul(RR& z, const RR& a, double b) { mpfr_mul_d(*z.rep, *a.rep, b, MPFR_RNDN); }
inline void mul(RR& z, double a, const RR& b) { mpfr_mul_d(*z.rep, *b.rep, a, MPFR_RNDN); }

inline void sqr(RR& z, const RR& a) { mpfr_sqr(*z.rep, *a.rep, MPFR_RNDN); }
inline RR sqr(const RR& a) { RR z; sqr(z, a); newNTL_OPT_RETURN(RR, z); }

inline void div(RR& z, const RR& a, const RR& b) { mpfr_div(*z.rep, *a.rep, *b.rep, MPFR_RNDN); }
inline void div(RR& z, const RR& a, double b) { mpfr_div_d(*z.rep, *a.rep, b, MPFR_RNDN); }
inline void div(RR& z, double a, const RR& b) { mpfr_d_div(*z.rep, a, *b.rep, MPFR_RNDN); }

inline void inv(RR& z, const RR& a) { mpfr_ui_div(*z.rep, 1ul, *a.rep, MPFR_RNDN); }
inline RR inv(const RR& a) { RR z; inv(z, a); newNTL_OPT_RETURN(RR, z); }

// operator notation:

inline RR operator+(const RR& a, const RR& b) { RR x; add(x, a, b); newNTL_OPT_RETURN(RR, x); }
inline RR operator+(const RR& a, double b) { RR x; add(x, a, b); newNTL_OPT_RETURN(RR, x); }
inline RR operator+(double a, const RR& b) { RR x; add(x, a, b); newNTL_OPT_RETURN(RR, x); }
inline RR& operator+=(RR& x, const RR& b) { add(x, x, b); return x; } 
inline RR& operator+=(RR& x, double b) { add(x, x, b); return x; } 



inline RR operator-(const RR& a, const RR& b) { RR x; sub(x, a, b); newNTL_OPT_RETURN(RR, x); }
inline RR operator-(const RR& a, double b) { RR x; sub(x, a, b); newNTL_OPT_RETURN(RR, x); }
inline RR operator-(double a, const RR& b) { RR x; sub(x, a, b); newNTL_OPT_RETURN(RR, x); }
inline RR& operator-=(RR& x, const RR& b) { sub(x, x, b); return x; } 
inline RR& operator-=(RR& x, double b) { sub(x, x, b); return x; } 



inline RR operator*(const RR& a, const RR& b) { RR x; mul(x, a, b); newNTL_OPT_RETURN(RR, x); }
inline RR operator*(const RR& a, double b) { RR x; mul(x, a, b); newNTL_OPT_RETURN(RR, x); }
inline RR operator*(double a, const RR& b) { RR x; mul(x, a, b); newNTL_OPT_RETURN(RR, x); }
inline RR& operator*=(RR& x, const RR& b) { mul(x, x, b); return x; } 
inline RR& operator*=(RR& x, double b) { mul(x, x, b); return x; } 


inline RR operator/(const RR& a, const RR& b) { RR x; div(x, a, b); newNTL_OPT_RETURN(RR, x); }
inline RR operator/(const RR& a, double b) { RR x; div(x, a, b); newNTL_OPT_RETURN(RR, x); }
inline RR operator/(double a, const RR& b) { RR x; div(x, a, b); newNTL_OPT_RETURN(RR, x); }
inline RR& operator/=(RR& x, const RR& b) { div(x, x, b); return x; } 
inline RR& operator/=(RR& x, double b) { div(x, x, b); return x; } 


inline RR operator-(const RR& a) { RR x; negate(x, a); newNTL_OPT_RETURN(RR, x); }
inline RR& operator++(RR& x) { add(x, x, 1); return x; }
inline void operator++(RR& x, int) { add(x, x, 1); }
inline RR& operator--(RR& x) { sub(x, x, 1); return x; }
inline void operator--(RR& x, int) { sub(x, x, 1); }



inline long compare(const RR& a, const RR& b) { return mpfr_cmp(*a.rep, *b.rep); }

inline long compare(const RR& a, double b) { return mpfr_cmp_d(*a.rep, b); }
inline long compare(double a, const RR& b) { return -compare(b, a); }


inline long operator==(const RR& a, const RR& b) { return mpfr_cmp(*a.rep,*b.rep)==0; }
inline long operator!=(const RR& a, const RR& b) { return mpfr_cmp(*a.rep,*b.rep)!=0; }
inline long operator<=(const RR& a, const RR& b) { return mpfr_cmp(*a.rep,*b.rep)<=0; }
inline long operator>=(const RR& a, const RR& b) { return mpfr_cmp(*a.rep,*b.rep)>=0; }
inline long operator <(const RR& a, const RR& b) { return mpfr_cmp(*a.rep,*b.rep)< 0; }
inline long operator >(const RR& a, const RR& b) { return mpfr_cmp(*a.rep,*b.rep)> 0; }

inline long operator==(const RR& a, double b) { return compare(a, b) == 0; }
inline long operator!=(const RR& a, double b) { return compare(a, b) != 0; }
inline long operator<=(const RR& a, double b) { return compare(a, b) <= 0; }
inline long operator>=(const RR& a, double b) { return compare(a, b) >= 0; }
inline long operator <(const RR& a, double b) { return compare(a, b)  < 0; }
inline long operator >(const RR& a, double b) { return compare(a, b)  > 0; }

inline long operator==(double a, const RR& b) { return (b == a); }
inline long operator!=(double a, const RR& b) { return !(a == b); }
inline long operator<=(double a, const RR& b) { return compare(a, b) <= 0; }
inline long operator>=(double a, const RR& b) { return compare(a, b) >= 0; }
inline long operator <(double a, const RR& b) { return compare(a, b)  < 0; }
inline long operator >(double a, const RR& b) { return compare(a, b)  > 0; }

inline void ceil(RR& z, const RR& a) { mpfr_rint_ceil(*z.rep, *a.rep, MPFR_RNDN); }
inline RR ceil(const RR& a) { RR z; ceil(z, a); newNTL_OPT_RETURN(RR, z); }

inline void floor(RR& z, const RR& a) { mpfr_rint_floor(*z.rep, *a.rep, MPFR_RNDN); }
inline RR floor(const RR& a) { RR z; floor(z, a); newNTL_OPT_RETURN(RR, z); }

inline void trunc(RR& z, const RR& a) { mpfr_rint_trunc(*z.rep, *a.rep, MPFR_RNDN); }
inline RR trunc(const RR& a) { RR z; trunc(z, a); newNTL_OPT_RETURN(RR, z); }

inline void round(RR& z, const RR& a) { mpfr_rint_round(*z.rep, *a.rep, MPFR_RNDN); }
inline RR round(const RR& a) { RR z; round(z, a); newNTL_OPT_RETURN(RR, z); }

inline void RoundToPrecision(RR& z, const RR& a, long p) { mpfr_set_prec(*z.rep, p); mpfr_set(*z.rep, *a.rep, MPFR_RNDN); }
inline RR RoundToPrecision(const RR& a, long p) { RR z; RoundToPrecision(z, a, p); newNTL_OPT_RETURN(RR, z); }


// routines with a precision parameter

inline void ConvPrec(RR& z, const RR& a, long p) { mpfr_set_prec(*z.rep, p); mpfr_set(*z.rep, *a.rep, MPFR_RNDN); }
inline RR ConvPrec(const RR& a, long p) { RR z; ConvPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void AddPrec(RR& z, const RR& a, const RR& b, long p);
inline RR AddPrec(const RR& a, const RR& b, long p) { RR z; AddPrec(z, a, b, p); newNTL_OPT_RETURN(RR, z); }

void SubPrec(RR& z, const RR& a, const RR& b, long p);
inline RR SubPrec(const RR& a, const RR& b, long p) { RR z; SubPrec(z, a, b, p); newNTL_OPT_RETURN(RR, z); }

void NegatePrec(RR& z, const RR& a, long p);
inline RR NegatePrec(const RR& a, long p) { RR z; NegatePrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void AbsPrec(RR& z, const RR& a, long p);
inline RR AbsPrec(const RR& a, long p) { RR z; AbsPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void MulPrec(RR& z, const RR& a, const RR& b, long p);
inline RR MulPrec(const RR& a, const RR& b, long p) { RR z; MulPrec(z, a, b, p); newNTL_OPT_RETURN(RR, z); }

void SqrPrec(RR& z, const RR& a, long p);
inline RR SqrPrec(const RR& a, long p) { RR z; SqrPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void DivPrec(RR& z, const RR& a, const RR& b, long p);
inline RR DivPrec(const RR& a, const RR& b, long p) { RR z; DivPrec(z, a, b, p); newNTL_OPT_RETURN(RR, z); }

void InvPrec(RR& z, const RR& a, long p);
inline RR InvPrec(const RR& a, long p) { RR z; InvPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void SqrRootPrec(RR& z, const RR& a, long p);
inline RR SqrRootPrec(const RR& a, long p) { RR z; SqrRootPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void TruncPrec(RR& z, const RR& a, long p);
inline RR TruncPrec(const RR& a, long p) { RR z; TruncPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void FloorPrec(RR& z, const RR& a, long p);
inline RR FloorPrec(const RR& a, long p) { RR z; FloorPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void CeilPrec(RR& z, const RR& a, long p);
inline RR CeilPrec(const RR& a, long p) { RR z; CeilPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void RoundPrec(RR& z, const RR& a, long p);
inline RR RoundPrec(const RR& a, long p) { RR z; RoundPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void ConvPrec(RR& z, const ZZ& a, long p);
inline RR ConvPrec(const ZZ& a, long p) { RR z; ConvPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void ConvPrec(RR& z, long a, long p);
inline RR ConvPrec(long a, long p) { RR z; ConvPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

inline void ConvPrec(RR& z, int a, long p) { ConvPrec(z, long(a), p); }
inline RR ConvPrec(int a, long p) { RR z; ConvPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void ConvPrec(RR& z, unsigned long a, long p);
inline RR ConvPrec(unsigned long a, long p) { RR z; ConvPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

inline void ConvPrec(RR& z, unsigned int a, long p)  { ConvPrec(z, (unsigned long)(a), p); }
inline RR ConvPrec(unsigned int a, long p) { RR z; ConvPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void ConvPrec(RR& z, double a, long p);
inline RR ConvPrec(double a, long p) { RR z; ConvPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void ConvPrec(RR& z, const xdouble& a, long p);
inline RR ConvPrec(const xdouble& a, long p) { RR z; ConvPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void ConvPrec(RR& z, const quad_float& a, long p);
inline RR ConvPrec(const quad_float& a, long p) { RR z; ConvPrec(z, a, p); newNTL_OPT_RETURN(RR, z); }

void ConvPrec(RR& z, const char *s, long p);
inline RR ConvPrec(const char *s, long p) { RR z; ConvPrec(z, s, p); newNTL_OPT_RETURN(RR, z); }

void InputPrec(RR& z, newNTL_SNS istream& s, long p);
inline RR InputPrec(newNTL_SNS istream& s, long p) { RR z; InputPrec(z, s, p); newNTL_OPT_RETURN(RR, z); }

void MakeRRPrec(RR& z, const ZZ& a, long e, long p);
inline RR MakeRRPrec(const ZZ& a, long e, long p) { RR z; MakeRRPrec(z, a, e, p); newNTL_OPT_RETURN(RR, z); }






void conv(RR& z, const ZZ& a);
void conv(RR& z, long a);
inline void conv(RR& z, int a) { conv(z, long(a)); }
void conv(RR& z, unsigned long a);
inline void conv(RR& z, unsigned int a) { conv(z, (unsigned long)(a)); }
void conv(RR& z, const char *s);
void conv(RR& z, double a);
inline void conv(RR& z, float a) { conv(z, double(a)); }
void conv(RR& z, const xdouble& a);
void conv(RR& z, const quad_float& a);

void conv(RR& z, const RR& a);



inline RR::RR(INIT_VAL_TYPE, int a) { init_nan(); mpfr_set_si(*rep, a,MPFR_RNDN); }
inline RR::RR(INIT_VAL_TYPE, long a) { init_nan(); mpfr_set_si(*rep, a,MPFR_RNDN); }
inline RR::RR(INIT_VAL_TYPE, unsigned int a) { init_nan(); mpfr_set_ui(*rep, a,MPFR_RNDN); }
inline RR::RR(INIT_VAL_TYPE, unsigned long a) { init_nan(); mpfr_set_ui(*rep, a,MPFR_RNDN); }
inline RR::RR(INIT_VAL_TYPE, float a) { init_nan(); mpfr_set_flt(*rep, a,MPFR_RNDN); }
inline RR::RR(INIT_VAL_TYPE, double a) { init_nan(); mpfr_set_d(*rep, a,MPFR_RNDN); }

inline RR::RR(INIT_VAL_TYPE, const RR& a) { init_copy(a); }
inline RR::RR(INIT_VAL_TYPE, const ZZ& a) { init_nan(); conv(*this, a); }
inline RR::RR(INIT_VAL_TYPE, const xdouble& a) { init_nan(); conv(*this, a); }
inline RR::RR(INIT_VAL_TYPE, const quad_float& a) { init_nan(); conv(*this, a); }
inline RR::RR(INIT_VAL_TYPE, const char *a) { init_nan(); mpfr_set_str(*rep,a,10,MPFR_RNDN); }

inline RR::RR(int a) { init_nan(); mpfr_set_si(*rep, a,MPFR_RNDN); }
inline RR::RR(long a) { init_nan(); mpfr_set_si(*rep, a,MPFR_RNDN); }
inline RR::RR(unsigned int a) { init_nan(); mpfr_set_ui(*rep, a,MPFR_RNDN); }
inline RR::RR(unsigned long a) { init_nan(); mpfr_set_ui(*rep, a,MPFR_RNDN); }
inline RR::RR(float a) { init_nan(); mpfr_set_flt(*rep, a,MPFR_RNDN); }
inline RR::RR(double a) { init_nan(); mpfr_set_d(*rep, a,MPFR_RNDN); }

inline RR::RR(const RR& a) { init_copy(a); }
inline RR::RR(const ZZ& a) { init_nan(); conv(*this, a); }
inline RR::RR(const xdouble& a) { init_nan(); conv(*this, a); }
inline RR::RR(const quad_float& a) { init_nan(); conv(*this, a); }
inline RR::RR(const char *a) { init_nan(); mpfr_set_str(*rep,a,10,MPFR_RNDN); }

template<> inline RR to<RR>(int a) { return RR(INIT_VAL, a); }
template<> inline RR to<RR>(long a) { return RR(INIT_VAL, a); }
template<> inline RR to<RR>(unsigned int a) { return RR(INIT_VAL, a); }
template<> inline RR to<RR>(unsigned long a) { return RR(INIT_VAL, a); }
template<> inline RR to<RR>(float a) { return RR(INIT_VAL, a); }
template<> inline RR to<RR>(double a) { return RR(INIT_VAL, a); }
template<> inline RR to<RR>(const ZZ& a) { return RR(INIT_VAL, a); }
template<> inline RR to<RR>(const RR& a) { return RR(INIT_VAL, a); }
template<> inline RR to<RR>(const xdouble& a) { return RR(INIT_VAL, a); }
template<> inline RR to<RR>(const quad_float& a) { return RR(INIT_VAL, a); }
template<> inline RR to<RR>(const char *a) { return RR(INIT_VAL, a); }

inline RR& RR::operator=(double a) { conv(*this, a); return *this; }
inline RR& RR::operator=(const RR& a) { conv(*this, a); return *this; }

void conv(RR& r, const RR& x);
void conv(ZZ& z, const RR& a);
void conv(long& z, const RR& a);
void conv(double& z, const RR& a);
void conv(xdouble& z, const RR& a);
void conv(quad_float& z, const RR& a);

inline void conv(int& z, const RR& a) 
   { long t; conv(t, a); z = int(t); }

inline void conv(float& z, const RR& a) 
   { double t; conv(t, a); z = float(t); }

template<> inline int to<int>(const RR& a) { int z; conv(z, a); return z; }
template<> inline long to<long>(const RR& a) { long z; conv(z, a); return z; }
template<> inline float to<float>(const RR& a) { float z; conv(z, a); return z; }
template<> inline double to<double>(const RR& a) { double z; conv(z, a); return z; }

template<> inline xdouble to<xdouble>(const RR& a) 
   { xdouble z; conv(z, a); return z; }
template<> inline quad_float to<quad_float>(const RR& a) 
   { quad_float z; conv(z, a); return z; }

template<> inline ZZ to<ZZ>(const RR& a) 
{ ZZ z; conv(z, a); newNTL_OPT_RETURN(ZZ, z); }

void CeilToZZ(ZZ& z, const RR& a);
inline ZZ CeilToZZ(const RR& a) { ZZ z; CeilToZZ(z, a); newNTL_OPT_RETURN(ZZ, z); }

void TruncToZZ(ZZ& z, const RR& a);
inline ZZ TruncToZZ(const RR& a) { ZZ z; TruncToZZ(z, a); newNTL_OPT_RETURN(ZZ, z); }

void RoundToZZ(ZZ& z, const RR& a);
inline ZZ RoundToZZ(const RR& a) { ZZ z; RoundToZZ(z, a); newNTL_OPT_RETURN(ZZ, z); }

inline void FloorToZZ(ZZ& z, const RR& a) { conv(z, a); }
inline ZZ FloorToZZ(const RR& a) { ZZ z; conv(z, a); newNTL_OPT_RETURN(ZZ, z); }

void MakeRR(RR& z, const ZZ& a,  long e);
inline RR MakeRR(const ZZ& a,  long e) { RR z; MakeRR(z, a, e); newNTL_OPT_RETURN(RR, z); }

void random(RR& z);
inline RR random_RR() { RR z; random(z); newNTL_OPT_RETURN(RR, z); }


inline void power(RR& z, const RR& a, long e) {mpfr_pow_si(*z.rep, *a.rep, e, MPFR_RNDN); }
inline RR power(const RR& a, long e) { RR z; power(z, a, e); newNTL_OPT_RETURN(RR, z); }

inline void power2(RR& z, long e) { mpfr_set_ui_2exp(*z.rep, 1ul,e, MPFR_RNDN); }
inline RR power2_RR(long e) { RR z; power2(z, e); newNTL_OPT_RETURN(RR, z); }

newNTL_SNS ostream& operator<<(newNTL_SNS ostream& s, const RR& a);
newNTL_SNS istream& operator>>(newNTL_SNS istream& s, RR& x);


inline void SqrRoot(RR& x, const RR& a) { mpfr_sqrt(*x.rep,*a.rep,MPFR_RNDN); }
inline RR SqrRoot(const RR& a) { RR z; SqrRoot(z, a); newNTL_OPT_RETURN(RR, z); }
inline RR sqrt(const RR& a) { RR z; SqrRoot(z, a); newNTL_OPT_RETURN(RR, z); }

inline void exp(RR& res, const RR& x) {mpfr_exp(*res.rep, *x.rep, MPFR_RNDN); }
inline RR exp(const RR& a) { RR z; exp(z, a); newNTL_OPT_RETURN(RR, z); }

inline void log(RR& res, const RR& x) { mpfr_log(*res.rep, *x.rep, MPFR_RNDN); }
inline RR log(const RR& a) { RR z; log(z, a); newNTL_OPT_RETURN(RR, z); }

inline void log10(RR& res, const RR& x) { mpfr_log10(*res.rep, *x.rep, MPFR_RNDN); }
inline RR log10(const RR& a) { RR z; log10(z, a); newNTL_OPT_RETURN(RR, z); }

inline void expm1(RR& res, const RR& x) { mpfr_expm1(*res.rep, *x.rep, MPFR_RNDN); }
inline RR expm1(const RR& a) { RR z; expm1(z, a); newNTL_OPT_RETURN(RR, z); }

inline void log1p(RR& res, const RR& x) { mpfr_log1p(*res.rep, *x.rep, MPFR_RNDN);}
inline RR log1p(const RR& a) { RR z; log1p(z, a); newNTL_OPT_RETURN(RR, z); }

inline void pow(RR& res, const RR& x, const RR& y) { mpfr_pow(*res.rep, *x.rep, *y.rep, MPFR_RNDN); }
inline RR pow(const RR& x, const RR& y) { RR z; pow(z, x, y); newNTL_OPT_RETURN(RR, z); }

inline void ComputePi(RR& res) { mpfr_const_pi(*res.rep,MPFR_RNDN); }
inline RR ComputePi_RR() { RR z; ComputePi(z); newNTL_OPT_RETURN(RR, z); }

inline void sin(RR& res, const RR& x) { mpfr_sin(*res.rep,*x.rep,MPFR_RNDN); }
inline RR sin(const RR& a) { RR z; sin(z, a); newNTL_OPT_RETURN(RR, z); }

inline void cos(RR& res, const RR& x) { mpfr_cos(*res.rep,*x.rep,MPFR_RNDN); }
inline RR cos(const RR& a) { RR z; cos(z, a); newNTL_OPT_RETURN(RR, z); }




newNTL_CLOSE_NNS

#endif
