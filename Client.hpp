#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client {
 public:
    static void InsertProperties(int client_socket);
    static void DisplayProperties(int client_socket);
    static void DeleteProperties(int client_socket);
    static void UpdateProperties(int client_socket);
    static void AddCategory(int client_socket);
    static void RenameCategoryByName(int client_socket);
    static void RenameCategoryById(int client_socket);
    static void RemoveCategoryById(int client_socket);
    static void RemoveCategoryByName(int client_socket);
};

#endif