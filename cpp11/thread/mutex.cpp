#include <iostream>
#include <mutex>
#include <thread>

int num = 0;
std::mutex mutex;

void add() {
	for (;;) {
		mutex.lock();
		num++;
		mutex.unlock();
		std::cout << "id:" << std::this_thread::get_id() << " add 1" << std::endl;
	}
}

void print() {
	for (;;) {
		{
			std::lock_guard<std::mutex> lock(mutex);
			std::cout << "id:" << std::this_thread::get_id() << " num = " << num << std::endl;
		}
	}
}

int main() {
	std::thread t1(add);
	std::thread t2(print);
	t1.join();
	t2.join();
	return 0;
}

