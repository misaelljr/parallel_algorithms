/* 
Misael Jr 
Phd Student
ICMC - USP
execute on mac: clang minimo_par_omp.c -o minimo_par_omp -fopenmp
execute on linux: gcc -fopenmp minimo_par_omp.c -o minimo_par_omp
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <omp.h>
#include <math.h>

#define N 450000000
#define n_threads 8

/*
Program that calculates the minimum value from a randomly generated array
Programa with openMP.
*/

// generate an array randomly
int *random_array(int array_size, int range){

	int *A = (int *) malloc (array_size * sizeof(int));

	for (int i = 0; i <= array_size; i++) {
	    A[i] = rand() % range;  
	}

	return A;
}

int main(int argc, char *argv[])
{
	//array size defined from N
	int array_size = N;

	//range value for random number generation
	int range = 10000;

	//allocating memory for array
	int *my_array = (int *)malloc(array_size * sizeof(int));

	//my randomly array 
	my_array = random_array(array_size, range);
	
	printf("#############################################\n");

	int my_min;

	//###parallel region start###
	#pragma omp parallel reduction (min : my_min) num_threads(n_threads)
	{	
		int id = omp_get_thread_num();
		int nt = omp_get_num_threads();
		my_min = INT_MAX;

		// partitioning between threads done automatically by openMP -- directive for
		#pragma omp for 
			for (int i = 0; i < array_size; i++)
			{	
				if (my_array[i] < my_min)
					my_min = my_array[i];
		    	//print minimum value per thread
		    	printf("Thread %d found the minimum = %d\n", id, my_min);
			}	

	}
	//###parallel region end###

	printf("#############################################\n");

	//Final value
	printf("Minimum value: %d\n", my_min);

	return 0;
} 



		
