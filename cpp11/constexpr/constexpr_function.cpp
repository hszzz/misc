#include <iostream>

using namespace std;	

constexpr int get_num() {
	return 5;
}

constexpr int get_num1() {
	constexpr int i = 1;
	constexpr int j = 1;
	return i + j;
}

int main() {
	cout << get_num() << endl;
	cout << get_num1() << endl;
	return 0;
}

