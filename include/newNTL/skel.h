#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <fplll.h>
#include <stdint.h>
#include <cassert>
#include <newNTL/LLL.h>

#define failwith(errormsg) { \
    cerr << errormsg << "at line " << __LINE__ << endl; \
    cout << errormsg << "at line " << __LINE__ << endl; \
    abort(); \
}

newNTL_CLIENT;

typedef Vec<double> vec_double;

//functions to parse main arguments

//conversion string to anything
static __thread istringstream* global_iss = 0;  
    
template <typename T> inline istringstream& operator>>(const std::string& s,T& obj)
{
    if (global_iss) delete global_iss;
    global_iss = new istringstream (s);
    *(global_iss) >> obj;
    return *(global_iss);
}

template <typename T> inline void PARSE(const std::string& s,T& obj)
{
    istringstream iss(s); iss >> obj;
}

template<>  inline void PARSE(const std::string& s,std::string& obj)
{
    obj = s;
}

//parsing des arguments de main
#define PARSE_MAIN_ARGS ostringstream thesyntax; \
    for (int i=0;i<argc;i++)

#define MATCH_MAIN_ARGID(parsewhat,towhere) \
    if (i==0) thesyntax << "[ " << parsewhat << " " << towhere << " ] "; \
    else if (0==strcmp(argv[i],(parsewhat))) { PARSE( string(argv[++i]) , (towhere) ); continue;}

#define DETECT_MAIN_ARGID(parsewhat,towhere,value) \
    if (i==0) thesyntax << "[ " << parsewhat  << " ] "; \
    else if (0==strcmp(argv[i],(parsewhat))) {towhere = value; continue;}


#define END_OF_MAIN_ARGS() \
    if (i>0) { \
        cerr << "Syntax error at argument" << i << endl; \
        cerr << "Syntax: " << argv[0] << " " << thesyntax.str() << endl; \
        exit(1); \
    }

#define SYNTAX(whatcorrect) \
    if (i>0) { \
	cerr << "Syntax error at argument" << i << endl; \
        cerr << "Syntax: " << argv[0] << " " << thesyntax.str() << endl << whatcorrect << endl; \
        exit(1); \
    }

//-------------------------------------------------------

//DEBUG functions (useful in gdb: p PrintElement(v) )
#define DECLARE_DEBUG_PRINT(T) \
    void PrintElement(T elt) {  cout << elt << endl; }

DECLARE_DEBUG_PRINT(ZZ);
DECLARE_DEBUG_PRINT(RR);
DECLARE_DEBUG_PRINT(vec_ZZ);
DECLARE_DEBUG_PRINT(vec_RR);
DECLARE_DEBUG_PRINT(mat_ZZ);
DECLARE_DEBUG_PRINT(mat_RR);


