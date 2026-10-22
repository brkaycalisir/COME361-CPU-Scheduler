#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <vector>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

class CPUScheduler {
public:
    void run_fcfs(std::vector<Process>& processes);
};

#endif