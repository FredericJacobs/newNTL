#include <newNTL/LLL.h>

newNTL_CLIENT;

int main() {
    mat_ZZ B;
    mat_RR mu;
    vec_RR C;
    cin >> B;
    //ComputeGS(B,mu,C);
    //cerr << C << endl;
    cout << "LLL reduction" << endl;
    LLL_fplll(B,0.99);
    cout << B << endl;
    ComputeGS(B,mu,C);
    cerr << C << endl;
    cout << "BKZ reduction (20)" << endl;
    BKZ_fplll(B,0.99,20);
    ComputeGS(B,mu,C);
    cerr << C << endl;
    cout << "BKZ reduction (30)" << endl;
    BKZ_fplll(B,0.99,30);
    ComputeGS(B,mu,C);
    cerr << C << endl;
    cout << "BKZ reduction (40)" << endl;
    BKZ_fplll(B,0.99,40);
    ComputeGS(B,mu,C);
    cerr << C << endl;
}


