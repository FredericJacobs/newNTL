
#ifndef newNTL_pair__H
#define newNTL_pair__H

#include <newNTL/tools.h>

#define newNTL_pair_decl(S,T,pair_S_T)  \
class pair_S_T {  \
public:  \
   S a;  \
   T b;  \
  \
   pair_S_T() { }  \
   pair_S_T(const pair_S_T& l__x) : a(l__x.a), b(l__x.b) { } \
   pair_S_T& operator=(const pair_S_T& l__x) { a = l__x.a; b = l__x.b; return *this; } \
   pair_S_T(const S& l__x, const T& l__y) : a(l__x), b(l__y) { }  \
   ~pair_S_T() { }  \
};  \
  \
inline pair_S_T cons(const S& l__x, const T& l__y) { return pair_S_T(l__x, l__y); } \




#define newNTL_pair_io_decl(S,T,pair_S_T) \
newNTL_SNS istream& operator>>(newNTL_SNS istream&, pair_S_T&);  \
  \
newNTL_SNS ostream& operator<<(newNTL_SNS ostream&, const pair_S_T&);  \



#define newNTL_pair_eq_decl(S,T,pair_S_T)  \
inline long operator==(const pair_S_T& l__x, const pair_S_T& l__y)  \
   { return l__x.a == l__y.a && l__x.b == l__y.b; }  \
inline long operator!=(const pair_S_T& l__x, const pair_S_T& l__y) \
   { return !(l__x == l__y); }  \



// For compatability...
#define newNTL_pair_impl(S,T,pair_S_T)


#define newNTL_pair_io_impl(S,T,pair_S_T)  \
newNTL_SNS istream& operator>>(newNTL_SNS istream& l__s, pair_S_T& l__x)  \
{  \
   long l__c;  \
  \
   if (!l__s) newNTL_NNS Error("bad pair input");  \
  \
   l__c = l__s.peek();  \
   while (newNTL_NNS IsWhiteSpace(l__c)) {  \
      l__s.get();  \
      l__c = l__s.peek();  \
   }  \
  \
   if (l__c != '[')  \
      newNTL_NNS Error("bad pair input");  \
  \
   l__s.get();  \
  \
   if (!(l__s >> l__x.a))   \
      newNTL_NNS Error("bad pair input");  \
   if (!(l__s >> l__x.b))  \
      newNTL_NNS Error("bad pair input");  \
  \
   l__c = l__s.peek();  \
   while (newNTL_NNS IsWhiteSpace(l__c)) {  \
      l__s.get();  \
      l__c = l__s.peek();  \
   }  \
  \
   if (l__c != ']')  \
      newNTL_NNS Error("bad pair input");  \
  \
   l__s.get();  \
  \
   return l__s;  \
}  \
  \
newNTL_SNS ostream& operator<<(newNTL_SNS ostream& l__s, const pair_S_T& l__x)  \
{  \
   return l__s << "[" << l__x.a << " " << l__x.b << "]";  \
}  \



// For compatability...
#define newNTL_pair_eq_impl(S,T,pair_S_T)




#endif
