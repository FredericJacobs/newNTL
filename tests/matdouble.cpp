#include <newNTL/LLL.h>
#include <string>
#include <sstream>


newNTL_CLIENT;


int main() {
    Vec<double> v;
    Vec<float> w;
    Vec<RR> z;
    Vec<long> a;
    string s("[0 1.11231231212 2 3.5]");
    string t("[0 1 2 3]");
    const double deux = 2.f;
    const long deuxl = 2;
    istringstream is(s);
    is >> v;
    { istringstream it(s); it >> w; }
    { istringstream it(s); it >> z; }
    { istringstream it(t); it >> a; }
    cout << "w" << w << endl;
    cout << "w+w" << w+w << endl;
    cout << "w-w" << w-w << endl;
    cout << "w*w" << w*w << endl;
    cout << "deux*w" << deux*w << endl;
    cout << "3.14*w" << 3.1415*w << endl;
    cout << "w*3.14" << w*3.1415 << endl;
    cout << v << endl;
    cout << v*2.+3.*v << endl;
    cout << deux*v+v << endl;
    cout << deuxl*v+v << endl;
    cout << a << endl;
    cout << deux*a+a << endl;
    cout << deuxl*a+a << endl;
    cout << "z" << z << endl;
    cout << "z+z" << z+z << endl;
    cout << "z-z" << z-z << endl;
    cout << "z*z" << z*z << endl;
    cout << "2*z" << 2*z << endl;
    cout << "3.14*z" << 3.1415*z << endl;
    cout << "z*3.14" << z*3.1415 << endl;
    double x;
    add(x,1,2);
    Mat<long > m;
    string ms("[[0 1.11231231212 2 3.5][1 1.11231231212 2 3.5][2 1.11231231212 2 3.5][3 1.11231231212 2 3.5]]");
    string msl("[[0 12 2 35][1 11 2 3][2 131 2 5][3 1 2 35]]");
    {istringstream iss(msl); iss >> m;}
    cout << "m: " << m << endl;
    cout << "2*m: " << 2*m << endl;
    cout << "m*2: " << m*2 << endl;
    cout << "2.*m: " << 2.*m << endl;
    cout << "m*2.: " << m*2. << endl;
    cout << "deux*m: " << deux*m <<endl;
    cout << "m*deux: " << m*deux <<endl;
    cout << "deuxl*m: " << deuxl*m <<endl;
    cout << "m*deuxl: " << m*deuxl <<endl;
    cout << "v*m: " << a*m <<endl;
    cout << "m*v: " << m*a <<endl;
    clear(m);
    cout << "clear" << m << endl;
    diag(m,5,10u);
    cout << "diag(m,5,1.225)" << m << endl;
    ident(m,6);
    cout << "ident(m,6)" << m << endl;

}
