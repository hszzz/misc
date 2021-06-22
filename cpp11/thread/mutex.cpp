#include <iostream>
#include <mutex>
#include <thread>

int num = 0;
std::mutex mutex;

void add() {
	for (;;) {
		mutex.lock();
		num++;
		std::cout << "id:" << std::this_thread::get_id() << " add 1" << std::endl;
		mutex.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void print() {
	for (;;) {
		{
			{
				std::lock_guard<std::mutex> lock(mutex);
				std::cout << "id:" << std::this_thread::get_id() 
						  << " num = " << num << std::endl;
			}
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}

int main() {
	std::thread t1(add);
	std::thread t2(print);
	std::thread t3(add);
	std::thread t4(print);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	return 0;
}

