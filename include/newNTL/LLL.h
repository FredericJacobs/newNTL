#ifndef newNTL_LLL__H
#define newNTL_LLL__H

#include <newNTL/mat_ZZ.h>
#include <newNTL/mat_RR.h>

newNTL_OPEN_NNS

long LLL(ZZ& det, mat_ZZ& B, long verbose = 0);
long LLL(ZZ& det, mat_ZZ& B, mat_ZZ& U, long verbose = 0);

long LLL(ZZ& det, mat_ZZ& B, long a, long b, long verbose = 0);
long LLL(ZZ& det, mat_ZZ& B, mat_ZZ& U, long a, long b, long verbose = 0);

long LLL_plus(vec_ZZ& D, mat_ZZ& B, mat_ZZ& U, long verbose=0);
long LLL_plus(vec_ZZ& D, mat_ZZ& B, long verbose=0);
long LLL_plus(vec_ZZ& D, mat_ZZ& B, mat_ZZ& U, long a, long b, long verbose=0);
long LLL_plus(vec_ZZ& D, mat_ZZ& B, long a, long b, long verbose=0);

long image(ZZ& det, mat_ZZ& B, long verbose = 0);
long image(ZZ& det, mat_ZZ& B, mat_ZZ& U, long verbose = 0);

long LatticeSolve(vec_ZZ& x, const mat_ZZ& A, const vec_ZZ& y, long reduce=0);



typedef long (*LLLCheckFct)(const vec_ZZ&); 

extern double LLLStatusInterval;
extern char *LLLDumpFile;


// classical Gramm-Schmidt versions
void LLL_fplll(mat_ZZ& B, double delta = 0.99);
void LLL_fplll(mat_ZZ& B, mat_ZZ& U, double delta = 0.99);
void BKZ_fplll(mat_ZZ& BB, double delta=0.99, long BlockSize=10);
void BKZ_fplll(mat_ZZ& BB, mat_ZZ& U, double delta=0.99, 
         long BlockSize=10);
void BKZ_fplll_aborted(mat_ZZ& BB, double delta=0.99, long BlockSize=10, long maxLoops=5);

long LLL_FP(mat_ZZ& B, double delta = 0.99,
	    long deep = 0, LLLCheckFct check = 0, long verbose = 0);

long LLL_FP(mat_ZZ& B, mat_ZZ& U, double delta = 0.99, long deep = 0,
           LLLCheckFct check = 0, long verbose = 0);


long BKZ_FP(mat_ZZ& BB, double delta=0.99, long BlockSize=10, long prune=0,
         LLLCheckFct check = 0, long verbose = 0) ;
long BKZ_FP(mat_ZZ& BB, mat_ZZ& U, double delta=0.99, 
         long BlockSize=10, long prune=0, 
         LLLCheckFct check = 0, long verbose = 0);

long LLL_XD(mat_ZZ& B, double delta = 0.99, long deep = 0,
           LLLCheckFct check = 0, long verbose = 0);
long LLL_XD(mat_ZZ& B, mat_ZZ& U, double delta = 0.99, long deep = 0,
           LLLCheckFct check = 0, long verbose = 0);


long BKZ_XD(mat_ZZ& BB, double delta=0.99, long BlockSize=10, long prune=0,
         LLLCheckFct check = 0, long verbose = 0);
long BKZ_XD(mat_ZZ& BB, mat_ZZ& U, double delta=0.99,
         long BlockSize=10, long prune=0, LLLCheckFct check = 0, long verbose = 0);

long LLL_QP(mat_ZZ& B, double delta = 0.99, long deep = 0,
           LLLCheckFct check = 0, long verbose = 0);
long LLL_QP(mat_ZZ& B, mat_ZZ& U, double delta = 0.99, long deep = 0,
           LLLCheckFct check = 0, long verbose = 0);


long BKZ_QP(mat_ZZ& BB, double delta=0.99, long BlockSize=10, long prune=0,
         LLLCheckFct check = 0, long verbose = 0);
long BKZ_QP(mat_ZZ& BB, mat_ZZ& U, double delta=0.99,
         long BlockSize=10, long prune=0, LLLCheckFct check = 0, long verbose = 0);

long BKZ_QP1(mat_ZZ& BB, double delta=0.99, long BlockSize=10, long prune=0,
         LLLCheckFct check = 0, long verbose = 0);
long BKZ_QP1(mat_ZZ& BB, mat_ZZ& U, double delta=0.99,
         long BlockSize=10, long prune=0, LLLCheckFct check = 0, long verbose = 0);

long LLL_RR(mat_ZZ& B, double delta = 0.99, long deep = 0,
           LLLCheckFct check = 0, long verbose = 0);
long LLL_RR(mat_ZZ& B, mat_ZZ& U, double delta = 0.99, 
            long deep = 0, LLLCheckFct check = 0, long verbose = 0);


long BKZ_RR(mat_ZZ& BB, double delta=0.99, long BlockSize=10, 
            long prune=0, LLLCheckFct check = 0, long verbose = 0);

long BKZ_RR(mat_ZZ& BB, mat_ZZ& U, double delta=0.99, 
            long BlockSize=10, long prune=0, LLLCheckFct check = 0, long verbose = 0);


// Givens rotations versions

long G_LLL_FP(mat_ZZ& B, double delta = 0.99,
	    long deep = 0, LLLCheckFct check = 0, long verbose = 0);

long G_LLL_FP(mat_ZZ& B, mat_ZZ& U, double delta = 0.99, long deep = 0,
           LLLCheckFct check = 0, long verbose = 0);


long G_BKZ_FP(mat_ZZ& BB, double delta=0.99, long BlockSize=10, long prune=0,
         LLLCheckFct check = 0, long verbose = 0) ;
long G_BKZ_FP(mat_ZZ& BB, mat_ZZ& U, double delta=0.99, 
         long BlockSize=10, long prune=0, 
         LLLCheckFct check = 0, long verbose = 0);

long G_LLL_XD(mat_ZZ& B, double delta = 0.99, long deep = 0,
           LLLCheckFct check = 0, long verbose = 0);
long G_LLL_XD(mat_ZZ& B, mat_ZZ& U, double delta = 0.99, long deep = 0,
           LLLCheckFct check = 0, long verbose = 0);


long G_BKZ_XD(mat_ZZ& BB, double delta=0.99, long BlockSize=10, long prune=0,
         LLLCheckFct check = 0, long verbose = 0);
long G_BKZ_XD(mat_ZZ& BB, mat_ZZ& U, double delta=0.99,
         long BlockSize=10, long prune=0, LLLCheckFct check = 0, long verbose = 0);

long G_LLL_QP(mat_ZZ& B, double delta = 0.99, long deep = 0,
           LLLCheckFct check = 0, long verbose = 0);
long G_LLL_QP(mat_ZZ& B, mat_ZZ& U, double delta = 0.99, long deep = 0,
           LLLCheckFct check = 0, long verbose = 0);


long G_BKZ_QP(mat_ZZ& BB, double delta=0.99, long BlockSize=10, long prune=0,
         LLLCheckFct check = 0, long verbose = 0);
long G_BKZ_QP(mat_ZZ& BB, mat_ZZ& U, double delta=0.99,
         long BlockSize=10, long prune=0, LLLCheckFct check = 0, long verbose = 0);

long G_BKZ_QP1(mat_ZZ& BB, double delta=0.99, long BlockSize=10, long prune=0,
         LLLCheckFct check = 0, long verbose = 0);
long G_BKZ_QP1(mat_ZZ& BB, mat_ZZ& U, double delta=0.99,
         long BlockSize=10, long prune=0, LLLCheckFct check = 0, long verbose = 0);

long G_LLL_RR(mat_ZZ& B, double delta = 0.99, long deep = 0,
           LLLCheckFct check = 0, long verbose = 0);
long G_LLL_RR(mat_ZZ& B, mat_ZZ& U, double delta = 0.99, 
            long deep = 0, LLLCheckFct check = 0, long verbose = 0);


long G_BKZ_RR(mat_ZZ& BB, double delta=0.99, long BlockSize=10, 
            long prune=0, LLLCheckFct check = 0, long verbose = 0);

long G_BKZ_RR(mat_ZZ& BB, mat_ZZ& U, double delta=0.99, 
            long BlockSize=10, long prune=0, LLLCheckFct check = 0, long verbose = 0);

void ComputeGS(const mat_ZZ& B, mat_RR& mu, vec_RR& c);


void NearVector(vec_ZZ& ww, const mat_ZZ& BB, const vec_ZZ& a);

newNTL_CLOSE_NNS

#endif
