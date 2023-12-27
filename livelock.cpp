#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;

void threadFunction1() {
    while (true) {
        std::unique_lock<std::mutex> lock1(mutex1, std::defer_lock);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate some work

        std::unique_lock<std::mutex> lock2(mutex2, std::defer_lock);

        if (std::try_lock(lock1, lock2) == -1) {
            std::cout << "Thread 1: Acquired both locks." << std::endl;
            // Release locks and break the loop
            lock1.unlock();
            lock2.unlock();
            break;
        } else {
            std::cout << "Thread 1: Failed to acquire locks, releasing and retrying." << std::endl;
            lock1.unlock();
            lock2.unlock();
        }
    }
}

void threadFunction2() {
    while (true) {
        std::unique_lock<std::mutex> lock2(mutex2, std::defer_lock);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate some work

        std::unique_lock<std::mutex> lock1(mutex1, std::defer_lock);

        if (std::try_lock(lock2, lock1) == -1) {
            std::cout << "Thread 2: Acquired both locks." << std::endl;
            // Release locks and break the loop
            lock2.unlock();
            lock1.unlock();
            break;
        } else {
            std::cout << "Thread 2: Failed to acquire locks, releasing and retrying." << std::endl;
            lock2.unlock();
            lock1.unlock();
        }
    }
}

int main() {
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);

    t1.join();
    t2.join();

    return 0;
}

