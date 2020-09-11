#include "CrudProp.hpp"
#include "DbResponse.hpp"
#include "DisplayMenuProp.hpp"
#include "CrudCategory.hpp"
#include "ReadHierarchy.hpp"

#include <mysql/mysql.h>

#include <iostream>

using namespace std;

int main() {
    DbResponse::ConnectionFunction();
    DisplayMenuProp::DisplayMenu();
}