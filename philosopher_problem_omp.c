/* 
Misael Jr 
Phd Student
ICMC - USP
execute on mac: clang philosopher_problem_omp.c -fopenmp -o philosopher_problem_omp
execute on linux: gcc -fopenmp philosopher_problem_omp.c -o philosopher_problem_omp
*/

#include <omp.h>        
#include <stdio.h>      
#include <stdlib.h>     
#include <unistd.h> 
#include <time.h>   

#define NUM_PHI 5 //number of philosophers
#define NUM_MEALS 100 //number of iterations

static omp_lock_t hashis[NUM_PHI]; 

/*
Philosophers' dinner problem proposed by Dijkstra (1965) as a classic problem of synchronization.
Programa with openMP.
*/

//function that simulates the synchronization between philosophers
void philosopher()
{
	//threads wait for each other to start
	#pragma omp barrier 

	//setting useful parameters
	int id = omp_get_thread_num();
	int left_hashi;
	int right_hashi;

	//verifying whether the philosopher is last to use the hashis.
	//the behavior is different between the last philosophers and the others.
	if(id < NUM_PHI - 1)
	{
		right_hashi = id;
		left_hashi = id + 1;
	}
	//if he is the last philosopher, one of the hashis to be used is that of the philosopher 0
	else
	{
		right_hashi = 0;
		left_hashi = id;
	}

	int i;

	//demonstrating the lock and unlock in the two hashis by the philosophers
	for (i = 0; i < NUM_MEALS; i++)
	{
	    //occupying both hashis
	    omp_set_lock(&hashis[left_hashi]);
	    omp_set_lock(&hashis[right_hashi]);

	    //id print of the thread that occupied the hashis
	    printf("Philosopher %d is eating\n", id);

	    //wainting 100 ms
	    usleep(100);

	    //releasing the hashis
	    omp_unset_lock(&hashis[left_hashi]);
	    omp_unset_lock(&hashis[right_hashi]);
	}
}

int main(int argc, char *argv[])
{
	int i;

	//initiating mutual exclusion
	for ( i = 0; i < NUM_PHI; i++)
		omp_init_lock(&hashis[i]);	

	//###parallel region start###
	#pragma omp parallel num_threads(NUM_PHI)
	{ 
		philosopher();
	}
	//###parallel region end###

	//closing mutual exclusion
	for ( i = 0; i < NUM_PHI; i++)
		omp_destroy_lock(&hashis[i]);

	return(0);
}
