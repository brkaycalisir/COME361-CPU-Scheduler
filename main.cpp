#include <iostream>
#include <vector>
#include "scheduler.h"

void CPUScheduler::run_fcfs(std::vector<Process>& processes) {
    std::cout << "\n=== FCFS CPU Scheduling Simulation (PoC) ===\n";
    int current_time = 0;

    for (auto& p : processes) {
        if (current_time < p.arrival_time) {
            current_time = p.arrival_time;
        }
        p.waiting_time = current_time - p.arrival_time;
        p.turnaround_time = p.waiting_time + p.burst_time;

        std::cout << "Process P" << p.id 
                  << " | Start: " << current_time 
                  << " | End: " << (current_time + p.burst_time)
                  << " | Waiting Time: " << p.waiting_time << "\n";

        current_time += p.burst_time;
    }
}

int main() {
    CPUScheduler scheduler;
    
    // Sample Processes: {id, arrival_time, burst_time, waiting_time, turnaround_time}
    std::vector<Process> process_list = {
        {1, 0, 5, 0, 0},
        {2, 1, 3, 0, 0},
        {3, 2, 8, 0, 0}
    };

    scheduler.run_fcfs(process_list);
    return 0;
}