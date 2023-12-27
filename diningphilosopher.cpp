#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

const int N = 5; // Number of philosophers

std::vector<std::mutex> forks(N);
std::vector<std::thread> philosophers(N);

void philosopher(int philosopher_id) {
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % N;

    while (true) {
        // Think
        std::cout << "Philosopher " << philosopher_id << " is thinking." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));

        // Pick up forks
        forks[left_fork].lock();
        std::cout << "Philosopher " << philosopher_id << " picked up left fork " << left_fork << "." << std::endl;
        forks[right_fork].lock();
        std::cout << "Philosopher " << philosopher_id << " picked up right fork " << right_fork << "." << std::endl;

        // Eat
        std::cout << "Philosopher " << philosopher_id << " is eating." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 1000));

        // Put down forks
        forks[left_fork].unlock();
        std::cout << "Philosopher " << philosopher_id << " put down left fork " << left_fork << "." << std::endl;
        forks[right_fork].unlock();
        std::cout << "Philosopher " << philosopher_id << " put down right fork " << right_fork << "." << std::endl;
    }
}

int main() {
    srand(time(NULL));

    // Create philosopher threads
    for (int i = 0; i < N; ++i) {
        philosophers[i] = std::thread(philosopher, i);
    }

    // Wait for philosopher threads to finish (this will never happen in this example)
    for (int i = 0; i < N; ++i) {
        philosophers[i].join();
    }

    return 0;
}

