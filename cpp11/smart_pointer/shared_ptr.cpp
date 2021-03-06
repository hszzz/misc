#include <iostream>
#include <memory>

using namespace std;

class Test {
public:
	Test() {
		cout << "Test()" << endl;
	}

	Test(int) {
		cout << "Test(int)" << endl;
	}
	
	Test(string) {
		cout << "Test(string)" << endl;
	}

	~Test() {
		cout << "~Test()" << endl;
	}
};

void test_init() {
	shared_ptr<Test> s(new Test(1));
	cout << "s: " << s.use_count() << endl;			// 1

	shared_ptr<Test> s1(s);
	cout << "s: " << s.use_count() << endl;			// 2
	cout << "s1: " << s1.use_count() << endl;		// 2
	
	shared_ptr<Test> s2 = s;
	cout << "s: " << s.use_count() << endl;			// 3
	cout << "s2: " << s2.use_count() << endl;		// 3

	shared_ptr<Test> s3(std::move(s)); 
	cout << "s: " << s.use_count() << endl;			// 0
	cout << "s3: " << s3.use_count() << endl;		// 3

	shared_ptr<Test> s4 = std::move(s1); 
	cout << "s1: " << s1.use_count() << endl;		// 0
	cout << "s4: " << s4.use_count() << endl;		// 3

	shared_ptr<Test> s5 = make_shared<Test>();
	shared_ptr<Test> s6 = make_shared<Test>(1);
	shared_ptr<Test> s7 = make_shared<Test>("hello world");

	shared_ptr<Test> s8 = s2;
	cout << "s2: " << s2.use_count() << endl; // 4
	cout << "s3: " << s3.use_count() << endl; // 4
	cout << "s8: " << s8.use_count() << endl; // 4
	s8.reset(new Test()); // s3--  s8 = 1
	cout << "s2: " << s2.use_count() << endl; // 3
	cout << "s3: " << s3.use_count() << endl; // 3
	cout << "s8: " << s8.use_count() << endl; // 1
}

// shared_ptr can't work well when it is managing an object array
void test_user_defined_delete() { 
	cout << __FUNCTION__ << endl;
	// shared_ptr<Test> s(new Test[5]);	// error
	shared_ptr<Test> s(new Test[5], [](Test* t) { delete[] t; });
	shared_ptr<Test> s1(new Test[5], default_delete<Test[]>());
}

template <typename T>
shared_ptr<T> make_shared_array_ptr(size_t t) {
	return shared_ptr<T>(new T[t], [](T* t) { delete[] t; });
}

int main() {
	test_init();
	test_user_defined_delete();

	auto arr = make_shared_array_ptr<Test>(5);

	return 0;
}

