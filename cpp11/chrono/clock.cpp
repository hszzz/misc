#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

int main() {
	chrono::system_clock::time_point y1970;
	time_t tm =chrono::system_clock::to_time_t(y1970);
	cout << ctime(&tm) << endl;
	return 0;
}

