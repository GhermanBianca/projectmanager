#include "Server.hpp"
#include "CrudPropClient.hpp"
#include "DbResponseServer.hpp"
#include "DisplayMenuClient.hpp"

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>

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
            Server::InsertProperties(client_socket,
                                        tokens[1], tokens[2], tokens[3]);
        } else if (tokens[0] == "DisplayProp") {
            Server::DisplayProperties(client_socket, tokens[1]);
        } else if (tokens[0] == "DeleteProp") {
            Server::DeleteProperties(client_socket, tokens[1]);
        } else if (tokens[0] == "UpdateProp-DisplayTable") {
            Server::DisplayTable(client_socket);
        } else if (tokens[0] == "UpdateProp-DisplayPropById") {
            Server::DisplayPropertyById(client_socket, tokens[1]);
        } else if (tokens[0] == "UpdateProp") {
            Server::UpdateProperties(client_socket, tokens[1],
                                        tokens[2], tokens[3], tokens[4]);
        }
    }
}

void Server::InsertProperties(int server_socket, string prop_name,
                                string prop_value, string product_fk) {
    string insert_query1 = "INSERT INTO propertyproduct(PropertyName,
                                PropertyValue, Fk_PropertyProductID) VALUES
                                ('" + prop_name + "', '" + prop_value + "',
                                '" + product_fk + "') ";

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

void Server::DisplayProperties(int server_socket, string propID) {
    string findbyid_query = "SELECT PropertyProductID, PropertyName,
                                PropertyValue, Fk_PropertyProductID  FROM
                                propertyproduct WHERE PropertyProductID =
                                '" + propID +"' ";

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
            send(server_socket, message.c_str(),
                    strlen(message.c_str()) + 1 , 0);
        }
    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::DeleteProperties(int server_socket, string propID) {
    string delete_query ="DELETE  FROM propertyproduct
                            WHERE PropertyProductID = '" + propID + "' ";

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

void Server::DisplayTable(int server_socket) {
    qstate = mysql_query(conn, "SELECT PropertyProductID,
                            PropertyName, PropertyValue, Fk_PropertyProductID
                            FROM propertyproduct");
    if (!qstate) {
        res = mysql_store_result(conn);
        string message;
        while ((row = mysql_fetch_row(res))) {
            string r0, r1, r2, r3;
            r0 += row[0];
            r1 += row[1];
            r2 += row[2];
            r3 += row[3];

            message += r0 + "  " + r1 + "  " + r2 + "  " + r3 + "\n";
        }
        send(server_socket, message.c_str(), strlen(message.c_str()) + 1 , 0);

    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::DisplayPropertyById(int server_socket, string propID) {
    string findbyid_query = "SELECT PropertyProductID, PropertyName,
                                PropertyValue, Fk_PropertyProductID  FROM
                                propertyproduct WHERE PropertyProductID =
                                '" + propID +"' ";

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
            send(server_socket, message.c_str(),
                    strlen(message.c_str()) + 1 , 0);
        }

    } else {
        char message[] = "Query Execution Problem!";
        send(server_socket, message, sizeof(message), 0);
    }
}

void Server::UpdateProperties(int server_socket, string name,
                                string value, string fk_prod_id,
                                string propID) {
    string update_query = "UPDATE propertyproduct SET PropertyName
                            = '" + name + "', PropertyValue = '" + value +
                            "', Fk_PropertyProductID = '" + fk_prod_id +
                            "'  WHERE PropertyProductID = '" + propID + "' ";

    const char* qu = update_query.c_str();

    qstate = mysql_query(conn, qu);

    if (!qstate) {
        char message[] = "Successfully Saved in DB";
        send(server_socket, message, sizeof(message), 0);
    } else {
        char message[] = "Failed tu Update";
        send(server_socket, message, sizeof(message), 0);
    }
}