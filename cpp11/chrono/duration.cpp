#include <iostream>
#include <chrono>

using namespace std;

int main() {
	chrono::hours h(1);
	cout << "1 hour : "  << h.count() << endl;
	chrono::milliseconds ms(1000);
	cout << "1000ms : " << ms.count() << endl;

	chrono::microseconds us = ms*6;
	cout << "us : " << us.count() << endl;

	chrono::duration<int, ratio<1, 1>> hz(20);
	cout << hz.count() << "hz" << endl;

	chrono::duration<double, ratio<1, 36>> d(3);
	cout << d.count() << endl;
}

