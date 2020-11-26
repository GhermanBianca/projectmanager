#include "WindowDetails.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>


using namespace std;

WindowDetails::WindowDetails(int server_socket, QWidget *parent)
    : QWidget(parent)
{
    this->server_socket = server_socket;

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("product_manager");
    db.setUserName("root");
    db.setPassword("1q2w3e");
    if(!db.open())
        QMessageBox::information(this, "Error", "Couldn't open database!");

    table_model = new QSqlTableModel();
    table_model->setTable("details");
    table_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table_model->select();
    table_model->setHeaderData(0, Qt::Horizontal, tr("DetailID"));
    table_model->setHeaderData(1, Qt::Horizontal, tr("Stock"));
    table_model->setHeaderData(2, Qt::Horizontal, tr("Price"));
    table_model->setHeaderData(1, Qt::Horizontal, tr("Fk_ProductID"));

    QTableView *view = new QTableView;
    view->setModel(table_model);
    view->resize(430, 350);
    view->show();
}