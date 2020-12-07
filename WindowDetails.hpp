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
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QVariant>
#include <QModelIndex>

using namespace std;

class WindowDetails : public QWidget
{
    Q_OBJECT

public:
    WindowDetails(int server_socket, QWidget *parent = nullptr);
    
private:
    
    int server_socket;

    QSqlTableModel *table_model;

    QTableView *view;

    QModelIndex index_model;

    string string_value_cell;

private slots:
    void on_any_itemChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>() );
};