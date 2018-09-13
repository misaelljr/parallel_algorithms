/* 
Misael Jr 
Phd Student
ICMC - USP
execute on mac: clang prime_par_omp.c -o prime_par_omp -fopenmp
execute on linux: gcc -fopenmp prime_par_omp.c -o prime_par_omp
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

/*
Program that determines the number of existing prime numbers of 1 and N.
The purpose of the application is to obtain the shortest execution time for the sequential algorithm proposed by John Burkardt.

Based on Author: John Burkardt
*/

#define NUM_THREADS 8

//checking the prime numbers
//returns the number of prime numbers
int prime_number(int n){
	int i, j, prime, total=0;

	//###parallel region start###
	#pragma omp parallel for reduction(+ : total) private(i, j, prime) num_threads(NUM_THREADS)
		for(i=2; i<=n; i++){
			prime = 1;

			// For sequencial
			for(j=2;j<i; j++)
				if(i%j == 0){
					prime = 0;
					break;
				}

			total += prime;
		}
	//###parallel region end###

	return total;
}


int main(int argc, char const *argv[]){
	int n, primes;
	int n_lo, n_hi, n_factor;
	struct timeval t0, t1;
 	long elapsed;

	n_lo = 5;
	n_hi = 500000;
 	n_factor = 10;

 	n = n_lo;

 	while ( n <= n_hi ){

    	gettimeofday(&t0, 0);
    	primes = prime_number(n);
    	gettimeofday(&t1, 0);
    	
    	elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;

 		printf ("%8d		%8d		%ld\n", n, primes, elapsed);
 
    	n = n * n_factor;
  	}

	return 0;
}
