#include "WindowDelete.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void WindowDelete::setupModel()
{
    model = new QStandardItemModel(1, 1, this);
    QString id = "1";
    QStandardItem *item = new QStandardItem(id);
    model->setItem(0, item);
}

WindowDelete::WindowDelete(int server_socket, QWidget *parent)
    : QWidget(parent)
{
    this->server_socket = server_socket;

    setupModel();
    idLabel = new QLabel(tr("Id:"));
    idEdit = new QLineEdit();
    deleteButton = new QPushButton(tr("Delete"));

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(idEdit, 0);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(idLabel, 0, 0, 1, 1);
    layout->addWidget(idEdit, 0, 1, 1, 1);

    layout->addWidget(deleteButton, 1, 0, 1, 1);
    setLayout(layout);

    setWindowTitle(tr("Delete Property"));
    mapper->toFirst();

    connect(deleteButton, &QPushButton::clicked, this, &WindowDelete::buttonClicked);
    connect(idEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this, &WindowDelete::on_lineEdit_textEdited_idEdit);
}

void WindowDelete::buttonClicked(bool clicked) {
    char server_reply[REPLY_DIMENSION];

    string send_message = "DeleteProp," + idEdit->text().toStdString();

    int n = send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
	cout << server_reply << endl;
}

void WindowDelete::on_lineEdit_textEdited_idEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= '0') && (str[i] <= '9')) {
            idEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            idEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}