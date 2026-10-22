#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>

// Bir process'in bilgileri
struct Process {
    int id;               // process numarasi (P1, P2...)
    int arrival_time;     // ne zaman geldi
    int burst_time;       // CPU'da kac birim calisacak
    int waiting_time;     // kuyrukta ne kadar bekledi
    int turnaround_time;  // gelisinden bitisine toplam sure
};

class CPUScheduler {
public:
    void run_fcfs(std::vector<Process>& processes);
};

#endif
