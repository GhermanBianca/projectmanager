#include "StockSimulation.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

void StockSimulation::setupModel()
{
    model = new QStandardItemModel(1, 1, this);
}

StockSimulation::StockSimulation(int server_socket, QWidget *parent)
    : QWidget(parent)
{
    this->server_socket = server_socket;

    setupModel();

    simulationButton = new QPushButton(tr("Simulation"));

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);

    QGridLayout *layout = new QGridLayout();

    layout->addWidget(simulationButton, 1, 0, 1, 1);
    setLayout(layout);

    setWindowTitle(tr("Stock Simulation"));

    connect(simulationButton, &QPushButton::clicked, this, &StockSimulation::buttonClicked);
}

void StockSimulation::buttonClicked(bool checked) {
    char server_reply[REPLY_DIMENSION];
    
    string send_message = "Simulation,";

    int n = send(server_socket , send_message.c_str(), strlen(send_message.c_str()) + 1 , 0);

    if (recv(server_socket, server_reply , REPLY_DIMENSION, 0) < 0) {
        cout << "Recv failed" << endl;
    }
    cout << "Reply received\n" << endl;
    cout << server_reply << endl;
}
