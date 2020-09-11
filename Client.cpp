#include "Client.hpp"
#include "CrudPropClient.hpp"
#include "DisplayMenuClient.hpp"

#include <iostream>
#include <string>

using namespace std;

void Client::InsertProperties(int client_socket) {
    char choose;
    string prop_name;
    string prop_value;
    string product_fk;

    cout << "Insert Property of Product" << endl << endl;
    cout << "Enter Property Name \n";
    cin >> prop_name;

    cout << "Enter Property Value \n";
    cin >> prop_value;

    cout << "Enter Fk Product ID \n";
    cin >> product_fk;

    CrudPropClient::InsertProperties(client_socket, prop_name,
                                        prop_value, product_fk);

    cout << "\n";
    cout << "Press 'q' to Exit or any other key to Main Menu:\n";
    cin >> choose;
    if (choose == 'q' || choose == 'Q') {
        exit(0);
    } else {
        DisplayMenuClient::DisplayMenu(client_socket);
    }
}

void Client::DisplayProperties(int client_socket) {
    char choose;
    string propID;

    cout << "Display Property of Product" << endl << endl;
    cout << endl;
    cout << "Enter Property ID: ";
    cin >> propID;
    cout << endl;

    CrudPropClient::DisplayProperties(client_socket, propID);

    cout << "\n";
    cout << "Press 'q' to Exit or any other key to Main Menu:\n";
    cin >> choose;
    if (choose == 'q' || choose == 'Q') {
        exit(0);
    } else {
        DisplayMenuClient::DisplayMenu(client_socket);
    }
}

void Client::DeleteProperties(int client_socket) {
    char choose;
    string propID;

    cout << "Delete Property of Product" << endl << endl;
    cout << endl;
    cout << "Enter Property ID: ";
    cin >> propID;
    cout << endl;

    CrudPropClient::DeleteProperties(client_socket, propID);

    cout << "\n";
    cout << "Press 'q' to Exit or any other key to Main Menu:\n";
    cin >> choose;
    if (choose == 'q' || choose == 'Q') {
        exit(0);
    } else {
        DisplayMenuClient::DisplayMenu(client_socket);
    }
}

void Client::UpdateProperties(int client_socket) {
    string name;
    string value;
    string fk_prod_id;
    string propID;
    char choose;
    string storeId;
    string storeName;
    string storeValue;
    string storePropProdId;

    cout << "Update Property of Product" << endl;

    CrudPropClient::DisplayTable(client_socket);

    cout << endl;
    cout << "Enter Property ID: ";
    cin >> propID;
    cout << endl;

    CrudPropClient::DisplayPropertyById(client_socket, propID);

    cin.ignore(1, '\n');
    cout << "Enter new property name: ";
    getline(cin, name);
    if (name == "0" || name.empty()) {
        name = storeName;
    }
    cout << "Enter new property value: ";
    getline(cin, value);
    if (value == "0" || value.empty()) {
        value = storeValue;
    }
    cout << "Enter new fk product id: ";
    getline(cin, fk_prod_id);
    if (fk_prod_id == "0" || fk_prod_id.empty()) {
        fk_prod_id = storePropProdId;
    }

    CrudPropClient::UpdateProperties(client_socket,
                                        name, value, fk_prod_id, propID);

    cout << "\n";
    cout << "Press 'q' to Exit or any other key to Main Menu:" << endl;
    cin >> choose;
    if (choose == 'q' || choose == 'Q') {
        exit(0);
    } else {
        DisplayMenuClient::DisplayMenu(client_socket);
    }
}