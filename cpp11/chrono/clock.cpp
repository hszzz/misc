#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

void dosomething() {
	for (int i=0; i<100000; i++) {
		for (int i=0; i<1000; i++) {
		}
	}
}

int main() {
	chrono::system_clock::time_point y1970;
	time_t tm =chrono::system_clock::to_time_t(y1970);
	cout << ctime(&tm) << endl;

	chrono::system_clock::time_point today = chrono::system_clock::now();
	time_t td = chrono::system_clock::to_time_t(today);
	cout << "today : " << ctime(&td) << endl;

	chrono::steady_clock::time_point start = chrono::steady_clock::now();
	dosomething();
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	cout << "cost " << (end - start).count() << "ns" << endl;

	// high_resolution_clock = steady_clock
	chrono::high_resolution_clock::time_point start1 = chrono::high_resolution_clock::now();
	dosomething();
	chrono::high_resolution_clock::time_point end1 = chrono::high_resolution_clock::now();
	cout << "cost " << (end1 - start1).count() << "ns" << endl;

	return 0;
}

