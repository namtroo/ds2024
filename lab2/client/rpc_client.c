#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "rpc_transfer.h"

int main(int argc, char *argv[]) {
    CLIENT *client;
    char *server;
    int *fd;
    int bytes_read;
    data *file_data;
    char buffer[512]; 

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    server = argv[1];

    // Create RPC client
    client = clnt_create(server, FILE_TRANSFER_PROG, FILE_TRANSFER_VER, "tcp");
    if (client == NULL) {
        clnt_pcreateerror(server);
        exit(EXIT_FAILURE);
    }
   
    fd = open_rpc_1(&filename, client);
    if (fd == NULL) {
        clnt_perror(client, "Open RPC failed");
        clnt_destroy(client);
        exit(EXIT_FAILURE);
    }


    file_data = read_rpc_1(fd, client);
    if (file_data == NULL) {
        clnt_perror(client, "Read RPC failed");
        close_rpc_1(fd, client); 
        clnt_destroy(client);
        exit(EXIT_FAILURE);
    }

 
    printf("Received data from server:\n%s\n", file_data->data_val);


    if (!close_rpc_1(fd, client)) {
        fprintf(stderr, "Close RPC failed\n");
        clnt_destroy(client);
        exit(EXIT_FAILURE);
    }

    clnt_destroy(client);
    exit(EXIT_SUCCESS);
}

