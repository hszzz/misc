#include <iostream>
#include <vector>

using namespace std;

// non-aggregate can use {}-initializer by initializer list

void print(initializer_list<int> list) {
	for (auto it=list.begin(); it!=list.end(); it++) {
		cout << *it << " ";
	}
	cout << endl; 
}

class Test {
public:
	Test(const initializer_list<int>& l) {
		for (auto it=l.begin(); it!=l.end(); it++) {
			a.push_back(*it);
		}
	}
private:
	vector<int> a;
};

int main() {
	print({1, 2, 3});

	Test t({1, 2, 3, 3, 2, 1});

	return 0;
}

