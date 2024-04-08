#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 9876
#define BUFFER_SIZE 1024

void receive_file() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);
    char buffer[BUFFER_SIZE];
    FILE *file;

    // create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // bind socket
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(SERVER_PORT);
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }


    if (listen(server_socket, 1) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("[*] Listening on port %d\n", SERVER_PORT);

    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
    if (client_socket == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    printf("[*] Accepted connection from %s:%d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));


    ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received == -1) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    }

    // write data to a file
    file = fopen("received_file.txt", "wb");
    if (file == NULL) {
        perror("File open failed");
        exit(EXIT_FAILURE);
    }
    fwrite(buffer, 1, bytes_received, file);
    fclose(file);
    printf("File received: received_file.txt\n");

    close(client_socket);

    close(server_socket);
}

int main() {
    receive_file();

    return 0;
}

