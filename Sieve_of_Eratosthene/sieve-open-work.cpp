//
//  sieve-open-work.cpp
//  Sieve_of_Eratosthene
//
//  Created by Imad Collin on 2017-10-11.
//  Copyright © 2017 Imad Collin. All rights reserved.
//

#include "sieve-open-work.hpp"
//sieve.c
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
double mine() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (1.0e-6*t.tv_usec + t.tv_sec);
}
pthread_mutex_t   mutex;

long maxnumber;
long counter ;
int nSeeds=0;
int *seeds;

void * find(void * pn){
    int i;
    int lCounter;
    
    unsigned char * numbers = (unsigned char *) pn;
    while (counter<(maxnumber+1)) {
        pthread_mutex_lock(&mutex);
        while(numbers[++counter]){} //take the next unmarked number from the counter
        lCounter = counter;
        pthread_mutex_unlock(&mutex);
        
        //for all the seeds, check if the number is divisible by them
        //printf("number of seeds: %d\n",nSeeds);
        for(i=0; i<nSeeds; i++){
            if((lCounter % seeds[i])==0){ //if the number is divisible by the seed
                //          printf("Counter: %d\n",lCounter);
                numbers[lCounter] = 1;   //mark the number
                break;
            }
        }
    }
    pthread_exit(0);
}

void calcSeeds(unsigned char numbers[]){
    int k_cur = 2;
    int k_mul = 2;
    int i=0;
    
    int sqrtMax = round (sqrt (maxnumber));
    
    while (k_cur <= sqrtMax){
        k_mul = k_cur*k_cur;
        while(k_mul <= sqrtMax){
            numbers[k_mul] = 1;
            k_mul += k_cur;
        }
        while(numbers[++k_cur]){}
    }
#pragma omp parallel for
    for(i=0; i<sqrtMax; i++){
        if(numbers[i]==0)
            nSeeds++;
    }
    
    seeds = (int *)malloc(sizeof(int)*(nSeeds+1));
    if (seeds == NULL) {
        printf("no memory\n");
        exit(1);
    }
    k_cur = 2;
    i = 0;
    while(!numbers[k_cur] && k_cur<=sqrtMax){
        seeds[i] = k_cur;
        i++;
        while(numbers[++k_cur]){}
    }
}

int main(int argc, char* argv[]){
    unsigned char *numbers;
    //char *help = "-h";
    int total = 0;
    double start_time, end_time;
    int thread_count,i;
    
    if (argc == 2){
        printf("Help message\n");
        exit(0);
        
    }
    else if(argc == 3){
        thread_count = strtol(argv[1], NULL, 10);
        maxnumber = strtol(argv[2], NULL, 10);
        counter = round(sqrt(maxnumber));
        numbers =(unsigned char *) malloc(sizeof(unsigned char)*(maxnumber+1));
        if (numbers == NULL) {
            printf("no memory\n");
            return(1);
        }
        for (i=0; i<maxnumber; i++) {
            numbers[i] = 0;
        }
        numbers[0] = numbers[1] = 1;
        
        calcSeeds(numbers);
        printf("NUMBER OF SEEDS %d\n",nSeeds);
        for (i=0; i<nSeeds; i++) {
            //printf("%d\n",seeds[i]);
        }
        
        //invalid conversion from 'void*' to '_opaque_pthread_t
        // pt =  malloc(sizeof(pthread_t)*thread_count);
        pthread_t pt[thread_count];
        pthread_mutex_init(&mutex, NULL);
        start_time = mine();
        for (i=0; i<thread_count; i++) {
            pthread_create(&pt[i], NULL, find, (void *)numbers);
        }
        for (i=0; i<thread_count; i++) {
            if (pthread_join(pt[i], NULL)) {
                printf("Thread no: %d returned with an error!\n", i);
            }
        }
        end_time = mine();
        //printf("Prime numbers are: \n");
        for (i=0;i<maxnumber;i++){
            if(numbers[i]==0){
                //printf("%d\n", i);
                total++;
            }
        }
        printf("NUMBER OF PRIMES %d\n", total);
        printf("TOTAL TIME OF INTEGRATION WAS %lf\n", end_time-start_time);
        
        pthread_mutex_destroy(&mutex);
        // free(pt);
        free(numbers);
        free(seeds);
    }
    else{
        printf("Wrong arguments input.");
        exit(1);
    }
    
    
    return 0;
}
