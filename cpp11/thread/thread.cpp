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

void func3() {
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::this_thread::yield();
	std::cout << "id:" << std::this_thread::get_id() << " sleep 2 s." << std::endl;
}

void func4() {
	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(3));
	std::cout << "id:" << std::this_thread::get_id() << " sleep 3 s." << std::endl;
}

int main() {
	// std::thread t(func1, 10);
	// std::thread t1(func2);
	// t.join();
	// t1.join();
	
	std::thread t2(func3);
	std::thread t3(func4);
	t2.join();
	t3.join();

	std::cout << "main thread exited ." << std::endl;
	return 0;
}

