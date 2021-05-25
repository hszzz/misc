#include <iostream>

using namespace std;

class Test {
public:
	void operator()() {
		cout << "hello world" << endl;
	}
};

void print() {
	cout << "hello world" << endl;
}

int print1(int i, float f) {
	cout << "hello world" << endl;
	return 0;
}

using func_ptr = void(*)(int);
class Test1 {
public:
	static void print(int) {
		cout << "hello world\n";
	}	

	operator func_ptr () {
		return print;
	}
};

class Test2 {
public:
	void print(int) {
		cout << "hello world\n";
	}
	int m;
};

int main() {
	Test t;
	t();

	void (*func)() = &print;
	func();

	using func1 = int(*)(int, float);
	func1 f = print1;
	f(1, 1.1);

	Test1 t1;
	t1(1);

	void (Test2::*func_ptr2)(int) = &Test2::print;
	int Test2::*obj_ptr = &Test2::m;

	Test2 t2;
	(t2.*func_ptr2)(1);
	t2.*obj_ptr = 3;
	cout << t2.m << endl;

	return 0;
}

