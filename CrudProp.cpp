#include "CrudProp.hpp"
#include "DbResponse.hpp"
#include "DisplayMenuProp.hpp"

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>


#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>


using namespace std;

void CrudProp::InsertProperties(int new_socket, string prop_name, string prop_value, string product_fk) { 

    char server_reply[6000];

    system("clear");
    
    string send_message = "InsertProp," + prop_name + "," + prop_value + "," + product_fk;

    int n = send(new_socket , send_message.c_str() , strlen(send_message.c_str()) , 0 );

    printf ("Error send: %s\n",strerror(errno));
    cout << "n=" << n << endl;
    if(recv(new_socket, server_reply , 6000, 0)<0) {
        cout << "Insert failed" ; 
    }
    else {
        cout << server_reply;
    }

}

// void CrudProp::DisplayProperties() {

//     system("clear");

//     int new_socket;

//     string send_message = "DisplayProp" + "," + to_string(propID);

//     send(new_socket , send_message.c_str() , strlen(send_message.c_str()) , 0 );
// }

// void CrudProp::UpdateProperties() {

//     system("clear");

//     int new_socket;
   
//     string send_message = "UpdateProp" + "," + name + "," + value + "," + fk_prod_id;

//     send(new_socket , send_message.c_str() , strlen(send_message.c_str()) , 0 );
// }

// void CrudProp::DeleteProperties() {

//     system("clear");

//     int new_socket;

//     string send_message = "DeleteProp" + "," + to_string(propID);

//     send(new_socket , send_message.c_str() , strlen(send_message.c_str()) , 0 );
// }