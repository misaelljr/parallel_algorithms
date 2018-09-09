#include <stdio.h>
#include <omp.h>
//execute: clang sum_array_omp_for.c -fopenmp -o sum_array_omp_for

/*
Program that calculates the sum of the elements of two vectors (A and B) 
and stores the result in a vector C. To perform parallelization, the program contains
a directive for that automates the partitioning process between the number of threads.
*/

#define N 2048

int main(int argc, char *argv[])
{
	//vectors A, B and C defined statically
	float vetA[N];
	float vetB[N];
	float vetC[N];

	// initializing vectors A and B
	for (int i = 0; i < N; i++)
	{
		vetA[i] = 2;
		vetB[i] = 3;
	}
	
	//###parallel region start###
	#pragma omp parallel num_threads(8)
	{	
		int id = omp_get_thread_num();
		int nt = omp_get_num_threads();

		// partitioning between threads done automatically by openMP -- directive for
		#pragma omp for
		for (int i = 0; i < N; i++)
		{	
			printf("A thread %d somou a posição %d\n", id, i);
			vetC[i] = vetA[i] + vetB[i];
		}
	}
	//###parallel region end###

	return 0;
} 