
#include <newNTL/ctools.h>


#include <stdlib.h>
#include <math.h>

#if (defined(newNTL_CXX_ONLY) && !defined(__cplusplus))
#error "CXX_ONLY flag set...must use C++ compiler"
#endif

/*
 * An IEEE double x is finite if and only if x - x == 0.
 * The function _newntl_IsFinite implements this logic;  however,
 * it does not completely trust that an optimizing compiler
 * really implements this correctly, and so it goes out of its way to
 * confuse the compiler.  For a good compiler that respects IEEE floating
 * point arithmetic, this is not be necessary, but it is better
 * to be a bit paranoid.
 *
 * Like the routine _newntl_ForceToMem below, this routine has the
 * side effect of forcing its argument into memory.
 */

double _newntl_IsFinite__local;
double *_newntl_IsFinite__ptr1 = &_newntl_IsFinite__local;
double *_newntl_IsFinite__ptr2 = &_newntl_IsFinite__local;
double *_newntl_IsFinite__ptr3 = &_newntl_IsFinite__local;
double *_newntl_IsFinite__ptr4 = &_newntl_IsFinite__local;

long _newntl_IsFinite(double *p)
{
   *_newntl_IsFinite__ptr1 = *p;
   *_newntl_IsFinite__ptr3 = (*_newntl_IsFinite__ptr2 - *p);
   if (*_newntl_IsFinite__ptr4 != 0.0) return 0;
   return 1;
}


/*
 * On machines with wide floating point registers, the routine _newntl_ForceToMem
 * is used to force a floating point double to a memory location.
 * This relies on "separate compilation" model, so that optimizing
 * compilers cannot "optimize away" the whole thing.
 */


void _newntl_ForceToMem(double *p)
{ }



/*
 * The routine _newntl_ldexp(x, e) is like the standard ldexp(x, e) routine,
 * except that it takes a long exponent e, rather than an int exponenet.
 * Some care is taken to ensure reasonable overflow/undeflow behavior.
 * If the value of e does not fit into an int, then the result
 * is x*infinity or x*0, as appropriate.
 * Of course, this can only happen on platforms where long is wider
 * than int (e.g., most 64-bit platforms).
 *
 * We go out of our way to hide the fact that we are multiplying/dividing
 * by zero, so as to avoid unnecessary warnings, and to prevent 
 * overly-agressive optimizing compilers from screwing things up.
 */

double _newntl_ldexp_zero = 0.0;

double _newntl_ldexp(double x, long e)
{
   if (e > newNTL_MAX_INT)
      return x/_newntl_ldexp_zero;
   else if (e < newNTL_MIN_INT)
      return x*_newntl_ldexp_zero;
   else
      return ldexp(x, ((int) e));
}


void _newntl_abort(void)
{
   _newntl_abort_cxx_callback();
   abort();
}



