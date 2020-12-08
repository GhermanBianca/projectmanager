#include "WindowUpdate.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void WindowUpdate::setupModel()
{
    model = new QStandardItemModel(1, 4, this);

    QStringList id;
    id << "1";

    QStringList newName;
    newName << "Diagonala";
              
    QStringList newValue;
    newValue << "15";

    QStringList newFk;
    newFk << "2";

    for (int row = 0; row < 1; ++row) {
      QStandardItem *item = new QStandardItem(id[row]);
      model->setItem(row, 0, item);
      item = new QStandardItem(newName[row]);
      model->setItem(row, 1, item);
      item = new QStandardItem(newValue[row]);
      model->setItem(row, 2, item);
      item = new QStandardItem(newFk[row]);
      model->setItem(row, 3, item);
    }
}

WindowUpdate::WindowUpdate(int server_socket, QWidget *parent)
    :QWidget(parent) {

        this->server_socket = server_socket;

        setupModel();
        idLabel = new QLabel(tr("Id"));
        idEdit = new QLineEdit();
        newNameLabel = new QLabel(tr("New Name"));
        newNameEdit = new QLineEdit();
        newValueLabel = new QLabel(tr("New Value"));
        newValueEdit = new QLineEdit();
        newFkLabel = new QLabel(tr("New Foreign Key"));
        newFkEdit = new QLineEdit();
        updateButton = new QPushButton(tr("Update"));

        mapper = new QDataWidgetMapper(this);
        mapper->setModel(model);

        mapper->addMapping(idEdit, 0);
        mapper->addMapping(newNameEdit, 1);
        mapper->addMapping(newValueEdit, 2);
        mapper->addMapping(newFkEdit, 3);

        QGridLayout *layout = new QGridLayout();
        layout->addWidget(idLabel, 0, 0, 1, 1);
        layout->addWidget(idEdit, 0, 1, 1, 1);

        layout->addWidget(newNameLabel, 1, 0, 1, 1);
        layout->addWidget(newNameEdit, 1, 1, 2, 1);

        layout->addWidget(newValueLabel, 3, 0, 1, 1);
        layout->addWidget(newValueEdit, 3, 1, 1, 1);

        layout->addWidget(newFkLabel, 4, 0, 1, 1);
        layout->addWidget(newFkEdit, 4, 1, 2, 1);

        layout->addWidget(updateButton, 6, 0, 1, 1);
        setLayout(layout);

        setWindowTitle(tr("Update Property"));
        mapper->toFirst();

        connect(updateButton, &QPushButton::clicked, this, &WindowUpdate::buttonClicked);
        connect(newNameEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this, &WindowUpdate::on_lineEdit_textEdited_newNameEdit);
        connect(newValueEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this, &WindowUpdate::on_lineEdit_textEdited_newValueEdit);
        connect(newFkEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this, &WindowUpdate::on_lineEdit_textEdited_newFkEdit);
        connect(idEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this, &WindowUpdate::on_lineEdit_textEdited_idEdit);
    }

    void WindowUpdate::buttonClicked(bool checked) {
    char server_reply[REPLY_DIMENSION];

    string send_message = "UpdateProp," + newNameEdit->text().toStdString() + "," + newValueEdit->text().toStdString() + "," + newFkEdit->text().toStdString() + "," + idEdit->text().toStdString();

    int n = send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
	cout << server_reply << endl;
}

void WindowUpdate::on_lineEdit_textEdited_newNameEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= 'A') && (str[i] <= 'Z') || (str[i] >= 'a') && (str[i] <= 'z') ) {
            newNameEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        }
        else {
            newNameEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}

void WindowUpdate::on_lineEdit_textEdited_newValueEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= 'A') && (str[i] <= 'Z') || (str[i] >= 'a') && (str[i] <= 'z') || (str[i] >= '0') && (str[i] <= '9') || (str[i] == '-') || (str[i] == ' ') || (str[i] == '.')) {
            newValueEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            newValueEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}

void WindowUpdate::on_lineEdit_textEdited_newFkEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= '0') && (str[i] <= '9')) {
            newFkEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            newFkEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}

void WindowUpdate::on_lineEdit_textEdited_idEdit(const QString &str) {
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