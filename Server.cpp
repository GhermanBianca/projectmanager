#include "Server.hpp"
#include "DbResponseServer.hpp"

#define MINIMUM 50

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void Server::ProcessClientRequests(int client_socket) {
    char buffer[1024] = {0};
    while (true) {
        memset(buffer, 0, 1024);
        ssize_t valread = recv(client_socket , buffer, 1024, 0);
        if (valread <= 0) {
            continue;
        }
        string message(buffer);
        int count = 0;
        for (auto &elem : message) {
            if (elem == ',') {
            count++;
            }
        }

        std::vector<string> tokens;
        char * pch;
        char delim[] = ",";
        pch = strtok(buffer, delim);

        for (int i = 0; i <= count; i++) {
            if (pch != NULL) {
                string tokenstr(pch);
                tokens.push_back(tokenstr);
            }
            pch = strtok(NULL, delim);
        }

        if (tokens[0] == "InsertProp") {
            Server::InsertProperties(client_socket, tokens[1], tokens[2], tokens[3]);
        } else if (tokens[0] == "DisplayProp") {
            Server::DisplayProperties(client_socket, tokens[1]);
        }  else if (tokens[0] == "DeleteProp") {
            Server::DeleteProperties(client_socket, tokens[1]);
        } else if (tokens[0] == "UpdateProp") {
            Server::UpdateProperties(client_socket, tokens[1], tokens[2], tokens[3], tokens[4]);
        } else if (tokens[0] == "InsertCat") {
            Server::InsertCategory(client_socket, tokens[1]);
        } else if (tokens[0] == "FindIdNewCatName") {
            Server::FindIdNewCategoryName(client_socket, tokens[1]);
        } else if (tokens[0] == "InsertCatToCat") {
            Server::InsertIntoCategoryToCategory(client_socket, tokens[1], tokens[2]);
        } else if (tokens[0] == "RenameCatById") {
            Server::RenameCategoryById(client_socket, tokens[1], tokens[2]);
        } else if (tokens[0] == "RenameCatByName") {
            Server::RenameCategoryByName(client_socket, tokens[1], tokens[2]);
        } else if (tokens[0] == "DeleteCatId") {
            Server::DeleteCategoryById(client_socket, tokens[1]);
        } else if (tokens[0] == "DeleteCatName") {
            Server::DeleteCategoryByName(client_socket, tokens[1]);
        } else if (tokens[0] == "InsertStock") {
            Server::InsertStock(client_socket, tokens[1], tokens[2], tokens[3], tokens[4]);
        }
    }
}

void Server::InsertProperties(int server_socket, string prop_name, string prop_value, string product_fk) {
    string insert_query1 = "INSERT INTO propertyproduct (PropertyName, PropertyValue, Fk_PropertyProductID) VALUES ('" + prop_name + "', '" + prop_value + "', '" + product_fk + "') ";
   
    const char* q = insert_query1.c_str();

    qstate = mysql_query(conn, q);

    if (!qstate) {
        char message[] = "Registration succes!";

        send(server_socket, message, sizeof(message), 0);
    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::DisplayProperties(int server_socket, const string &propID) {
    string findbyid_query = "SELECT PropertyProductID, PropertyName, PropertyValue, Fk_PropertyProductID  FROM propertyproduct WHERE PropertyProductID = '" + propID +"' ";

    const char* qi = findbyid_query.c_str();

    qstate = mysql_query(conn, qi);

    if (!qstate) {
        res = mysql_store_result(conn);
        cout << endl;
        while ((row = mysql_fetch_row(res))) {
            string r0, r1, r2, r3;
            r0 += row[0];
            r1 += row[1];
            r2 += row[2];
            r3 += row[3];

            string message = r0 + "  " + r1 + "  " + r2 + "  " + r3;
            send(server_socket, message.c_str(), strlen(message.c_str()) + 1 , 0);
        }
    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::DeleteProperties(int server_socket, const string &propID) {
    string delete_query ="DELETE  FROM propertyproduct WHERE PropertyProductID = '" + propID + "' ";

    const char* qd = delete_query.c_str();

    qstate = mysql_query(conn, qd);

    if (!qstate) {
        char message[] = "Successfuly Deleted!";
        send(server_socket, message, sizeof(message), 0);
    } else {
        char message[] = "Failed to Delete!";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::UpdateProperties(int server_socket, const string &name, const string &value, const string &fk_prod_id, const string &propID) {
    string update_query = "UPDATE propertyproduct SET PropertyName = '" + name + "', PropertyValue = '" + value + "', Fk_PropertyProductID = '" + fk_prod_id + "'  WHERE PropertyProductID = '" + propID + "' ";

    const char* qu = update_query.c_str();

    qstate = mysql_query(conn, qu);

    if (!qstate) {
        char message[] = "Successfully Saved in DB";
        send(server_socket, message, sizeof(message), 0);
    } else {
        char message[] = "Failed to Update";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::InsertCategory(int server_socket, const string &category_name) {
    string insertcategory_query = "INSERT INTO category (CategoryName) VALUES ('"+category_name+"')";

    const char* qi = insertcategory_query.c_str();

    qstate = mysql_query(conn, qi);

    if (!qstate) {
        char message[] = "Registration succes!";
        send(server_socket, message, sizeof(message), 0);
    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::FindIdNewCategoryName(int server_socket, const string &category_name) {
    string findid_query = "SELECT CategoryID FROM category WHERE CategoryName = '"+ category_name +"' ";
    const char* qf = findid_query.c_str();
    qstate = mysql_query(conn, qf);

    if (!qstate) {
        res = mysql_store_result(conn);
        cout << endl;
        while ((row = mysql_fetch_row(res))) {
            string r0;
            r0 += row[0];
            string message = r0;
            send(server_socket, message.c_str(), strlen(message.c_str()) + 1 , 0);
        }
    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::InsertIntoCategoryToCategory(int server_socket, const string &child_id, const string &id_parent) {
    string insertparent_query = "INSERT INTO categorytocategory (Child,Parent) VALUES('"+ child_id +"', '"+ id_parent +"')";

    const char* qp = insertparent_query.c_str();

    qstate = mysql_query(conn, qp);

    if (!qstate) {
        char message[] = "Registration succes!";
        send(server_socket, message, sizeof(message), 0);
    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::RenameCategoryById(int server_socket, const string &new_category_name, const string &category_id) {
    string update_query = "UPDATE category SET CategoryName = '" + new_category_name + "' WHERE CategoryID = '" + category_id + "' ";
    const char* qu = update_query.c_str();
    qstate = mysql_query(conn, qu);

    if (!qstate) {
        char message[] = "Successfully Saved In Database!";
        send(server_socket, message, sizeof(message), 0);
    } else {
        char message[] = "Failed to Update!";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::RenameCategoryByName(int server_socket, const string &new_category_name, const string &category_name) {
    
    string update_query = "UPDATE category SET CategoryName = '" + new_category_name + "' WHERE CategoryName = '" + category_name + "' ";
    const char* qu = update_query.c_str();
    qstate = mysql_query(conn, qu);

    if (!qstate) {
        char message[] = "Successfully Saved In Database!";
        send(server_socket, message, sizeof(message), 0);
    } else {
        char message[] = "Failed to Update!";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::DeleteCategoryById(int server_socket, const string &category_id) {
    string id_parent;
    vector<int> parent;
     
    string findid_query1 = "SELECT Child FROM categorytocategory WHERE Parent = '"+ category_id +"'";
    const char* qf1 = findid_query1.c_str();
    qstate = mysql_query(conn, qf1);

    if (!qstate) {
        res = mysql_store_result(conn);
        cout << endl;
        while ((row = mysql_fetch_row(res))) {
            parent.push_back(atoi(row[0]));
        }
    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    }

    string delete_query ="DELETE FROM categorytocategory WHERE Parent = '"+ id_parent +"' ";
    const char* qd = delete_query.c_str();
    qstate = mysql_query(conn, qd);

    if (!qstate) {
        char message[] = "Successfully Deleted From Database!";
        send(server_socket, message, sizeof(message), 0);
    } else {
        char message[] = "Failed to Delete.";
        send(server_socket, message, sizeof(message), 0);
    }

    for (auto i : parent) {
        string delete_query1 ="DELETE FROM category WHERE CategoryID = ' "+ to_string(i) +"  ' ";
        const char* qd1 = delete_query1.c_str();
        qstate = mysql_query(conn, qd1);

        if (!qstate) {
            char message[] = "Successfully Deleted From Database!";
            send(server_socket, message, sizeof(message), 0);
        } else {
            char message[] = "Failed to Delete.";
            send(server_socket, message, sizeof(message), 0);
        }
    }

    string delete_query4 ="DELETE FROM category WHERE CategoryID = '"+ category_id +"' ";
        const char* qd4 = delete_query4.c_str();
        qstate = mysql_query(conn, qd4);

        if (!qstate) {
            char message[] = "Successfully Deleted From Database!";
            send(server_socket, message, sizeof(message), 0);
        } else {
            char message[] = "Failed to Delete.";
            send(server_socket, message, sizeof(message), 0);
        }
}

void Server::DeleteCategoryByName(int server_socket, const string &category_name) {
    int id_parent;
    vector<int> parent;

    string findid_query = "SELECT CategoryID FROM category WHERE CategoryName = '"+ category_name + "' ";
    const char* qf = findid_query.c_str();
    qstate = mysql_query(conn, qf);

    if(!qstate) {
        res = mysql_store_result(conn);
        cout << endl;
        while ((row = mysql_fetch_row(res))) {
            id_parent = atoi(row[0]);
        }
    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    }

    string findid_query1 = "SELECT Child FROM categorytocategory WHERE Parent = '"+ to_string(id_parent) +"'";
    const char* qf1 = findid_query1.c_str();
    qstate = mysql_query(conn, qf1);

    if(!qstate) {
        res = mysql_store_result(conn);
        cout << endl;
        while ((row = mysql_fetch_row(res))) {
            parent.push_back(atoi(row[0]));
        }
    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    } 

    for (auto i : parent) {
        string delete_query1 ="DELETE FROM category WHERE CategoryID = ' "+ to_string(i) +"  ' ";
        const char* qd1 = delete_query1.c_str();
        qstate = mysql_query(conn, qd1);

        if (!qstate) {
            char message[] = "Successfully Deleted From Database!";
            send(server_socket, message, sizeof(message), 0);
        } else {
            char message[] = "Failed to Delete.";
            send(server_socket, message, sizeof(message), 0);
        }
    }
    
    string delete_query3 ="DELETE FROM category WHERE CategoryName = '"+ category_name +"' ";
    const char* qd3 = delete_query3.c_str();
    qstate = mysql_query(conn, qd3);

    if (!qstate) {
        char message[] = "Successfully Deleted From Database!";
        send(server_socket, message, sizeof(message), 0);
    } else {
        char message[] = "Failed to Delete.";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::InsertStock(int server_socket,  const string &id, const string &stock, const string &price, const string &fk) {
    string insert_query1 = "INSERT INTO details (DetailID, Stock, Price, Fk_ProductID) VALUES ('" + id + "','" + stock + "', '" + price + "', '" + fk + "') ";
   
    const char* q = insert_query1.c_str();

    qstate = mysql_query(conn, q);

    if (!qstate) {
        char message[] = "Registration succes!";
        send(server_socket, message, sizeof(message), 0);
    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::CheckProductStock(int server_socket) {
    MYSQL* conn_;
    int qstate_;
    MYSQL_ROW row_;
    MYSQL_RES* res_;
   
    srand(time(0));
    vector<int> id_vector;

    conn_ = mysql_init(0);
    if (conn_) {
        cout << "Database Connected" << endl;
        cout << "Press any key to continue..." << endl;
    } else {
        cout << "Failed To Connect!" << mysql_errno(conn_) << endl;
    }

    conn_ = mysql_real_connect(conn_, "127.0.0.1", "root", "1q2w3e", "product_manager", 3306, NULL, 0);

    if (conn_) {
        cout << "Database Connected To MySQL" << conn_ << endl;
    } else {
        cout << "Failed To Connect!" << mysql_errno(conn_) << endl;
    }
    
    string add_vector_query1 = "SELECT * FROM details";
    const char* qf1 = add_vector_query1.c_str();
    qstate_ = mysql_query(conn_, qf1);

    if(!qstate_) {
        res_ = mysql_store_result(conn_);
        cout << endl;
        while ((row_ = mysql_fetch_row(res_))) {
            id_vector.push_back(atoi(row_[3]));
        } 
    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    }

    const int dim_id_vector = id_vector.size();
    for(int i = 0; i < 1 ; i++) {
        int stock = 0;
        int random = rand() % dim_id_vector - 1;
        int random_value_change_product_stock = rand() % 100;
        int shouldIncrement = rand() % 1;
        cout << " Id vector: " << endl;
        cout << id_vector[random] << endl;
        string select_stock_query1 = "SELECT * FROM details where Fk_ProductID =  '"+ to_string(id_vector[random]) +"'  ";
           
        const char* qf1 = select_stock_query1.c_str();
            
        qstate = mysql_query(conn_, qf1);

        if(!qstate_) {
            res_ = mysql_store_result(conn_);
            cout << endl;
            while ((row_ = mysql_fetch_row(res_))) {
                if(shouldIncrement) {
                    cout << "In if:" << endl;
                    stock = atoi(row_[1]);
                    cout << "Initial Stock:" << endl;
                    cout << stock << endl;
                    //stock += atoi(row_[1]) - random_value_change_product_stock; 
                    cout << "Random change value:" << endl;
                    stock -= random_value_change_product_stock; 
                    cout << "Modified stock:" << endl;
                    cout << stock << endl;
                } else {
                    cout << "In else:" << endl;
                    stock = atoi(row_[1]);
                    cout << "Initial Stock:" << endl;
                    cout << stock << endl;
                    cout << random_value_change_product_stock << endl;
                    //stock += atoi(row_[1]) + random_value_change_product_stock;
                    cout << "Random change value:" << endl;
                    stock += random_value_change_product_stock; 
                    cout << "Modified stock:" << endl;
                    cout << stock << endl;  
                }  

                if(stock < MINIMUM) {
                    cout << "The stock is too small!" << endl;
                }  
            }
        } else {
            char message[] = "Query Execution Problem!";
            send(server_socket, message, sizeof(message), 0);
        }

        string update_query = "UPDATE details SET Stock = '" + to_string(stock) + "' WHERE Fk_ProductID =  '"+ to_string(id_vector[random]) +"' ";
        const char* qu = update_query.c_str();
        qstate = mysql_query(conn, qu);

        if (!qstate) {
            char message[] = "Successfully Saved In Database!";
            cout << message << endl;
        } else {
            char message[] = "Failed to Update!";
            cout << message << endl;
        }    
    }   
}