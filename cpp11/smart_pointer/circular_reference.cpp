#include <iostream>
#include <memory>

using namespace std;

class A;
class B;
class C;

class A {
public:
	shared_ptr<B> sb;
	shared_ptr<C> sc;
	~A() {
		cout << "~A" << endl;
	}
};

class B {
public:
	shared_ptr<A> sa;
	~B() {
		cout << "~A" << endl;
	}
};

void test() {
	shared_ptr<A> s1(new A);
	shared_ptr<B> s2(new B); 

	s1->sb = s2;
	s2->sa = s1;
	// A and B can't be destructed ...
}

class C {
public:
	weak_ptr<A> sa;
	~C() {
		cout << "~C" << endl;
	}
};

void test1() {
	shared_ptr<A> s1(new A);
	shared_ptr<C> s2(new C); 

	s1->sc = s2;
	s2->sa = s1;
}

int main() {
	test();
	test1();
	return 0;
}

