#include <iostream>
#include <queue>

struct Process {
    int id;
    int burstTime;
};

void roundRobinScheduling(const std::vector<Process>& processes, int timeQuantum) {
    std::queue<Process> readyQueue = std::queue<Process>(std::deque<Process>(processes.begin(), processes.end()));

    while (!readyQueue.empty()) {
        Process currentProcess = readyQueue.front();
        readyQueue.pop();

        int remainingTime = std::min(timeQuantum, currentProcess.burstTime);
        currentProcess.burstTime -= remainingTime;

        std::cout << "Processing Process " << currentProcess.id << " for " << remainingTime << " units." << std::endl;

        if (currentProcess.burstTime > 0) {
            readyQueue.push(currentProcess); 
        }
    }
}

int main() {
    std::vector<Process> processes = {{1, 10}, {2, 5}, {3, 8}, {4, 2}};
    int timeQuantum = 3;

    roundRobinScheduling(processes, timeQuantum);

    return 0;
}

