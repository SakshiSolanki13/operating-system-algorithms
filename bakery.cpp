#include <iostream>
#include <vector>
#include <atomic>

class Bakery {
private:
    std::vector<std::atomic<bool>> choosing;
    std::vector<std::atomic<int>> number;

    int numThreads;

public:
    Bakery(int n) : numThreads(n), choosing(n, false), number(n, 0) {}

    void lock(int threadId) {
        choosing[threadId] = true;
        int maxNumber = 0;

        for (int i = 0; i < numThreads; ++i) {
            if (number[i] > maxNumber) {
                maxNumber = number[i];
            }
        }

        number[threadId] = maxNumber + 1;
        choosing[threadId] = false;

        for (int otherThread = 0; otherThread < numThreads; ++otherThread) {
            while (choosing[otherThread]) {
              
            }

            while (number[otherThread] != 0 &&
                   (number[otherThread] < number[threadId] ||
                    (number[otherThread] == number[threadId] && otherThread < threadId))) {
                
            }
        }
    }

    void unlock(int threadId) {
        number[threadId] = 0;
    }
};

Bakery bakery(2);

void criticalSection(int threadId) {
    bakery.lock(threadId);

    
    std::cout << "Thread " << threadId << " is in the critical section." << std::endl;

    bakery.unlock(threadId);

    
    std::cout << "Thread " << threadId << " is in the non-critical section." << std::endl;
}

int main() {
    std::thread thread1(criticalSection, 0);
    std::thread thread2(criticalSection, 1);

    thread1.join();
    thread2.join();

    return 0;
}

