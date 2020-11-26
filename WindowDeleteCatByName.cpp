#include "WindowDeleteCatByName.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void WindowDeleteCatByName::setupModel()
{
    model = new QStandardItemModel(1, 1, this);
    QString name = "Laptop-uri";
    QStandardItem *item = new QStandardItem(name);
    model->setItem(0, item);
}

WindowDeleteCatByName::WindowDeleteCatByName(int server_socket, QWidget *parent)
    : QWidget(parent)
{
    this->server_socket = server_socket;

    setupModel();

    nameLabel = new QLabel(tr("Name:"));
    nameEdit = new QLineEdit();
    deleteButton = new QPushButton(tr("Delete Category"));

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(nameEdit, 0);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(nameLabel, 0, 0, 1, 1);
    layout->addWidget(nameEdit, 0, 1, 1, 1);

    layout->addWidget(deleteButton, 1, 0, 1, 1);
    setLayout(layout);

    setWindowTitle(tr("Delete Category"));
    mapper->toFirst();

    connect(deleteButton, &QPushButton::clicked, this, &WindowDeleteCatByName::buttonClicked);
}

void WindowDeleteCatByName::buttonClicked(bool checked) {
    char property_reply[REPLY_DIMENSION];

    string send_message = "DeleteCatName," + nameEdit->text().toStdString();

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}