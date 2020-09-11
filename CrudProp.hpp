#ifndef CRUD_HPP
#define CRUD_HPP

#include <string>

using namespace std;

class CrudProp {
 public:

    static void ConnectionFunction();
    static void InsertProperties(int new_socket, string prop_name, string prop_value, string product_fk);
    // static void DisplayProperties();
    // static void UpdateProperties();
    // static void DeleteProperties();
};
#endif