/*#include <stdio.h>


struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};


void sjf_preemptive(struct Process processes[], int n) {
    int total_time = 0;
    int completed = 0;
    float average_turnaround_time = 0, average_waiting_time = 0;

   
    for (int i = 0; i < n; i++) {
        processes[i].remaining_burst_time = processes[i].burst_time;
    }

    while (completed < n) {
        int min_burst_index = -1;
        int min_burst_time = __INT_MAX__;

        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= total_time && processes[i].remaining_burst_time < min_burst_time && processes[i].remaining_burst_time > 0) {
                min_burst_index = i;
                min_burst_time = processes[i].remaining_burst_time;
            }
        }


        if (min_burst_index == -1) {
            total_time++;
            continue;
        }

       
        processes[min_burst_index].remaining_burst_time--;
        total_time++;

        
        if (processes[min_burst_index].remaining_burst_time == 0) {
            completed++;
            processes[min_burst_index].completion_time = total_time;
            processes[min_burst_index].turnaround_time = processes[min_burst_index].completion_time - processes[min_burst_index].arrival_time;
            processes[min_burst_index].waiting_time = processes[min_burst_index].turnaround_time - processes[min_burst_index].burst_time;
            average_turnaround_time += processes[min_burst_index].turnaround_time;
            average_waiting_time += processes[min_burst_index].waiting_time;
        }
    }

   
    average_turnaround_time /= n;
    average_waiting_time /= n;

    
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("\nAverage Turnaround Time: %.2f\nAverage Waiting Time: %.2f\n", average_turnaround_time, average_waiting_time);
}

int main() {
    struct Process processes[] = { {1, 0, 20}, {2, 25, 25}, {3, 30, 25}, {4, 60, 15}, {5, 100,10}, {6, 105, 10} };
    int n = sizeof(processes) / sizeof(processes[0]);

    
    sjf_preemptive(processes, n);

    return 0;
}*/
#include <stdio.h>
#include <string.h>
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void sjf_preemptive(struct Process processes[], int n) {
    int total_time = 0;
    int completed = 0;
    float average_turnaround_time = 0, average_waiting_time = 0;

    for (int i = 0; i < n; i++) {
        processes[i].remaining_burst_time = processes[i].burst_time;
    }

    printf("Gantt Chart:\n");
    printf("|");
    int track [6] = {0}, k=0, trackT[6] ={0};
    //char str[30];
    
    while (completed < n) {
        int min_burst_index = -1;
        int min_burst_time = __INT_MAX__;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= total_time && processes[i].remaining_burst_time < min_burst_time && processes[i].remaining_burst_time > 0) {
                min_burst_index = i;
                min_burst_time = processes[i].remaining_burst_time;
            }
        }

        if (min_burst_index == -1) {
            total_time++;
            
        } else {
            
            processes[min_burst_index].remaining_burst_time--;
            total_time++;

            if (processes[min_burst_index].remaining_burst_time == 0) {
                completed++;
                processes[min_burst_index].completion_time = total_time;
                processes[min_burst_index].turnaround_time = processes[min_burst_index].completion_time - processes[min_burst_index].arrival_time;
                processes[min_burst_index].waiting_time = processes[min_burst_index].turnaround_time - processes[min_burst_index].burst_time;
                average_turnaround_time += processes[min_burst_index].turnaround_time;
                average_waiting_time += processes[min_burst_index].waiting_time;
                track[k] = processes[min_burst_index].id;
                trackT[k] = processes[min_burst_index].completion_time;
                k++;
            }
        }
    }
    for(int i=0; i<n; i++){
       printf("--P%d--|", track[i]);
    }
    printf("\n");
    
    printf("0");
     for(int i=0; i<n; i++){
         printf("      %d",trackT[i]);
     }
     
    
    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }

    average_turnaround_time /= n;
    average_waiting_time /= n;
    printf("\nAverage Turnaround Time: %.2f\nAverage Waiting Time: %.2f\n", average_turnaround_time, average_waiting_time);
}

int main() {
    struct Process processes[] = { {1, 0, 20}, {2, 25, 25}, {3, 30, 25}, {4, 60, 15}, {5, 100,10}, {6, 105, 10} };
    int n = sizeof(processes) / sizeof(processes[0]);

    sjf_preemptive(processes, n);

    return 0;
}


