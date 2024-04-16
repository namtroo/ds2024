#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 1) {

        if (argc != 2) {
            fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        FILE *file;
        char buffer[BUFFER_SIZE];
        MPI_Status status;

        file = fopen(argv[1], "rb");
        if (file == NULL) {
            perror("File open failed");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }


        size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
        fclose(file);

        MPI_Send(buffer, bytes_read, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        
        printf("File sent: %s\n", argv[1]);
    }

    MPI_Finalize();
    return 0;
}
