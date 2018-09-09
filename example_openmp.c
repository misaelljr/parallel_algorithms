#include <stdio.h>
#include <omp.h>
//execute: clang example_openmp.c -o example_openmp -fopenmp

/*
Program that exemplifies the use of openMP. 
Note that there are prints outside the parallel region and within the parallel region.
*/

int main()
{	
	//print outside the parallel region
	printf("Outside the parallel region\n");

	// parallel directive openMP with number of threads defined
	#pragma omp parallel num_threads(8) 
	{
		int tid = omp_get_thread_num(); // thread identifier
		int nt = omp_get_num_threads(); // number of threads defined
		//print thread identifier and number of threads defined
	   	printf("I'm the thread %d of a total of %d\n", tid, nt);
	}

	//print outside the parallel region
   	printf("Outside the parallel region\n");

   	return 0;
}