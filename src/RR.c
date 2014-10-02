#include <sstream>
#include <string>
#include <newNTL/RR.h>


#include <newNTL/new.h>

newNTL_START_IMPL


int RR::initialize_prec_150() {
#pragma omp parallel
  RR::SetPrecision(150);
  fprintf(stderr,"RR precision initialized to 150\n");
  return 1;
}
int RR::default_precision_initialized=initialize_prec_150();

long RR::oprec = 53;

void RR::SetOutputPrecision(long p)
{
   if (p < 1)
      p = 1;

   if (newNTL_OVERFLOW(p, 1, 0))
      Error("RR: output precision too high");

#pragma omp atomic
   oprec = p;
}

/* TODO
void MakeRR(RR& z, const ZZ& a,  long e)
{
   if (e >= newNTL_OVFBND)
      Error("MakeRR: e too big");

   if (e <= -newNTL_OVFBND)
      Error("MakeRR: e too small");

   normalize1(z, a, e, RR::prec, 0);
}

void MakeRRPrec(RR& x, const ZZ& a, long e, long p)
{
   if (p < 1 || newNTL_OVERFLOW(p, 1, 0))
      Error("MakeRRPrec: bad precsion");

   long old_p = RR::prec;
   RR::prec = p;
   MakeRR(x, a, e);
   RR::prec = old_p;
}
 */

void random(RR& z)
{
   long prec = RR::precision();
   staticthread ZZ t;
   RandomBits(t, prec);
   conv(z,t);
   mpfr_div_2si(*z.rep,*z.rep,prec,MPFR_RNDN);
}


namespaceanon inline void xcopy(RR& x, const RR& a)   { mpfr_set(*x.rep, *a.rep, MPFR_RNDN); }

// xcopy emulates old assignment semantics...
// many routines here implicitly assume assignment normalizes,
// but that is no longer the case as of v3.0.


void conv(RR& x, const RR& a)
{
   mpfr_set_prec(*x.rep, mpfr_get_prec(*a.rep));
   mpfr_set(*x.rep, *a.rep,MPFR_RNDN);
}


void AddPrec(RR& x, const RR& a, const RR& b, long p)
{
  if (&x!=&a && &x!=&b) { 
    mpfr_set_prec(*x.rep,p); 
    mpfr_add(*x.rep,*a.rep,*b.rep,MPFR_RNDN); 
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_add(*tmp.rep,*a.rep,*b.rep,MPFR_RNDN);
    swap(x,tmp);
  }
}

void SubPrec(RR& x, const RR& a, const RR& b, long p)
{
  if (&x!=&a && &x!=&b) { 
    mpfr_set_prec(*x.rep,p); 
    mpfr_sub(*x.rep,*a.rep,*b.rep,MPFR_RNDN); 
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_sub(*tmp.rep,*a.rep,*b.rep,MPFR_RNDN);
    swap(x,tmp);
  }
}

void NegatePrec(RR& x, const RR& a, long p)
{
  if (&x!=&a) { 
    mpfr_set_prec(*x.rep,p); 
    mpfr_neg(*x.rep,*a.rep,MPFR_RNDN); 
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_neg(*tmp.rep,*a.rep,MPFR_RNDN);
    swap(x,tmp);
  }
}

void AbsPrec(RR& x, const RR& a, long p)
{
  if (&x!=&a) { 
    mpfr_set_prec(*x.rep,p); 
    mpfr_abs(*x.rep,*a.rep,MPFR_RNDN); 
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_abs(*tmp.rep,*a.rep,MPFR_RNDN);
    swap(x,tmp);
  }
}


void MulPrec(RR& x, const RR& a, const RR& b, long p)
{
  if (&x!=&a && &x!=&b) { 
    mpfr_set_prec(*x.rep,p); 
    mpfr_mul(*x.rep,*a.rep,*b.rep,MPFR_RNDN); 
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_mul(*tmp.rep,*a.rep,*b.rep,MPFR_RNDN);
    swap(x,tmp);
  }

}


void SqrPrec(RR& x, const RR& a, long p)
{
  if (&x!=&a) { 
    mpfr_set_prec(*x.rep,p); 
    mpfr_sqr(*x.rep,*a.rep,MPFR_RNDN); 
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_sqr(*tmp.rep,*a.rep,MPFR_RNDN);
    swap(x,tmp);
  }
}


void DivPrec(RR& x, const RR& a, const RR& b, long p)
{
  if (&x!=&a && &x!=&b) { 
    mpfr_set_prec(*x.rep,p); 
    mpfr_div(*x.rep,*a.rep,*b.rep,MPFR_RNDN); 
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_div(*tmp.rep,*a.rep,*b.rep,MPFR_RNDN);
    swap(x,tmp);
  }
}


void SqrRootPrec(RR& x, const RR& a, long p)
{
  if (&x!=&a) { 
    mpfr_set_prec(*x.rep,p); 
    mpfr_sqrt(*x.rep,*a.rep,MPFR_RNDN); 
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_sqrt(*tmp.rep,*a.rep,MPFR_RNDN);
    swap(x,tmp);
  }
}


void TruncPrec(RR& x, const RR& a, long p)
{
  if (&x!=&a) { 
    mpfr_set_prec(*x.rep,p); 
    mpfr_rint_trunc(*x.rep,*a.rep,MPFR_RNDN); 
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_rint_trunc(*tmp.rep,*a.rep,MPFR_RNDN);
    swap(x,tmp);
  }
}

void FloorPrec(RR& x, const RR& a, long p)
{
  if (&x!=&a) { 
    mpfr_set_prec(*x.rep,p); 
    mpfr_rint_floor(*x.rep,*a.rep,MPFR_RNDN); 
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_rint_floor(*tmp.rep,*a.rep,MPFR_RNDN);
    swap(x,tmp);
  }
}

void CeilPrec(RR& x, const RR& a, long p)
{
  if (&x!=&a) { 
    mpfr_set_prec(*x.rep,p); 
    mpfr_rint_ceil(*x.rep,*a.rep,MPFR_RNDN); 
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_rint_ceil(*tmp.rep,*a.rep,MPFR_RNDN);
    swap(x,tmp);
  }
}

void RoundPrec(RR& x, const RR& a, const RR& b, long p)
{
  if (&x!=&a) { 
    mpfr_set_prec(*x.rep,p); 
    mpfr_rint_round(*x.rep,*a.rep,MPFR_RNDN); 
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_rint_round(*tmp.rep,*a.rep,MPFR_RNDN);
    swap(x,tmp);
  }
}

   

void conv(RR& z, const ZZ& a)
{
  //TODO optimize speed
  ostringstream os; os << a;
  mpfr_set_str(*z.rep,os.str().c_str(),0,MPFR_RNDN);
}

void ConvPrec(RR& z, const ZZ& a, long p)
{
  //TODO optimize seed
  ostringstream os; os << a;
  mpfr_set_prec(*z.rep,p);
  mpfr_set_str(*z.rep,os.str().c_str(),0,MPFR_RNDN);
}


void conv(RR& z, long a)
{
  mpfr_set_si(*z.rep,a,MPFR_RNDN);
}

void ConvPrec(RR& z, long a, long p)
{
  mpfr_set_prec(*z.rep,p);
  mpfr_set_si(*z.rep,a,MPFR_RNDN);
}

void conv(RR& z, unsigned long a)
{
  mpfr_set_ui(*z.rep,a,MPFR_RNDN);
}

void ConvPrec(RR& z, unsigned long a, long p)
{
  mpfr_set_prec(*z.rep,p);
  mpfr_set_si(*z.rep,a,MPFR_RNDN);
}


void conv(RR& z, double a)
{
  mpfr_set_d(*z.rep,a,MPFR_RNDN);
}

void ConvPrec(RR& z, double a, long p)
{
  mpfr_set_prec(*z.rep,p);
  mpfr_set_d(*z.rep,a,MPFR_RNDN);
}

void conv(ZZ& z, const RR& a)
{
  mpz_t tmp; mpz_init(tmp);
  mpfr_get_z(tmp,*a.rep,MPFR_RNDN);
  conv(z,tmp); //TODO
  mpz_clear(tmp);
}

void CeilToZZ(ZZ& z, const RR& a)
{
  mpz_t tmp; mpz_init(tmp);
  mpfr_get_z(tmp,*a.rep,MPFR_RNDU);
  conv(z,tmp); //TODO
  mpz_clear(tmp);
}

void TruncToZZ(ZZ& z, const RR& a)
{
  mpz_t tmp; mpz_init(tmp);
  mpfr_get_z(tmp,*a.rep,MPFR_RNDZ);
  conv(z,tmp); //TODO
  mpz_clear(tmp);

}


void RoundToZZ(ZZ& z, const RR& a)
{
  mpz_t tmp; mpz_init(tmp);
  mpfr_get_z(tmp,*a.rep,MPFR_RNDN);
  conv(z,tmp); //TODO
  mpz_clear(tmp);
}


void conv(long& z, const RR& a)
{
  z = mpfr_get_si(*a.rep,MPFR_RNDN);
}

void conv(double& z, const RR& a)
{
  z = mpfr_get_d(*a.rep,MPFR_RNDN);
}


void InvPrec(RR& x, const RR& a, long p)
{
  if (&x!=&a) {
    mpfr_set_prec(*x.rep,p);
    mpfr_si_div(*x.rep,1,*a.rep,MPFR_RNDN);
  } else {
    RR tmp; mpfr_set_prec(*tmp.rep,p);
    mpfr_si_div(*tmp.rep,1,*a.rep,MPFR_RNDN);
    swap(x,tmp);
  }
}


istream& operator>>(istream& in, RR& x)
{
   string s; 
   bool began = false;
   for (char c=in.get(); in; c=in.get()) {
     if (c==']' || c=='}') { in.putback(c); break; }
     bool space = (c==' ' ||
         c=='\t' ||
         c=='\r' ||
         c=='\n');
     bool digit = (c=='.' ||
         c>='0' && c<='9' ||
         c>='a' && c<='z' ||
         c>='A' && c<='Z' ||
         c=='+' ||
         c=='-');
     if (began && space) break;
     if (!began && space) continue;
     if (digit) { began=true; s.push_back(c); continue; }
     failwith("bad RR input");
   }
   if (!began) failwith("bad RR input");
   mpfr_set_str(*x.rep,s.c_str(),0,MPFR_RNDN);  
   return in;
}

void InputPrec(RR& x, istream& in, long p)
{
   string s; in>>s;
   mpfr_set_prec(*x.rep,p);
   mpfr_set_str(*x.rep,s.c_str(),0,MPFR_RNDN);  
}


void conv(RR& z, const xdouble& a)
{
  //TODO
  failwith("not implemented");
}

void ConvPrec(RR& x, const xdouble& a, long p)
{
  //TODO
  failwith("not implemented");
}



void conv(xdouble& z, const RR& a)
{
  //TODO
  failwith("not implemented");
}
      
void conv(RR& z, const quad_float& a)
{
  //TODO
  failwith("not implemented");
}

void ConvPrec(RR& x, const quad_float& a, long p)
{
  //TODO
  failwith("not implemented");
}


void conv(quad_float& z, const RR& a)
{
  //TODO
  failwith("not implemented");
}

void conv(RR& x, const char *s)
{
  mpfr_set_str(*x.rep,s,0,MPFR_RNDN);
}

void ConvPrec(RR& x, const char *s, long p)
{
  mpfr_set_prec(*x.rep,p);
  mpfr_set_str(*x.rep,s,0,MPFR_RNDN);
}


long Lg2(const RR& x)
{ 
  long exp;
  double d = mpfr_get_d_2exp(&exp,*x.rep,MPFR_RNDN);
  return exp;
}



ostream& operator<<(ostream& out, const RR& a)
{
    if (mpfr_nan_p(*a.rep)) { out << "@NaN@"; return out; }
    if (mpfr_inf_p(*a.rep)) { 
        if (mpfr_sgn(*a.rep) > 0) out << "@Inf@"; else out << "-@Inf@";
        return out;
    }
    if (mpfr_zero_p(*a.rep)) { 
        if (mpfr_sgn(*a.rep) > 0) out << "0"; else out << "-0";
        return out;
    }
    long oprec = RR::OutputPrecision();
    RR c; ConvPrec(c,a,oprec);

  mpfr_exp_t e;
  char* buf = mpfr_get_str(0,&e,10,0,*c.rep,MPFR_RNDN);
  //eliminate trailing zeros
  for (int i=strlen(buf)-1; i>=0; i--) {
    if (buf[i]!='0') break;
    buf[i]=0;
  }
  char* s = buf;
  if (*s == '-') { out << '-'; ++s; }
  if (e>0 && e<9) {
    //print mantissa
    for (; e>0; e--) {
      if (*s!=0) {out << *s; ++s; }
      else { out << '0'; }
    }
  } else {
    //just one digit
    if (*s!=0) {out << *s; ++s; --e;}
    else { out << '0'; --e; }
  }
  if (*s!=0) out << '.';
  //print the rest of mantissa
  if (*s!=0) out << s;
  //print the exponent
  if (e) out << 'e' << e;
  mpfr_free_str(buf);
  return out;
}

FLOOR_ROUND_CEIL_TO_ZZ_IMPL(float);
FLOOR_ROUND_CEIL_TO_ZZ_IMPL(double);


newNTL_END_IMPL
