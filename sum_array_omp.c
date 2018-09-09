#include <stdio.h>
#include <omp.h>
//execute: clang sum_array_omp.c -fopenmp -o sum_array_omp

/*
Program that calculates the sum of the elements of two vectors (A and B) 
and stores the result in a vector C. Program parallelized with openMP.
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
		//####start of partitioning between number of threads####
		int id = omp_get_thread_num();
		int nt = omp_get_num_threads();
		int size = (int) N/nt;
		int start = id*size;
		int end = start + size - 1;
		//####end of partitioning between number of threads####

		//sum
		for (int i = start; i <= end; i++)
		{
			vetC[i] = vetA[i] + vetB[i];
		}
	}
	//###parallel region end###

	//printing result vector C
	for (int i = 0; i < N; i++)
	{
		printf("C[%d] = %f\n", i, vetC[i]);	
	}

	return 0;
} 