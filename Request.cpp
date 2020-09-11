#include "Request.hpp"
#include "CrudProp.hpp"

#include <iostream>

using namespace std;

void Request::InsertProperties(int sockfd) { 

    system("clear");

    string prop_name;
    string prop_value;
    string product_fk;

    cout << "Enter Property Name \n";
    cin >> prop_name;

    cout << "Enter Property Value \n";
    cin >> prop_value;

    cout << "Enter Fk Product ID \n";
    cin >> product_fk;

    CrudProp::InsertProperties(sockfd, prop_name, prop_value, product_fk);
}

// void Request::DisplayProperties() {
//     system("clear");

//     char choose;
//     int propID;  

//     try {
//         cout << endl;
//         cout << "Enter Property ID: ";
//         cin >> propID;
//         cout << endl;
//     } catch(exception e){
//         DisplayMenuProp::DisplayMenu();
//     }
    
//     cout << "\n";
//     cout << "Press 'q' to Exit or any other key to Main Menu:\n";
//     cin >> choose;
//     if (choose == 'q' || choose == 'Q') {
//         exit(0);
//     } else {
//         DisplayMenuProp::DisplayMenu();
//         }
//     }
// }

// void Request::UpdateProperties(){
//     system("clear");

//     string name;
//     string value;
//     string fk_prod_id;
//     std::vector<string> items;
//     int propID;
//     int choose;

//     string storeId;
//     string storeName;
//     string storeValue;
//     string storePropProdId;

//     try {
//         cout << endl;
//         cout << "Enter Property ID: ";
//         cin >> propID;
//         cout << endl;
//     } catch(exception e){
//         cout << "Please enter a valid number." << endl;
//         DisplayMenuProp::DisplayMenu();
//     }
        
//     cin.ignore(1, '\n');
//     cout << "Enter new property name: ";
//     getline(cin, name);
//     if (name == "0" || name.empty()) {
//         name = storename;
//     }
//     cout << "Enter new property value: ";
//     getline(cin, value);
//     if (value == "0" || value.empty()) {
//         value = storevalue;
//     }
//     cout << "Enter new fk product id: ";
//     getline(cin, fk_prod_id);
//     if (fk_prod_id == "0" || fk_prod_id.empty()) {
//         fk_prod_id = storePropProdId;
//     }
     
//     cout << "\n";
//     cout << "Press 'q' to Exit or any other key to Main Menu:\n";
//     cin >> choose;
//     if (choose == 'q' || choose == 'Q') {
//         exit(0);
//     } else {
//         DisplayMenuProp::DisplayMenu();
//         }
//     }
// }

// void Request::DeleteProperties() {
//     system("clear");

//     char choose;
//     int propID;

//     try {
//         cout << endl;
//         cout << "Enter Property ID: ";
//         cin >> propID;
//         cout << endl;
//     } catch(exception e){
//         cout << "Please enter a valid number." << endl;
//         DisplayMenuProp::DisplayMenu();
//     }
    
//     cout << "Press 'q' to Exit and any other key to Main Menu: ";
//     cin >> choose;
//     if (choose == 'q' || choose == 'Q') {
//         exit(0);
//     } else {
//         DisplayMenuProp::DisplayMenu();
//     }
// }