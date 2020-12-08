#include "WindowRenameCatByName.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void WindowRenameCatByName::setupModel()
{
    model = new QStandardItemModel(1, 2, this);

    QStringList newCatName;
    newCatName << "Accesorii laptop";

    QStringList catName;
    catName << "Laptop-uri";
              
    for (int row = 0; row < 1; ++row) {
      QStandardItem *item = new QStandardItem(newCatName[row]);
      model->setItem(row, 0, item);
      item = new QStandardItem(catName[row]);
      model->setItem(row, 1, item);
    }
}

WindowRenameCatByName::WindowRenameCatByName(int server_socket, QWidget *parent)
    :QWidget(parent) {

        this->server_socket = server_socket;

        setupModel();
        newCatNameLabel = new QLabel(tr("New Category Name"));
        newCatNameEdit = new QLineEdit();
        catNameLabel = new QLabel(tr("Category Name"));
        catNameEdit = new QLineEdit();
        updateButton = new QPushButton(tr("Update Category"));

        mapper = new QDataWidgetMapper(this);
        mapper->setModel(model);

        mapper->addMapping(newCatNameEdit, 0);
        mapper->addMapping(catNameEdit, 1);

        QGridLayout *layout = new QGridLayout();
        layout->addWidget(catNameLabel, 0, 0, 1, 1);
        layout->addWidget(catNameEdit, 0, 1, 1, 1);

        layout->addWidget(newCatNameLabel, 1, 0, 1, 1);
        layout->addWidget(newCatNameEdit, 1, 1, 2, 1);

        layout->addWidget(updateButton, 6, 0, 1, 1);
        setLayout(layout);

        setWindowTitle(tr("Update Category"));
        mapper->toFirst();

        connect(updateButton, &QPushButton::clicked, this, &WindowRenameCatByName::buttonClicked);
        connect(newCatNameEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this, &WindowRenameCatByName::on_lineEdit_textEdited_newCatNameEdit);
        connect(catNameEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this, &WindowRenameCatByName::on_lineEdit_textEdited_catNameEdit);
    }

void WindowRenameCatByName::buttonClicked(bool clicked) {
    char property_reply[REPLY_DIMENSION];

    string send_message = "RenameCatByName," + newCatNameEdit->text().toStdString() + "," + catNameEdit->text().toStdString();

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}

void WindowRenameCatByName::on_lineEdit_textEdited_newCatNameEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= 'A') && (str[i] <= 'Z') || (str[i] >= 'a') && (str[i] <= 'z') || (str[i] == '-') || (str[i] == ' ') || (str[i] == ',') || (str[i] == '&')) {
            newCatNameEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            newCatNameEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}

void WindowRenameCatByName::on_lineEdit_textEdited_catNameEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= 'A') && (str[i] <= 'Z') || (str[i] >= 'a') && (str[i] <= 'z') || (str[i] == '-') || (str[i] == ' ') || (str[i] == ',') || (str[i] == '&')) {
            catNameEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            catNameEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}