
#ifndef newNTL_fileio__H
#define newNTL_fileio__H

#include <newNTL/tools.h>

#if (defined(newNTL_STD_CXX) || defined(newNTL_PSTD_NHF))

#include <fstream>                                                              

#else

#include <fstream.h>

#endif

#if 0
namespace foo_bar {

class ofstream;
class ifstream;

}
#endif

newNTL_OPEN_NNS


void OpenWrite(newNTL_SNS ofstream& s, const char *name);

// opens file for writing...aborts if fails

void OpenRead(newNTL_SNS ifstream& s, const char *name);

// opens file for reading

char *FileName(const char* stem, const char *ext);

// builds the name "stem.ext"

char *FileName(const char* stem, const char *ext, long d);

// builds the name stem.ext.d

newNTL_CLOSE_NNS

#endif


