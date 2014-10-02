#ifndef newNTL_vector__H
#define newNTL_vector__H

#include <memory>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <newNTL/tools.h>

newNTL_OPEN_NNS
//Warning: these two functions need to be specialized for other behaviour
template <typename T> void BlockConstruct(T* p, long n, const T& x=T())  
{  
   for (long i = 0; i < n; i++)  
      (void) new((&p[i])) T(x);  
}  
  
template <typename T> void BlockDestroy(T* p, long n)  
{  
   for (long i = 0; i < n; i++)  
      p[i].~T();  
}

template <typename T> class newntl_allocator 
{
    public:
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
    typedef size_t size_type;
    typedef std::ptrdiff_t difference_type;
    template <class U> struct rebind { typedef newntl_allocator<U> other; };

    inline pointer address ( reference x ) const { return &x; }
    inline const_pointer address ( const_reference x ) const { return &x; }
    inline pointer allocate(size_type n, void const* hint = 0) { return (pointer) malloc(n*sizeof(T)); }
    inline void deallocate(pointer p, size_type n) { free(p); }
    inline size_type max_size() const { return size_type(-1) / sizeof(T); }
    inline void construct(pointer p, const_reference t) { BlockConstruct(p,1,t); }
    inline void destroy(pointer p){ BlockDestroy(p,1); }
};


newNTL_CLOSE_NNS



//#define newNTL_vector_decl(T,vec_T)  
newNTL_OPEN_NNS
template <typename T, typename Alloc = newntl_allocator<T> > class Vec
{
    typedef std::vector<T, Alloc> Base;
    Base rep;
    long nbelems;
    bool fixed_length;
    public:
    typedef typename Base::iterator iterator;
    typedef typename Base::const_iterator const_iterator;

    void RangeError(long i) const {} 

    inline Vec():rep() { nbelems=0; fixed_length=false; }  
    inline Vec(newNTL_NNS INIT_SIZE_TYPE, long n):rep(n) { nbelems=n; fixed_length=false;}  
    inline Vec(const Vec<T, Alloc>& a):rep(a.rep) { nbelems=a.nbelems; fixed_length=a.fixed_length;}
    inline Vec& operator=(const Vec<T, Alloc>& a) { rep=a.rep; nbelems=a.nbelems; return *this;}
    inline ~Vec() {}
    inline void kill() { rep.resize(0); nbelems=0; }

    inline void SetLength(long n) { if (n >= rep.size()) rep.resize(n); nbelems=n; }
    inline void SetMaxLength(long n) { if (n >= rep.size()) rep.resize(n); }
    inline void FixLength(long n) { SetLength(n); fixed_length=true; }
    inline void QuickSetLength(long n) { nbelems=n; } 

    long length() const { return nbelems; }  
    long MaxLength() const { return rep.size(); } 
    long allocated() const { return rep.capacity(); } 
    long fixed() const { return fixed_length; } 

    inline T& operator[](long i) {  newNTL_assert(i>=0 && i<nbelems); return rep[i]; }  
    inline const T& operator[](long i) const { newNTL_assert(i>=0 && i<nbelems); return rep[i]; }  
    inline T& RawGet(long i)  {  return rep[i]; }  
    inline const T& RawGet(long i) const {  return rep[i]; }  
    inline T& operator()(long i) { newNTL_assert(i>0 && i<=nbelems); return rep[i-1]; }  
    inline const T& operator()(long i) const { newNTL_assert(i>0 && i<=nbelems); return rep[i-1]; } 

    inline const T* elts() const { return rep.data(); }  
    inline T* elts() { return rep.data(); }  

    inline Vec(Vec<T,Alloc>& a, newNTL_NNS INIT_TRANS_TYPE):rep() { rep.swap(a.rep); nbelems=a.nbelems; fixed_length=a.fixed_length; }
    inline void swap(Vec<T,Alloc>& a) {rep.swap(a.rep); std::swap(nbelems,a.nbelems); std::swap(fixed_length,a.fixed_length); } 
    inline long position(const T& a) const { long offset = long(&a - rep.data()); return (offset>=0 && offset<MaxLength()); }
    inline long position1(const T& a) const { long offset = long(&a - rep.data()); return (offset>=0 && offset<nbelems); }  
    //iterator overrides
    inline typename Base::const_iterator end() const { return rep.begin()+nbelems; }
    inline typename Base::iterator end() { return rep.begin()+nbelems; }
    inline typename Base::const_iterator begin() const { return rep.begin(); }
    inline typename Base::iterator begin() { return rep.begin(); }
    inline const T& back() const { return RawGet(nbelems-1); }
    inline T& back() { return RawGet(nbelems-1); }
    inline void push_back(const T& a) {  if (nbelems == MaxLength()) rep.push_back(a); else RawGet(nbelems)=a; nbelems++; }
    inline void pop_back(const T& a) {  if (nbelems > 0) --nbelems; }
};


template <typename T> void swap(Vec<T>& x, Vec<T>& y);  
template <typename T> void append(Vec<T>& v, const T& a); 
template <typename T> void append(Vec<T>& v, const Vec<T>& w);

#define newNTL_vector_decl(T,vec_T)  \
  typedef Vec<T> vec_T; 

#define newNTL_vector_impl(T,vec_T)
newNTL_CLOSE_NNS
  



//#define newNTL_io_vector_decl(T,vec_T)  
newNTL_OPEN_NNS
template <typename T> newNTL_SNS istream& operator>>(newNTL_SNS istream&, Vec<T>&);  
template <typename T> newNTL_SNS ostream& operator<<(newNTL_SNS ostream&, const Vec<T>&); 

#define newNTL_io_vector_decl(T,vec_T) 

#define newNTL_io_vector_impl(T,vec_T)
newNTL_CLOSE_NNS




//#define newNTL_eq_vector_decl(T,vec_T) 
newNTL_OPEN_NNS
template <typename T> long operator==(const Vec<T>& a, const Vec<T>& b);  
template <typename T> long operator!=(const Vec<T>& a, const Vec<T>& b);
#define newNTL_eq_vector_decl(T,vec_T) 

#define newNTL_eq_vector_impl(T,vec_T)
newNTL_CLOSE_NNS



 
newNTL_OPEN_NNS
template <typename T> void swap(Vec<T>& x, Vec<T>& y) 
{  
   T* t; 
   long xf = x.fixed(); 
   long yf = y.fixed(); 
   if (xf != yf ||  (xf && x.length() != y.length())) 
       newNTL_NNS failwith("swap: can't swap these vectors"); 
   x.swap(y);
}
 
template <typename T> void append(Vec<T>& v, const T& a) { v.push_back(a); } 
template <typename T> void append(Vec<T>& v, const Vec<T>& w)  
{  
   long l = v.length();  
   long m = w.length();  
   v.SetLength(l+m);  
   for (long i = 0; i < m; i++)  
      v[l+i] = w[i];  
}
newNTL_CLOSE_NNS





//#define newNTL_io_vector_impl(T,vec_T)  
newNTL_OPEN_NNS
template <typename T> newNTL_SNS istream & operator>>(newNTL_SNS istream& s, Vec<T>& a)   
{   
   Vec<T> ibuf;  
   long c;   
   long n;   
   if (!s) newNTL_NNS failwith("bad vector input"); 
   
   c = s.peek();  
   while (newNTL_NNS IsWhiteSpace(c)) {  
      s.get();  
      c = s.peek();  
   }  
   if (c != '[') {  
      newNTL_NNS failwith("bad vector input");  
   }  
   
   n = 0;   
   ibuf.SetLength(0);  
      
   s.get();  
   c = s.peek();  
   while (newNTL_NNS IsWhiteSpace(c)) {  
      s.get();  
      c = s.peek();  
   }  
   while (c != ']' && !newNTL_NNS IsEOFChar(c)) {   
      n++;   
      ibuf.SetLength(n);   
      if (!(s >> ibuf[n-1])) newNTL_NNS failwith("bad vector input");   
      c = s.peek();  
      while (newNTL_NNS IsWhiteSpace(c)) {  
         s.get();  
         c = s.peek();  
      }  
   }   
   if (newNTL_NNS IsEOFChar(c)) newNTL_NNS Error("bad vector input");  
   s.get(); 
   
   a = ibuf; 
   return s;   
}   
   
   
template <typename T> newNTL_SNS ostream& operator<<(newNTL_SNS ostream& s, const Vec<T>& a)   
{   
   long i, n;   
   n = a.length();  
   s << '[';   
   for (i = 0; i < n; i++) {   
      s << a[i];   
      if (i < n-1) s << " ";   
   }   
   s << ']';   
   return s;   
}   
newNTL_CLOSE_NNS

//#define newNTL_eq_vector_impl(T,vec_T) 
newNTL_OPEN_NNS
template <typename T> long operator==(const Vec<T>& a, const Vec<T>& b) 
{  
   long n = a.length();  
   if (b.length() != n) return 0;  
   const T* ap = a.elts(); 
   const T* bp = b.elts(); 
   long i;  
   for (i = 0; i < n; i++) if (ap[i] != bp[i]) return 0;  
   return 1;  
} 

template <typename T> long operator!=(const Vec<T>& a, const Vec<T>& b) 
{  return !(a == b); }
newNTL_CLOSE_NNS

//Common Vector Arithmetic
newNTL_OPEN_NNS
template<typename NUM>
void InnerProduct(NUM& xx, const Vec<NUM>& a, const Vec<NUM>& b)
{
   NUM t1, x;
   long n = min(a.length(), b.length());
   long i;
   clear(x);
   for (i = 1; i <= n; i++) {
      mul(t1, a(i), b(i));
      add(x, x, t1);
   }
   xx = x;
}

template<typename NUM>
void mul(Vec<NUM>& x, const Vec<NUM>& a, const NUM& b_in)
{
   NUM b = b_in;
   long n = a.length();
   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      mul(x[i], a[i], b);
}

template<typename NUM>
void add(Vec<NUM>& x, const Vec<NUM>& a, const Vec<NUM>& b)
{
   long n = a.length();
   if (b.length() != n) Error("vector add: dimension mismatch");

   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      add(x[i], a[i], b[i]);
}

template<typename NUM>
void sub(Vec<NUM>& x, const Vec<NUM>& a, const Vec<NUM>& b)
{
   long n = a.length();
   if (b.length() != n) Error("vector sub: dimension mismatch");
   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      sub(x[i], a[i], b[i]);
}

template<typename NUM>
void clear(Vec<NUM>& x)
{
   long n = x.length();
   long i;
   for (i = 0; i < n; i++)
      clear(x[i]);
}

template<typename NUM>
void negate(Vec<NUM>& x, const Vec<NUM>& a)
{
   long n = a.length();
   x.SetLength(n);
   long i;
   for (i = 0; i < n; i++)
      negate(x[i], a[i]);
}

template<typename NUM>
long IsZero(const Vec<NUM>& a)
{
   long n = a.length();
   long i;

   for (i = 0; i < n; i++)
      if (!IsZero(a[i]))
         return 0;

   return 1;
}

template<typename NUM>
inline void mul(Vec<NUM>& x, const NUM& a, const Vec<NUM>& b) { mul(x, b, a); }

//product vector times ptimitive type 
//(define it only if NUM!=NUMERIC to avoid ambiguous overload)
#define EXTERNAL_VEC_PRODUCT_DECL(NUMERIC) \
template<typename NUM> \
inline typename ifAneqBthenT<NUM,NUMERIC,void >::type \
mul(Vec<NUM>& x, const Vec<NUM>& a, NUMERIC b) \
{ \
   long n = a.length(); \
   x.SetLength(n); \
   long i; \
   for (i = 0; i < n; i++) \
      mul(x[i], a[i], b); \
} \
template<typename NUM> \
inline typename ifAneqBthenT<NUM,NUMERIC,void >::type \
mul(Vec<NUM>& x, NUMERIC a, const Vec<NUM>& b) { mul(x, b, a); } \
template<typename NUM> \
inline typename ifAneqBthenT<NUM,NUMERIC,Vec<NUM> >::type \
operator*(const Vec<NUM>& a, NUMERIC b) \
   { Vec<NUM> x; mul(x, a, b); newNTL_OPT_RETURN(Vec<NUM>, x); } \
template<typename NUM> \
inline typename ifAneqBthenT<NUM,NUMERIC,Vec<NUM> >::type \
operator*(NUMERIC a, const Vec<NUM>& b) \
   { Vec<NUM> x; mul(x, a, b); newNTL_OPT_RETURN(Vec<NUM>, x); } \
template<typename NUM> \
inline typename ifAneqBthenT<NUM,NUMERIC,Vec<NUM>& >::type \
operator*=(Vec<NUM>& x, NUMERIC a) \
{ \
   mul(x, x, a); \
   return x; \
}
EXTERNAL_VEC_PRODUCT_DECL(long);
EXTERNAL_VEC_PRODUCT_DECL(double);
EXTERNAL_VEC_PRODUCT_DECL(float);
EXTERNAL_VEC_PRODUCT_DECL(int);
EXTERNAL_VEC_PRODUCT_DECL(unsigned);
EXTERNAL_VEC_PRODUCT_DECL(unsigned long);


template<typename NUM>
Vec<NUM> operator+(const Vec<NUM>& a, const Vec<NUM>& b)
{
   Vec<NUM> res;
   add(res, a, b);
   newNTL_OPT_RETURN(Vec<NUM>, res);
}

template<typename NUM>
Vec<NUM> operator-(const Vec<NUM>& a, const Vec<NUM>& b)
{
   Vec<NUM> res;
   sub(res, a, b);
   newNTL_OPT_RETURN(Vec<NUM>, res);
}


template<typename NUM>
Vec<NUM> operator-(const Vec<NUM>& a)
{
   Vec<NUM> res;
   negate(res, a);
   newNTL_OPT_RETURN(Vec<NUM>, res);
}


template<typename NUM>
NUM operator*(const Vec<NUM>& a, const Vec<NUM>& b)
{
   NUM res;
   InnerProduct(res, a, b);
   //newNTL_OPT_RETURN(NUM, res);
   return res;
}


template<typename NUM>
inline Vec<NUM> operator*(const Vec<NUM>& a, const NUM& b)
   { Vec<NUM> x; mul(x, a, b); newNTL_OPT_RETURN(Vec<NUM>, x); }


template<typename NUM>
inline Vec<NUM> operator*(const NUM& a, const Vec<NUM>& b)
   { Vec<NUM> x; mul(x, a, b); newNTL_OPT_RETURN(Vec<NUM>, x); }




template<typename NUM>
inline Vec<NUM>& operator+=(Vec<NUM>& x, const Vec<NUM>& a)
{ 
   add(x, x, a);
   return x;
}

template<typename NUM>
inline Vec<NUM>& operator-=(Vec<NUM>& x, const Vec<NUM>& a)
{ 
   sub(x, x, a);
   return x;
}

template<typename NUM>
inline Vec<NUM>& operator*=(Vec<NUM>& x, const NUM& a)
{ 
   mul(x, x, a);
   return x;
}

//conversion from one vector to another
template<typename NUMA,typename NUMB> 
inline void conv(Vec<NUMA>& v,const Vec<NUMB>& w) {
    int n = w.length();
    v.SetLength(n);
    for (int i=0; i<n; i++) 
	conv(v[i],w[i]);
}

//square norm
template<typename NUM>
inline NUM normsq(const Vec<NUM>& v){
    return v*v;
}

newNTL_CLOSE_NNS
   

#endif

