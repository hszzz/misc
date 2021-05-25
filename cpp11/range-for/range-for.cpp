#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<int> vec{1, 2, 3, 3, 2, 1};
	for (auto& v : vec) {
		v *= 2;
	}	

	for (const auto& v : vec) {
		cout << v << " ";
	}
	cout << endl;
	return 0;
}

