#include <newNTL/config.h>
#include <newNTL/ctools.h>

#if (defined(newNTL_CXX_ONLY) && !defined(__cplusplus))
#error "CXX_ONLY flag set...must use C++ compiler"
#endif

#include <time.h>


#if (defined(__cplusplus) && !defined(newNTL_CXX_ONLY))
extern "C" double _newntl_GetTime();
#endif


double _newntl_GetTime(void)
{
   staticthread clock_t last_clock = 0;
   staticthread double acc = 0;

   clock_t this_clock;
   double delta;

   this_clock = clock();

   delta = (this_clock - last_clock)/((double)CLOCKS_PER_SEC);
   if (delta < 0) delta = 0;

   acc += delta;
   last_clock = this_clock;

   return acc;
}

