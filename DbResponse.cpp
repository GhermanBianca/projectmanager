#include "DbResponse.hpp"

#include <iostream> 
#include <sstream>

using namespace std;

MYSQL* conn;
int qstate;
MYSQL_ROW row;
MYSQL_RES* res;

void DbResponse::ConnectionFunction() {
    conn = mysql_init(0);
    if (conn) {
        cout << "Database Connected" << endl;
        cout << "Press any key to continue..." << endl;
        system("clear");
    } else {
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
    conn = mysql_real_connect(conn, "127.0.0.1", "root", "1q2w3e", "product_manager", 3306, NULL, 0);
    if (conn) {
        cout << "Database Connected To MySQL" << conn << endl;
    } else {
         cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
}