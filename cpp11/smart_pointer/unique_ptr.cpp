#include <iostream>
#include <functional>
#include <memory>

using namespace std;

unique_ptr<int> get_uni() {
	return unique_ptr<int>(new int{2});
}

class Test {
public:
	Test() {
		cout << "constructor ..." << endl; 
	}
	~Test() {
		cout << "destructor ..." << endl;
	}
};

int main() {
	unique_ptr<int> u(new int{1});
	cout << *u << endl;

	// unique_ptr<int> u1 = u; // error
	
	unique_ptr<int> u2 = std::move(u);
	// cout << *u << endl; // error
	cout << *u2 << endl;

	unique_ptr<int> u3 = get_uni();
	cout << *u3 << endl;

	// unique_ptr<Test> u4(new Test[3]); // error
	unique_ptr<Test, void(*)(Test*)> u5(new Test[3], [](Test* t) { delete[] t; });
	unique_ptr<Test, function<void(Test*)>> u6(new Test[3], [&](Test* t) { delete[] t; });

	return 0;
}

