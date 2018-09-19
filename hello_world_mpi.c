/* 
Misael Jr 
Phd Student
ICMC - USP
execute on linux: mpirun -np 1 hello_world_mpi
*/

#include <mpi.h>
#include <stdio.h>

/*
Simple example of Hello World with OpenMPI
Note that to compile it's necessary to execute the comand on linux: mpicc hello_world_mpi.c -o hello_world_mpi
*/

int main(int argc, char** argv) {

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

    // Finalize the MPI environment.
    MPI_Finalize();
}
