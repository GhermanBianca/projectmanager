#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <string>

class Manager {
 public:

    static void ProcessClientRequests(int client_sok);
    static void InsertProperties(int new_socket, std::string prop_name, std::string prop_value, std::string product_fk);
    // static void DisplayProperties();
    // static void UpdateProperties();
    // static void DeleteProperties();
};

#endif