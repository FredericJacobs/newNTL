#ifndef newNTL_QQ__H
#define newNTL_QQ__H

#include <newNTL/ZZ.h>
#include <gmpxx.h>

newNTL_OPEN_NNS


class QQ {
  public:
    mpq_t* rep;

  private:
    
    inline void init_0() {
      rep = (mpq_t*) malloc(sizeof(mpq_t));
      mpq_init(*rep);
    }
    inline void init_copy(const QQ& a) {
      rep = (mpq_t*) malloc(sizeof(mpq_t));
      mpq_init(*rep);
      mpq_set(*rep,*a.rep);
    }
    inline void destroy() {
      if (rep) 
      {
        mpq_clear(*rep);
        free(rep);
	rep=0;
      }
    }
  public:

QQ() {  init_0(); }

inline QQ(INIT_VAL_TYPE, const ZZ& a);
inline QQ(INIT_VAL_TYPE, int a, int b=1, bool is_normalized=false);
inline QQ(INIT_VAL_TYPE, long a, long b=1l, bool is_normalized=false);
inline QQ(INIT_VAL_TYPE, unsigned int a, unsigned int b=1u, bool is_normalized=false);
inline QQ(INIT_VAL_TYPE, unsigned long a, unsigned long b=1ul, bool is_normalized=false);
inline QQ(INIT_VAL_TYPE, const char *a, bool is_normalized=false);  // read from string
inline QQ(INIT_VAL_TYPE, const QQ& a);

inline QQ(const ZZ& a);
inline QQ(int a, int b=1, bool is_normalized=false);
inline QQ(long a, long b=1l, bool is_normalized=false);
inline QQ(unsigned int a, unsigned int b=1u, bool is_normalized=false);
inline QQ(unsigned long a, unsigned long b=1ul, bool is_normalized=false);
inline QQ(const char *a, bool is_normalized=false);  // read from string
inline QQ(const QQ& a);


inline QQ& operator=(const QQ& a);
inline QQ& operator=(const ZZ& a);
inline QQ& operator=(int a);
inline QQ& operator=(long a);
inline QQ& operator=(unsigned int a);
inline QQ& operator=(unsigned long a);
inline QQ& operator=(const char *a);  // read from string

inline QQ(QQ& z, INIT_TRANS_TYPE) { rep = z.rep; z.rep = 0; }
inline ~QQ() { destroy(); }

};


inline long IsZero(const QQ& a) { return mpq_cmp_si(*a.rep,0,1)==0; }
inline long IsOne(const QQ& a) { return mpq_cmp_si(*a.rep,1,1)==0; }
inline long sign(const QQ& a) { return mpq_sgn(*a.rep); }
inline void clear(QQ& z) { mpq_set_si(*z.rep,0,1); }
inline void set(QQ& z) { mpq_set_si(*z.rep,1,1); }
inline void swap(QQ& a, QQ& b) { mpq_t* tmp = a.rep; a.rep=b.rep; b.rep=tmp; }

inline void add(QQ& z, const QQ& a, const QQ& b) { mpq_add(*z.rep, *a.rep, *b.rep); }

inline void add(QQ& z, const QQ& a, long b) { add(z, a, QQ(b)); }
inline void add(QQ& z, long a, const QQ& b) { add(z, b, QQ(a)); }



inline void sub(QQ& z, const QQ& a, const QQ& b) { mpq_sub(*z.rep, *a.rep, *b.rep); }
inline void sub(QQ& z, const QQ& a, long b) { sub(z, a, QQ(b)); }
inline void sub(QQ& z, long a, const QQ& b) { sub(z, QQ(a), b); }

inline void negate(QQ& z, const QQ& a) { mpq_neg(*z.rep, *a.rep); }

inline void abs(QQ& z, const QQ& a) { mpq_abs(*z.rep, *a.rep); }
inline QQ abs(const QQ& a) { QQ z; abs(z, a); newNTL_OPT_RETURN(QQ, z); }

inline void mul(QQ& z, const QQ& a, const QQ& b) { mpq_mul(*z.rep, *a.rep, *b.rep); }
inline void mul(QQ& z, const QQ& a, long b) { mul(z, a, QQ(b)); }
inline void mul(QQ& z, long a, const QQ& b) { mul(z, b, QQ(a)); }

inline void sqr(QQ& z, const QQ& a) { mpq_mul(*z.rep, *a.rep, *a.rep); }
inline QQ sqr(const QQ& a) { QQ z; sqr(z, a); newNTL_OPT_RETURN(QQ, z); }

inline void div(QQ& z, const QQ& a, const QQ& b) { mpq_div(*z.rep, *a.rep, *b.rep); }
inline void div(QQ& z, const QQ& a, long b) { div(z, a, QQ(b)); }
inline void div(QQ& z, long a, const QQ& b) { div(z, QQ(a), b); }

inline void inv(QQ& z, const QQ& a) { mpq_inv(*z.rep, *a.rep); }
inline QQ inv(const QQ& a) { QQ z; inv(z, a); newNTL_OPT_RETURN(QQ, z); }

// operator notation:

inline QQ operator+(const QQ& a, const QQ& b) { QQ x; add(x, a, b); newNTL_OPT_RETURN(QQ, x); }
inline QQ operator+(const QQ& a, long b) { QQ x; add(x, a, b); newNTL_OPT_RETURN(QQ, x); }
inline QQ operator+(long a, const QQ& b) { QQ x; add(x, a, b); newNTL_OPT_RETURN(QQ, x); }
inline QQ& operator+=(QQ& x, const QQ& b) { add(x, x, b); return x; } 
inline QQ& operator+=(QQ& x, long b) { add(x, x, b); return x; } 



inline QQ operator-(const QQ& a, const QQ& b) { QQ x; sub(x, a, b); newNTL_OPT_RETURN(QQ, x); }
inline QQ operator-(const QQ& a, long b) { QQ x; sub(x, a, b); newNTL_OPT_RETURN(QQ, x); }
inline QQ operator-(long a, const QQ& b) { QQ x; sub(x, a, b); newNTL_OPT_RETURN(QQ, x); }
inline QQ& operator-=(QQ& x, const QQ& b) { sub(x, x, b); return x; } 
inline QQ& operator-=(QQ& x, long b) { sub(x, x, b); return x; } 



inline QQ operator*(const QQ& a, const QQ& b) { QQ x; mul(x, a, b); newNTL_OPT_RETURN(QQ, x); }
inline QQ operator*(const QQ& a, long b) { QQ x; mul(x, a, b); newNTL_OPT_RETURN(QQ, x); }
inline QQ operator*(long a, const QQ& b) { QQ x; mul(x, a, b); newNTL_OPT_RETURN(QQ, x); }
inline QQ& operator*=(QQ& x, const QQ& b) { mul(x, x, b); return x; } 
inline QQ& operator*=(QQ& x, long b) { mul(x, x, b); return x; } 


inline QQ operator/(const QQ& a, const QQ& b) { QQ x; div(x, a, b); newNTL_OPT_RETURN(QQ, x); }
inline QQ operator/(const QQ& a, long b) { QQ x; div(x, a, b); newNTL_OPT_RETURN(QQ, x); }
inline QQ operator/(long a, const QQ& b) { QQ x; div(x, a, b); newNTL_OPT_RETURN(QQ, x); }
inline QQ& operator/=(QQ& x, const QQ& b) { div(x, x, b); return x; } 
inline QQ& operator/=(QQ& x, long b) { div(x, x, b); return x; } 


inline QQ operator-(const QQ& a) { QQ x; negate(x, a); newNTL_OPT_RETURN(QQ, x); }
inline QQ& operator++(QQ& x) { add(x, x, 1); return x; }
inline void operator++(QQ& x, int) { add(x, x, 1); }
inline QQ& operator--(QQ& x) { sub(x, x, 1); return x; }
inline void operator--(QQ& x, int) { sub(x, x, 1); }



inline long compare(const QQ& a, const QQ& b) { return mpq_cmp(*a.rep, *b.rep); }

inline long compare(const QQ& a, long b) { return compare(a, QQ(b)); }
inline long compare(long a, const QQ& b) { return compare(QQ(a), b); }


inline long operator==(const QQ& a, const QQ& b) { return mpq_cmp(*a.rep,*b.rep)==0; }
inline long operator!=(const QQ& a, const QQ& b) { return mpq_cmp(*a.rep,*b.rep)!=0; }
inline long operator<=(const QQ& a, const QQ& b) { return mpq_cmp(*a.rep,*b.rep)<=0; }
inline long operator>=(const QQ& a, const QQ& b) { return mpq_cmp(*a.rep,*b.rep)>=0; }
inline long operator <(const QQ& a, const QQ& b) { return mpq_cmp(*a.rep,*b.rep)< 0; }
inline long operator >(const QQ& a, const QQ& b) { return mpq_cmp(*a.rep,*b.rep)> 0; }

inline long operator==(const QQ& a, long b) { return compare(a, b) == 0; }
inline long operator!=(const QQ& a, long b) { return compare(a, b) != 0; }
inline long operator<=(const QQ& a, long b) { return compare(a, b) <= 0; }
inline long operator>=(const QQ& a, long b) { return compare(a, b) >= 0; }
inline long operator <(const QQ& a, long b) { return compare(a, b)  < 0; }
inline long operator >(const QQ& a, long b) { return compare(a, b)  > 0; }

inline long operator==(long a, const QQ& b) { return (b == a); }
inline long operator!=(long a, const QQ& b) { return !(a == b); }
inline long operator<=(long a, const QQ& b) { return compare(a, b) <= 0; }
inline long operator>=(long a, const QQ& b) { return compare(a, b) >= 0; }
inline long operator <(long a, const QQ& b) { return compare(a, b)  < 0; }
inline long operator >(long a, const QQ& b) { return compare(a, b)  > 0; }

inline void ceil(QQ& z, const QQ& a) { 
    staticthread  mpz_t m; 
    staticthread  bool initialized=0;
    if (!initialized) mpz_init(m); 
    mpz_cdiv_q(m, mpq_numref(*a.rep), mpq_denref(*a.rep)); 
    mpq_set_z(*z.rep, m);
}
inline QQ ceil(const QQ& a) { QQ z; ceil(z, a); newNTL_OPT_RETURN(QQ, z); }

inline void floor(QQ& z, const QQ& a) { 
    staticthread  mpz_t m; 
    staticthread  bool initialized=0;
    if (!initialized) mpz_init(m); 
    mpz_fdiv_q(m, mpq_numref(*a.rep), mpq_denref(*a.rep)); 
    mpq_set_z(*z.rep, m);
}
inline QQ floor(const QQ& a) { QQ z; floor(z, a); newNTL_OPT_RETURN(QQ, z); }

inline void trunc(QQ& z, const QQ& a) {
    staticthread  mpz_t m; 
    staticthread  bool initialized=0;
    if (!initialized) mpz_init(m); 
    mpz_tdiv_q(m, mpq_numref(*a.rep), mpq_denref(*a.rep)); 
    mpq_set_z(*z.rep, m);
}
inline QQ trunc(const QQ& a) { QQ z; trunc(z, a); newNTL_OPT_RETURN(QQ, z); }

inline void round(QQ& z, const QQ& a) { 
    staticthread  QQ aa;
    staticthread  mpz_t m;
    staticthread  bool initialized=0;
    if (!initialized) mpz_init(m); 
    add(aa,a,QQ(1,2,true)); 
    mpz_fdiv_q(m, mpq_numref(*aa.rep), mpq_denref(*a.rep)); 
    mpq_set_z(*z.rep, m);
}
inline QQ round(const QQ& a) { QQ z; round(z, a); newNTL_OPT_RETURN(QQ, z); }

inline void RoundToZZ(ZZ& z, const QQ& a) {
    staticthread  QQ aa;
    staticthread  mpz_t m;
    staticthread  bool initialized=0;
    if (!initialized) mpz_init(m); 
    add(aa,a,QQ(1,2,true)); 
    mpz_fdiv_q(m, mpq_numref(*aa.rep), mpq_denref(*a.rep)); 
    conv(z, m);
}
inline void FloorToZZ(ZZ& z, const QQ& a) {
    staticthread  mpz_t m; 
    staticthread  bool initialized=0;
    if (!initialized) mpz_init(m); 
    mpz_fdiv_q(m, mpq_numref(*a.rep), mpq_denref(*a.rep)); 
    conv(z, m);
}
inline void TruncToZZ(ZZ& z, const QQ& a) {
    staticthread  mpz_t m; 
    staticthread  bool initialized=0;
    if (!initialized) mpz_init(m); 
mpz_tdiv_q(m, mpq_numref(*a.rep), mpq_denref(*a.rep)); 
    conv(z, m);
}    
inline void CeilToZZ(ZZ& z, const QQ& a) {
    staticthread  mpz_t m;
    staticthread  bool initialized=0;
    if (!initialized) mpz_init(m); 
    mpz_cdiv_q(m, mpq_numref(*a.rep), mpq_denref(*a.rep)); 
    conv(z, m);
}

void conv(QQ& z, const ZZ& a) { staticthread mpz_t m; conv(m,a); mpq_set_z(*z.rep,m); }
void conv(QQ& z, long a) { mpq_set_si(*z.rep,a,1); }
inline void conv(QQ& z, int a) { mpq_set_si(*z.rep,a,1); }
void conv(QQ& z, unsigned long a) { mpq_set_ui(*z.rep,a,1); }
inline void conv(QQ& z, unsigned int a) { mpq_set_ui(*z.rep,a,1); }
void conv(QQ& z, const char *s) { mpq_set_str(*z.rep,s,0); mpq_canonicalize(*z.rep); }

//TODO
void conv(QQ& z, double a);
inline void conv(QQ& z, const QQ& a) { z=a; }


inline QQ::QQ(INIT_VAL_TYPE, const ZZ& a) {
   mpz_t az; mpz_init(az); 
   conv(az,a);
   init_0();
   mpq_set_z(*rep, az);
   mpz_clear(az);
}
inline QQ::QQ(INIT_VAL_TYPE, int a, int b, bool is_normalized) {
   init_0();
   mpq_set_si(*rep,a,b);
   if (!is_normalized) mpq_canonicalize(*rep);
}
inline QQ::QQ(INIT_VAL_TYPE, long a, long b, bool is_normalized) {
   init_0();
   mpq_set_si(*rep,a,b);
   if (!is_normalized) mpq_canonicalize(*rep);
}
inline QQ::QQ(INIT_VAL_TYPE, unsigned int a, unsigned int b, bool is_normalized) {
   init_0();
   mpq_set_si(*rep,a,b);
   if (!is_normalized) mpq_canonicalize(*rep);
}
inline QQ::QQ(INIT_VAL_TYPE, unsigned long a, unsigned long b, bool is_normalized){
   init_0();
   mpq_set_si(*rep,a,b);
   if (!is_normalized) mpq_canonicalize(*rep);
}
inline QQ::QQ(INIT_VAL_TYPE, const char *a, bool is_normalized) {  // read from string
   init_0();
   mpq_set_str(*rep,a,0);
   if (!is_normalized) mpq_canonicalize(*rep);
}
inline QQ::QQ(INIT_VAL_TYPE, const QQ& a) {
    init_copy(a);
}

inline QQ::QQ(const ZZ& a){
   mpz_t az; mpz_init(az); 
   conv(az,a);
   init_0();
   mpq_set_z(*rep, az);
   mpz_clear(az);
}
inline QQ::QQ(int a, int b, bool is_normalized){
   init_0();
   mpq_set_si(*rep,a,b);
   if (!is_normalized) mpq_canonicalize(*rep);
}
inline QQ::QQ(long a, long b, bool is_normalized){
   init_0();
   mpq_set_si(*rep,a,b);
   if (!is_normalized) mpq_canonicalize(*rep);
}
inline QQ::QQ(unsigned int a, unsigned int b, bool is_normalized){
   init_0();
   mpq_set_si(*rep,a,b);
   if (!is_normalized) mpq_canonicalize(*rep);
}
inline QQ::QQ(unsigned long a, unsigned long b, bool is_normalized){
   init_0();
   mpq_set_si(*rep,a,b);
   if (!is_normalized) mpq_canonicalize(*rep);
}
inline QQ::QQ(const char *a, bool is_normalized){  // read from string
   init_0();
   mpq_set_str(*rep,a,0);
   if (!is_normalized) mpq_canonicalize(*rep);
}
inline QQ::QQ(const QQ& a){
    init_copy(a);
}

inline QQ& QQ::operator=(const QQ& a){
    mpq_set(*rep,*a.rep); 
    return *this;
}
inline QQ& QQ::operator=(const ZZ& a){
   mpz_t az; mpz_init(az); 
   conv(az,a);
   mpq_set_z(*rep, az);
   mpz_clear(az);
   return *this;
}
inline QQ& QQ::operator=(int a) { mpq_set_si(*rep, a,1);  return *this;}
inline QQ& QQ::operator=(long a) { mpq_set_si(*rep, a,1); return *this; }
inline QQ& QQ::operator=(unsigned int a) { mpq_set_ui(*rep, a,1); return *this; }
inline QQ& QQ::operator=(unsigned long a) { mpq_set_ui(*rep, a,1); return *this; }
inline QQ& QQ::operator=(const char *a) {mpq_set_str(*rep,a,0); return *this; }  // read from string

template<> inline QQ to<QQ>(int a) { return QQ(INIT_VAL, a); }
template<> inline QQ to<QQ>(long a) { return QQ(INIT_VAL, a); }
template<> inline QQ to<QQ>(unsigned int a) { return QQ(INIT_VAL, a); }
template<> inline QQ to<QQ>(unsigned long a) { return QQ(INIT_VAL, a); }
template<> inline QQ to<QQ>(const ZZ& a) { return QQ(INIT_VAL, a); }
template<> inline QQ to<QQ>(const QQ& a) { return QQ(INIT_VAL, a); }
template<> inline QQ to<QQ>(const char *a) { return QQ(INIT_VAL, a); }


inline void power(QQ& z, const QQ& a, long e);
inline QQ power(const QQ& a, long e);


newNTL_SNS ostream& operator<<(newNTL_SNS ostream& s, const QQ& a) {
    mpq_class aa(*a.rep);
    s << aa.get_str();
    return s;
}
newNTL_SNS istream& operator>>(newNTL_SNS istream& s, QQ& x) {
    std::string xx; s>>xx;
    mpq_set_str(*x.rep,xx.c_str(),0);
    mpq_canonicalize(*x.rep);
    return s;
}


newNTL_CLOSE_NNS

#endif //newNTL_QQ__H
