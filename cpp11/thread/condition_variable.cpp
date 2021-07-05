#include <thread>
#include <iostream>
#include <queue>
#include <condition_variable>
#include <functional>

template <typename T>
class SyncQueue {
public:
	SyncQueue(int size) : max_(size) { }

	void push(const T& val) {
		std::unique_lock<std::mutex> lock(mutex_);
		while (queue_.size() == max_) {
			cond_not_full_.wait(lock);
		}
		queue_.push(val);
		std::cout << "push : " << val << std::endl;
		cond_not_empty_.notify_all();
	}	

	T pop() {
		std::unique_lock<std::mutex> lock(mutex_);
		while (queue_.empty()) {
			cond_not_empty_.wait(lock);
		}
		T tmp = queue_.front();
		queue_.pop();
		std::cout << "pop : " << tmp << std::endl;
		return tmp;
	}

	bool full() const {
		std::lock_guard<std::mutex> lock(mutex_);
		return queue_.size() == max_;
	}

	bool empty() const {
		std::lock_guard<std::mutex> lock(mutex_);
		return queue_.empty();
	}

	int size() const {
		std::lock_guard<std::mutex> lock(mutex_);
		return queue_.size();
	}
private:
	std::queue<T> queue_;
	std::mutex mutex_;
	std::condition_variable cond_not_empty_;
	std::condition_variable cond_not_full_;
	int max_;
};

int main() {
	SyncQueue<int> queue(3);
	auto producer = std::bind(&SyncQueue<int>::push, &queue, std::placeholders::_1);
	auto consumer = std::bind(&SyncQueue<int>::pop, &queue);

	std::thread t1[5];
	std::thread t2[5];
	
	for (int i=0; i<5; i++) {
		t1[i] = std::thread(producer, i);
		t2[i] = std::thread(consumer);
	}

	for (int i=0; i<5; i++) {
		t1[i].join();
		t2[i].join();
	}

	return 0;
}

