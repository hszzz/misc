#include <iostream>

using namespace std;

class Test {
public:
	Test(int a) : a(a) { }
	void print() {
		cout << a << endl;
	}
private:
	int a;
};

// using uniform initialization must be aggregate: 
// 1. no user-defined constructor
// 2. no private or protected and static member
// 3. no base class
// 4. no virtual function
// 5. no { } and = initialize member in class (c++11 ×, since c++14 √)

int main() {
	int a = 1;
	int a1 = { 1 };
	int a2{ 1 };
	cout << a << endl;
	cout << a1 << endl;
	cout << a2 << endl;

	Test t = 1;
	Test t1 = { 2 };
	Test t2{ 3 };
	Test t3(3);
	t.print();
	t1.print();
	t2.print();
	t3.print();

	return 0;
}

