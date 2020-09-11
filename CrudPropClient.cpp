#include "CrudPropClient.hpp"
#include "DbResponseServer.hpp"
#include "DisplayMenuClient.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void CrudPropClient::InsertProperties(int server_socket,
                                        string prop_name, string prop_value,
                                        string product_fk) {
    char server_reply[REPLY_DIMENSION];

    string send_message = "InsertProp," + prop_name +
                            "," + prop_value + "," + product_fk;

    int n = send(server_socket , send_message.c_str(),
                    strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << server_reply << endl;
}

void CrudPropClient::DisplayProperties(int server_socket, string propID) {
    char server_reply[REPLY_DIMENSION];

    string send_message = "DisplayProp," + propID;

    int n = send(server_socket , send_message.c_str(),
                    strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
	cout << server_reply << endl;
}

void CrudPropClient::DeleteProperties(int server_socket, string propID) {
    char server_reply[REPLY_DIMENSION];

    string send_message = "DeleteProp," + propID;

    int n = send(server_socket , send_message.c_str(),
                    strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
	cout << server_reply << endl;
}

void CrudPropClient::DisplayTable(int server_socket) {
    char table_reply[REPLY_DIMENSION];

    string send_message = "UpdateProp-DisplayTable";

    send(server_socket , send_message.c_str(),
                    strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, table_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << table_reply << endl;
}

void CrudPropClient::DisplayPropertyById(int server_socket, string propID) {
    char property_reply[REPLY_DIMENSION];

    string send_message = "UpdateProp-DisplayPropById," + propID;

    send(server_socket , send_message.c_str(),
                    strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}

void CrudPropClient::UpdateProperties(int server_socket, string name,
                                        string value, string fk_prod_id,
                                        string propID) {
    char server_reply[REPLY_DIMENSION];

    string send_message = "UpdateProp," + name + "," + value +
                            "," + fk_prod_id + "," + propID;

    int n = send(server_socket , send_message.c_str(),
                    strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
	cout << server_reply << endl;
}