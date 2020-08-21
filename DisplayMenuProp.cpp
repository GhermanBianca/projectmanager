#include "DisplayMenuProp.hpp"
#include "CrudProp.hpp"
#include "CrudCategory.hpp"

#include <iostream>

using namespace std;

void DisplayMenuProp:: DisplayMenu() {

    std::cout << "0. Quit" << std:: endl << "1. Insert Properties " 
    << std:: endl << "2. Display Properties"
    << std:: endl << "3. Update Properties"
    << std:: endl << "4. Delete Properties"
    << std:: endl << "5. Insert Category"
    << std:: endl << "6. Remove Category By Id"
    << std:: endl << "7. Remove Category By Name "
    << std:: endl << "8. Rename Category By Id "
    << std:: endl << "9. Rename Category By Name\n ";

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
        case 5:
            CrudCategory::AddCategory(4,"Laptop-uri");
            CrudCategory::AddCategory(5,"Asus");
            CrudCategory::AddCategory(6,"Hp");
            break;
        case 6:
            CrudCategory::RemoveCategoryById(4);
            break;
        case 7:
            CrudCategory::RemoveCategoryByName("Laptop-uri");
            break;
        case 8:
            CrudCategory::RenameCategoryById(5,"Asus UltraBooks");
            break;
        case 10:
            CrudCategory::RenameCategoryByName("Asus", "Asus UltraBooks");
            break;
    }
}