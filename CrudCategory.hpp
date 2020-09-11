#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#include <string>

class CrudCategory {
 public:

    static int AddCategory(int ParentId, const std::string &CategoryName);
    static void RemoveCategoryById(int CategoryId);
    static void RemoveCategoryByName(const std::string &CategoryName);
    static void RenameCategoryById(int CategoryId, const std::string &CategoryName);
    static void RenameCategoryByName(const std::string &CategoryName, const std::string &NewCategoryName);
};
#endif