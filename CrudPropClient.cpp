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

void CrudPropClient::InsertProperties(int server_socket, const string &prop_name, const string &prop_value, const string &product_fk) {
    char server_reply[REPLY_DIMENSION];

    string send_message = "InsertProp," + prop_name + "," + prop_value + "," + product_fk;

    int n = send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << server_reply << endl;
}

void CrudPropClient::DisplayProperties(int server_socket, const string &propID) {
    char server_reply[REPLY_DIMENSION];

    string send_message = "DisplayProp," + propID;

    int n = send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
	cout << server_reply << endl;
}

void CrudPropClient::DeleteProperties(int server_socket, const string &propID) {
    char server_reply[REPLY_DIMENSION];

    string send_message = "DeleteProp," + propID;

    int n = send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
	cout << server_reply << endl;
}

void CrudPropClient::DisplayTable(int server_socket) {
    char table_reply[REPLY_DIMENSION];

    string send_message = "UpdateProp-DisplayTable";

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, table_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << table_reply << endl;
}

void CrudPropClient::DisplayPropertyById(int server_socket, const string &propID) {
    char property_reply[REPLY_DIMENSION];

    string send_message = "UpdateProp-DisplayPropById," + propID;

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}

void CrudPropClient::UpdateProperties(int server_socket, const string &name, const string &value, const string &fk_prod_id, const string &propID) {
    char server_reply[REPLY_DIMENSION];

    string send_message = "UpdateProp," + name + "," + value + "," + fk_prod_id + "," + propID;

    int n = send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
	cout << server_reply << endl;
}

void CrudPropClient::InsertCategory(int server_socket, const string &category_name) {
    char property_reply[REPLY_DIMENSION];

    string send_message = "InsertCat," + category_name;

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}

void CrudPropClient::FindIdNewCategoryName(int server_socket, const string &category_name) {

    cout << "Before char" << endl;
    char property_reply[REPLY_DIMENSION];

    string send_message = "FindIdNewCatName," + category_name;

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}

void CrudPropClient::InsertIntoCategoryToCategory(int server_socket, const string &child_id, const string &id_parent) {
    char property_reply[REPLY_DIMENSION];

    string send_message = "InsertIntoCatToCat," + child_id + "," + id_parent;

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}

void CrudPropClient::RenameCategoryByName(int server_socket, const string &new_category_name, const string &category_name) {
    char property_reply[REPLY_DIMENSION];

    string send_message = "RenameCatByName," + new_category_name + "," + category_name;

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}

void CrudPropClient::RenameCategoryById(int server_socket, const string &new_category_name, const string &category_id) {
    char property_reply[REPLY_DIMENSION];

    string send_message = "RenameCatById," + new_category_name + "," + category_id;

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}

void CrudPropClient::DeleteCategoryById(int server_socket, const string &category_id) {
    char property_reply[REPLY_DIMENSION];

    string send_message = "DeleteCatId," + category_id;

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}

void CrudPropClient::DeleteCategoryByName(int server_socket, const string &category_name) {
    char property_reply[REPLY_DIMENSION];

    string send_message = "DeleteCatName," + category_name;

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}