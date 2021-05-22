#include <iostream>

using namespace std;

class A {
public:
	A() : A(0, 0, 0) { }
	A(int a) : A(a, 0, 0) { }
	A(int a, int b) : A(a, b, 0) { }
	A(int a, int b, int c) : a(a), b(b), c(c) { }
private:
	int a;
	int b;
	int c;
};

int main() {
	A a(1, 1, 1);
	A a1(1, 1);
	A a2(1);
	A a3();
	return 0;
}

