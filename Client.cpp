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

    while(1) {
        cout << "Please enter property name:" << endl ;
        cin >> prop_name;
	    //getline(cin, prop_name) ;

	    bool rejected = false ; //set a boolean to check against

	    for (unsigned int i = 0; i < prop_name.length() && !rejected ; i++) {

		    if (isalpha(prop_name[i])) //check for alpha characters
			    continue;

		    if (prop_name[i] == ' ') //check for spaces
			    continue;

		    rejected = true ; //set rejected if anything apart from alpha or space characters
	    }

	    if (!rejected){
		    cout << "Thanks for entering only alpha and/or spaces" << endl ;
            break;
	    } else {
		    cout << "Next time please don't enter numbers or punctuation." << endl ;
	    }
    }

    while(1) {
        cout << "Please enter property value:" << endl ;
        cin >> prop_value;

	    bool rejected = false ; //set a boolean to check against

	    for (unsigned int i = 0; i < prop_value.length() && !rejected ; i++) {

		    if (isalpha(prop_value[i])) //check for alpha characters
			    continue;

		    if (prop_value[i] == ' ') //check for spaces
			    continue;
            
            if (isdigit(prop_value[i])) //check for digit characters
			    continue;
            
		    rejected = true ; //set rejected if anything apart from alpha or space characters
	    }

	    if (!rejected){
		    cout << "Thanks for entering only alpha and/or spaces and/or digit" << endl ;
            break;
	    } else {
		    cout << "Next time please don't enter punctuation." << endl ;
	    }
    }

    while(1) {
        cout << "Please enter fk product id:" << endl ;
        cin >> product_fk;

	    bool rejected = false ; //set a boolean to check against

	    for (unsigned int i = 0; i < product_fk.length() && !rejected ; i++) {
            
            if (isdigit(product_fk[i])) //check for digit characters
			    continue;
            
		    rejected = true ; //set rejected if anything apart from alpha or space characters
	    }

	    if (!rejected){
		    cout << "Thanks for entering only digit" << endl ;
            break;
	    } else {
		    cout << "Next time please don't enter spaces/alpha/punctuation." << endl ;
	    }
    }

    CrudPropClient::InsertProperties(client_socket, prop_name, prop_value, product_fk);

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

    CrudPropClient::UpdateProperties(client_socket, name, value, fk_prod_id, propID);

    cout << "\n";
    cout << "Press 'q' to Exit or any other key to Main Menu:" << endl;
    cin >> choose;
    if (choose == 'q' || choose == 'Q') {
        exit(0);
    } else {
        DisplayMenuClient::DisplayMenu(client_socket);
    }
}

void Client::AddCategory(int client_socket) {
    string id_parent;
    string child_id;
    string category_name;

    cout << "Add Category" << endl;

    cout << "Enter Id Parent:" << endl;
    cin >> id_parent;
    cout << "Enter Category Name:" << endl;
    cin >> category_name;

    CrudPropClient::InsertCategory(client_socket, category_name);

    CrudPropClient::FindIdNewCategoryName(client_socket, category_name);

    cout << "Enter Id Child:" << endl;
    cin >> child_id;
    cout << "Enter Id Parent:" << endl;
    cin >> id_parent;

    CrudPropClient::InsertIntoCategoryToCategory(client_socket, child_id, id_parent); 

    char choose;
    cout << "\n";
    cout << "Press 'q' to Exit or any other key to Main Menu:" << endl;
    cin >> choose;
    if (choose == 'q' || choose == 'Q') {
        exit(0);
    } else {
        DisplayMenuClient::DisplayMenu(client_socket);
    }
}

void Client::RenameCategoryByName(int client_socket) {
    string category_name;
    string new_category_name;

    cout << "Enter New Category Name:" << endl;
    cin >> new_category_name;
    cout << "Enter Category Name:" << endl;
    cin >> category_name;

    CrudPropClient::RenameCategoryByName(client_socket, new_category_name, category_name); 
    
    char choose;
    cout << "\n";
    cout << "Press 'q' to Exit or any other key to Main Menu:" << endl;
    cin >> choose;
    if (choose == 'q' || choose == 'Q') {
        exit(0);
    } else {
        DisplayMenuClient::DisplayMenu(client_socket);
    }
}

void Client::RenameCategoryById(int client_socket) {
    string category_id;
    string new_category_name;

    cout << "Enter Category Id:" << endl;
    cin >> category_id;
    cout << "Enter Category Name:" << endl;
    cin >> new_category_name;

    CrudPropClient::RenameCategoryById(client_socket, new_category_name, category_id);
}

void Client::RemoveCategoryById(int client_socket) {
    string category_id;

    cout << "Enter Category Id" << endl;
    cin >> category_id;

    CrudPropClient::DeleteCategoryById(client_socket, category_id);
}

void Client::RemoveCategoryByName(int client_socket) {
    string category_name;

    cout << "Enter Category Name:" << endl;
    cin >> category_name;

    CrudPropClient::DeleteCategoryByName(client_socket, category_name); 
}