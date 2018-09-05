/* 
Misael Jr 
Phd Student
ICMC - USP
para executar: gcc minimo_par_paralelo.c -o minimo_par_paralelo -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>

#define N 45000
#define T 8

//struct for passing parameters
typedef struct{
	int *array;
	int start, end;
} args;

//search minimal
int min(void *str){

	//make a cast to struct
	args *parms = (args *) str;

	//initializing parameter of the struct
	int start = parms -> start;
	int end = parms -> end;
	int *B = (int *)malloc(end + 1 * sizeof(int));
	B = parms -> array;

	int min = INT_MAX; 

	for (int i = start; i <= end; i++){ 
	    if (B[i] < min){
			min = B[i];
	    }
	}

	return min;
}

// generate an array randomly
int *random_array(int array_size, int range){

	int *A = (int *) malloc (array_size * sizeof(int));

	for (int i = 0; i <= array_size; i++) {
	    A[i] = rand() % 10000;  
	}

	return A;
}

//algorithm to scale the division of elements by number of threads
int *split_search(int *array_target, int number_threads, int array_size){

	//store the results; the array gonna have the same number of the number of threads
	int * results = (int *)malloc(number_threads * sizeof(int)); 

	//struct to run search_min with multiple args on pthreads
	args * parametrs = (args *)malloc(sizeof(args));

	//malloc memory to the array into the struct
	parametrs->array = (int *)malloc(array_size * sizeof(int));
	parametrs->array = array_target; //copy target array to the struct

	pthread_t *ptr;  //poiter to array of threads
	ptr = malloc(number_threads * sizeof(pthread_t));

	//size of the arrays for each thread
	int chunk_size = array_size/number_threads;
	int inicio,fim; //helpers
	int cont = 0;

	void *status; // memory address where the return value of this thread should be stored
	
	//get the results from threads
	for (int i = 0; i < number_threads-1; i++) {
		inicio = i * chunk_size;
		fim = inicio + chunk_size - 1;

		printf("Thread %d: %d, %d \n", i+1, inicio, fim);

		//set parametrs to the struct
		parametrs->start = inicio;
		parametrs->end   = fim;

		//create a thread with array interval[start:end-1]
		pthread_create(&ptr[cont], 0, (void *) min, (void *) parametrs);

		//syncronize threads and receive results
		pthread_join(ptr[cont], &status);
		
		//store the results into an array
		results[cont] = (int*)status;

		cont++;
	}

	//Last chunk with all the remaining content
	inicio = fim + 1;
	fim = array_size - 1;

	//set parametrs to the struct
	parametrs->start = inicio;
	parametrs->end   = fim;
	
	//print threads by elements
	printf("Thread %d: %d, %d \n", number_threads, inicio, fim);
	
	//create thread
	pthread_create(&ptr[cont], 0, (void *) min, (void *) parametrs);

	//syncronize threads
	pthread_join(ptr[cont], &status);

	//store the results into an array
	results[cont] = (int*)status;;


	return results;
}

int main()
{	
	//array size defined from N
	int array_size = N;
	//range value for random number generation
	int range = 10000;
	
	//number of threads defined 
	int number_threads = T;

	int *my_array = (int *) malloc (array_size * sizeof(int));

	//array of random numbers
	my_array = random_array(array_size, 10000);

	//malloc memory to struct and for the array in the struct
	args * parametros = (args *)malloc(sizeof(args));
	parametros->array = (int *)malloc(array_size * sizeof(int));
	
	//array to store the results of each thread
	int * results = (int *)malloc(number_threads * sizeof(int));

	//get the results
	results = split_search(my_array, number_threads, array_size);

	//malloc memory to struct and for the array in the struct
	args * final = (args *)malloc(sizeof(args));
	final->array = (int *)malloc(number_threads * sizeof(int));

	final->array = results;
	final->start = 0;
	final->end = number_threads-1;

	//find the smallest value in the results
	int smallest = min(final);

	// Final value
	printf("Minimal Value: %d\n", smallest);

	fflush(0);

	return 0;
}
