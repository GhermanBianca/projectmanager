#include "WindowDisplay.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void WindowDisplay::setupModel()
{
    model = new QStandardItemModel(1, 1, this);
    QString ids = "1";
    QStandardItem *item = new QStandardItem(ids);
    model->setItem(0, item);
}

WindowDisplay::WindowDisplay(int server_socket, QWidget *parent)
    : QWidget(parent)
{
    this->server_socket = server_socket;

    setupModel();

    idLabel = new QLabel(tr("Id:"));
    idEdit = new QLineEdit();
    displayButton = new QPushButton(tr("Display"));

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(idEdit, 0);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(idLabel, 0, 0, 1, 1);
    layout->addWidget(idEdit, 0, 1, 1, 1);

    layout->addWidget(displayButton, 1, 0, 1, 1);
    setLayout(layout);

    setWindowTitle(tr("Display Property"));
    mapper->toFirst();

    connect(displayButton, &QPushButton::clicked, this, &WindowDisplay::buttonClicked);
}

void WindowDisplay::buttonClicked(bool checked) {
    char server_reply[REPLY_DIMENSION];

    string send_message = "DisplayProp," + idEdit->text().toStdString();

    int n = send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);


    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
	cout << server_reply << endl;
}
