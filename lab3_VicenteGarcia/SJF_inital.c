#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int is_completed;
} Process;

int n; // Number of processes

// Function to find the index of the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {
    int min_arrival_time = INT_MAX; //minimum arrival time
    int min_remaining_time = INT_MAX;
    int index = -1;
    for (int i = 0; i < n; i++) {
        //if the arrival time is first go with that for the index
        if (proc[i].arrival_time <= current_time && proc[i].is_completed == 0){
            if(proc[i].remaining_time < min_remaining_time){
                min_remaining_time = proc[i].remaining_time;
                index = i;
            }
        }
        
    }
    return index;
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
    int current_time = 0;
    int completed = 0;

    // Initialize waiting and turnaround times
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
        proc[i].is_completed = 0;
    }

    //Track for the previously executed process assigned
    int prev = findNextProcess(proc, current_time); 
    //Find the next proccess to execute
    int index = findNextProcess(proc, current_time);

    //Print the first proccess executing
    printf("Execution Order: \n");
    int order = 1; //Used for order of processes
    printf("%d. Proccess %d began executing.\n", order, proc[index].process_id);

    // Build the loop to execute processes in the queue list
    while (completed != n) {

        //Process found to execute
        if (proc[index].remaining_time > 0){
            proc[index].remaining_time--;//Decrement the remaining time

            
            if(index != prev ){ //If there is a change in proccess execution
                proc[prev].turnaround_time = proc[prev].burst_time - proc[prev].remaining_time; //tracking prev executed time in arrival time
                prev = index;
                proc[index].waiting_time = current_time; //Get the total waiting time based on when proccess starts
                //increment the order and print the proccess executeing
                order++;
                printf("%d. Proccess %d began executing.\n", order, proc[index].process_id);
            }

            //Process is done executeing
            if (proc[index].remaining_time == 0){
                //Save the amount of time spent executing before
                int prev_exe_time = proc[index].turnaround_time; 
                //Calculate waiting time
                int totalWaitingTime = proc[index].waiting_time;
                proc[index].waiting_time = totalWaitingTime - prev_exe_time - proc[index].arrival_time;

                //Calulate turnaround time
                proc[index].turnaround_time = current_time - proc[index].arrival_time;

                //Mark proccess as completed
                proc[index].is_completed = 1;
                //Increment completion count
                completed++;
            }
        }

        current_time++;//Increment current time

        //find the next proccess to execute
        index = findNextProcess(proc, current_time);
    }
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

// Function to calculate Avargae turnaround time and Waiting time
void calculateAvgerages(Process proc[], int n) {
    double sum_waiting_time = 0;
    double sum_turnaround_time = 0;

    for(int i = 0; i < n; i++){
        sum_waiting_time = sum_waiting_time + proc[i].waiting_time;
        sum_turnaround_time = sum_turnaround_time + proc[i].turnaround_time;
    }

    double avg_waiting_time = sum_waiting_time/n;
    double avg_turnaround_time = sum_turnaround_time/n;

    printf("Average Waiting Time: %.2f \n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f \n", avg_turnaround_time);
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);
    calculateAvgerages(proc, n);

    return 0;
}
