/*
// Programa que calcula o máximo divisor comum entre 3 números
// versao em MPI
//
//compile on mac/linux: mpicc max_div_mpi.c -o max_div_mpi
//execute on mac/linux: mprun -np 4 max_div_mpi num1 num2 num3

Casos de testes executados no ValiMPIy

10 20 40 -- input 1 (Tudo)
10 20 > 10 -- processo 1
20 40 > 20 -- processo 2
10 20 > 10 -- processo 3
resultado = 10

7 5 4 -- input 2 (P-Usos e S-Usos)
7 5 > 1 -- processo 1 
5 4 > 1 -- processo 2
resultado = 1

6 18 30 -- input 3 (C-Usos, P-Usos e S-Usos)
6 18 > 6 -- processo 1
18 30 > 6 -- processo 2
6 6 > 6 -- processo 3
resultado = 6

30 42 70 -- input 4 (C-Usos e P-Usos)
30 42 > 6 -- processo 1 
42 79 > 14 -- processo 2
6 14 > 2 -- processo 3
resultado = 2

3 5 7 -- input 5 (C-Usos e P-Usos)
3 5 > 1 -- processo 1 
5 7 > 1 -- processo 2
1 1 > 1 -- processo 3
resultado = 1

1 1 1 -- input 6 (P-Usos e S-Usos)
1 1 > 1 -- processo 1 
1 1 > 1 -- processo 2
resultado = 1

10 20 1 -- input 7 (P-Usos e S-Usos)
10 20 > 10 -- processo 1 
20 1 > 1 -- processo 2
resultado = 1

1 20 10 -- input 8 (S-Usos)
1 20 > 1 -- processo 1 
20 10 > 10 --processo 2
resultado = 1

10 20 0 -- input 9 (ERROR)
10 20 > 10 -- processo 1
20 0 > ERROR -- processo 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

MPI_Status status;
void Master(int, int, int);
void Slave(int);
//
// Sao necessarios 4 processos do programa!
// $ mpirun -np 4 gcd
//
int main(int argc, char** argv)
{
	 int myRank;
	 int x, y, z;
	 // if (argc != 4)
	 //{
		// fazer 2 sends so para testar, FUNCIONOU!
		// MPI_Send(buf);
		// puts("argc != 4");
		// MPI_Send(buf);
		// return 1;
	 // }

	 MPI_Init(&argc, &argv);
	 MPI_Comm_rank(MPI_COMM_WORLD, &myRank);

	 if (myRank == 0)
	 {
		 x = atoi(argv[1]);
		 y = atoi(argv[2]);
		 z = atoi(argv[3]);
		 Master(x, y, z);
	 }
	 else
	 {
	 	Slave(myRank);
	 }
	 //printf("myRank = %d\n", myRank);
	 MPI_Finalize();
	 return 0;
}
//
// processo principal
//
void Master(int x, int y, int z)
{
	 int buf[3];
	 // envia x e y
	 buf[0] = x;
	 buf[1] = y;
	 MPI_Send(buf, 2, MPI_INT, 1, 1, MPI_COMM_WORLD);

	 // envia y e z
	 buf[0] = y;
	 buf[1] = z;
	 MPI_Send(buf, 2, MPI_INT, 2, 1, MPI_COMM_WORLD);
	 MPI_Recv(buf, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);

	 x = buf[0];
	 printf("%d\n", x);

	 MPI_Recv(buf, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
	 y = buf[0];
	 printf("%d\n", y);

	 if (x > 1 && y > 1)
	 {
		 buf[0] = x;
		 buf[1] = y;
		 MPI_Send(buf, 2, MPI_INT, 3, 1, MPI_COMM_WORLD);
		 MPI_Recv(buf, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
		 z = buf[0];
	 }
	 else
	 {
	 	 //printf("entrou\n");
		 buf[0] = -1;
		 buf[1] = -1;
		 MPI_Send(buf, 2, MPI_INT, 3, 1, MPI_COMM_WORLD);
		 MPI_Recv(buf, 1, MPI_INT, 3, 2, MPI_COMM_WORLD, &status);
		 z = 1;
	 }

	 printf("resultado = %d\n", z);
}
//
// processo que faz a computacao
//
void Slave(int rank)
{
	 int buf[2];
	 MPI_Recv(buf, 2, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

	 while (buf[0] != buf[1])
	 {
		 if (buf[0] < buf[1]){
		 	buf[1] = buf[1] - buf[0];
		 }
		 else{
		 	buf[0] = buf[0] - buf[1];
		 }
	 }

	 MPI_Send(buf, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
}