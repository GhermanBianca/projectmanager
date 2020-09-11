#ifndef CRUD_HPP
#define CRUD_HPP

#include <string>

class CrudPropClient {
 public:

    static void ConnectionFunction();
    static void InsertProperties( int server_socket, std::string prop_name, std::string prop_value, std::string product_fk );
    static void DisplayProperties( int server_socket, std::string propID );
    static void DeleteProperties(int server_socket, std::string propID);
    static void DisplayTable(int server_socket);
    static void DisplayPropertyById(int server_socket, std::string propID);
    static void UpdateProperties(int server_socket, std::string name, std::string value, std::string fk_prod_id, std::string propID);
};

#endif