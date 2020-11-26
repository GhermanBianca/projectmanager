#include "WindowInsertCatToCat.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void WindowInsertCatToCat::setupModel()
{
    model = new QStandardItemModel(1, 2, this);
              
    QStringList idChild;
    idChild << "5";

    QStringList idPrt;
    idPrt << "4";

    for (int row = 0; row < 1; ++row) {
      QStandardItem *item = new QStandardItem(idChild[row]);
      item = new QStandardItem(idChild[row]);
      model->setItem(row, 0, item);
      item = new QStandardItem(idPrt[row]);
      model->setItem(row, 1, item);
    }
}

WindowInsertCatToCat::WindowInsertCatToCat(int server_socket, QWidget *parent)
    : QWidget(parent)
{
    this->server_socket = server_socket;

    setupModel();

    idChildLabel = new QLabel(tr("Id Child:"));
    idChildEdit = new QLineEdit();
    idPrtLabel = new QLabel(tr("Id Parent:"));
    idPrtEdit = new QLineEdit();
    
    insertCatToCatButton = new QPushButton(tr("Insert Category"));

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    mapper->addMapping(idChildEdit, 0);
    mapper->addMapping(idPrtEdit, 1);

    QGridLayout *layout = new QGridLayout();
    
    layout->addWidget(idChildLabel, 0, 0, 1, 1);
    layout->addWidget(idChildEdit, 0, 1, 1, 1);

    layout->addWidget(idPrtLabel, 1, 0, 1, 1);
    layout->addWidget(idPrtEdit, 1, 1, 1, 1);

    layout->addWidget(insertCatToCatButton, 2, 0, 1, 1);
    setLayout(layout);

    setWindowTitle(tr("Insert Category"));
    mapper->toFirst();

    connect(insertCatToCatButton, &QPushButton::clicked, this, &WindowInsertCatToCat::buttonClickedInsertCatToCat);
}

void WindowInsertCatToCat::buttonClickedInsertCatToCat(bool checked) {
    char server_reply[REPLY_DIMENSION];
    
    string send_message = "InsertCatToCat," + idChildEdit->text().toStdString() + "," + idPrtEdit->text().toStdString();

    int n = send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << server_reply << endl;
}

