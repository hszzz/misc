#include <iostream>

using namespace std;

class A {
public:
	virtual void hello(int) = 0;
	virtual void hello1() final {}
};

class B final : public A {
public:
	virtual void hello(int i) final override {
		cout << "hello B" << endl;
	}

	// virtual void hello1() {}
};

// class C : public B {}; error

int main() {
	A* obj = new B();
	obj->hello(1);
	return 0;
}

