#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <string>
#include <vector>

// Bir process'in bilgileri
struct Process {
    int id;
    int arrival_time;     // ne zaman geldi
    int burst_time;       // toplam CPU suresi
    int priority;         // kucuk sayi = yuksek oncelik
    int remaining_time;   // Round Robin icin kalan sure
    int completion_time;  // bittigi an
    int waiting_time;     // sirada bekledigi sure
    int turnaround_time;  // gelisinden bitisine toplam sure
};

// Gantt chart'in bir parcasi: "P<pid>, start'tan end'e kadar CPU'da calisti"
struct GanttEntry {
    int pid;
    int start;
    int end;
};

// Bir algoritmanin sonucu. UI ve karsilastirma kismi SADECE bunu kullanir.
struct ScheduleResult {
    std::string algorithm_name;          // ornek: "SJF", "Round Robin (q=2)"
    std::vector<Process> processes;      // waiting/turnaround dolu, id'ye gore sirali
    std::vector<GanttEntry> gantt;       // calisma sirasi
    double avg_waiting_time = 0;
    double avg_turnaround_time = 0;
};

// Algoritmalar: process listesi alir, sonucu dondurur (ekrana yazdirmaz)
ScheduleResult run_fcfs(std::vector<Process> processes);
ScheduleResult run_sjf(std::vector<Process> processes);                  // non-preemptive
ScheduleResult run_priority(std::vector<Process> processes);             // non-preemptive
ScheduleResult run_round_robin(std::vector<Process> processes, int quantum);

#endif
