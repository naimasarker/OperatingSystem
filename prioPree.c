#include <stdio.h>


struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};


void preemptive_priority_scheduling(struct Process processes[], int n) {
    int total_time = 0;
    int completed = 0;
    float average_turnaround_time = 0, average_waiting_time = 0;
    int current_process = -1; 

    for (int i = 0; i < n; i++) {
        processes[i].remaining_burst_time = processes[i].burst_time;
    }

    while (completed < n) {
        int highest_priority_index = -1;
        int highest_priority = __INT_MAX__;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= total_time && processes[i].priority < highest_priority && processes[i].remaining_burst_time > 0) {
                highest_priority_index = i;
                highest_priority = processes[i].priority;
            }
        }

       
        if (highest_priority_index != -1) {
            
            if (current_process != -1 && processes[highest_priority_index].priority < processes[current_process].priority) {
                current_process = highest_priority_index;
            }
            
            else if (current_process == -1) {
                current_process = highest_priority_index;
            }
        }

        
        if (current_process != -1) {
            processes[current_process].remaining_burst_time--;
            total_time++;

        
            if (processes[current_process].remaining_burst_time == 0) {
                completed++;
                processes[current_process].completion_time = total_time;
                processes[current_process].turnaround_time = processes[current_process].completion_time - processes[current_process].arrival_time;
                processes[current_process].waiting_time = processes[current_process].turnaround_time - processes[current_process].burst_time;
                average_turnaround_time += processes[current_process].turnaround_time;
                average_waiting_time += processes[current_process].waiting_time;

                
                current_process = -1;
            }
        } else {
            total_time++;
        }
    }

   
    average_turnaround_time /= n;
    average_waiting_time /= n;

   
    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("\nAverage Turnaround Time: %.2f\nAverage Waiting Time: %.2f\n", average_turnaround_time, average_waiting_time);
}

int main() {
    struct Process processes[] = { {1, 0, 20, 40}, {2, 25, 25, 30}, {3, 30, 25, 30}, {4, 60, 15, 35}, {5, 100, 10, 5}, {6, 105, 10, 10} };
    int n = sizeof(processes) / sizeof(processes[0]);

    preemptive_priority_scheduling(processes, n);

    return 0;
}
