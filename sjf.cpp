#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

bool compareProcesses(const Process& a, const Process& b) {
    return a.burstTime < b.burstTime;
}

void shortestJobFirst(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), compareProcesses);

    int currentTime = 0;

    for (const Process& process : processes) {
        std::cout << "Processing Process " << process.id << " for " << process.burstTime << " units." << std::endl;
        currentTime += process.burstTime;
    }
}

int main() {
    std::vector<Process> processes = {{1, 0, 6}, {2, 2, 8}, {3, 3, 7}, {4, 5, 3}};

    shortestJobFirst(processes);

    return 0;
}

