#include "DisplayMenuClient.hpp"

#define PORT 20001 

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int client_socket = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(client_socket, (struct sockaddr *)&serv_addr,
                    sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    DisplayMenuClient::DisplayMenu(client_socket);

    close(client_socket);

    return 0;
}