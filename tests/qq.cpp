#include <newNTL/LLL.h>
#include <newNTL/QQ.h>

newNTL_CLIENT;

int main() {
    QQ k;
    cout << "entrez un rationnel" << endl;
    cin >> k;
    cout << k << endl;
    ZZ r = 50;
    QQ x = 1;
    QQ y = "2/5";
    QQ z = x/r;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "x/50: " << z << endl;
    cout << "2*x+5/z: " << ZZ(2)*x+5l/z << endl;
}
