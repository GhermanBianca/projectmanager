#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <mysql/mysql.h>

using namespace std;

extern MYSQL* conn;
extern int qstate;
extern MYSQL_ROW row;
extern MYSQL_RES* res;

class DbResponse {
 public: 
    static void ConnectionFunction();
};

#endif
