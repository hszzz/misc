#include <thread>
#include <iostream>
#include <queue>
#include <condition_variable>

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
		while (queue_.size().empty()) {
			cond_not_empty_.wait(lock);
		}
		T tmp;
		queue_.pop(&tmp);
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

	return 0;
}

