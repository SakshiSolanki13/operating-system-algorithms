#include <iostream>
#include <vector>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

void firstComeFirstServe(std::vector<Process>& processes) {
    int currentTime = 0;

    for (const Process& process : processes) {
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime; 
        }

        std::cout << "Processing Process " << process.id << " for " << process.burstTime << " units." << std::endl;
        currentTime += process.burstTime;
    }
}

int main() {
    std::vector<Process> processes = {{1, 0, 6}, {2, 2, 8}, {3, 3, 7}, {4, 5, 3}};

    firstComeFirstServe(processes);

    return 0;
}

