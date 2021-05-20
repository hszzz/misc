#include <iostream>
#include <map>

using namespace std;

// void test(auto a) {} // error

class Test {
public:
	// static auto a = 1; // error
};

void test() {
	map<string, int> m;
	m.insert({"111", 1});
	m.insert({"222", 2});
	m.insert({"333", 3});

	for (auto it=m.begin(); it!=m.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
}

// test2
struct Test2 {
	static int get_one() {return 1;}
};

struct Test3 {
	static string get_one() {return "1";}
};

template <typename T>
void test2() {
	auto val = T::get_one();
	cout << val << endl;
}

int main() {
	auto a = 1;   // int
	auto b = 1.2; // float

	// auto arr = {1, 2, 3};   // error, arr --> std::initializer_list<int>
	// auto arr[] = {1, 2, 3}; // error
	
	cout << a << " "  << b << endl;

	test();
	test2<Test2>();
	test2<Test3>();
	return 0;
}

