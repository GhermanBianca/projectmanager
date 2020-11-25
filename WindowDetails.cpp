#include "WindowDetails.hpp"
#include "WindowViewDetails.hpp"

#define REPLY_DIMENSION 6000

#include <mysql/mysql.h>
#include <sys/socket.h>
#include <errno.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

WindowDetails::WindowDetails(int server_socket, QWidget *parent)
    : QWidget(parent)
{
    this->server_socket = server_socket;

    table_details = new QTableView();

    myModel = new WindowViewDetails(server_socket);
    table_details->setModel(myModel);

    QGridLayout *layout = new QGridLayout();

    layout->addWidget(table_details, 0, 0, 1, 1);
    setLayout(layout);

    setWindowTitle(tr("Details"));
}
