# CPU Scheduling Simulator

COME 361 Operating Systems – Term Project

A command-line CPU scheduling simulator written in C++. The user enters a
list of processes, chooses a scheduling algorithm, and the program prints the
execution order and performance metrics.

## Algorithms
- FCFS (First-Come, First-Served)
- SJF (Shortest Job First, non-preemptive)
- Round Robin (user-defined time quantum)
- Priority (non-preemptive, smaller number = higher priority)

## Metrics
- Waiting time and turnaround time per process
- Average waiting time and average turnaround time
- Comparison of all algorithms (option 5)

## Build and Run
Requires a C++17 compiler (g++).

```
g++ main.cpp scheduler.cpp -o scheduler
./scheduler        (Windows: .\scheduler)
```

## Usage
1. Enter the number of processes.
2. For each process enter arrival time, burst time and priority.
3. Choose an algorithm (1-4) or compare all (5).
4. For Round Robin, enter the time quantum.

## Project Structure
- `scheduler.hpp` – `Process`, `GanttEntry`, `ScheduleResult` structures and algorithm declarations
- `scheduler.cpp` – algorithm implementations (each returns a `ScheduleResult`)
- `main.cpp` – user input and result printing

## Test results
Test Number	Process Count	Process Details (Arrival, Burst, Priority)	Menu Choice	Quantum
Test 1	4	P1(0, 5, 2), P2(1, 3, 1), P3(2, 8, 4), P4(3, 6, 3)	5 (Compare all)	2
Test 2	3	P1(0, 2, 1), P2(10, 3, 1), P3(10, 3, 1)	5 (Compare all)	4
Test 3	1	P1(0, 3, 1)	5 (Compare all)	10
 
