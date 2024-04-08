#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9876
#define BUFFER_SIZE 1024

void send_file(const char *file_name) {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
    FILE *file;

    // create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // connect to server
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(SERVER_PORT);
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("[*] Connected to %s:%d\n", SERVER_IP, SERVER_PORT);

    // read file data
    file = fopen(file_name, "rb");
    if (file == NULL) {
        perror("File open failed");
        exit(EXIT_FAILURE);
    }
    size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
    fclose(file);

    // send file data
    ssize_t bytes_sent = send(client_socket, buffer, bytes_read, 0);
    if (bytes_sent == -1) {
        perror("Send failed");
        exit(EXIT_FAILURE);
    }
    printf("[*] File sent: %s\n", file_name);

    close(client_socket);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *file_name = argv[1];

    send_file(file_name);

    return 0;
}

