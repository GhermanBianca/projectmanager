#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QAbstractButton>
#include <QStandardItemModel>
#include <QStringList>
#include <QStandardItem>
#include <QApplication>
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <QTableView>
class WindowViewDetails;

class WindowDetails : public QWidget
{
    Q_OBJECT

public:
    WindowDetails(int server_socket, QWidget *parent = nullptr);
    
private:
    
    int server_socket;

    QTableView *table_details;

    WindowViewDetails *myModel;
};