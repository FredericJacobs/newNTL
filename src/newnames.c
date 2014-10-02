
/************************************************************************

This program can be compiled under either C or C++.
It copies its input to its output, substituting all old
newNTL macro names by new newNTL macro names.
This is intended to automate the transition from newNTL 3.1 to 3.5.

Each maximal length alphanumeric substring in the input
is looked up in a table, and if there is a match, the substring
is replaced.

*************************************************************************/


#include <stdio.h>
#include <string.h>

#define NumNames (79)

const char *names[NumNames][2] = {
{ "BB_HALF_MUL_CODE", "newNTL_BB_HALF_MUL_CODE" },
{ "BB_MUL_CODE", "newNTL_BB_MUL_CODE" },
{ "BB_REV_CODE", "newNTL_BB_REV_CODE" },
{ "BB_SQR_CODE", "newNTL_BB_SQR_CODE" },
{ "FFTFudge", "newNTL_FFTFudge" },
{ "FFTMaxRoot", "newNTL_FFTMaxRoot" },
{ "FFTMaxRootBnd", "newNTL_FFTMaxRootBnd" },
{ "QUAD_FLOAT_SPLIT", "newNTL_QUAD_FLOAT_SPLIT" },
{ "WV_newNTL_RANGE_CHECK_CODE", "newNTL_WV_RANGE_CHECK_CODE" },
{ "WordVectorExpansionRatio", "newNTL_WordVectorExpansionRatio" },
{ "WordVectorInputBlock", "newNTL_WordVectorInputBlock" },
{ "WordVectorMinAlloc", "newNTL_WordVectorMinAlloc" },
{ "XD_BOUND", "newNTL_XD_BOUND" },
{ "XD_BOUND_INV", "newNTL_XD_BOUND_INV" },
{ "XD_HBOUND", "newNTL_XD_HBOUND" },
{ "XD_HBOUND_INV", "newNTL_XD_HBOUND_INV" },
{ "ZZ_ARITH_RIGHT_SHIFT", "newNTL_ARITH_RIGHT_SHIFT" },
{ "ZZ_BITS_PER_INT", "newNTL_BITS_PER_INT" },
{ "ZZ_BITS_PER_LONG", "newNTL_BITS_PER_LONG" },
{ "ZZ_DOUBLES_LOW_HIGH", "newNTL_DOUBLES_LOW_HIGH" },
{ "ZZ_DOUBLE_PRECISION", "newNTL_DOUBLE_PRECISION" },
{ "ZZ_EXT_DOUBLE", "newNTL_EXT_DOUBLE" },
{ "ZZ_FDOUBLE_PRECISION", "newNTL_FDOUBLE_PRECISION" },
{ "ZZ_FRADIX", "newNTL_FRADIX" },
{ "ZZ_FRADIX_INV", "newNTL_FRADIX_INV" },
{ "ZZ_FetchHiLo", "newNTL_FetchHiLo" },
{ "ZZ_FetchLo", "newNTL_FetchLo" },
{ "ZZ_HI_WD", "newNTL_HI_WD" },
{ "ZZ_LO_WD", "newNTL_LO_WD" },
{ "ZZ_MAX_INT", "newNTL_MAX_INT" },
{ "ZZ_MAX_LONG", "newNTL_MAX_LONG" },
{ "ZZ_MIN_INT", "newNTL_MIN_INT" },
{ "ZZ_MIN_LONG", "newNTL_MIN_LONG" },
{ "ZZ_NBITS", "newNTL_NBITS" },
{ "ZZ_NBITSH", "newNTL_NBITSH" },
{ "ZZ_NBITS_MAX", "newNTL_NBITS_MAX" },
{ "ZZ_newNTL_SINGLE_MUL_OK", "newNTL_SINGLE_MUL_OK" },
{ "ZZ_PRIME_BND", "newNTL_PRIME_BND" },
{ "ZZ_RADIX", "newNTL_RADIX" },
{ "ZZ_RADIXM", "newNTL_RADIXM" },
{ "ZZ_RADIXROOT", "newNTL_RADIXROOT" },
{ "ZZ_RADIXROOTM", "newNTL_RADIXROOTM" },
{ "ZZ_pRegister", "newNTL_ZZ_pRegister" },
{ "ZZ_pX_BERMASS_CROSSOVER", "newNTL_ZZ_pX_BERMASS_CROSSOVER" },
{ "ZZ_pX_DIV_CROSSOVER", "newNTL_ZZ_pX_DIV_CROSSOVER" },
{ "ZZ_pX_FFT_CROSSOVER", "newNTL_ZZ_pX_FFT_CROSSOVER" },
{ "ZZ_pX_GCD_CROSSOVER", "newNTL_ZZ_pX_GCD_CROSSOVER" },
{ "ZZ_pX_HalfGCD_CROSSOVER", "newNTL_ZZ_pX_HalfGCD_CROSSOVER" },
{ "ZZ_pX_NEWTON_CROSSOVER", "newNTL_ZZ_pX_NEWTON_CROSSOVER" },
{ "ZZ_pX_TRACE_CROSSOVER", "newNTL_ZZ_pX_TRACE_CROSSOVER" },
{ "newntl_eq_matrix_decl", "newNTL_eq_matrix_decl" },
{ "newntl_eq_matrix_impl", "newNTL_eq_matrix_impl" },
{ "newntl_eq_vector_decl", "newNTL_eq_vector_decl" },
{ "newntl_eq_vector_impl", "newNTL_eq_vector_impl" },
{ "newntl_io_matrix_decl", "newNTL_io_matrix_decl" },
{ "newntl_io_matrix_impl", "newNTL_io_matrix_impl" },
{ "newntl_io_vector_decl", "newNTL_io_vector_decl" },
{ "newntl_io_vector_impl", "newNTL_io_vector_impl" },
{ "newntl_matrix_decl", "newNTL_matrix_decl" },
{ "newntl_matrix_impl", "newNTL_matrix_impl" },
{ "newntl_pair_decl", "newNTL_pair_decl" },
{ "newntl_pair_eq_decl", "newNTL_pair_eq_decl" },
{ "newntl_pair_eq_impl", "newNTL_pair_eq_impl" },
{ "newntl_pair_impl", "newNTL_pair_impl" },
{ "newntl_pair_io_decl", "newNTL_pair_io_decl" },
{ "newntl_pair_io_impl", "newNTL_pair_io_impl" },
{ "newntl_vector_decl", "newNTL_vector_decl" },
{ "newntl_vector_default", "newNTL_vector_default" },
{ "newntl_vector_impl", "newNTL_vector_impl" },
{ "newntl_vector_impl_plain", "newNTL_vector_impl_plain" },
{ "zz_pRegister", "newNTL_zz_pRegister" },
{ "zz_pX_BERMASS_CROSSOVER", "newNTL_zz_pX_BERMASS_CROSSOVER" },
{ "zz_pX_DIV_CROSSOVER", "newNTL_zz_pX_DIV_CROSSOVER" },
{ "zz_pX_GCD_CROSSOVER", "newNTL_zz_pX_GCD_CROSSOVER" },
{ "zz_pX_HalfGCD_CROSSOVER", "newNTL_zz_pX_HalfGCD_CROSSOVER" },
{ "zz_pX_MOD_CROSSOVER", "newNTL_zz_pX_MOD_CROSSOVER" },
{ "zz_pX_MUL_CROSSOVER", "newNTL_zz_pX_MUL_CROSSOVER" },
{ "zz_pX_NEWTON_CROSSOVER", "newNTL_zz_pX_NEWTON_CROSSOVER" },
{ "zz_pX_TRACE_CROSSOVER", "newNTL_zz_pX_TRACE_CROSSOVER" },
};


void PrintName(const char *name)
{
   int i;

   i = 0;
   while (i < NumNames && strcmp(name, names[i][0]))
      i++;

   if (i >= NumNames)
      printf("%s", name);
   else
      printf("%s", names[i][1]);
}


int IsAlphaNum(int c)
{
   return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c == '_') || (c >= '0' && c <= '9'));
}

char buf[10000];


int main()
{
   int c;
   int state;
   int len;

   state = 0;
   len = 0;


   do {
      c = getchar();

      switch (state) {
      case 0:
         if (IsAlphaNum(c)) {
            buf[len] = c;
            len++;
            state = 1;
         }
         else {
            if (c != EOF) putchar(c);
         }

         break;

      case 1:
         if (IsAlphaNum(c)) {
            buf[len] = c;
            len++;
         }
         else {
            buf[len] = '\0';
            PrintName(buf);
            len = 0;

            if (c != EOF) putchar(c);
            state = 0;
         }

         break;
      }
   } while (c != EOF);
   
   return 0;
}
