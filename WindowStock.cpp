#include "WindowStock.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void WindowStock::setupModel()
{
    model = new QStandardItemModel(1, 4, this);

    QStringList id;
    id << "1";

    QStringList stock;
    stock << "45";

    QStringList price;
    price << "213 lei";
              
    QStringList fk;
    fk << "8";


    for (int row = 0; row < 1; ++row) {
      QStandardItem *item = new QStandardItem(id[row]);
      model->setItem(row, 0, item);
      item = new QStandardItem(stock[row]);
      model->setItem(row, 1, item);
      item = new QStandardItem(price[row]);
      model->setItem(row, 2, item);
      item = new QStandardItem(fk[row]);
      model->setItem(row, 3, item);
    }
}

WindowStock::WindowStock(int server_socket, QWidget *parent)
    : QWidget(parent)
{
    this->server_socket = server_socket;

    setupModel();

    idLabel = new QLabel(tr("Id:"));
    idEdit = new QLineEdit();
    stockLabel = new QLabel(tr("Stock:"));
    stockEdit = new QLineEdit();
    priceLabel = new QLabel(tr("Price:"));
    priceEdit = new QLineEdit();
    fkLabel = new QLabel(tr("Foreign Key"));
    fkEdit = new QLineEdit();
    insertButton = new QPushButton(tr("Insert"));
    
    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(idEdit, 0);
    mapper->addMapping(stockEdit, 1);
    mapper->addMapping(priceEdit, 2);
    mapper->addMapping(fkEdit, 3);

    QGridLayout *layout = new QGridLayout();

    layout->addWidget(idLabel, 0, 0, 1, 1);
    layout->addWidget(idEdit, 0, 1, 1, 1);

    layout->addWidget(stockLabel, 1, 0, 1, 1);
    layout->addWidget(stockEdit, 1, 1, 1, 1);
    
    layout->addWidget(priceLabel, 2, 0, 1, 1);
    layout->addWidget(priceEdit, 2, 1, 1, 1);
    
    layout->addWidget(fkLabel, 3, 0, 1, 1);
    layout->addWidget(fkEdit, 3, 1, 1, 1);

    layout->addWidget(insertButton, 4, 0, 1, 1);
    setLayout(layout);

    setWindowTitle(tr("Insert Product Details"));
    mapper->toFirst();

    connect(insertButton, &QPushButton::clicked, this, &WindowStock::buttonClicked);
    connect(idEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this,&WindowStock::on_lineEdit_textEdited_idEdit);
    connect(stockEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this,&WindowStock::on_lineEdit_textEdited_stockEdit);
    connect(priceEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this,&WindowStock::on_lineEdit_textEdited_priceEdit);
    connect(fkEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this,&WindowStock::on_lineEdit_textEdited_fkEdit);
}

void WindowStock::buttonClicked(bool checked) {
    char server_reply[REPLY_DIMENSION];
    
    string send_message = "InsertStock," + idEdit->text().toStdString() + "," + stockEdit->text().toStdString() + "," + priceEdit->text().toStdString() + "," + fkEdit->text().toStdString();

    int n = send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << server_reply << endl;
}

void WindowStock::on_lineEdit_textEdited_priceEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= 'A') && (str[i] <= 'Z') || (str[i] >= 'a') && (str[i] <= 'z') || (str[i] >= '0') && (str[i] <= '9') || (str[i] <= ' ')) {
            priceEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            priceEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}

void WindowStock::on_lineEdit_textEdited_stockEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= '0') && (str[i] <= '9')) {
            stockEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            stockEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}

void WindowStock::on_lineEdit_textEdited_fkEdit(const QString &str) {
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

void WindowStock::on_lineEdit_textEdited_idEdit(const QString &str) {
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


