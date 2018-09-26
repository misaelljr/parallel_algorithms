/* 
Misael Jr 
Phd Student
ICMC - USP
execute on linux: mpirun -np 2 example_mpi_broadcast
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/*
Simple example of Broadcast operation with OpenMPI
Note that to compile it's necessary to execute the comand on linux: mpicc example_mpi_broadcast.c -o example_mpi_broadcast
*/

int main(int argc, char** argv) {

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int input = 0;

    if (my_rank == 0) //process root
    {
        printf("Input a integer value to send to every process\n"); //
        scanf("%d", &input);
    }else{
        printf("Process %d have the value %d BEFORE of the Broadcast\n", my_rank, input);
    }

    // each processor calls MPI_Bcast, data is broadcast from root processor and ends up in everyone value variable
    // root process uses MPI_Bcast to broadcast the value, each other process uses MPI_Bcast to receive the broadcast value
    MPI_Bcast(&input, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Process %d have the value %d AFTER of the Broadcast\n", my_rank, input);
 
    MPI_Finalize();
}