/* 
Misael Jr 
Phd Student
ICMC - USP
execute: clang sum_matrix_omp_for.c -fopenmp -o sum_matrix_omp_for
*/

#include <stdio.h>
#include <omp.h>

/*
Program that calculates the sum of the elements of two matrices (A and B) 
and stores the result in a matrix C. To perform parallelization, the program contains
a directive for that automates the partitioning process between the number of threads.
*/

#define L 16
#define R 16

int main(int argc, char *argv[])
{
	//matrices A, B and C defined statically
	float matA[L][R];
	float matB[L][R];
	float matC[L][R];

	// initializing matrices A and B
	for (int i = 0; i < L; i++){
		for (int j = 0; j < R; j++)
		{		
			matA[i][j] = 2;
			matB[i][j] = 3;
		}
	}
	
	//###parallel region start###
	#pragma omp parallel num_threads(8)
	{	
		int id = omp_get_thread_num();
		int nt = omp_get_num_threads();

		// partitioning between threads done automatically by openMP -- directive for
		#pragma omp for
		for (int i = 0; i < L; i++)
		{
			for (int j = 0; j < R; j++)
			{
				printf("The thread %d measure the position [%d][%d]\n", id, i, j);
				matC[i][j] = matA[i][j] + matB[i][j];
			}
		}
	}
	//###parallel region end###

	return 0;
} 
