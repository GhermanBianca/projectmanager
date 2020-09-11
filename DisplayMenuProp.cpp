#include "DisplayMenuProp.hpp"
#include "CrudProp.hpp"
#include "CrudCategory.hpp"
#include "Request.hpp"

#include <iostream>

using namespace std;

void DisplayMenuProp::DisplayMenu(int sockfd) {

    std::cout << "0. Quit" << std:: endl << "1. Insert Properties " 
    << std:: endl << "2. Display Properties"
    << std:: endl << "3. Update Properties"
    << std:: endl << "4. Delete Properties"
    << std:: endl << "5. Insert Category";
    // << std:: endl << "6. Remove Category By Id"
    // << std:: endl << "7. Remove Category By Name "
    // << std:: endl << "8. Rename Category By Id "
    // << std:: endl << "9. Rename Category By Name\n ";

    int choice;
    cout << "Enter your choice : " << endl;
    std::cin >> choice;

    switch(choice) {
        case 0:
            return ;
        case 1:
            Request::InsertProperties(sockfd);
            break;
        // case 2:
        //     Request::DisplayProperties();
        //     break;
        // case 3:
        //     Request::UpdateProperties();
        //     break;
        // case 4:
        //     Request::DeleteProperties();
        //     break;
        /*case 5:
            //CrudCategory::AddCategory(2,"Laptop-uri");
            //CrudCategory::AddCategory(58,"Asus");
            //CrudCategory::AddCategory(58,"Hp");
            break;
        case 6:
            //CrudCategory::RemoveCategoryById(58);
            break;
        case 7:
            //CrudCategory::RemoveCategoryByName("Laptopuri");
            break;
        case 8:
            //CrudCategory::RenameCategoryById(4,"Asus UltraBooks");
            break;
        case 9:
            //CrudCategory::RenameCategoryByName("Asus UltraBooks", "Asus");
            break;*/
    }
}