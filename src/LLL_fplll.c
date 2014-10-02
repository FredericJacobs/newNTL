
#include <newNTL/LLL.h>
#include <newNTL/fileio.h>
#include <newNTL/vec_double.h>


#include <newNTL/new.h>

#include <fplll.h>

#include <string>
#include <sstream>
#include <iostream>
newNTL_START_IMPL


void ComputeGS(const mat_ZZ& B, mat_RR& mu, vec_RR& c);

void conv(fplll::IntMatrix& m,const mat_ZZ& B)
{
    std::ostringstream os; os << B;
    std::istringstream is(os.str()); is >> m;
}
void conv(mat_ZZ& B, const fplll::IntMatrix& m)
{
    std::ostringstream os; os << m;
    std::istringstream is(os.str()); is >> B;
}


void LLL_fplll(fplll::IntMatrix& B,double delta)
{
    fplll::lllReduction(B,delta);
}
void LLL_fplll(mat_ZZ& B,double delta)
{
    fplll::IntMatrix BB; conv(BB,B);
    fplll::lllReduction(BB,delta);
    conv(B,BB);
}

void LLL_fplll(fplll::IntMatrix& B, fplll::IntMatrix& U,double delta)
{
    fplll::lllReduction(B,U,delta);
}
void LLL_fplll(mat_ZZ& B, mat_ZZ& U,double delta)
{
    fplll::IntMatrix BB; conv(BB,B);
    fplll::IntMatrix UU; conv(UU,U); //?
    fplll::lllReduction(BB,UU,delta);
    conv(U,UU);
    conv(B,BB);
}

void BKZ_fplll(mat_ZZ& B, mat_ZZ& U, double delta, long beta)
{
    fplll::IntMatrix BB; conv(BB,B);
    fplll::IntMatrix UU; conv(UU,U); //?
    fplll::bkzReduction(BB,UU,beta);
    conv(U,UU);
    conv(B,BB);
}

void BKZ_fplll(mat_ZZ& B, double delta, long beta)
{
    fplll::IntMatrix BB; conv(BB,B);
    fplll::bkzReduction(BB,beta);
    conv(B,BB);    
}

void BKZ_fplll_aborted(mat_ZZ& B, double delta, long beta, long maxLoops)
{
    fplll::BKZParam param;
    fplll::IntMatrix BB; conv(BB,B);
    param.b=&BB;
    //param.u
    param.blockSize=beta;
    param.delta=delta;
    param.flags=BKZ_MAX_LOOPS;
    param.maxLoops=maxLoops;
    fplll::bkzReduction(param);
    conv(B,BB);    
}

newNTL_END_IMPL
