#include "WindowDeleteCatById.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void WindowDeleteCatById::setupModel()
{
    model = new QStandardItemModel(1, 1, this);
    QString id = "1";
    QStandardItem *item = new QStandardItem(id);
    model->setItem(0, item);
}

WindowDeleteCatById::WindowDeleteCatById(int server_socket, QWidget *parent)
    : QWidget(parent)
{
    this->server_socket = server_socket;

    setupModel();
    idLabel = new QLabel(tr("Id:"));
    idEdit = new QLineEdit();
    deleteButton = new QPushButton(tr("Delete Category"));

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(idEdit, 0);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(idLabel, 0, 0, 1, 1);
    layout->addWidget(idEdit, 0, 1, 1, 1);

    layout->addWidget(deleteButton, 1, 0, 1, 1);
    setLayout(layout);

    setWindowTitle(tr("Delete Category"));
    mapper->toFirst();

    connect(deleteButton, &QPushButton::clicked, this, &WindowDeleteCatById::buttonClicked);
}

void WindowDeleteCatById::buttonClicked(bool checked) {
    char property_reply[REPLY_DIMENSION];

    string send_message = "DeleteCatId," + idEdit->text().toStdString();

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}
