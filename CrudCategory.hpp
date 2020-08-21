#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#include <string>
using namespace std;


class CrudCategory {
 public:

    static int AddCategory(int ParentId, const string &CategoryName);
    static void RemoveCategoryById(int CategoryId);
    static void RemoveCategoryByName(const string &CategoryName);
    static void RenameCategoryById(int CategoryId,const string &CategoryName);
    static void RenameCategoryByName(const string &CategoryName, const string &NewCategoryName);
};
#endif