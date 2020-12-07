#include "WindowInsert.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void WindowInsert::setupModel()
{
    model = new QStandardItemModel(1, 3, this);

    QStringList name;
    name << "Culoare";

    QStringList value;
    value << "Albastru";
              
    QStringList fk;
    fk << "1";

    for (int row = 0; row < 1; ++row) {
      QStandardItem *item = new QStandardItem(name[row]);
      model->setItem(row, 0, item);
      item = new QStandardItem(value[row]);
      model->setItem(row, 1, item);
      item = new QStandardItem(fk[row]);
      model->setItem(row, 2, item);
    }
}

WindowInsert::WindowInsert(int server_socket, QWidget *parent)
    : QWidget(parent)
{
    this->server_socket = server_socket;

    setupModel();

    nameLabel = new QLabel(tr("Name:"));
    nameEdit = new QLineEdit();
    valueLabel = new QLabel(tr("Value:"));
    valueEdit = new QLineEdit();
    fkLabel = new QLabel(tr("Foreign Key"));
    fkEdit = new QLineEdit();
    insertButton = new QPushButton(tr("Insert"));
    
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(nameEdit, 0);
    mapper->addMapping(valueEdit, 1);
    mapper->addMapping(fkEdit, 2);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(nameLabel, 0, 0, 1, 1);
    layout->addWidget(nameEdit, 0, 1, 1, 1);
    
    layout->addWidget(valueLabel, 1, 0, 1, 1);
    layout->addWidget(valueEdit, 1, 1, 2, 1);
    
    layout->addWidget(fkLabel, 3, 0, 1, 1);
    layout->addWidget(fkEdit, 3, 1, 1, 1);

    layout->addWidget(insertButton, 4, 0, 1, 1);
    setLayout(layout);

    setWindowTitle(tr("Insert Property"));
    mapper->toFirst();

    connect(insertButton, &QPushButton::clicked, this, &WindowInsert::buttonClicked);
    connect(nameEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this,&WindowInsert::on_lineEdit_textEdited_nameEdit);
    connect(valueEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this,&WindowInsert::on_lineEdit_textEdited_valueEdit);
    connect(fkEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this,&WindowInsert::on_lineEdit_textEdited_fkEdit);
}

void WindowInsert::buttonClicked(bool checked) {
    char server_reply[REPLY_DIMENSION];
    
    string send_message = "InsertProp," + nameEdit->text().toStdString() + "," + valueEdit->text().toStdString() + "," + fkEdit->text().toStdString();

    int n = send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << server_reply << endl;
}

void WindowInsert::on_lineEdit_textEdited_nameEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= 'A') && (str[i] <= 'Z') || (str[i] >= 'a') && (str[i] <= 'z')) {
            nameEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            nameEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}

void WindowInsert::on_lineEdit_textEdited_valueEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= 'A') && (str[i] <= 'Z') || (str[i] >= 'a') && (str[i] <= 'z') || (str[i] >= '0') && (str[i] <= '9') || (str[i] == '-') || (str[i] == ' ') || (str[i] == '.')) {
            valueEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            valueEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}

void WindowInsert::on_lineEdit_textEdited_fkEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= '0') && (str[i] <= '9')) {
            fkEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            fkEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}