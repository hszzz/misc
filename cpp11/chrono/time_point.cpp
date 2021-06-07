#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;

int main() {
	const chrono::time_point<chrono::system_clock> now =
		chrono::system_clock::now();
	// const time_t t_c = chrono::system_clock::to_time_t(now - chrono::hours(24));
	const time_t t_c = chrono::system_clock::to_time_t(now - 24h); // c++14
	cout << "24 hours ago, the time was " << 
		put_time(localtime(&t_c), "%F %T.\n") << flush;

	chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
	for (int i=0; i<100000; i++) {
		for (int i=0; i<100000; i++) {
		}
	}
	chrono::time_point<chrono::steady_clock> end = chrono::steady_clock::now();

	cout << "duration is " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "us" << endl;
	cout << "duration is " << (end - start) / 1ms << "ms" << endl; // c++14
	cout << "duration is " << (end - start) / 1s << "s" << endl;   // c++14

	return 0;
}

