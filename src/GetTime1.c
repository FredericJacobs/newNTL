#include <newNTL/config.h>

#if (defined(newNTL_CXX_ONLY) && !defined(__cplusplus))
#error "CXX_ONLY flag set...must use C++ compiler"
#endif

#include <sys/time.h>
#include <sys/resource.h>

#if (defined(__cplusplus))
extern "C"
#else
extern
#endif
int getrusage(int, struct rusage*);

#if (defined(__cplusplus) && !defined(newNTL_CXX_ONLY))
extern "C" double _newntl_GetTime();
#endif

double _newntl_GetTime(void)
{
   struct rusage used;

   getrusage(RUSAGE_SELF, &used);
   return (used.ru_utime.tv_sec + used.ru_stime.tv_sec +
      (used.ru_utime.tv_usec + used.ru_stime.tv_usec) / 1e6);
}

