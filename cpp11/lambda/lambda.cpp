#include <iostream>
#include <functional>

using namespace std;

int main() {
	[]() {
		cout << "hello world!" << endl;
	}();

	return 0;
}

