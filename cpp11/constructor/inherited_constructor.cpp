#include <iostream>

using namespace std;

class Base {
public:
	Base(int a, float b, string c) : a(a), b(b), c(c) { }

	Base() : Base(1, 1, "1") { }
	Base(int a) : Base(a, 1, "1") { }
	Base(int a, float b) : Base(a, b, "1") { }
private:
	int a;
	float b;
	string c;
};

class Child : public Base {
public:
	using Base::Base;
private:
	int d{1};
};

int main() {
	Child c;
	Child c1(1);
	Child c2(1, 1.1);
	Child c3(1, 1.1, "hello");

	return 0;
}

