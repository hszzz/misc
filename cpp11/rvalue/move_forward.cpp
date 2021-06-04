#include <iostream>

using namespace std;
void test1() {
	auto&& a = 5; // a -> int&&
	auto&& b = a; // b -> int&

	auto c = 1;
	auto&& d = c; // d -> int&

	int e = 2;
	auto& f = e;
	auto& g = f;  // g -> int&

	const int& h = 1;
	const int&& i = 2;
	auto&& j = h; // j -> const int&
	auto&& k = i; // k -> const int&

	const auto&& l = 3; // l -> int&&
}

template <typename T>
void cb(T&& t) {
	cout << "[T&&] ..." << t << endl;
}

template <typename T>
void cb(T& t) {
	cout << "[T&] ..." << t << endl;
}

template<typename T>
void test_forward1(T&& t) {
	cb(t);
}

void test2() {
	int a = 1;
	test_forward1(a); // T&
	int& b = a;
	test_forward1(b); // T&
	int&& c = 2;
	test_forward1(c); // T&

	test_forward1(std::move(c)); // T&
	test_forward1(std::forward<int&&>(c)); // T&
}

void test3() {
	int a = 1;
	int& b = a;
	int&& c = 2;

	cb(a); // T&
	cb(b); // T&
	cb(c); // T&
	cb(3); // T&&

	cb(std::move(a)); // T&&
	cb(std::move(b)); // T&&
	cb(std::move(c)); // T&&
}

template <typename T>
void test5(T&& t) {
	cb(t);
	cb(std::move(t));
	cb(std::forward<T>(t));
}

int main() {
	test1();
	cout << "--------" << endl;
	test2();
	cout << "--------" << endl;
	test3();
	cout << "--------" << endl;

	cout << endl << "TEST ............." << endl;
	test5(1); // T& T&& T&&
	cout << "--------" << endl;
	int a = 1;
	test5(a); // T& T&& T&
	cout << "--------" << endl;
	test5(std::forward<int>(a)); // T& T&& T&&
	cout << "--------" << endl;
	test5(std::forward<int&>(a)); // T& T&& T&
	cout << "--------" << endl;
	test5(std::forward<int&&>(a)); // T& T&& T&&
	return 0;
}

