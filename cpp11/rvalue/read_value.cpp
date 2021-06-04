#include <iostream>

using namespace std;

class Test {
public:
	Test() : arr(new int[1000000]) {
		cout << "constructor ..." << endl;
	}

	Test(const Test& t) : arr(new int[1000000]) {
		cout << "copy constructor ..." << endl;
		for (int i=0; i<1000000; i++) {
			arr[i] = t.arr[i];
		}
	}

	Test(Test&& t) : arr(t.arr) {
		cout << "move constructor ..." << endl;
		t.arr = nullptr;
	}

	~Test() {
		cout << "destructor ..." << endl;
		delete[] arr;
	}
private:
	int* arr;
};

Test get_test() {
	return Test();
}

int main() {
	int a = 5;
	int& b = a;

	int&& c = 6;

	// int&& d = c; // error
	// int&& d = std::move(c); // ok

	cout << a << " " << b << " " << c << endl;

	Test t = get_test();

	return 0;
}

