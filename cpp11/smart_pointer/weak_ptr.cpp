#include <iostream>
#include <memory>

using namespace std;

void test_weak() {
	shared_ptr<int> s(new int{1});
	cout << "s: " << s.use_count() << endl; // 1
	weak_ptr<int> w(s);
	weak_ptr<int> w1(w);
	cout << "s: " << s.use_count() << endl; // 1
	cout << "w: " << w.use_count() << endl; // 1
	cout << "w1: " << w1.use_count() << endl; // 1
}

template <typename T>
void test_weak1(weak_ptr<T> ptr) {
	if (!ptr.expired()) {
		shared_ptr<T> p = ptr.lock(); // return a shared_ptr, use_count++
		cout << "p use_count = " << p.use_count() << " " << "*p = "  << *p << endl;
		return;
	}
	cout << "ptr is expired ..." << endl;
}

void test() {
	shared_ptr<int> p(new int{999});
	test_weak1<int>(p);
	p.reset();
	cout << "===================" << endl;
	test_weak1<int>(p);
}

int main() {
	test_weak();
	cout << "=====================" << endl;
	test();
	return 0;
}

