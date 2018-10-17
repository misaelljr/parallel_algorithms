/* 
Misael Jr 
Phd Student
ICMC - USP
execute on linux: mpirun -np 1 vetor_scatter_mpi
*/

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

/*
Exemplo simples de divisão de vetor entre processos com OpenMPI
Para executar este programa é necessário compilar da maneira correta, como segue em linux: mpicc vetor_scatter_mpi.c -o vetor_scatter_mpi
*/

int main(int argc, char* argv[]) 
{
	int rank, tam;
	//vetor de entrada com 32 elementos
	float vetsend[] = {1,2,3,4,5,6,7,8,9,10,11,2,2,14,15,16,17,18,19,2,2,2,23,24,25,26,2,28,2,30,31,32};

	int x = 2; //elemento que desejamos saber suas posições
	int n = 32; //número total de elementos no vetor
	int n_p; //número de elementos por proc

	//ponteiros de inteiros que serão alocados
	int *vpos,*res,*subvetor;

	//MPI_Status, status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &tam);

	/**inicio processamento**/
	printf("****Inicio processamento****\n");
	//o proc 0 (zero) faz a conta para saber
	//quantos elementos cada parte terá
	if(rank==0)
	{
	//guardando em n_p o tamanho dos subvetores
		n_p=n/tam;
	//corrigindo caso tenha sido arredondado para baixo
		if(n_p*tam < n) n_p++;

	//alocando o vetor de resultado (conterá as posições onde se encontra X)
		res = (int *) malloc(n * sizeof (int));
		printf("Serão %d por processo\n", n_p);
	}
	/**fim processamento**/
	printf("****Fim processamento****\n");

	MPI_Bcast(&n_p, 1, MPI_INT, 0, MPI_COMM_WORLD);

	//aloca o subvetor que cada processo irá receber
	subvetor = (int *) malloc (n_p * sizeof (int));

	//o proc 0 divide o vetor em subvetores de tamanho n/p
	MPI_Scatter(subvetor,n_p, MPI_INT,subvetor,n_p,MPI_INT,0, MPI_COMM_WORLD);

	vpos = (int *) malloc (n_p * sizeof(int));

	//indíce atual do vetor de respostas
	int indice=0;

	//passa por todas as posições do subvetor procurando por X
	for(int i=0;i<n_p;++i){
		if( x == subvetor[i] ){ //achou X
		//guarda posição de X no vetor de respostas
		//para ter a posição original desse elemento no vetor basta fazer
		//i é a posição no subvetor + (o número do proc * o tamanho)
			vpos[indice++] = i+(rank*n_p);
		}
	}

	//junta todos os subvetores de resposta no vetor principal de respostas
	MPI_Gather(&vpos,indice,MPI_INT,res,indice,MPI_INT,0, MPI_COMM_WORLD);

	/**saída de dados**/
	//o proc 0 imprime a resposta final
	if(rank==0){
	//mostra todas as posições que tem X
		for(int i=0;i<n;++i)
			printf("\nRes[%d]=%d\n",i,res[i]);
	}

	MPI_Finalize();
	return 0;
} 