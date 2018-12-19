//
//  main.c
//  main
//
//  Created by Parth Merchant on 12/2/18.
//  Copyright © 2018 Parth Merchant. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sched_algos.h"

void fillProcessArr(struct process ** processArr, int arrSize) { //Helper function to fill our array with randomly generated processes.
    int currIdx = 0;
    while(currIdx < arrSize) {
        processArr[currIdx] = malloc(sizeof(struct process));
        processArr[currIdx]->id = currIdx + 1;
        processArr[currIdx]->duration = rand() % 5 + 1;
        processArr[currIdx]->priority = rand() % 10 + 1;
        currIdx++;}
}

void fillCopyArr(struct process ** processArr, struct process ** copyArr, int arrSize){
    int currIdx = 0;
    while(currIdx < arrSize){
        copyArr[currIdx] = malloc(sizeof(struct process));
        copyArr[currIdx]-> id = (processArr[currIdx]->id);
        copyArr[currIdx]-> duration = (processArr[currIdx]->duration);
        copyArr[currIdx]-> priority = (processArr[currIdx]->priority);
        currIdx++;}
}

void fillAdditionalArr(struct process ** processArr, int arrSize){
    int currIdx = 0, idValue = 10;
    while (currIdx < 2){
        processArr[currIdx]->id = idValue + 1;
        processArr[currIdx]->duration = rand() % 5 + 1;
        processArr[currIdx]->priority = rand() % 10 + 1;
        currIdx++; idValue++; }
}

void fillPrioritiesArr(struct process ** processArr, int ** priorities, int arrSize){
    int currIdx = 0;
    while(currIdx < arrSize){
        priorities[currIdx] = &processArr[currIdx]->priority; currIdx++; }
}


void outputProcess(struct process *process) { //Helper function to output a single process.
    printf("Process ID: %i, Duration: %i, Priority: %i\n", process->id, process->duration, process->priority);
}

void outputProcesses(struct process ** processes, int arrSize) {
    int idx = 0; while(idx < arrSize) {
        outputProcess(processes[idx]); idx++; }
}

void outputFirstTwo(struct process ** processes){
    int idx = 0;
    while(idx < 2){
        outputProcess(processes[idx]); idx++; }
}

void outputAdditionalTwo(struct process ** processes){
    int idx = 0;
    while(idx < 2){
        outputProcess(processes[idx]); idx++; }
}

void quicksortPriority(struct process ** processes, int arrSize) {
    if (arrSize < 2) return;
    
    int pivot = processes[arrSize/2]->priority;
    
    int i, j;
    for (i = 0, j = arrSize - 1; ; i++, j--) {
        while (processes[i]->priority < pivot) i++;
        while (processes[j]->priority > pivot) j--;
        
        if (i >= j) break;
        
        int tempDuration = processes[i]->duration;
        int tempID = processes[i]->id;
        int tempPriority = processes[i]->priority;
        processes[i]->duration = processes[j]->duration;
        processes[i]->id = processes[j]->id;
        processes[i]->priority = processes[j]->priority;
        processes[j]->duration = tempDuration;
        processes[j]->id = tempID;
        processes[j]->priority = tempPriority;
    }
    
    quicksortPriority(processes, i);
    quicksortPriority(processes + i, arrSize - i);
}

void quicksortDuration(struct process ** processes, int arrSize) {
    if (arrSize < 2) return;
    
    int pivot = processes[arrSize/2]->duration;
    
    int i, j;
    for (i = 0, j = arrSize - 1; ; i++, j--) {
        while (processes[i]->duration < pivot) i++;
        while (processes[j]->duration > pivot) j--;
        
        if (i >= j) break;
        
        int tempDuration = processes[i]->duration;
        int tempID = processes[i]->id;
        int tempPriority = processes[i]->priority;
        processes[i]->duration = processes[j]->duration;
        processes[i]->id = processes[j]->id;
        processes[i]->priority = processes[j]->priority;
        processes[j]->duration = tempDuration;
        processes[j]->id = tempID;
        processes[j]->priority = tempPriority;
    }
    
    quicksortDuration(processes, i);
    quicksortDuration(processes + i, arrSize - i);
}

int main(int argc, char ** argv) {
    
    srand(time(NULL)); //Seed our random with the current time.
    const int ARR_SIZE = 10; //The size of our array of randomly generated processes.
    const int TIME_SLICE = 2; //The time slice for any preemptive scheduling algorithms.
    struct process ** processes = malloc(sizeof(struct process *) * ARR_SIZE);
    //Our process array, used in each of our scheduling algorithms.
    int ** priorities = malloc(sizeof(int *) * ARR_SIZE); //Our priorities array, used for priority scheduling. Index i of the priorities array corresponds to the same index of the processes array.
    
    fillProcessArr(processes, ARR_SIZE); // Fill Array with processes
    fillPrioritiesArr(processes, priorities, ARR_SIZE); // Fill Priorities Array with priorities
    //fillPrioritiesArr wasn't implemented for the priorities array as I was able to sort the entire struct using quicksort
    
    
    printf("Outputting initial process array:\n");
    outputProcesses(processes, ARR_SIZE); // Outputs initial process
    printf("\n\n");
    
    sched_fcfs(processes, ARR_SIZE);
    sched_priority(processes, ARR_SIZE, priorities);
    sched_spn(processes, ARR_SIZE);
    sched_srt(processes, ARR_SIZE, TIME_SLICE);
    sched_round_robin(processes, ARR_SIZE, TIME_SLICE);
    
    free(processes); // deallocation of array
}

void sched_fcfs(struct process ** processes, int arrSize) {
    struct process ** firstCopy = malloc(sizeof(struct processor *) * arrSize); // empty process array
    fillCopyArr(processes, firstCopy, arrSize); // copy elements into new process array
    printf("First Come First Serve:\n");
    outputProcesses(firstCopy,arrSize);
    printf("\n\n");
}

void sched_priority(struct process ** processes, int arrSize, int ** priorities) {

    struct process ** priorityCopy = malloc(sizeof(struct processor *) * arrSize);
    fillCopyArr(processes, priorityCopy, arrSize);
    quicksortPriority(priorityCopy,arrSize); // Sort struct process based on priority
    printf("Priority:\n");
    outputProcesses(priorityCopy, arrSize);
    printf("\n\n");
}

void sched_spn(struct process ** processes, int arrSize) {
    
    struct process ** spnCopy = malloc(sizeof(struct processor *) * arrSize);
    fillCopyArr(processes, spnCopy, arrSize);
    quicksortDuration(spnCopy,arrSize); // Sort struct process based on duration
    printf("Shortest Process Next:\n");
    printf("\n\n");
    printf("First Two Processes:\n");
    outputFirstTwo(spnCopy); // Outputs first two shortest processes
    printf("\n\n");
    fillAdditionalArr(spnCopy, arrSize); // Creates two new processes and adds to process array
    printf("Two Additional Processes:\n");
    outputAdditionalTwo(spnCopy); // Outputs the two new processes that were added
    printf("\n\n");
    quicksortDuration(spnCopy,arrSize); // Sorts array with new added processes
    printf("Final Shortest Process Next:\n");
    outputProcesses(spnCopy, arrSize);
    printf("\n\n");
}

void sched_srt(struct process ** processes, int arrSize, int timeSlice) {
    
    struct process ** srtCopy = malloc(sizeof(struct processor *) * arrSize);
    fillCopyArr(processes, srtCopy, arrSize);
    quicksortDuration(srtCopy,arrSize);
    printf("Shortest Remaining Time:\n");
    outputProcesses(srtCopy, arrSize);
    printf("\n\n");
    
    int curr = 0; // Used to keep track of the first two completed processes
    int time = 0; // Used to keep track of what the time
    while (curr < 2){
        printf("Time Slice ");
        printf("%d",time+1);
        printf(": \n");
        for (int j = curr + 0; j < arrSize; j++){
            int change = srtCopy[j]->duration;
            change = change - timeSlice;
            srtCopy[j]->duration = change;
            if (srtCopy[j]->duration <= 0){
                srtCopy[j]->duration = 0; // Set duration to zero to avoid negative duration
                outputProcess(srtCopy[j]);
                curr++;
            }
            if (curr >= 2){
                break;
            }
        }
        time++;
    }
    printf("\n\n");
    fillAdditionalArr(srtCopy, arrSize); // Creates two new processes and adds them to array
    printf("Processes's ID: 11 & 12 added \n");
    printf("\n\n");
    quicksortDuration(srtCopy,arrSize); // Sorts the new array based on duration
    printf("Final Shortest Time Remaining: \n");
    outputProcesses(srtCopy, arrSize);
    printf("\n\n");
    
    for (int i = 0; i < arrSize; i++){
        printf("Time Slice ");
        printf("%d",time+1);
        printf(": \n");
        int change = srtCopy[i]->duration;change = change - timeSlice;srtCopy[i]->duration = change;
        if (srtCopy[i]->duration <= 0){ // Checks if duration is zero or less
            srtCopy[i]->duration = 0; // Set duration to zero to avoid negative duration
            outputProcess(srtCopy[i]);
            printf("\n\n");
            curr++;
            time++;}
        else {
            outputProcess(srtCopy[i]);
            printf("\n\n");
            curr++;
            time++;
            i--;}
    } printf("\n\n");
}

void sched_round_robin(struct process ** processes, int arrSize, int timeSlice) {
    
    struct process ** rrCopy = malloc(sizeof(struct processor *) * arrSize);
    fillCopyArr(processes, rrCopy, arrSize);
    printf("Round Robin:\n");
    printf("\n\n");
    printf("Initial Round Robin Array: \n");
    outputProcesses(rrCopy, arrSize);
    printf("\n\n");
    

    int complete = 0; // Used to track completed processes
    int time = 0; // Used to track what time slice the scheduler is on
    while (complete < 10){
        printf("Time Slice ");
        printf("%d",time+1);
        printf(": \n");
        for (int i = 0; i < arrSize; i++){ // Checks if the duration is zero
            if (rrCopy[i]->duration <= 0){
                continue;
            }
            int change = rrCopy[i]->duration;
            change = change - timeSlice;
            rrCopy[i]->duration = change;
            if (rrCopy[i]->duration <= 0){
                rrCopy[i]->duration = 0; // Set duration to zero to avoid negative duration
                outputProcess(rrCopy[i]);
                complete++;
            }
        }
        time++;
        printf("\n\n");
    }
    
    printf("\n\n");
}
