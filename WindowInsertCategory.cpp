#include "WindowInsertCategory.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void WindowInsertCategory::setupModel()
{
    model = new QStandardItemModel(1, 1, this);

    QStringList catName;
    catName << "Laptop";

    for (int row = 0; row < 1; ++row) {
      QStandardItem *item = new QStandardItem(catName[row]);
      item = new QStandardItem(catName[row]);
      model->setItem(row, 0, item);
    }
}

WindowInsertCategory::WindowInsertCategory(int server_socket, QWidget *parent)
    : QWidget(parent)
{
    this->server_socket = server_socket;

    setupModel();

    categoryNameLabel = new QLabel(tr("Category Name:"));
    categoryNameEdit = new QLineEdit();
    
    insertCategoryButton = new QPushButton(tr("Insert Category"));
    showCategoryIdButton = new QPushButton(tr("Show Category Id"));

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(categoryNameEdit, 0);

    QGridLayout *layout = new QGridLayout();
    
    layout->addWidget(categoryNameLabel, 0, 0, 1, 1);
    layout->addWidget(categoryNameEdit, 0, 1, 1, 1);
    
    layout->addWidget(insertCategoryButton, 3, 0, 1, 1);
    layout->addWidget(showCategoryIdButton, 4, 0, 1, 1);

    setLayout(layout);

    setWindowTitle(tr("Insert Category"));
    mapper->toFirst();

    connect(insertCategoryButton, &QPushButton::clicked, this, &WindowInsertCategory::buttonClickedInsert);
    connect(showCategoryIdButton, &QPushButton::clicked, this, &WindowInsertCategory::findIdNewCategoryNamebuttonClicked);
    connect(categoryNameEdit, static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textEdited), this, &WindowInsertCategory::on_lineEdit_textEdited_categoryNameEdit);
}

void WindowInsertCategory::buttonClickedInsert(bool checked) {
    char server_reply[REPLY_DIMENSION];
    
    string send_message = "InsertCat," + categoryNameEdit->text().toStdString();

    int n = send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << server_reply << endl;
}

void WindowInsertCategory::findIdNewCategoryNamebuttonClicked(bool checked) {

    char property_reply[REPLY_DIMENSION];

    string send_message = "FindIdNewCatName," + categoryNameEdit->text().toStdString();

    send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, property_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << property_reply << endl;
}

void WindowInsertCategory::on_lineEdit_textEdited_categoryNameEdit(const QString &str) {
    int flag = 0;

    for(int i = 0; i < str.length(); ++i) {
        if((str[i] >= 'A') && (str[i] <= 'Z') || (str[i] >= 'a') && (str[i] <= 'z') || (str[i] == '-') || (str[i] == ' ') || (str[i] == ',') || (str[i] == '&')) {
            categoryNameEdit->setStyleSheet("QLineEdit{border: 2px solid green}");
        } else {
            categoryNameEdit->setStyleSheet("QLineEdit{border: 2px solid red}");
            flag = 1;
            break;
        }
    }

    if(flag == 1) {
        QMessageBox::warning(this, "Check", "Wrong Input!");
    }
}