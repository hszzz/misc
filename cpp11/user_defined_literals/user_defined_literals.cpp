#include <iostream>

using namespace std;

constexpr int operator"" _multi2(unsigned long long int n) {
	return n * 2;
}

struct my_type {
	const char* x;

	void print() {
		cout << "x: " << x << endl;
	}
};

constexpr my_type operator"" _x(const char* x, size_t) {
	return my_type{x};
}

void operator"" _print(const char* s) {
	cout << s << endl;
}

int main() {
	cout << 2_multi2 << endl;

	my_type t = "hello world!"_x;
	t.print();

	0x123ABC_print;

	return 0;
}

