#include "DisplayMenuClient.hpp"
#include "CrudPropClient.hpp"
#include "Client.hpp"

#include <iostream>
#include <limits>

using namespace std;

void DisplayMenuClient::DisplayMenu(int client_socket) {
    std::cout << "0. Quit" << std:: endl << "1. Insert Properties "
    << std:: endl << "2. Display Properties"
    << std:: endl << "3. Delete Properties"
    << std:: endl << "4. Update Properties"
    << std:: endl << "5. Add Category"
    << std:: endl << "6. Rename Category By Name"
    << std:: endl << "7. Rename Category By Id"
    << std:: endl << "8. Remove Category By Id"
    << std:: endl << "9. Remove Category By Name\n";
    
    
    int choice;
    cout << "Enter your choice : " << endl;
    std::cin >> choice;

    switch (choice) {
        case 0:
            return;
        case 1:
            Client::InsertProperties(client_socket);
            break;
        case 2:
            Client::DisplayProperties(client_socket);
            break;
        case 3:
            Client::DeleteProperties(client_socket);
            break;
        case 4:
            Client::UpdateProperties(client_socket);
            break;
        case 5:
            Client::AddCategory(client_socket);
            break;
        case 6:
            Client::RenameCategoryByName(client_socket);
            break;
        case 7:
            Client::RenameCategoryById(client_socket);
            break;
        case 8:
            Client::RemoveCategoryById(client_socket);
            break;
        case 9:
            Client::RemoveCategoryByName(client_socket);
            break;
    }
}