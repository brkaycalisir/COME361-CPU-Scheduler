#include <iostream>
#include <vector>
#include <algorithm>
#include "scheduler.h"

// FCFS: ilk gelen ilk calisir
void CPUScheduler::run_fcfs(std::vector<Process>& processes) {
    std::cout << "\n=== FCFS CPU Scheduling Simulation (PoC) ===\n";

    // Once gelis zamanina gore sirala (ilk gelen basa)
    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b) {
                  return a.arrival_time < b.arrival_time;
              });

    int current_time = 0;
    double total_waiting = 0, total_turnaround = 0;

    for (auto& p : processes) {
        // Process henuz gelmediyse CPU bos bekler
        if (current_time < p.arrival_time) {
            current_time = p.arrival_time;
        }

        p.waiting_time = current_time - p.arrival_time;
        p.turnaround_time = p.waiting_time + p.burst_time;

        std::cout << "Process P" << p.id
                  << " | Start: " << current_time
                  << " | End: " << (current_time + p.burst_time)
                  << " | Waiting: " << p.waiting_time
                  << " | Turnaround: " << p.turnaround_time << "\n";

        total_waiting += p.waiting_time;
        total_turnaround += p.turnaround_time;
        current_time += p.burst_time;
    }

    std::cout << "Average Waiting Time    : " << total_waiting / processes.size() << "\n";
    std::cout << "Average Turnaround Time : " << total_turnaround / processes.size() << "\n";
}

int main() {
    CPUScheduler scheduler;

    // {id, arrival_time, burst_time, waiting_time, turnaround_time}
    std::vector<Process> process_list = {
        {1, 0, 5, 0, 0},
        {2, 1, 3, 0, 0},
        {3, 2, 8, 0, 0}
    };

    scheduler.run_fcfs(process_list);
    return 0;
}
