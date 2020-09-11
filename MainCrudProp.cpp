#include "CrudProp.hpp"
#include "DbResponse.hpp"
#include "DisplayMenuProp.hpp"
#include "CrudCategory.hpp"
#include "ReadHierarchy.hpp"
#include "Manager.hpp"

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <iostream>
#include <functional>




using namespace std;

int main() {

    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    short PORT = 20001;
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 

    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) //returneaza socket-ul clientului new_socket
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

    DbResponse::ConnectionFunction();
   // ReadHierarchy::InsertRelations();
    // for(auto & el : ReadHierarchy::category_map) {
    //     ReadHierarchy::PrintChilds(el.first, el.second, ReadHierarchy::depth);
    // }
   // DisplayMenuProp::DisplayMenu();
    Manager::ProcessClientRequests(new_socket);
}