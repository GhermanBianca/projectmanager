#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

class Server {
 public:
    static void ProcessClientRequests(int client_socket);
    static void InsertProperties(int server_socket, std::string prop_name, std::string prop_value, std::string product_fk);
    static void DisplayProperties(int server_socket, const std::string &propID);
    static void DeleteProperties(int server_socket, const std::string &propID);
    static void UpdateProperties(int server_socket, const std::string &name, const std::string &value, const std::string &fk_prod_id, const std::string &propID);
    static void InsertCategory(int server_socket, const std::string &category_name);
    static void FindIdNewCategoryName(int server_socket, const std::string &category_name);
    static void InsertIntoCategoryToCategory(int server_socket, const std::string &child_id, const std::string &id_parent);
    static void RenameCategoryById(int server_socket, const std::string &new_category_name, const std::string &category_id);
    static void RenameCategoryByName(int server_socket, const std::string &new_category_name, const std::string &category_name);
    static void DeleteCategoryById(int server_socket, const std::string &category_id);
    static void DeleteCategoryByName(int server_socket, const std::string &category_name);
    static void InsertStock(int server_socket,  const std::string &id, const std::string &stock, const std::string &price, const std::string &fk);
    static void CheckProductStock(int server_socket);
};

#endif