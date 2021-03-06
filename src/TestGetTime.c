

#include <newNTL/config.h>

#include <stdlib.h>
#include <stdio.h>

#if (defined(__cplusplus) && !defined(newNTL_CXX_ONLY))
extern "C" double _newntl_GetTime();
#else
extern double _newntl_GetTime();
#endif

/* Assuming the processor speed is at most 200GHz, and that
 * the clock resolution is at least 1 millisecond, the following
 * code should correctly determine if the GetTime function
 * is working properly, and should not run for more than 
 * a few seconds on a machine with a speed of at least 100MHz.
 */

#define LOOP_COUNT (400)

int main(int argc, char **argv)
{
   long a, x, n, m;
   long i, j, k;
   double t0, t1;

   fprintf(stderr, "running");

   x = atol(argv[1]); /* = 1 */

   n = atol(argv[2]); /* = 1048576 = 2^20 */

   m = atol(argv[3]); /* = 1048575 = 2^20 - 1 */

   k = -1;
   t0 = _newntl_GetTime();

   a = 1;
   
   for (i = 1; i <= LOOP_COUNT; i++) {
      for (j = 0; j < n; j++) 
         a = (a + x) & m;

      if (a == 17) return -2; /* keeps the compiler honest! */

      t1 = _newntl_GetTime();
      if (t1 > t0) { fprintf(stderr, "\n"); return 0; }

      if ((i % 10) == 0) {
         fprintf(stderr, ".");
      }
   }

   fprintf(stderr, "\n");
   return -1;
}
