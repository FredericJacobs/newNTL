
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <newNTL/config.h>


#ifndef newNTL_GMP_LIP


int main()
{
   fprintf(stderr, "newNTL_GMP_LIP flag not set\n");

   return 0;
}



#else


#include <gmp.h>
#include <newNTL/mach_desc.h>

void print2k(FILE *f, long k, long bpl)
{
   long m, l;
   long first;

   if (k <= 0) {
      fprintf(f, "((double) 1.0)");
      return;
   }

   m = bpl - 2;
   first = 1;

   fprintf(f, "(");

   while (k > 0) {
      if (k > m)
         l = m;
      else
         l = k;

      k = k - l;


      if (first)
         first = 0;
      else
         fprintf(f, "*");

      fprintf(f, "((double)(1L<<%ld))", l);
   }

   fprintf(f, ")");
}

void Error(const char *s)
{
   fprintf(stderr, "%s\n", s);
   abort();
}


int main()
{
   long bpl;
   long newntl_zz_nbits, newntl_wsp_nbits, newntl_sp_nbits;

   fprintf(stderr, "newNTL_GMP_LIP flag set\n");

   bpl = newNTL_BITS_PER_LONG;


   /*
    * We require that the number of bits per limb quantity correspond to the
    * number of bits of a long, or possibly a "long long" that is twice as wide
    * as a long.  These restrictions will almost certainly be satisfied, unless
    * GMP is installed using the newly proposed "nail" option.
    */

   newntl_zz_nbits = 0;

   if (sizeof(mp_limb_t) == sizeof(long) && mp_bits_per_limb == bpl)
      newntl_zz_nbits = bpl;
   else if (sizeof(mp_limb_t) == 2*sizeof(long) && mp_bits_per_limb == 2*bpl)
      newntl_zz_nbits = 2*bpl;
   else
      Error("sorry...this is a funny gmp");

   if (sizeof(mp_size_t) != sizeof(long) &&
       sizeof(mp_size_t) != sizeof(int))

   Error("sorry...this is a funny gmp");

   newntl_wsp_nbits = bpl - 2;

   newntl_sp_nbits = newNTL_NBITS_MAX;

   if (sizeof(mp_size_t) < sizeof(long)) {
      printf("#define newNTL_SMALL_MP_SIZE_T\n");
      fprintf(stderr, "setting newNTL_SMALL_MP_SIZE_T\n");
   }

   fprintf(stderr, "newNTL_ZZ_NBITS = %ld\n", newntl_zz_nbits);
   fprintf(stderr, "newNTL_WSP_NBITS = %ld\n", newntl_wsp_nbits);
   fprintf(stderr, "newNTL_SP_NBITS = %ld\n", newntl_sp_nbits);

   printf("#define newNTL_ZZ_NBITS (%ld)\n",  newntl_zz_nbits);

   printf("#define newNTL_ZZ_FRADIX ");
   print2k(stdout, newntl_zz_nbits, bpl);
   printf("\n");

   return 0;
}

#endif
