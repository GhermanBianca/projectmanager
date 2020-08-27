#include "CrudCategory.hpp"
#include "DbResponse.hpp"
#include "DisplayMenuProp.hpp"

#include <iostream>
#include <vector>
#include <mysql/mysql.h>
#include <string>

using namespace std;

int CrudCategory::AddCategory(int ParentId, const string &CategoryName) {

     int IdParent;

    //inserarea noii categorii
    string insertcategory_query = "INSERT INTO category (CategoryName) VALUES ('"+CategoryName+"') ";

    const char* qi = insertcategory_query.c_str();

    qstate = mysql_query(conn, qi);

    if(!qstate) {
        cout << endl << "Registration succes!" << endl;
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    //aflarea id-ului noii categorii
    string findid_query = "SELECT CategoryID FROM category WHERE CategoryName = '"+ CategoryName +"' ";
    const char* qf = findid_query.c_str();
    qstate = mysql_query(conn, qf);

    if(!qstate) {
        res = mysql_store_result(conn);
        cout << endl;
        while ((row = mysql_fetch_row(res))) {
            IdParent = atoi(row[0]);
            cout << IdParent <<  endl;
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    //inserare in tabela jonctiune
    string insertparent_query = "INSERT INTO categorytocategory (Child,Parent) VALUES ('"+ to_string(IdParent) +"', '"+to_string(ParentId)+"') ";

    const char* qp = insertparent_query.c_str();

    qstate = mysql_query(conn, qp);

    if(!qstate) {
        cout << endl << "Registration succes!" << endl;
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    return IdParent;
}

void CrudCategory::RemoveCategoryById(int CategoryId) {

    int IdParent;
    vector<int> parent;

    string findid_query1 = "SELECT Child FROM categorytocategory WHERE Parent = '"+ to_string(CategoryId) +"'";
    const char* qf1 = findid_query1.c_str();
    qstate = mysql_query(conn, qf1);

    if(!qstate) {
        res = mysql_store_result(conn);
        cout << endl;
        while ((row = mysql_fetch_row(res))) {
            parent.push_back(atoi(row[0]));
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    for (auto i : parent)	
        cout << i << " ";   

    string delete_query ="DELETE FROM categorytocategory WHERE Parent = '"+ to_string(IdParent) +"' ";
    const char* qd = delete_query.c_str();
    qstate = mysql_query(conn, qd);

    if (!qstate) {
        cout << endl << "Successfully Deleted From Database." << endl;
    } else {
        cout << "Failed to Delete." << endl;
    }

    for (auto i : parent) {
        string delete_query1 ="DELETE FROM category WHERE CategoryID = ' "+ to_string(i) +"  ' ";
        const char* qd1 = delete_query1.c_str();
        qstate = mysql_query(conn, qd1);

        if (!qstate) {
            cout << endl << "Successfully Deleted From Database." << endl;
        } else {
            cout << "Failed to Delete." << endl;
        }
    }
    
    string delete_query3 ="DELETE FROM category WHERE CategoryID = '"+ to_string(IdParent) +"' ";
        const char* qd3 = delete_query3.c_str();
        qstate = mysql_query(conn, qd3);

        if (!qstate) {
            cout << endl << "Successfully Deleted From Database." << endl;
        } else {
            cout << "Failed to Delete." << endl;
        }
}

void CrudCategory::RemoveCategoryByName(const string &CategoryName) {

    int IdParent;
    vector<int> parent;

    string findid_query = "SELECT CategoryID FROM category WHERE CategoryName = '"+ CategoryName + "' ";
    const char* qf = findid_query.c_str();
    qstate = mysql_query(conn, qf);

    if(!qstate) {
        res = mysql_store_result(conn);
        cout << endl;
        while ((row = mysql_fetch_row(res))) {
            IdParent = atoi(row[0]);
            cout << IdParent <<  endl;
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    string findid_query1 = "SELECT Child FROM categorytocategory WHERE Parent = '"+ to_string(IdParent) +"'";
    const char* qf1 = findid_query1.c_str();
    qstate = mysql_query(conn, qf1);

    if(!qstate) {
        res = mysql_store_result(conn);
        cout << endl;
        while ((row = mysql_fetch_row(res))) {
            parent.push_back(atoi(row[0]));
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    for (auto i : parent)	
        cout << i << " ";   

    for (auto i : parent) {
        string delete_query1 ="DELETE FROM category WHERE CategoryID = ' "+ to_string(i) +"  ' ";
        const char* qd1 = delete_query1.c_str();
        qstate = mysql_query(conn, qd1);

        if (!qstate) {
            cout << endl << "Successfully Deleted From Database." << endl;
        } else {
            cout << "Failed to Delete." << endl;
        }
    }
    
    string delete_query3 ="DELETE FROM category WHERE CategoryName = '"+ CategoryName +"' ";
        const char* qd3 = delete_query3.c_str();
        qstate = mysql_query(conn, qd3);

        if (!qstate) {
            cout << endl << "Successfully Deleted From Database." << endl;
        } else {
            cout << "Failed to Delete." << endl;
        }

    string delete_query ="DELETE FROM categorytocategory WHERE Parent = '"+ to_string(IdParent) +"' ";
    const char* qd = delete_query.c_str();
    qstate = mysql_query(conn, qd);

    if (!qstate) {
        cout << endl << "Successfully Deleted From Database." << endl;
    } else {
        cout << "Failed to Delete." << endl;
    }
}

void CrudCategory::RenameCategoryById(int CategoryId,const string &CategoryName ) {

    int IdParent;

    string findid_query = "SELECT CategoryID FROM category WHERE CategoryName = '"+ CategoryName +"' ";
    const char* qf = findid_query.c_str();
    qstate = mysql_query(conn, qf);

    if(!qstate) {
        res = mysql_store_result(conn);
        cout << endl;
        while ((row = mysql_fetch_row(res))) {
            IdParent = atoi(row[0]);
            cout << IdParent <<  endl;
        }
    } else {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }

    string update_query = "UPDATE category SET CategoryName = '" + CategoryName + "' WHERE CategoryID = '" + to_string(CategoryId) + "' ";
    const char* qu = update_query.c_str();
    qstate = mysql_query(conn, qu);

    if (!qstate) {
        cout << endl << "Successfully Saved In Database." << endl;
    } else {
        cout << "Failed tu Update." << endl;
    }
}

void CrudCategory::RenameCategoryByName(const string &CategoryName, const string &NewCategoryName) {

    string update_query = "UPDATE category SET CategoryName = '" + NewCategoryName + "' WHERE CategoryName = '" + CategoryName + "' ";
    const char* qu = update_query.c_str();
    qstate = mysql_query(conn, qu);

    if (!qstate) {
        cout << endl << "Successfully Saved In Database." << endl;
    } else {
        cout << "Failed tu Update." << endl;
    }
}