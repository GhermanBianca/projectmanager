#ifndef CRUD_HPP
#define CRUD_HPP

#include <string>

class CrudPropClient {
 public:
    static void ConnectionFunction();
    static void InsertProperties(int server_socket, const std::string &prop_name,
                                    const std::string &prop_value,
                                    const std::string &product_fk);
    static void DisplayProperties(int server_socket, const std::string &propID);
    static void DeleteProperties(int server_socket, const std::string &propID);
    static void DisplayTable(int server_socket);
    static void DisplayPropertyById(int server_socket, const std::string &propID);
    static void UpdateProperties(int server_socket, const std::string &name,
                                    const std::string &value, const std::string &fk_prod_id,
                                    const std::string &propID);
    static void InsertCategory(int server_socket, const std::string &category_name);
    static void FindIdNewCategoryName(int server_socket, const std::string &category_name);
    static void InsertIntoCategoryToCategory(int server_socket, const std::string &child_id, const std::string &id_parent);
    static void RenameCategoryByName(int server_socket, const std::string &new_category_name, const std::string &category_name);
    static void RenameCategoryById(int server_socket, const std::string &new_category_name, const std::string &category_id);

    static void DeleteCategoryById(int server_socket, const std::string &category_id);
    static void DeleteCategoryByName(int server_socket, const std::string &category_name);
};

#endif