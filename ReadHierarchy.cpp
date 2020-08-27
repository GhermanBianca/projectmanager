#include "ReadHierarchy.hpp"
#include "DbResponse.hpp"
#include "DisplayMenuProp.hpp"

#include <mysql/mysql.h>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

using namespace std;

std::map <int, std::vector<int>> category_map;
int depth;

void ReadHierarchy::PrintDepth(int depth) {
  stringstream a; 
  for(int i = 1; i <= depth ; i++) {
    a << "   ";
  }
  cout << a.str() ;
}

void ReadHierarchy::PrintCategory(int parent_id) {
  string findid_query1 = "select CategoryName  from category WHERE CategoryID = ' " + to_string(parent_id) + " ' ";
  const char* qf1 = findid_query1.c_str();
  int qstate = mysql_query(conn, qf1);
  if (!qstate) {
    res = mysql_store_result(conn);
    while ((row = mysql_fetch_row(res))) {
      cout << row[0] << endl;
    }
  } else {
      cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

  res = mysql_store_result(conn);
}

void ReadHierarchy::PrintChilds(int parent_id, std::vector<int> childs, int depth) {
  PrintDepth(depth); //aceasta functie va printa spatiile goale necesare identarii fiecarei categorii
  PrintCategory(parent_id); //aceasta functie va printa numele categoriei care are id-ul trimis ca argument
  for ( auto & el : childs) {
    PrintChilds(el, category_map[el], ++depth);
  }
}

void ReadHierarchy::InsertRelations() {
  int qstate = mysql_query(conn, "select * from categorytocategory");
  if (!qstate) {
      res = mysql_store_result(conn);
      while ((row = mysql_fetch_row(res))) {
          category_map[atoi(row[1])].push_back(atoi(row[0]));
          }
  } else {
      cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
  }
}