#ifndef newNTL_matrix__H
#define newNTL_matrix__H

#include <newNTL/tools.h>
#include <newNTL/vector.h>


// matrix templates


//#define newNTL_matrix_decl(T,vec_T,vec_vec_T,mat_T)  
newNTL_OPEN_NNS
template <typename T > class Mat {
public:
   Vec<Vec<T> > rep;
   long numcols;


   inline Mat() { numcols = 0; }
   Mat(const Mat<T>& a);
   Mat& operator=(const Mat<T>& a);
   inline ~Mat() {}

   Mat(newNTL_NNS INIT_SIZE_TYPE, long n, long m);

   inline void kill() { numcols=0; rep.kill(); }

   void SetDims(long n, long m);

   inline long NumRows() const { return rep.length(); }
   inline long NumCols() const { return numcols; }

   inline Vec<T>& operator[](long i) { return rep[i]; }
   inline const Vec<T>& operator[](long i) const { return rep[i]; }

   inline Vec<T>& operator()(long i) { return rep[i-1]; }
   inline const Vec<T>& operator()(long i) const { return rep[i-1]; }

   inline T& operator()(long i, long j) { return rep[i-1][j-1]; }
   inline const T& operator()(long i, long j) const { return rep[i-1][j-1]; }

   long position(const Vec<T>& a) const { return rep.position(a); }
   long position1(const Vec<T>& a) const { return rep.position1(a); }
   inline Mat(Mat<T>& x, newNTL_NNS INIT_TRANS_TYPE): rep(x.rep, newNTL_NNS INIT_TRANS), numcols(x.numcols) {}
};

template <typename T> inline const Vec<Vec<T> >& rep(const Mat<T>& a)
   { return a.rep; }

template <typename T> void swap(Mat<T>& X, Mat<T>& Y);

template <typename T> void MakeMatrix(Mat<T>& x, const Vec<Vec<T> >& a);

#define newNTL_matrix_decl(T,vec_T,vec_vec_T,mat_T) \
  typedef Mat<T> mat_T; 

#define newNTL_matrix_impl(T,vec_T,vec_vec_T,mat_T)



#define newNTL_eq_matrix_decl(T,vec_T,vec_vec_T,mat_T) 

#define newNTL_eq_matrix_impl(T,vec_T,vec_vec_T,mat_T)



#define newNTL_io_matrix_decl(T,vec_T,vec_vec_T,mat_T) 

#define newNTL_io_matrix_impl(T,vec_T,vec_vec_T,mat_T)

newNTL_CLOSE_NNS


//#define newNTL_matrix_impl(T,vec_T,vec_vec_T,mat_T) 
newNTL_OPEN_NNS
template <typename T> Mat<T>::Mat(const Mat<T>& a)  
{  
   numcols = 0;  
   SetDims(a.NumRows(), a.NumCols());  
   rep = a.rep;  
}  
  
template <typename T> Mat<T>& Mat<T>::operator=(const Mat<T>& a)  
{  
   SetDims(a.NumRows(), a.NumCols());  
   rep = a.rep;  
   return *this;  
}  
  
  
template <typename T> Mat<T>::Mat(newNTL_NNS INIT_SIZE_TYPE, long n, long m)  
{  
   numcols = 0;  
   SetDims(n, m);  
}  
  
  
template <typename T> void Mat<T>::SetDims(long n, long m)  
{  
   if (n < 0 || m < 0)  
      newNTL_NNS failwith("SetDims: bad args");  
  
   if (m != numcols) {  
      rep.kill();  
      numcols = m;  
   }  
        
   long oldmax = rep.MaxLength();  
   long i;  
   rep.SetLength(n);  
  
   for (i = oldmax; i < n; i++)  
      rep[i].FixLength(m);  
}  
     
        
template <typename T> void MakeMatrix(Mat<T>& x, const Vec<Vec<T> >& a)  
{  
   long n = a.length();  
  
   if (n == 0) {  
      x.SetDims(0, 0);  
      return;  
   }  
  
   long m = a[0].length();  
   long i;  
  
   for (i = 1; i < n; i++)  
      if (a[i].length() != m) 
         newNTL_NNS Error("nonrectangular matrix");  
  
   x.SetDims(n, m);  
   for (i = 0; i < n; i++)  
      x[i] = a[i];  
}  
  
template <typename T> void swap(Mat<T>& X, Mat<T>& Y)  
{  
   newNTL_NNS swap(X.numcols, Y.numcols);  
   swap(X.rep, Y.rep);  
}  
newNTL_CLOSE_NNS
  




   

//#define newNTL_eq_matrix_impl(T,vec_T,vec_vec_T,mat_T)  
newNTL_OPEN_NNS
template <typename T> long operator==(const Mat<T>& a, const Mat<T>& b)  
{  
   if (a.NumCols() != b.NumCols())  
      return 0;  
  
   if (a.NumRows() != b.NumRows())  
      return 0;  
  
   long n = a.NumRows();  
   long i;  
  
   for (i = 0; i < n; i++)  
      if (a[i] != b[i])  
         return 0;  
  
   return 1;  
}  
  
  
template <typename T> long operator!=(const Mat<T>& a, const Mat<T>& b)  
{  
   return !(a == b);  
}  
newNTL_CLOSE_NNS




//#define newNTL_io_matrix_impl(T,vec_T,vec_vec_T,mat_T)  
newNTL_OPEN_NNS
template <typename T> newNTL_SNS istream& operator>>(newNTL_SNS istream& s, Mat<T>& x)  
{  
   Vec<Vec<T> > buf;  
   s >> buf;  
   MakeMatrix(x, buf);  
   return s;  
}  
  
template <typename T> newNTL_SNS ostream& operator<<(newNTL_SNS ostream& s, const Mat<T>& a)  
{  
   long n = a.NumRows();  
   long i;  
   s << "[";  
   for (i = 0; i < n; i++) {  
      s << a[i]; 
      s << "\n"; 
   }  
   s << "]";  
   return s;  
}  
newNTL_CLOSE_NNS

//COMMON MATRIX ARITHMETIC
newNTL_OPEN_NNS

template <typename NUM>
void add(Mat<NUM>& X, const Mat<NUM>& A, const Mat<NUM>& B)  
{  
   long n = A.NumRows();  
   long m = A.NumCols();  
   if (B.NumRows() != n || B.NumCols() != m)   
      Error("matrix add: dimension mismatch");  
   X.SetDims(n, m);  
   long i, j;  
   for (i = 1; i <= n; i++)   
      for (j = 1; j <= m; j++)  
         add(X(i,j), A(i,j), B(i,j));  
}  
  
template <typename NUM>
void sub(Mat<NUM>& X, const Mat<NUM>& A, const Mat<NUM>& B)  
{  
   long n = A.NumRows();  
   long m = A.NumCols();  
   if (B.NumRows() != n || B.NumCols() != m)  
      Error("matrix sub: dimension mismatch");  
   X.SetDims(n, m);  
   long i, j;  
   for (i = 1; i <= n; i++)  
      for (j = 1; j <= m; j++)  
         sub(X(i,j), A(i,j), B(i,j));  
}  

template <typename NUM>
void mul_aux(Mat<NUM>& X, const Mat<NUM>& A, const Mat<NUM>& B)  
{  
   long n = A.NumRows();  
   long l = A.NumCols();  
   long m = B.NumCols();  
  
   if (l != B.NumRows())  
      Error("matrix mul: dimension mismatch");  
  
   X.SetDims(n, m);  
  
   long i, j, k;  
   NUM acc, tmp;  
  
   for (i = 1; i <= n; i++) {  
      for (j = 1; j <= m; j++) {  
         clear(acc);  
         for(k = 1; k <= l; k++) {  
            mul(tmp, A(i,k), B(k,j));  
            add(acc, acc, tmp);  
         }  
         X(i,j) = acc;  
      }  
   }  
}  
  
  
template <typename NUM>
void mul(Mat<NUM>& X, const Mat<NUM>& A, const Mat<NUM>& B)  
{  
   if (&X == &A || &X == &B) {  
      Mat<NUM> tmp;  
      mul_aux(tmp, A, B);  
      X = tmp;  
   }  
   else  
      mul_aux(X, A, B);  
}  

  
template <typename NUM>
void mul_aux(Vec<NUM>& x, const Mat<NUM>& A, const Vec<NUM>& b)  
{  
   long n = A.NumRows();  
   long l = A.NumCols();  
  
   if (l != b.length())  
      Error("matrix mul: dimension mismatch");  
  
   x.SetLength(n);  
  
   long i, k;  
   NUM acc, tmp;  
  
   for (i = 1; i <= n; i++) {  
      clear(acc);  
      for (k = 1; k <= l; k++) {  
         mul(tmp, A(i,k), b(k));  
         add(acc, acc, tmp);  
      }  
      x(i) = acc;  
   }  
}  
  
  
template <typename NUM>
void mul(Vec<NUM>& x, const Mat<NUM>& A, const Vec<NUM>& b)  
{  
   if (&b == &x || A.position1(x) != -1) {
      Vec<NUM> tmp;
      mul_aux(tmp, A, b);
      x = tmp;
   }
   else
      mul_aux(x, A, b);
}  

template <typename NUM>
void mul_aux(Vec<NUM>& x, const Vec<NUM>& a, const Mat<NUM>& B)  
{  
   long n = B.NumRows();  
   long l = B.NumCols();  
  
   if (n != a.length())  
      Error("matrix mul: dimension mismatch");  
  
   x.SetLength(l);  
  
   long i, k;  
   NUM acc, tmp;  
  
   for (i = 1; i <= l; i++) {  
      clear(acc);  
      for (k = 1; k <= n; k++) {  
         mul(tmp, a(k), B(k,i));
         add(acc, acc, tmp);  
      }  
      x(i) = acc;  
   }  
}  

template <typename NUM>
void mul(Vec<NUM>& x, const Vec<NUM>& a, const Mat<NUM>& B)
{
   if (&a == &x) { 
      Vec<NUM> tmp;
      mul_aux(tmp, a, B);
      x = tmp;
   }
   else
      mul_aux(x, a, B);
}

template <typename NUM>
inline void mul(Mat<NUM>& X, const NUM& a, const Mat<NUM>& B)
   { mul(X, B, a); }


template <typename NUM>
inline Mat<NUM> diag(long n, const NUM& d)
   { Mat<NUM> X; diag(X, n, d); newNTL_OPT_RETURN(Mat<NUM>, X); }

template <typename NUM>
void transpose(Mat<NUM>& X, const Mat<NUM>& A)
{
   long n = A.NumRows();
   long m = A.NumCols();

   long i, j;

   if (&X == & A) {
      if (n == m)
         for (i = 1; i <= n; i++)
            for (j = i+1; j <= n; j++)
               swap(X(i, j), X(j, i));
      else {
         Mat<NUM> tmp;
         tmp.SetDims(m, n);
         for (i = 1; i <= n; i++)
            for (j = 1; j <= m; j++)
               tmp(j, i) = A(i, j);
         X.kill();
         X = tmp;
      }
   }
   else {
      X.SetDims(m, n);
      for (i = 1; i <= n; i++)
         for (j = 1; j <= m; j++)
            X(j, i) = A(i, j);
   }
}

template <typename NUM>
void mul(Mat<NUM>& X, const Mat<NUM>& A, const NUM& b_in)
{
   NUM b = b_in;
   long n = A.NumRows();
   long m = A.NumCols();

   X.SetDims(n, m);

   long i, j;
   for (i = 0; i < n; i++)
      for (j = 0; j < m; j++)
         mul(X[i][j], A[i][j], b);
}

#define EXTERNAL_PRODUCT_MATRIX_DECL(NUMERIC) \
template <typename NUM> \
inline typename ifAneqBthenT<NUM,NUMERIC,void>::type \
mul(Mat<NUM>& X, const Mat<NUM>& A, NUMERIC b_in) { \
    NUM b = b_in; mul(X,A,b); \
} \
template <typename NUM> \
inline typename ifAneqBthenT<NUM,NUMERIC,void>::type \
mul(Mat<NUM>& X, NUMERIC a_in, const Mat<NUM>& B) { \
    NUM a = a_in; mul(X, B, a);  \
} \
template <typename NUM> \
inline typename ifAneqBthenT<NUM,NUMERIC,Mat<NUM> >::type \
operator*(NUMERIC a, const Mat<NUM>& b) {  \
    Mat<NUM> x;  \
    mul(x, b, a);  \
    newNTL_OPT_RETURN(Mat<NUM>, x);  \
} \
template <typename NUM> \
inline typename ifAneqBthenT<NUM,NUMERIC,Mat<NUM> >::type \
operator*(const Mat<NUM>& a, NUMERIC b) {  \
    Mat<NUM> x;  \
    mul(x, a, b);  \
    newNTL_OPT_RETURN(Mat<NUM>, x);  \
}
EXTERNAL_PRODUCT_MATRIX_DECL(long);
EXTERNAL_PRODUCT_MATRIX_DECL(unsigned long);
EXTERNAL_PRODUCT_MATRIX_DECL(int);
EXTERNAL_PRODUCT_MATRIX_DECL(unsigned int);
EXTERNAL_PRODUCT_MATRIX_DECL(double);
EXTERNAL_PRODUCT_MATRIX_DECL(float);

template <typename NUM>
void diag(Mat<NUM>& X, long n, const NUM& d_in)  
{  
   NUM d = d_in;
   X.SetDims(n, n);  
   long i, j;  
  
   for (i = 1; i <= n; i++)  
      for (j = 1; j <= n; j++)  
         if (i == j)  
            X(i, j) = d;  
         else  
            clear(X(i, j));  
}

template <typename NUM>
long IsDiag(const Mat<NUM>& A, long n, const NUM& d)
{
   if (A.NumRows() != n || A.NumCols() != n)
      return 0;

   long i, j;

   for (i = 1; i <= n; i++)
      for (j = 1; j <= n; j++)
         if (i != j) {
            if (!IsZero(A(i, j))) return 0;
         }
         else {
            if (A(i, j) != d) return 0;
         }

   return 1;
}

template <typename NUM>
void ident(Mat<NUM>& X, long n)  
{  
   NUM d = 1;
   X.SetDims(n, n);  
   long i, j;  
  
   for (i = 1; i <= n; i++)  
      for (j = 1; j <= n; j++)  
         if (i == j)  
            X(i, j) = d;  
         else  
            clear(X(i, j));  
}

#define DIAG_MAT_PRIMITIVE_DECL(NUMERIC) \
template <typename NUM> \
inline typename ifAneqBthenT<NUM,NUMERIC,void>::type \
diag(Mat<NUM>& X, long n, NUMERIC d_in) { \
    std::cerr << "diag--" << #NUMERIC << std::endl; \
    NUM d=d_in; \
    diag(X,n,d); \
} \
template <typename NUM> \
inline typename ifAneqBthenT<NUM,NUMERIC,long>::type \
IsDiag(const Mat<NUM>& A, long n, NUMERIC d_in) { \
    std::cerr << "IsDiag--" << #NUMERIC << std::endl; \
    NUM d=d_in; \
    return IsDiag(A,n,d); \
}
DIAG_MAT_PRIMITIVE_DECL(long);
DIAG_MAT_PRIMITIVE_DECL(unsigned long);
DIAG_MAT_PRIMITIVE_DECL(int);
DIAG_MAT_PRIMITIVE_DECL(unsigned);
DIAG_MAT_PRIMITIVE_DECL(double);
DIAG_MAT_PRIMITIVE_DECL(float);


template <typename NUM>
inline void sqr(Mat<NUM>& X, const Mat<NUM>& A)
   { mul(X, A, A); }

template <typename NUM>
inline Mat<NUM> sqr(const Mat<NUM>& A)
   { Mat<NUM> X; sqr(X, A); newNTL_OPT_RETURN(Mat<NUM>, X); }


template <typename NUM>
inline Mat<NUM> transpose(const Mat<NUM>& A)
   { Mat<NUM> x; transpose(x, A); newNTL_OPT_RETURN(Mat<NUM>, x); }

template <typename NUM>
inline Mat<NUM> operator*(const Mat<NUM>& a, const NUM& b)
   { Mat<NUM> x; mul(x, a, b); newNTL_OPT_RETURN(Mat<NUM>, x); }


template <typename NUM>
inline Mat<NUM> operator*(const NUM& a, const Mat<NUM>& b)
   { Mat<NUM> x; mul(x, a, b); newNTL_OPT_RETURN(Mat<NUM>, x); }



template <typename NUM>
inline Mat<NUM>& operator+=(Mat<NUM>& x, const Mat<NUM>& a)
{
   add(x, x, a);
   return x;
}   

template <typename NUM>
inline Mat<NUM>& operator-=(Mat<NUM>& x, const Mat<NUM>& a)
{
   sub(x, x, a);
   return x;
}   


template <typename NUM>
inline Mat<NUM>& operator*=(Mat<NUM>& x, const Mat<NUM>& a)
{
   mul(x, x, a);
   return x;
}   

template <typename NUM>
inline Mat<NUM>& operator*=(Mat<NUM>& x, const NUM& a)
{
   mul(x, x, a);
   return x;
}   
   
template <typename NUM>
inline Mat<NUM>& operator*=(Mat<NUM>& x, long a)
{
   mul(x, x, a);
   return x;
}   

template <typename NUM>
inline Vec<NUM>& operator*=(Vec<NUM>& x, const Mat<NUM>& a)
{
   mul(x, x, a);
   return x;
}   

template <typename NUM>
void negate(Mat<NUM>& X, const Mat<NUM>& A)
{
   long n = A.NumRows();
   long m = A.NumCols();


   X.SetDims(n, m);

   long i, j;
   for (i = 1; i <= n; i++)
      for (j = 1; j <= m; j++)
         negate(X(i,j), A(i,j));
}



template <typename NUM>
long IsZero(const Mat<NUM>& a)
{
   long n = a.NumRows();
   long i;

   for (i = 0; i < n; i++)
      if (!IsZero(a[i]))
         return 0;

   return 1;
}

template <typename NUM>
void clear(Mat<NUM>& x)
{
   long n = x.NumRows();
   long i;
   for (i = 0; i < n; i++)
      clear(x[i]);
}


template <typename NUM>
Mat<NUM> operator+(const Mat<NUM>& a, const Mat<NUM>& b)
{
   Mat<NUM> res;
   add(res, a, b);
   newNTL_OPT_RETURN(Mat<NUM>, res);
}

template <typename NUM>
Mat<NUM> operator*(const Mat<NUM>& a, const Mat<NUM>& b)
{
   Mat<NUM> res;
   mul_aux(res, a, b);
   newNTL_OPT_RETURN(Mat<NUM>, res);
}

template <typename NUM>
Mat<NUM> operator-(const Mat<NUM>& a, const Mat<NUM>& b)
{
   Mat<NUM> res;
   sub(res, a, b);
   newNTL_OPT_RETURN(Mat<NUM>, res);
}


template <typename NUM>
Mat<NUM> operator-(const Mat<NUM>& a)
{
   Mat<NUM> res;
   negate(res, a);
   newNTL_OPT_RETURN(Mat<NUM>, res);
}

template <typename NUM>
Vec<NUM> operator*(const Mat<NUM>& a, const Vec<NUM>& b)
{
   Vec<NUM> res;
   mul_aux(res, a, b);
   newNTL_OPT_RETURN(Vec<NUM>, res);
}

template <typename NUM>
Vec<NUM> operator*(const Vec<NUM>& a, const Mat<NUM>& b)
{
   Vec<NUM> res;
   mul_aux(res, a, b);
   newNTL_OPT_RETURN(Vec<NUM>, res);
}

//conversion from one matrix to another
template<typename NUMA,typename NUMB> 
void conv(Mat<NUMA>& v,const Mat<NUMB>& w) {
    int n = w.NumRows();
    int m = w.NumCols();
    v.SetDims(n,m);
    for (int i=0; i<n; i++) 
    for (int j=0; j<m; j++) 
	conv(v[i][j],w[i][j]);
}

newNTL_CLOSE_NNS



#endif
