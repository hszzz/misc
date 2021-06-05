#include <iostream>
#include <vector>

using namespace std;

vector<int> gv{1, 2, 3, 2, 1};

vector<int> get_gv() {
	cout << __FUNCTION__ << endl;
	return gv;
}

int main() {
	vector<int> vec{1, 2, 3, 3, 2, 1};
	for (auto& v : vec) {
		v *= 2;
	}	

	for (const auto& v : vec) {
		cout << v << " ";
	}
	cout << endl;

	for (auto v : get_gv()) { // only call get_gv() once
		cout << v << " ";
	}
	cout << endl;

	return 0;
}

