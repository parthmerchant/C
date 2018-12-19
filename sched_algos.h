//
//  sched_algos.h
//  main
//
//  Created by Parth Merchant on 12/2/18.
//  Copyright © 2018 Parth Merchant. All rights reserved.
//

#ifndef sched_algos_h
#define sched_algos_h

struct process {
    int id;
    int duration;
    int priority;
};

//First-Come-First-Served
void sched_fcfs(struct process ** processes, int arrSize);

//Priority Scheduling
void sched_priority(struct process ** processes, int arrSize, int ** priorities);

//Shortest Process Next
void sched_spn(struct process ** processes, int arrSize);

//Shortest Remaining Time
void sched_srt(struct process ** processes, int arrSize, int timeSlice);

//Round Robin
void sched_round_robin(struct process ** processes, int arrSize, int timeSlice);

#endif /* sched_algos_h */

