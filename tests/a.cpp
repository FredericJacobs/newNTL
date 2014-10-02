#include <iostream>

using namespace std;

class A {
    int x;
    public:
	A() {x=0;}
	A(const A&) {x=0;}
};

template <typename T> void f(T x);
template<> void f(const A& x) {cout << "f(const A& x)" << endl;}
template<> void f(A x) {cout << "f(A x)" << endl; }

int main() {
    A a;
    f(a);
    f(A());
}
