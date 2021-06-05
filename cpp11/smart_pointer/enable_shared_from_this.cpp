#include <iostream>
#include <memory>

using namespace std;

class Test {
public:
	Test(int a, int b) : a(a), b(b) {
		cout << "a = " << a << "  b = " << b << endl;
	}

	void print() {
		cout << "call print: " << a << " " << b << endl;
	}

	shared_ptr<Test> get_this() {
		return shared_ptr<Test>(this);
	}
	~Test() {
		cout << "~Test ..." << endl;
	}
private:
	int a;
	int b;
};

void test() {
	shared_ptr<Test> s(new Test(888, 999));
	s->print();

	/**
	 * s --> Test <-- s1
	 */
	shared_ptr<Test> s1 = s->get_this(); // free(): double free detected in tcache 2
	s1->print();

	cout << "s use_count = " << s.use_count() << endl;   // 1
	cout << "s1 use_count = " << s1.use_count() << endl; // 1
}

class Test1 : public enable_shared_from_this<Test1> {
public:
	Test1(int a, int b) : a(a), b(b) {
		cout << "a = " << a << "  b = " << b << endl;
	}

	void print() {
		cout << "call print: " << a << " " << b << endl;
	}

	shared_ptr<Test1> get_this() {
		return shared_from_this();			// based on weak_ptr
	}
	~Test1() {
		cout << "~Test1 ..." << endl;
	}
private:
	int a;
	int b;
};

void test1() {
	shared_ptr<Test1> s(new Test1(888, 999));
	s->print();
	shared_ptr<Test1> s1 = s->get_this();
	s1->print();

	cout << "s use_count = " << s.use_count() << endl;   // 2
	cout << "s1 use_count = " << s1.use_count() << endl; // 2
}

int main() {
	test1();
	return 0;
}

