#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>

void func1(int n) {
	for (int i=0; i<n; i++) {
		std::cout << "[ID " << std::this_thread::get_id() << "] "
			 << "i = " << i << std::endl;
		sleep(1);
	}
}

void func2() {
	for (int i=0; i<5; i++) {
		std::cout << "[ID " << std::this_thread::get_id() << "] "
			 << "i = " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main() {
	std::thread t(func1, 10);
	std::thread t1(func2);
	t.join();
	t1.join();
	return 0;
}

