#include <iostream>
#include <functional>

using namespace std;

int add(int l, int r) {
	return l + r;
}

class Test {
public:
	static void print() {
		cout << "hello world" << endl;
	}
};

class Test1 {
public:
	void operator() () {
		cout << "hello world" << endl;
	}
};

class Test2 {
public:
	Test2(const function<void()>& cb) : call_back(cb) { }

	void exec() {
		call_back();
	}
private:
	function<void()> call_back;
};

void print() {
	cout << "hello world" << endl;
}

int main() {
	function<int(int, int)> func_add = add;
	cout << func_add(1, 1) << endl;

	function<void(void)> func_print = Test::print;
	func_print();

	Test1 t1;
	function<void(void)> func_print1 = t1;
	func_print1();

	Test2 t2(print);
	t2.exec();
	t2.exec();
	t2.exec();
	t2.exec();
	t2.exec();
	t2.exec();
	t2.exec();

	return 0;
}

