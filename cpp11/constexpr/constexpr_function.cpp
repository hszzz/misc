#include <iostream>

using namespace std;	

constexpr int get_num() {
	return 5;
}

// c++11 -> error; c++14 -> ok
constexpr int get_num1() {
	// constexpr int i = 1;
	// constexpr int j = 1;
	// return i + j;
	return 2;
}

template<typename T>
constexpr T get(T t) {
	return t;
}

class Test {
public:
	constexpr Test(int i, int j) : i(i), j(j) {}

	void print() {
		cout << i << " " << j << endl;
	}

	int i;
	int j;
};

int main() {
	cout << get_num() << endl;
	// cout << get_num1() << endl;
	
	constexpr int i = 1;
	cout << get(i) << endl; // constexpr function

	int j = 1;
	cout << get(j) << endl; // common function

	constexpr Test t(1, 2);
	t.print();

	return 0;
}

