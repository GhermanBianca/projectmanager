#include "MenuBar.hpp"

#define PORT 20001 

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <QApplication>
#include <QTableView>


int main(int argc, char *argv[]) {

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

if (connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
  printf("\nConnection Failed \n");
  return -1;
}

QApplication app(argc, argv);  
    
MenuBar window {client_socket};

window.resize(550, 500);
window.setWindowTitle("Product Manager");
window.show();

return app.exec();
}