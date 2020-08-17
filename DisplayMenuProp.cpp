#include "DisplayMenuProp.hpp"
#include "CrudProp.hpp"

#include <iostream>

using namespace std;

void DisplayMenuProp:: DisplayMenu() {

    std::cout << "0. Quit" << std:: endl << "1. Insert " 
    << std:: endl << "2. Display "
    << std:: endl << "3. Update "
    << std:: endl << "4. Delete\n ";

    int choice;
    std::cin >> choice;

    switch(choice) {
        case 0:
            return ;
        case 1:
            CrudProp::InsertProperties();
            break;
        case 2:
            CrudProp::DisplayProperties();
            break;
        case 3:
            CrudProp::UpdateProperties();
            break;
        case 4:
            CrudProp::DeleteProperties();
            break;
    }
}