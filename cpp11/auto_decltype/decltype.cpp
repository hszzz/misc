#include<iostream> 

using namespace std;

template <typename T, typename N>
// decltype(t + n) add(T t, N n) { // error
auto add(T t, N n) -> decltype(t + n) {
	return t + n;
}

class Test {
public:
	int t = 1;
};

int main() {
	int a = 1;
	decltype(a + 1) b = 2;

	cout << a << " " << b << endl;
	cout << add(1, 1.1) << endl;

	decltype((a)) c = a;  // c --> int&
	c = 3;
	cout << a << endl;

	const Test test;
	decltype(test.t) t = 999; // t --> int
	t = 1000;
	cout << t << endl;

	decltype((test.t)) t1 = 999; // t --> const int
	// t1 = 1000;
	cout << t1 << endl;

	return 0;
}

