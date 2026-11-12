#include <iostream>
#include <vector>
#include "scheduler.hpp"
void print_result(const ScheduleResult& r) {
    std::cout << "\n=== " << r.algorithm_name << " ===\n";
    for (const auto& g : r.gantt)
        std::cout << (g.pid == 0 ? std::string("IDLE") : "P" + std::to_string(g.pid)) << " | Start: " << g.start << " | End: " << g.end << "\n";
    std::cout << "\nPID | Waiting | Turnaround\n";
    for (const auto& p : r.processes)
        std::cout << " P" << p.id << " |   " << p.waiting_time << "     |    " << p.turnaround_time << "\n";
    std::cout << "Average Waiting Time    : " << r.avg_waiting_time << "\n";
    std::cout << "Average Turnaround Time : " << r.avg_turnaround_time << "\n";
}
void print_comparison(const std::vector<ScheduleResult>& results) {
    std::cout << "\n=== Karsilastirma ===\n";
    for (const auto& r : results)
        std::cout << r.algorithm_name << " -> Avg Waiting: " << r.avg_waiting_time << " | Avg Turnaround: " << r.avg_turnaround_time << "\n";
}
std::vector<Process> read_processes() {
    int n = 0;
    while (n <= 0) { std::cout << "Process sayisi: "; if (!(std::cin >> n)) { std::cin.clear(); std::cin.ignore(1000, '\n'); n = 0; } }
    std::vector<Process> list;
    for (int i = 1; i <= n; i++) {
        Process p = {i, 0, 0, 0, 0, 0, 0, 0};
        std::cout << "\nP" << i << " icin\n";
        std::cout << "  Arrival time (0 veya daha buyuk): ";
        while (!(std::cin >> p.arrival_time) || p.arrival_time < 0) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "  Gecersiz, tekrar gir: "; }
        std::cout << "  Burst time (1 veya daha buyuk): ";
        while (!(std::cin >> p.burst_time) || p.burst_time <= 0) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "  Gecersiz, tekrar gir: "; }
        std::cout << "  Priority (kucuk sayi = yuksek oncelik): ";
        while (!(std::cin >> p.priority)) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "  Gecersiz, tekrar gir: "; }
        list.push_back(p);
    }
    return list;
}
int read_quantum() { int q = 0; std::cout << "Quantum: "; while (!(std::cin >> q) || q <= 0) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "Gecersiz, tekrar gir: "; } return q; }
int main() {
    std::vector<Process> process_list = read_processes();
    int choice = 0;
    std::cout << "\n1) FCFS\n2) SJF\n3) Round Robin\n4) Priority\n5) Hepsini karsilastir\nSecim: ";
    std::cin >> choice;
    if (choice == 1) print_result(run_fcfs(process_list));
    else if (choice == 2) print_result(run_sjf(process_list));
    else if (choice == 3) print_result(run_round_robin(process_list, read_quantum()));
    else if (choice == 4) print_result(run_priority(process_list));
    else if (choice == 5) {
        std::vector<ScheduleResult> results = { run_fcfs(process_list), run_sjf(process_list), run_round_robin(process_list, read_quantum()), run_priority(process_list) };
        for (const auto& r : results) print_result(r);
        print_comparison(results);
    } else std::cout << "Gecersiz secim\n";
    return 0;
}
