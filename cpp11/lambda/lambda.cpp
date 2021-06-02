#include <iostream>
#include <functional>

using namespace std;

class Test {
public:
	Test(): a(0), b(0) { }

	void print() {
		cout << a << " " << b << endl;
	}
	
	void mod() {
		[this]() {
			this->a++;
			this->b++;
		}();
	}

private:
	int a;
	int b;
};

void return_test() {
	auto a = []() {
		return 1;
	};
	
	auto b = []() -> int {
		return 2;
	};
	cout << a << " " << b << endl;
}

void mutable_test() {
	int a = 0;
	[=]() mutable {
		a += 3;  // a is a duplication
		cout << "a = " << a << endl; // 3
	}();
	cout << __FUNCTION__ << " " << a << endl; // 0
}

void function_bind_test() {
	function<int(int)> f1 = [](int a) { return a;};
	cout << f1(999) << endl;;

	function<int(int)> f2 = bind([](int a, int b) { return a + b;}, 1, placeholders::_1);
	cout << f2(888) << endl;
	using func_ptr = int(*)(int);
	// 没有捕获任何外部变量的匿名函数
	 func_ptr f = [](int a)
	 {
	     return a;  
     };
	     // 函数调用
	 cout << f(9999999) << endl;
}

int main() {
	[]() {
		cout << "hello world!" << endl;
	}();

	int a = 0;
	int b = 0;
	[=]() {
		// a++; // a is read-only
		cout << a << " " << b << endl;
	}();

	[&]() {
		a++; 
		cout << a << " " << b << endl; // 1 0
	}();
	cout << a << endl; // 1

	[a, &b]() {
		// a++;
		b++;
	}();
	cout << b << endl; // 1

	Test t;
	t.print();
	t.mod();
	t.print();

	return_test();
	mutable_test();
	function_bind_test();

	return 0;
}

