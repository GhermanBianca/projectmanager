#include "WindowViewDetails.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

WindowViewDetails::WindowViewDetails(int server_socket, QWidget *parent)
    : QAbstractTableModel(parent)
{
    this->server_socket = server_socket;
}

int WindowViewDetails::rowCount(const QModelIndex & /*parent*/) const
{
   return 10;
}

int WindowViewDetails::columnCount(const QModelIndex & /*parent*/) const
{
    return 4;
}

QVariant WindowViewDetails::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    return QVariant();
}

QVariant WindowViewDetails::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Detail Id");
        case 1:
            return QString("Stock");
        case 2:
            return QString("Price");
        case 3:
            return QString("Fk Product Id");
        }
    }
    return QVariant();
}