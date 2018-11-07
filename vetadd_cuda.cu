#include <stdio.h>
#include <cuda.h>

#define N 10

void vectAdd(int *A, int *B, int *C, int n)
{
	int i = blockDim.x * threadIdx.x + blockIdx.x;

	if(i < n)
		C[i] = A[i] + B[i];
}

int main(int argc, char const *argv[])
{
	int A[N], B[N], C[N];

	int size = N * sizeof(int);

	for (int i = 0; i < N; i++)
	{
		A[i] = i; 
	}

	for (int i = 0; i < N; i++)
	{
		B[i] = i; 
	}

	int *d_A, *d_B, *d_C;

	cudaMalloc((void **)&d_A, N*sizeof(int));
	cudaMemcpy(d_A, A, N*sizeof(int), cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_B, N*sizeof(int));
	cudaMemcpy(d_B, B, N*sizeof(int), cudaMemcpyHostToDevice);

	cudaMalloc((void **)&d_C, size);

	vectAdd<<<1, 10>>>(d_A, d_B, d_C, N);

	cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

	return 0;
}