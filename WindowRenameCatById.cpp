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
    connect(catIdEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this, &WindowRenameCatById::on_lineEdit_textEdited_catIdEdit);
    connect(catNewNameEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this, &WindowRenameCatById::on_lineEdit_textEdited_catNewNameEdit);
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

void WindowRenameCatById::on_lineEdit_textEdited_catIdEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= '0') && (str[i] <= '9')) {
            catIdEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            catIdEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}

void WindowRenameCatById::on_lineEdit_textEdited_catNewNameEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= 'A') && (str[i] <= 'Z') || (str[i] >= 'a') && (str[i] <= 'z') || (str[i] == '-') || (str[i] == ' ') || (str[i] == ',') || (str[i] == '&')) {
            catNewNameEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            catNewNameEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}