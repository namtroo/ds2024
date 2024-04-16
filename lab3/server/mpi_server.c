#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {

        FILE *file;
        char buffer[BUFFER_SIZE];
        MPI_Status status;


        file = fopen("received_hello.txt", "wb");
        if (file == NULL) {
            perror("File open failed");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }


        MPI_Recv(buffer, BUFFER_SIZE, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &status);


        fwrite(buffer, 1, BUFFER_SIZE, file);
        fclose(file);
        
        printf("File received: received_hello.txt\n");
    }

    MPI_Finalize();
    return 0;
}
