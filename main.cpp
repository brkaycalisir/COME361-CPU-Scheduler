#include <iostream>
#include <vector>
#include "scheduler.hpp"
void print_result(const ScheduleResult& r) { // Prints the detailed performance report for a single scheduling algorithm
    std::cout << "\n=== " << r.algorithm_name << " ===\n";
    for (const auto& g : r.gantt) // Print the Gantt chart timeline (shows execution blocks, handles IDLE time if PID is 0)
        std::cout << (g.pid == 0 ? std::string("IDLE") : "P" + std::to_string(g.pid)) << " | Start: " << g.start << " | End: " << g.end << "\n";
    std::cout << "\nPID | Waiting | Turnaround\n"; // Print per-process metrics table header
    for (const auto& p : r.processes) // Print individual waiting time and turnaround time for each process
        std::cout << " P" << p.id << " |   " << p.waiting_time << "     |    " << p.turnaround_time << "\n";
    std::cout << "Average Waiting Time    : " << r.avg_waiting_time << "\n"; // Print overall summary averages for the algorithm
    std::cout << "Average Turnaround Time : " << r.avg_turnaround_time << "\n";
}
void print_comparison(const std::vector<ScheduleResult>& results) { // Prints a concise summary comparing all selected scheduling algorithms side-by-side
    std::cout << "\n=== Karsilastirma ===\n";
    for (const auto& r : results)
        std::cout << r.algorithm_name << " -> Avg Waiting: " << r.avg_waiting_time << " | Avg Turnaround: " << r.avg_turnaround_time << "\n";
}
std::vector<Process> read_processes() { // Safely reads process configurations (count, arrival time, burst time, priority) from the user
    int n = 0;// Prompt until a valid, positive number of processes is entered
    while (n <= 0) { std::cout << "Process sayisi: "; if (!(std::cin >> n)) { std::cin.clear(); std::cin.ignore(1000, '\n'); n = 0; } }
    std::vector<Process> list;
    for (int i = 1; i <= n; i++) { // Loop through and gather details for each process (P1, P2, etc.)
        Process p = {i, 0, 0, 0, 0, 0, 0, 0};  // Initialize process struct with default/zero values
        std::cout << "\nP" << i << " icin\n";
        std::cout << "  Arrival time (0 veya daha buyuk): "; // Read and validate Arrival Time (must be >= 0)
        while (!(std::cin >> p.arrival_time) || p.arrival_time < 0) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "  Gecersiz, tekrar gir: "; }
        std::cout << "  Burst time (1 veya daha buyuk): "; // Read and validate Burst Time (must be >= 1)
        while (!(std::cin >> p.burst_time) || p.burst_time <= 0) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "  Gecersiz, tekrar gir: "; }
        std::cout << "  Priority (kucuk sayi = yuksek oncelik): "; // Read and validate Priority (smaller number indicates higher priority)
        while (!(std::cin >> p.priority)) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "  Gecersiz, tekrar gir: "; }
        list.push_back(p); // Add the configured process to our list
    }
    return list;
}
int read_quantum() { int q = 0; std::cout << "Quantum: "; while (!(std::cin >> q) || q <= 0) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "Gecersiz, tekrar gir: "; } return q; }
int main() {
    std::vector<Process> process_list = read_processes(); // 1. Load the list of processes (e.g., from a file or user input)
    int choice = 0;
    std::cout << "\n1) FCFS\n2) SJF\n3) Round Robin\n4) Priority\n5) Hepsini karsilastir\nSecim: "; // 2. Display the scheduling algorithm menu options to the user
    std::cin >> choice; // 3. Handle user choice using conditional statements
    if (choice == 1) print_result(run_fcfs(process_list)); // Run First-Come, First-Served (FCFS) and print its result
    else if (choice == 2) print_result(run_sjf(process_list)); // Run Shortest Job First (SJF) and print its result
    else if (choice == 3) print_result(run_round_robin(process_list, read_quantum())); // Run Round Robin: prompts for quantum via read_quantum() and prints the result
    else if (choice == 4) print_result(run_priority(process_list)); // Run Priority scheduling and print its result
    else if (choice == 5) {  
         // Run all algorithms at once for comparison   // Note: read_quantum() is called here because Round Robin is part of the batch                                                                                                                                                                       
        std::vector<ScheduleResult> results = { run_fcfs(process_list), run_sjf(process_list), run_round_robin(process_list, read_quantum()), run_priority(process_list) };
        for (const auto& r : results) print_result(r); // Print individual results for each algorithm
        print_comparison(results);   // Print the final side-by-side comparison summary table
    } else std::cout << "Gecersiz secim\n"; // Handle invalid menu inputs
    return 0;
}
