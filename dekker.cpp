#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

const int N = 2;

std::atomic<int> turn;
std::atomic<bool> flag[N];

void enter_region(int process) {
    int other = 1 - process;
    flag[process] = true;

    while (flag[other]) {
        if (turn == other) {
            flag[process] = false;

            while (turn == other) {
                // Busy-wait
            }

            flag[process] = true;
        }
    }
}

void leave_region(int process) {
    int other = 1 - process;
    turn = other;
    flag[process] = false;
}

void process_function(int process_number) {
    for (int i = 0; i < 5; ++i) {
        enter_region(process_number);

        // Critical section
        std::cout << "Process " << process_number << " is in the critical section." << std::endl;

        leave_region(process_number);

        // Non-critical section
        std::cout << "Process " << process_number << " is in the non-critical section." << std::endl;

        // Sleep to simulate some work being done
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    turn = 0;
    flag[0] = false;
    flag[1] = false;

    std::thread thread1(process_function, 0);
    std::thread thread2(process_function, 1);

    thread1.join();
    thread2.join();

    return 0;
}

