/* 
Misael Jr 
Phd Student
ICMC - USP
execute on linux: mpirun -np 1 matriz_scatter_mpi
*/

#include <stdio.h>
#include <mpi.h>

/*
Exemplo simples de divisão de matriz entre processos com OpenMPI
Para executar este programa é necessário compilar da maneira correta, como segue em linux: mpicc matriz_scatter_mpi.c -o matriz_scatter_mpi
*/

int main(int argc, char* argv[]) 
{
	int rank, tam, tag=99, origem=0;
	float matsend[4][4] = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12},{13, 14, 15, 16}};
	float matrecv[4];

	//MPI_Status, status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &tam);

	if (tam == 4) {
		MPI_Scatter(matsend, 4, MPI_FLOAT, matrecv, 4, MPI_FLOAT, origem, MPI_COMM_WORLD );
	// Executa Scatter com conteúdo no processo origem=“0”
	printf("rank= %d Resultado: %f %f %f %f\n", rank, matrecv[0], matrecv[1], matrecv[2], matrecv[3]);
 	}else {
		if (rank==0)
 			printf("Deve ser executado com número de processos igual a 4. Finalizado sem sucesso!\n");
 	}

	MPI_Finalize();
	return 0;
} 