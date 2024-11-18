#include <stdio.h>
#include <stdbool.h>

int main() {
    int n; // Number of processes
    int burst_times[20], remaining_times[20]; // Arrays for burst and remaining times
    int completed = 0; // Number of completed processes
    int current_time = 0; // Tracks current time
    
    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input burst times for each process
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_times[i]);
        remaining_times[i] = burst_times[i]; // Initially, remaining time is the burst time
    }

    // Main loop: keep going until all processes are completed
    while (completed < n) {
        int time_quantum; // Define time quantum dynamically

        // Input dynamic time quantum
        printf("\nEnter time quantum for this round: ");
        scanf("%d", &time_quantum);

        // Go through all processes in order
        for (int i = 0; i < n; i++) {
            // If process is already completed, skip it
            if (remaining_times[i] == 0) {
                continue;
            }

            // Check if process can finish in this time slice
            if (remaining_times[i] <= time_quantum) {
                current_time += remaining_times[i]; // Use the remaining time
                printf("Process %d finishes at time %d\n", i + 1, current_time);
                remaining_times[i] = 0; // Mark it as completed
                completed++; // Increment completed count
            } else {
                // Process gets only the time quantum slice
                current_time += time_quantum;
                remaining_times[i] -= time_quantum;
                printf("Process %d runs for %d units, remaining time: %d\n", 
                       i + 1, time_quantum, remaining_times[i]);
            }
        }
    }

    printf("\nAll processes are completed at time %d.\n", current_time);
    return 0;
}
