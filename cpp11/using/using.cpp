#include <iostream>
#include <map>

using namespace std;

typedef int my_int;
using my_int1 = int;

/**  error
template <typename T>
typedef map<string, T> my_map;
*/

template <typename T>
struct MyMap {
	typedef map<string, T> type;
};

// cpp11 ↓
template <typename T>
using my_map = map<string, T>; 

int main() {
	my_int a = 1;
	my_int1 b = 1;
	cout << a << " " << b << endl;

	// my_map<int> m;
	MyMap<int>::type m;
	my_map<int> m1;
	m1.insert({"m1", 1});
	m1.insert({"m2", 2});
	for (auto v : m1) {
		cout << v.first << ": " << v.second << endl;
	}

	return 0;
}

