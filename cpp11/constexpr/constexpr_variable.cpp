#include <iostream>

using namespace std;

void func1(const int n) {
	int num[n]; // g++: ok msvc: error 
}

int f() {
	return 1;
}

void func2() {
	constexpr int i = 1 + 2 + 3; // ok

	// constexpr int j = f();       // error
	int n = 1;
	// constexpr int m = n + 1;        // error
}

struct Test {
	int x;
};

int main() {
	int n = 1;
	func1(n);
	func2();

	constexpr Test t{1};
	// t.x = 2;		// error
	constexpr int x = t.x;

	return 0;
}

