#include <iostream>
#include <functional>

using namespace std;

void print(int a, int b, int c) {
	cout << a <<  " " << b << " " << c << endl;
}

void print1(int a) {
	cout << a << endl;
}

class Test {
public:
	Test() {
		cout << "constructor" << endl;
	}
	~Test() {
		cout << "destructor" << endl;
	}
	void print(int a, int b) {
		cout << a << " " << b << endl;
		cout << "counter: " << this->counter << endl;
	}

	int counter = 0;
};

function<void(int, int)> get_func() {
	Test t;
	auto test_func = bind(&Test::print, t, placeholders::_1, placeholders::_2);
	return test_func;
}

int main() {
	auto f1 = bind(print, placeholders::_1, 
			       placeholders::_2, placeholders::_3);
	f1(1, 2, 3); // 1 2 3

	auto f2 = bind(print, placeholders::_3, 
			       placeholders::_2, placeholders::_1);
	f2(1, 2, 3); // 3 2 1

	bind(print, 1, 2, placeholders::_1)(999);  // 1 2 999
	bind(print, 1, placeholders::_2, placeholders::_1)(999, 888); // 1 888 999

	Test* t = new Test;
	function<void(int, int)> test_func = bind(&Test::print, t, placeholders::_1, placeholders::_2);
	test_func(1, 2);
	delete t;

	// error, t has been deconstructed, it's member counter will be indeterminate.
	test_func(1, 2);
	test_func(999, 2);
	test_func(1, 999);

	auto func = get_func();
	func(555, 555);

	Test t1; // = new Test;
	function<int&(void)> test_mem = bind(&Test::counter, t1);
	// delete t1;
	cout << "test_mem = " << test_mem() << endl;
	test_mem()++;
	cout << "test_mem = " << test_mem() << endl;
	test_mem()--;
	cout << "test_mem = " << test_mem() << endl;

	return 0;
}

