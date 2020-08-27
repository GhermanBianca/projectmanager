#ifndef READ_HPP
#define READ_HPP

#include <mysql/mysql.h>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

using namespace std;

extern std::map <int, std::vector<int>> category_map;
extern int depth;

class ReadHierarchy {
 public: 

    static void PrintDepth(int depth);
    static void PrintCategory(int parent_id);
    static void PrintChilds(int parent_id, std::vector<int> childs, int depth);
    static void InsertRelations();
};

#endif