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
Algorithm	Average Waiting Time	Average Turnaround Time
FCFS	12.40	18.20
SJF (Non-Preemptive)	8.15	13.95
Round Robin (Quantum = 4)	10.50	16.30
Priority Scheduling	9.80	15.60
