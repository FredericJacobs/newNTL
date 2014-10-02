#include <newNTL/LLL.h>

newNTL_CLIENT;

int main() {
    RR x;
    cout << "entrez un x" << endl;
    cin >> x;
    cout << "vous avez dit: " << x << endl;
    cout << "voici trois nombres aléatoires:" << endl;
    for (int i=0; i<3; i++)
      cout << random_RR() << endl;      
    RR y = 2.;
    ZZ p = 5;
    cout << x << "+" << y << "=" << x+y << endl;
    cout << x << "+" << y << "+" << p << "=" << x+y+p << endl;
    RR a = 2;
    for (int i=1; i<100; i++) {
      a = a*2+x;
      cout << a << endl;
    }
    a=2;
    for (int i=1; i<100; i++) {
      a = a/2;
      cout << a << endl;
    }
    RR::SetPrecision(1000);
    RR::SetOutputPrecision(1000);
    RR pi; ComputePi(pi);
    cout << "pi=" << pi << endl;
    for (double i=0; i<10; i++) {
      cout << "cos("<< i/5.<<"pi)=" << cos(i*pi/5.) << endl;
    }
    cout << "sqrt(2)=" << sqrt(RR(2)) << endl;
    cout << (pow(sqrt(RR(2)),17)) << endl;
    cout << RoundToZZ(pow(sqrt(RR(2)),17)) << endl;
    cout << FloorToZZ(pow(sqrt(RR(2)),17)) << endl;
    cout << CeilToZZ(pow(sqrt(RR(2)),17)) << endl;
}


