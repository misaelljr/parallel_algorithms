/* 
Misael Jr 
Phd Student
ICMC - USP
execute on mac: clang sum_matrix_omp.c -fopenmp -o sum_matrix_omp
execute on linux: gcc -fopenmp sum_matrix_omp.c -o sum_matrix_omp
*/

#include <stdio.h>
#include <omp.h>

/*
Program that calculates the sum of the elements of two matrices (A and B) 
and stores the result in a matrix C. Program parallelized with openMP.
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
		//####start of partitioning between number of threads####
		int id = omp_get_thread_num();
		int nt = omp_get_num_threads();
		int size = (int) L/nt;
		int start = id*size;
		int end = start + size - 1;
		//####end of partitioning between number of threads####

		//sum
		for (int i = start; i <= end; i++)
		{
			for (int j = 0; j < R; j++)
			{
				matC[i][j] = matA[i][j] + matB[i][j];
			}
		}
	}
	//###parallel region end###

	//printing result matrix C
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < R; j++)
		{
			printf("C[%d][%d] = %f\n", i, j, matC[i][j]);	
		}
		
	}

	return 0;
} 
