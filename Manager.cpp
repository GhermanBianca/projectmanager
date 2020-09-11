#include "Manager.hpp"
#include "CrudProp.hpp"
#include "DbResponse.hpp"
#include "DisplayMenuProp.hpp"

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void Manager::ProcessClientRequests(int client_sok) {
    char buffer[1024] = {0}; 
    while(true) {
        ssize_t valread = read(client_sok , buffer, 1024); //fac metoda de read
        string message(buffer); //pun string ul intr buffer si apoi fac split pe el
        int count = 0;
        for(auto &elem : message) {
            if(elem == ',') {
            count++;
            }
        }
        std::vector<string> tokens; //vector de stringuri
        // vector[0] = InsertProp vector[1] = culoare vector[2] = albastru vector[3] = 1
        //tokens = message.split(","); //ce returneaza el ii atribui lui tokens
        cout << "Buffer new" << buffer << endl;
        char * pch;
        char delim[] = ",";
        pch = strtok (buffer, delim);
        for( int i=0; i<count; i++)
            {
                cout << "Inside strtoken while" << endl;
               
                cout << "pch=" << pch << endl;
                if (pch != NULL) {
                    string tokenstr(pch);
                    tokens.push_back(tokenstr);
                }
                 pch = strtok (NULL, delim);
                cout << "End of str token while" << endl;
            }
        cout << "Inside Process Client Requests" << endl;
        for(auto &i:tokens) {
            cout << i << endl;
        }
        if(tokens[0] == "InsertProp") { // imi dau seama ce metoda trebuie sa apelez din server, sa accesez baza de date
    
            Manager::InsertProperties(client_sok, tokens[1], tokens[2], tokens[3]); //procesare mesaj

        } 
        /*else if(vector[0] == "DisplayProp") {
            Manager::DisplayProperties(vector[1]);
        } else if(vector[0] == "UpdateProp") {
            Manager::UpdateProperties(vector[1], vector[2], vector[3]);
        } else if(vector[0] == "DeleteProp") {
           Manager::DeleteProperties(vector[1]);
        }*/
    }
    //InsertProp, culoare, albastru, 1
}

void Manager::InsertProperties(int new_socket,string prop_name, string prop_value, string product_fk) { 

    cout << "Inside Insert Properties" << endl;
    system("clear");

    string insert_query1 = "INSERT INTO propertyproduct (PropertyName, PropertyValue, Fk_PropertyProductID) VALUES ('" + prop_name + "', '" + prop_value + "', '" + product_fk + "') ";

    const char* q = insert_query1.c_str();

    cout << "Before mysql_query" << endl;
    qstate = mysql_query(conn, q);
    cout << "After mysql_query" << endl;

    if(!qstate) {
        char message[] = "Registration succes!";
        //cout << endl << "Registration succes!" << endl;
        send(new_socket, message, sizeof(message), 0);
    } else {
        char mess[] = "Query Execution Problem!";
        send(new_socket, mess, sizeof(mess), 0);
        //cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

    }
}

// void Manager::DisplayProperties() {
//     system("clear");

//     int propID;  
//     std::vector <string> items;
//     bool HaveException = false;
//     bool NotInDatabase = false;

//     if(HaveException == false) {
//         for(auto &i : items) {
//             if(to_string(propID) != i) {
//                 NotInDatabase = true;
//             } else {
//                 NotInDatabase = false;
//             }
//         }

//     if(NotInDatabase == false) {
//         string findbyid_query = "SELECT PropertyProductID, PropertyName, PropertyValue, Fk_PropertyProductID  FROM propertyproduct WHERE PropertyProductID = '" + to_string(propID) +"' ";
//         const char* qi = findbyid_query.c_str();
//         qstate = mysql_query(conn, qi);

//     if(!qstate) {
//         res = mysql_store_result(conn);
//         cout << endl;
//         while ((row = mysql_fetch_row(res))) {
//             cout << "PropertyProductID: " << row[0] << "\nPropertyName: " << row[1] << "\nPropertyValue: " << row[2] << "\nFkProductId: " << row[3] << endl;
//         }
//     } else {
//         cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
//         }
//     }
// }

// void Manager::UpdateProperties(){
//     system("clear");

//     string name;
//     string value;
//     string fk_prod_id;
//     std::vector<string> items;
//     int propID;
//     bool HaveException = false;
//     bool NotInDatabase = false;

//     string storeId;
//     string storeName;
//     string storeValue;
//     string storePropProdId;

//     cout << "Update Properties of Product" << endl << endl;

//     qstate = mysql_query(conn, "SELECT PropertyProductID, PropertyName, PropertyValu, Fk_PropertyProductID FROM propertyproduct");
//     if (!qstate) {
//         res = mysql_store_result(conn);
//         cout << "PropertyProductID\tPropertyName\tPropertyValue\tPropProdID\n" << endl;
//         while ((row = mysql_fetch_row(res))) {
//             cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << endl;
//         }
//     } else {
//         cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
//     }

//     if(HaveException == false) {
//         for(auto &i : items) {
//             if(to_string(propID) != i) {
//                 NotInDatabase = true;
//             } else {
//                 NotInDatabase = false;
//             }
//         }

//     string findbyid_query = "SELECT PropertyProductID, PropertyName, PropertyValue, Fk_PropertyProductID  FROM propertyproduct WHERE PropertyProductID = '" + to_string(propID) +"' ";
//     const char* qi = findbyid_query.c_str();
//     qstate = mysql_query(conn, qi);

//     if(!qstate) {
//     res = mysql_store_result(conn);
//     cout << endl;
//     while ((row = mysql_fetch_row(res))) {
//         cout << "PropertyProductID: " << row[0] << "\nPropertyName: " << row[1] << "\nPropertyValue: " << row[2] << "\nPropProdID: " << row[3] << endl;
//         storeid = row[0];
//         storename = row[1];
//         storevalue = row[2];
//         storePropProdId = row[3];
//         }
//     } else {
//         cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
//         }
            
//     string update_query = "UPDATE propertyproduct SET PropertyName = '" + name + "', PropertyValue = '" + value + "', Fk_PropertyProductID = '" + fk_prod_id + "'  WHERE PropertyProductID = '" + to_string(propID) + "' ";

//     const char* qu = update_query.c_str();
//     qstate = mysql_query(conn, qu);

//     if (!qstate) {
//         cout << endl << "Successfully Saved In Database." << endl;
//     } else {
//         cout << "Failed tu Update." << endl;
//     }
// }

// void Manager::DeleteProperties() {
//     system("clear");

//     std::vector<string> items;
//     int propID;
//     bool HaveException = false;
//     bool NotInDatabase = false;

//     cout << "Update Properties of Product" << endl << endl;

//     qstate = mysql_query(conn, "SELECT PropertyProductID, PropertyName, PropertyValue, Fk_PropertyProductID FROM propertyproduct");
//     if (!qstate) {
//         res = mysql_store_result(conn);
//         cout << "PropertyProductID\tPropertyName\tPropertyValue\tFk_PropProductID\n" << endl;
//         while ((row = mysql_fetch_row(res))) {
//             cout << row[0] << "\t" << row[1] << "\t" << row[2] << "\t" << row[3] << endl;
//         }
//     } else {
//         cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
//     }

//     if(HaveException == false) {
//         for(auto &i : items) {
//             if(to_string(propID) != i) {
//                 NotInDatabase = true;
//             } else {
//                 NotInDatabase = false;
//                 break;
//             }
//         }

//     if(NotInDatabase == false) {
//         string delete_query ="DELETE  FROM propertyproduct WHERE PropertyProductID = '" + to_string(propID) + "' ";

//         const char* qd = delete_query.c_str();
//         qstate = mysql_query(conn, qd);

//         if (!qstate) {
//         cout << endl << "Successfully Deletede From Database." << endl;
//         } else {
//             cout << "Failed tu Delete." << endl;
//             }
//     }
//     } else {
//     cout << "Not Found in Database." << endl;
//     }
// }
