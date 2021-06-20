#include <thread>
#include <iostream>
#include <mutex>

// call_once: call once in multiple threads
using namespace std;

once_flag flag;

void call_once_func() {
	std::cout << "I should be showed only once." << std::endl;
}

void func() {
	static int num = 1;
	std::call_once(flag, call_once_func);
	std::cout << "num addr:" << &num << " num = " << num++ << std::endl;
}

int main() {
	std::thread t(func);
	std::thread t1(func);
	std::thread t2(func);
	t.join();
	t1.join();
	t2.join();
	return 0;
}

