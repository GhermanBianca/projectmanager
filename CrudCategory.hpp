#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#include <string>

class CrudCategory {
 public:
    static void AddCategory();
    static void RemoveCategoryById();
    static void RemoveCategoryByName();
    static void RenameCategoryById();
    static void RenameCategoryByName();
};
#endif