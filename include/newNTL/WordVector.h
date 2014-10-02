
#ifndef newNTL_WordVector__H
#define newNTL_WordVector__H

/**************************************************************

  A WordVector is functionally similar to
  a  generic newNTL vector of _newntl_ulong.  

  Be careful! the MaxLength() function does not return 
    the max length ever set, but rather the max space allocated,
    which *may* be more.

  The FixLength() facility is not available.

  The reason for special-casing is efficiency (of course).

**************************************************************/



#include <newNTL/tools.h>
#include <newNTL/ZZ.h>

newNTL_OPEN_NNS



#ifndef newNTL_RANGE_CHECK
#define newNTL_WV_RANGE_CHECK_CODE 
#else
#define newNTL_WV_RANGE_CHECK_CODE if (i < 0 || !rep || i >= long(rep[-1])) RangeError(i);
#endif

// vectors are allocated in chunks of this size

#ifndef newNTL_WordVectorMinAlloc
#define newNTL_WordVectorMinAlloc (4)
#endif

// vectors are always expanded by at least this ratio

#ifndef newNTL_WordVectorExpansionRatio
#define newNTL_WordVectorExpansionRatio (1.2)
#endif

// controls initialization during input

#ifndef newNTL_WordVectorInputBlock
#define newNTL_WordVectorInputBlock 50
#endif

// controls release functionality

#define newNTL_RELEASE_THRESH (10000)
// #define newNTL_RELEASE_THRESH (0)


class WordVector {  
public:  
   _newntl_ulong *rep;  
   void RangeError(long i) const;  

   WordVector(WordVector& x, INIT_TRANS_TYPE) { rep = x.rep; x.rep = 0; }


  
   WordVector() { rep = 0; }  
   WordVector(INIT_SIZE_TYPE, long n) { rep = 0; DoSetLength(n); }  
   WordVector(const WordVector& a) { rep = 0; *this = a; }     

   WordVector& operator=(const WordVector& a);  

   ~WordVector();  
   void kill(); 

   void release() { if (MaxLength() > newNTL_RELEASE_THRESH) kill(); }
   // this conditinally kills the vector, if its size is excessive

   void DoSetLength(long n);
  
   void SetLength(long n)
   {
      _newntl_ulong *x = rep;
      if (x && long(x[-2] >> 1) >= n && n >= 0)
         x[-1] = n;
      else
         DoSetLength(n);
   }

   void ZeroLength() { if (rep) rep[-1] = 0; }
         
   void SetMaxLength(long n); 
   void QuickSetLength(long n) { rep[-1] = _newntl_ulong(n); } 
  
   long length() const { return (!rep) ?  0 : long(rep[-1]); }  
   long MaxLength() const 
   { return (!rep) ?  0 : long(rep[-2] >> 1); } 
  
   _newntl_ulong& operator[](long i)   
   {  
      newNTL_WV_RANGE_CHECK_CODE  
      return rep[i];  
   }  
  
   const _newntl_ulong& operator[](long i) const 
   {  
      newNTL_WV_RANGE_CHECK_CODE  
      return rep[i];  
   }  
  
   _newntl_ulong& operator()(long i) { return (*this)[i-1]; }  
   const _newntl_ulong& operator()(long i) const { return (*this)[i-1]; } 
   
  
   const _newntl_ulong* elts() const { return rep; }  
   _newntl_ulong* elts() { return rep; }  
         
   static void swap_impl(WordVector& x, WordVector& y);  
   static void append_impl(WordVector& v, _newntl_ulong a); 
   static void append_impl(WordVector& v, const WordVector& w); 
}; 

inline void swap(WordVector& x, WordVector& y) 
   { WordVector::swap_impl(x, y); }

inline void append(WordVector& v, _newntl_ulong a)
   { WordVector::append_impl(v, a); }

inline void append(WordVector& v, const WordVector& w)
   { WordVector::append_impl(v, w); }


newNTL_SNS istream& operator>>(newNTL_SNS istream&, WordVector&);  
newNTL_SNS ostream& operator<<(newNTL_SNS ostream&, const WordVector&);  


long operator==(const WordVector& a, const WordVector& b);  
long operator!=(const WordVector& a, const WordVector& b);


long InnerProduct(const WordVector& a, const WordVector& b);

void ShiftAdd(_newntl_ulong *cp, const _newntl_ulong* ap, long sa, long n);
// cp = cp + (a << n)


long WV_BlockConstructAlloc(WordVector& x, long d, long n);
 
void WV_BlockConstructSet(WordVector& x, WordVector& y, long i);
 
long WV_BlockDestroy(WordVector& x);

long WV_storage(long d);





newNTL_CLOSE_NNS

#endif
