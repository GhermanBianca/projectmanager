#include "CrudProp.hpp"
#include "DbResponse.hpp"
#include "DisplayMenuProp.hpp"

#include <mysql/mysql.h>

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void CrudProp::InsertProperties() { 

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

    string insert_query1 = "INSERT INTO propertyproduct (PropertyName, PropertyValue, Fk_PropertyProductID) VALUES ('" + prop_name + "', '" + prop_value + "', '" + product_fk + "') ";

    const char* q = insert_query1.c_str();

    qstate = mysql_query(conn, q);

    if(!qstate) {
        cout << endl << "Registration succes!" << endl;
        DisplayMenuProp::DisplayMenu();
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}

void CrudProp::DisplayProperties() {
    system("clear");

    char choose;
    int propID;  
    std::vector <string> items;
    bool HaveException = false;
    bool NotInDatabase = false;

    try {
        cout << endl;
        cout << "Enter Property ID: ";
        cin >> propID;
        cout << endl;
    } catch(exception e){
        DisplayMenuProp::DisplayMenu();
    }
    if(HaveException == false) {
        for(auto &i : items) {
            if(to_string(propID) != i) {
                NotInDatabase = true;
            } else {
                NotInDatabase = false;
            }
        }

    if(NotInDatabase == false) {
        string findbyid_query = "SELECT PropertyProductID, PropertyName, PropertyValue FROM propertyproduct WHERE PropertyProductID = '" + to_string(propID) +"' ";
        const char* qi = findbyid_query.c_str();
        qstate = mysql_query(conn, qi);

    if(!qstate) {
        res = mysql_store_result(conn);
        cout << endl;
        while ((row = mysql_fetch_row(res))) {
            cout << "PropertyProductID: " << row[0] << "\nPropertyName: " << row[1] << "\nPropertyValue: " << row[2] << endl;
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
    }

    cout << "\n";
    cout << "Press 'q' to Exit or any other key to Main Menu:\n";
    cin >> choose;
    if (choose == 'q' || choose == 'Q') {
        exit(0);
    } else {
        DisplayMenuProp::DisplayMenu();
        }
    }
}

void CrudProp::UpdateProperties(){
    system("clear");

    string name;
    string value;
    std::vector<string> items;
    int propID;
    int choose;
    bool HaveException = false;
    bool NotInDatabase = false;

    string storeid;
    string storename;
    string storevalue;

    cout << "Update Properties of Product" << endl << endl;

    qstate = mysql_query(conn, "SELECT PropertyProductID, PropertyName, PropertyValue FROM propertyproduct");
    if (!qstate) {
        res = mysql_store_result(conn);
        cout << "PropertyProductID\tPropertyName\tPropertyValue\n" << endl;
        while ((row = mysql_fetch_row(res))) {
            cout << row[0] << "\t" << row[1] << "\t" << row[2] << endl;
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    try {
        cout << endl;
        cout << "Enter Property ID: ";
        cin >> propID;
        cout << endl;
    } catch(exception e){
        cout << "Please enter a valid number." << endl;
        DisplayMenuProp::DisplayMenu();
    }
    if(HaveException == false) {
        for(auto &i : items) {
            if(to_string(propID) != i) {
                NotInDatabase = true;
            } else {
                NotInDatabase = false;
            }
        }

    string findbyid_query = "SELECT PropertyProductID, PropertyName, PropertyValue FROM propertyproduct WHERE PropertyProductID = '" + to_string(propID) +"' ";
    const char* qi = findbyid_query.c_str();
    qstate = mysql_query(conn, qi);

    if(!qstate) {
    res = mysql_store_result(conn);
    cout << endl;
    while ((row = mysql_fetch_row(res))) {
        cout << "PropertyProductID: " << row[0] << "\nPropertyName: " << row[1] << "\nPropertyValue: " << row[2] << endl;
        storeid = row[0];
        storename = row [1];
        storevalue = row [2];
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
        
    cin.ignore(1, '\n');
    cout << "Enter new property name: ";
    getline(cin, name);
    if (name == "0" || name.empty()) {
        name = storename;
    }
    cout << "Enter new property value: ";
    getline(cin, value);
    if (value == "0" || name.empty()) {
        value = storevalue;
    }
            
    string update_query = "UPDATE propertyproduct SET PropertyName = '" + name + "', PropertyValue = '" + value + "' WHERE PropertyProductID = '" + to_string(propID) + "' ";
    const char* qu = update_query.c_str();
    qstate = mysql_query(conn, qu);

    if (!qstate) {
        cout << endl << "Successfully Saved In Database." << endl;
    } else {
        cout << "Failed tu Update." << endl;
    }
     
    cout << "\n";
    cout << "Press 'q' to Exit or any other key to Main Menu:\n";
    cin >> choose;
    if (choose == 'q' || choose == 'Q') {
        exit(0);
    } else {
        DisplayMenuProp::DisplayMenu();
        }
    }
}

void CrudProp::DeleteProperties() {
    system("clear");

    string name;
    string value;
    char choose;
    std::vector<string> items;
    int propID;
    bool HaveException = false;
    bool NotInDatabase = false;

    cout << "Update Properties of Product" << endl << endl;

    qstate = mysql_query(conn, "SELECT PropertyProductID, PropertyName, PropertyValue FROM propertyproduct");
    if (!qstate) {
        res = mysql_store_result(conn);
        cout << "PropertyProductID\tPropertyName\tPropertyValue\n" << endl;
        while ((row = mysql_fetch_row(res))) {
            cout << row[0] << "\t" << row[1] << "\t" << row[2] << endl;
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
    try {
        cout << endl;
        cout << "Enter Property ID: ";
        cin >> propID;
        cout << endl;
    } catch(exception e){
        cout << "Please enter a valid number." << endl;
        DisplayMenuProp::DisplayMenu();
    }
    if(HaveException == false) {
        for(auto &i : items) {
            if(to_string(propID) != i) {
                NotInDatabase = true;
            } else {
                NotInDatabase = false;
                break;
            }
        }

    if(NotInDatabase == false) {
        string delete_query ="DELETE  FROM propertyproduct WHERE PropertyProductID = '" + to_string(propID) + "' ";
        const char* qd = delete_query.c_str();
        qstate = mysql_query(conn, qd);

        if (!qstate) {
        cout << endl << "Successfully Deletede From Database." << endl;
        } else {
            cout << "Failed tu Delete." << endl;
            }
    }
    } else {
    cout << "Not Found in Database." << endl;
    }
    
    cout << "Press 'q' to Exit and any other key to Main Menu: ";
    cin >> choose;
    if (choose == 'q' || choose == 'Q') {
        exit(0);
    } else {
        DisplayMenuProp::DisplayMenu();
    }
}