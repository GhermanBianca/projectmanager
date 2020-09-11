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
    << std:: endl << "4. Update Properties\n";

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
    }
}