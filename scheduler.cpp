#include "scheduler.hpp"
#include <algorithm>
#include <queue>

// Ortak: id'ye gore sirala ve ortalamalari hesapla
static void finish_result(ScheduleResult& r) {
    std::sort(r.processes.begin(), r.processes.end(),
              [](const Process& a, const Process& b) { return a.id < b.id; });
    double tw = 0, tt = 0;
    for (const auto& p : r.processes) {
        tw += p.waiting_time;
        tt += p.turnaround_time;
    }
    r.avg_waiting_time = tw / r.processes.size();
    r.avg_turnaround_time = tt / r.processes.size();
}

// FCFS: ilk gelen ilk calisir
ScheduleResult run_fcfs(std::vector<Process> processes) {
    ScheduleResult r;
    r.algorithm_name = "FCFS";
    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b) {
                  return a.arrival_time < b.arrival_time;
              });

    int time = 0;
    for (auto& p : processes) {
        if (time < p.arrival_time) time = p.arrival_time;
        r.gantt.push_back({p.id, time, time + p.burst_time});
        p.waiting_time = time - p.arrival_time;
        p.turnaround_time = p.waiting_time + p.burst_time;
        p.completion_time = time + p.burst_time;
        time += p.burst_time;
    }
    r.processes = processes;
    finish_result(r);
    return r;
}

// SJF ve Priority ayni mantik: gelmis olanlar arasindan "en iyi" olani sec.
// SJF -> en kisa burst_time, Priority -> en kucuk priority sayisi
static ScheduleResult run_non_preemptive(std::vector<Process> processes, bool use_priority) {
    ScheduleResult r;
    int n = processes.size();
    std::vector<bool> done(n, false);
    int time = 0, finished = 0;

    while (finished < n) {
        int best = -1;
        for (int i = 0; i < n; i++) {
            if (done[i] || processes[i].arrival_time > time) continue;
            if (best == -1) { best = i; continue; }
            int a = use_priority ? processes[i].priority : processes[i].burst_time;
            int b = use_priority ? processes[best].priority : processes[best].burst_time;
            if (a < b) best = i;
        }
        if (best == -1) { time++; continue; }   // kimse gelmedi, CPU bos

        Process& p = processes[best];
        r.gantt.push_back({p.id, time, time + p.burst_time});
        p.waiting_time = time - p.arrival_time;
        p.turnaround_time = p.waiting_time + p.burst_time;
        p.completion_time = time + p.burst_time;
        time += p.burst_time;
        done[best] = true;
        finished++;
    }
    r.processes = processes;
    finish_result(r);
    return r;
}

ScheduleResult run_sjf(std::vector<Process> processes) {
    ScheduleResult r = run_non_preemptive(processes, false);
    r.algorithm_name = "SJF";
    return r;
}

ScheduleResult run_priority(std::vector<Process> processes) {
    ScheduleResult r = run_non_preemptive(processes, true);
    r.algorithm_name = "Priority";
    return r;
}

// Round Robin: herkes en fazla 'quantum' kadar calisir, bitmediyse siranin sonuna gider
ScheduleResult run_round_robin(std::vector<Process> processes, int quantum) {
    ScheduleResult r;
    r.algorithm_name = "Round Robin (q=" + std::to_string(quantum) + ")";
    std::sort(processes.begin(), processes.end(),
              [](const Process& a, const Process& b) {
                  return a.arrival_time < b.arrival_time;
              });

    int n = processes.size();
    for (auto& p : processes) p.remaining_time = p.burst_time;

    std::queue<int> ready;   // siradaki process'lerin indeksleri
    int next = 0;            // henuz kuyruga girmemis ilk process
    int time = 0, finished = 0;

    while (finished < n) {
        while (next < n && processes[next].arrival_time <= time)
            ready.push(next++);

        if (ready.empty()) {   // kimse yok, siradaki gelene atla
            time = processes[next].arrival_time;
            continue;
        }

        int i = ready.front();
        ready.pop();
        Process& p = processes[i];

        int run = std::min(quantum, p.remaining_time);
        r.gantt.push_back({p.id, time, time + run});
        time += run;
        p.remaining_time -= run;

        // Calisirken yeni gelenler, bitmeyen process'ten ONCE kuyruga girer
        while (next < n && processes[next].arrival_time <= time)
            ready.push(next++);

        if (p.remaining_time > 0) {
            ready.push(i);
        } else {
            p.completion_time = time;
            p.turnaround_time = p.completion_time - p.arrival_time;
            p.waiting_time = p.turnaround_time - p.burst_time;
            finished++;
        }
    }
    r.processes = processes;
    finish_result(r);
    return r;
}
