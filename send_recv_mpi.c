/* 
Misael Jr 
Phd Student
ICMC - USP
execute on linux and mac: mpirun -np 2 ./send_recv_mpi
*/

#include <stdio.h>
#include <mpi.h>

/*
Example using Send and Recv operations with OpenMPI
Note that to compile it's necessary to execute the comand on linux and mac: mpicc send_recv_mpi.c -o send_recv_mpi
*/

int main(int argc, char *argv[])
{
	int size, myrank;

	//inicialize OpenMPI
	MPI_Init(&argc, &argv);

	//number of processes
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//process identifier
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	//print of process by the total number of processes
	printf("Hello, I'm the process %d of a total of %d\n", myrank, size);

	//useful variables
	int initialValue, modifiedValue, total, nproc;
	//MPI status
	MPI_Status st;

	if (myrank == 0) // I'm the master process
	{
		for (nproc = 1; nproc < size; nproc++)
		{
			initialValue = nproc*10;
			//MPI_Send (variable_address, number_elements, datatype, destination, tag, MPI_communicator)
			MPI_Send(&initialValue, 1, MPI_INT, nproc, 0, MPI_COMM_WORLD);
			printf("Master -- Sent %d to PROC(%d)\n", initialValue, nproc);
		}

		total = 0;

		for (nproc = 1; nproc < size; nproc++)
		{
			//MPI_Recv (variable_address, number_elements, data_type, source, tag, communicator, source_label)
			MPI_Recv(&modifiedValue, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
			printf("Master -- received the modified value %d\n", modifiedValue);

			total+=modifiedValue;
		}

		printf("MASTER - total processing = %d\n", total);
	}
	else //slave process
	{ 
		//MPI_Recv (variable_address, number_elements, data_type, source, tag, communicator, source_label)
		MPI_Recv(&initialValue, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);
		printf("SLAVE (%d) -- received %d of the master\n", myrank, initialValue);
		modifiedValue = initialValue*10;
		//MPI_Send (variable_address, number_elements, datatype, destination, tag, MPI_communicator)
		MPI_Send(&modifiedValue, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		printf("SLAVE (%d) -- modified value = %d\n", myrank, modifiedValue);
	}

	//Ending MPI Interface
	MPI_Finalize();

	return 0;
}