#include "WindowRenameCatById.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;


void WindowRenameCatById::setupModel()
{
    model = new QStandardItemModel(1, 2, this);

    QStringList catId;
    catId << "1";

    QStringList catNewName;
    catNewName << "Diagonala";
              
    for (int row = 0; row < 1; ++row) {
      QStandardItem *item = new QStandardItem(catId[row]);
      model->setItem(row, 0, item);
      item = new QStandardItem(catNewName[row]);
      model->setItem(row, 1, item);
    }
}

WindowRenameCatById::WindowRenameCatById(int server_socket, QWidget *parent) :QWidget(parent) {

    this->server_socket = server_socket;
    setupModel();
    catIdLabel = new QLabel(tr("Category Id"));
    catIdEdit = new QLineEdit();
    catNewNameLabel = new QLabel(tr("New Category Name"));
    catNewNameEdit = new QLineEdit();
    updateButton = new QPushButton(tr("Update Category"));

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(catIdEdit, 0);
    mapper->addMapping(catNewNameEdit, 1);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(catIdLabel, 0, 0, 1, 1);
    layout->addWidget(catIdEdit, 0, 1, 1, 1);

    layout->addWidget(catNewNameLabel, 1, 0, 1, 1);
    layout->addWidget(catNewNameEdit, 1, 1, 2, 1);

    layout->addWidget(updateButton, 6, 0, 1, 1);
    setLayout(layout);

    setWindowTitle(tr("Update Category"));
    mapper->toFirst();

    connect(updateButton, &QPushButton::clicked, this, &WindowRenameCatById::buttonClicked);
}

void WindowRenameCatById::buttonClicked(bool clicked) {
    char property_reply[REPLY_DIMENSION];

    string send_message = "RenameCatById," + catNewNameEdit->text().toStdString() + "," + catIdEdit->text().toStdString();

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}