#include "WindowDetails.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

#include <QTableWidget>
#include <QVariant>
#include <QModelIndex>
#include <QDataStream>


using namespace std;

void WindowDetails::on_any_itemChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles){
    QVariant value_cell_price;
    QVariant value_cell_id;
    QVariant value_cell_stock;
    QVariant value_cell_fk;

    index_model=view->selectionModel()->currentIndex();

    if(index_model.column() != 1 || index_model.column() != 2 || index_model.column() != 3) {
        cout << "Try again!" << endl;
    } 

    value_cell_price = index_model.sibling(index_model.row(), 2).data();
    value_cell_stock = index_model.sibling(index_model.row(), 1).data();
    value_cell_fk = index_model.sibling(index_model.row(), 3).data();
    value_cell_id = index_model.sibling(index_model.row(), 0).data();


    int row = index_model.row();
    int column = index_model.column();

    cout << "Row changed:" << endl;
    cout << row << endl;
    cout << "Column changed:" << endl;
    cout << column << endl;

    QSqlQuery query_price;
    query_price.prepare("update details set Price = ? where DetailID = ? ");
    query_price.addBindValue(value_cell_price);
    query_price.addBindValue(value_cell_id);
    query_price.exec();

    QSqlQuery query_stock;
    query_stock.prepare("update details set Stock = ? where DetailID = ? ");
    query_stock.addBindValue(value_cell_stock);
    query_stock.addBindValue(value_cell_id);
    query_stock.exec();

    QSqlQuery query_fk;
    query_fk.prepare("update details set Fk_ProductID = ? where DetailID = ? ");
    query_fk.addBindValue(value_cell_fk);
    query_fk.addBindValue(value_cell_id);
    query_fk.exec();

}

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
    table_model->setHeaderData(3, Qt::Horizontal, tr("Fk_ProductID"));

    view = new QTableView;
    view->setModel(table_model);
    view->resize(430, 350);
    view->show();

    QAbstractItemModel * detail_table = view->model();

    connect(detail_table, &QAbstractItemModel::dataChanged, this, &WindowDetails::on_any_itemChanged);
}