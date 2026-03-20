#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
//For Round-Robin we need a Fixed time quantum. Here we are using Q=3.
#define MAX 20
#define Q 3 // Time Quantum for Round Robin

int main() {
    int n, time, i;
    int at[MAX], bt[MAX], pr[MAX];
    int wt_fcfs[MAX], wt_srtf[MAX], wt_pr[MAX], wt_rr[MAX];
    int rt[MAX], done[MAX] = {0};
    float avg_fcfs = 0, avg_srtf = 0, avg_pr = 0, avg_rr = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority (Lower number = Higher priority): ");
        scanf("%d", &pr[i]);
    }

    // ---------------- FCFS ----------------
    time = 0;
    for (i = 0; i < n; i++) {
        if (time < at[i]) {
            time = at[i];
        }
        wt_fcfs[i] = time - at[i];
        time += bt[i];
        avg_fcfs += wt_fcfs[i];
    }
    avg_fcfs /= n;

    // ---------------- SRTF ----------------
    for (i = 0; i < n; i++) {
        rt[i] = bt[i];
    }
    int complete = 0, shortest;
    time = 0;
    
    while (complete != n) {
        int min_rt = INT_MAX;
        shortest = -1;
        
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < min_rt) {
                min_rt = rt[i];
                shortest = i;
            }
        }
        
        
        if (shortest == -1) {
            time++;
            continue;
        }
        
        rt[shortest]--;
        time++; // SRTF increments time by 1 unit
        
        if (rt[shortest] == 0) {
            complete++;
            wt_srtf[shortest] = time - bt[shortest] - at[shortest];
            avg_srtf += wt_srtf[shortest];
        }
    }
    avg_srtf /= n;

    // ---------------- PRIORITY (Non-Preemptive) ----------------
    time = 0;
    for (int count = 0; count < n; ) {
        int highest = -1;
        int min_pr = INT_MAX;
        
        for (i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && pr[i] < min_pr) {
                min_pr = pr[i];
                highest = i;
            }
        }
        
        // If no process has arrived yet, CPU is idle
        if (highest == -1) {
            time++;
            continue;
        }
        
        wt_pr[highest] = time - at[highest];
        time += bt[highest];
        done[highest] = 1;
        avg_pr += wt_pr[highest];
        count++;
    }
    avg_pr /= n;

    // ---------------- ROUND ROBIN ----------------
    for (i = 0; i < n; i++) {
        rt[i] = bt[i];
    }
    time = 0;
    int remain = n;
    bool process_executed;
    
    while (remain > 0) {
        process_executed = false;
        for (i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= time) {
                process_executed = true;
                int exec = (rt[i] > Q) ? Q : rt[i];
                time += exec;
                rt[i] -= exec;
                
                if (rt[i] == 0) {
                    remain--;
                    wt_rr[i] = time - bt[i] - at[i];
                    avg_rr += wt_rr[i];
                }
            }
        }
        if (!process_executed) {
            time++;
        }
    }
    avg_rr /= n;

    // ---------------- DISPLAY RESULTS ----------------
    printf("\n--- Average Waiting Times ---\n");
    printf("FCFS: %.2f\n", avg_fcfs);
    printf("SRTF: %.2f\n", avg_srtf);
    printf("Priority: %.2f\n", avg_pr);
    printf("Round Robin (Q=%d): %.2f\n", Q, avg_rr);

    // Find Minimum Average Waiting Time
    float min_avg = avg_fcfs;
    char algo[30];
    strcpy(algo, "FCFS");

    if (avg_srtf < min_avg) {
        min_avg = avg_srtf;
        strcpy(algo, "SRTF");
    }
    if (avg_pr < min_avg) {
        min_avg = avg_pr;
        strcpy(algo, "Priority");
    }
    if (avg_rr < min_avg) {
        min_avg = avg_rr;
        strcpy(algo, "Round Robin");
    }

    printf("\nMinimum Average Waiting Time Algorithm: %s (%.2f)\n", algo, min_avg);

    return 0;
}
