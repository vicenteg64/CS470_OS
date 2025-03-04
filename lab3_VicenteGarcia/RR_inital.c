#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
} Process;



// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    // Array to store remaining burst times
    int remaining_brust_times[n];
    // Assuming a maximum of 1000 executions for simplicity
    //Intialize the remaining times for the proccesses
    for(int i = 0; i < n; i++){
        remaining_brust_times[i] = proc[i].burst_time;
    }
    

    //Current time
    int current_time = 0;

    int done = 0;//track the amount of proccesses completed

    // Keep traversing processes in round-robin manner until all of them are not done
    while (1) {
        int execution_time = 0;
        for (int i = 0; i < n; i++) {
            //skip proccess if the burst time is done
            if(remaining_brust_times[i] == 0){
                continue;
            }

            if (remaining_brust_times[i] > quantum){
                execution_time = quantum; //execute a quantum time amount
            } else {
                execution_time = remaining_brust_times[i]; //execute the remianming burst time amount
            }
            
            //Subtract the execution time for that proccess
            remaining_brust_times[i] -= execution_time;

            //Increase the current time becuase it is used for a calculation
            current_time += execution_time; 
            
            //Calculate waiting and turnaround times
            if(remaining_brust_times[i] == 0){
                // Track the Completion in turnaround time
                proc[i].turnaround_time = current_time - proc[i].arrival_time;
                proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
                done++;
            }
                
        }
        
        // If all processes are done
        if (done == n) break;
    }

    // Print the execution order
    printf("Execution Order: \n");
    for(int i = 0; i < n; i++){
        printf("%d. Proccess %d \n", i+1, proc[i].process_id);
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

void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
}

void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
    }
}

int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling
 

    roundRobin(proc, n, quantum);
    printProcesses(proc, n);
    calculateAvgerages(proc, n);

    return 0;
}
