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

class WindowInsert : public QWidget
{
    Q_OBJECT

public:
    WindowInsert(int server_socket, QWidget *parent = nullptr);
    
private:
    void setupModel();

    QLabel *nameLabel;
    QLabel *valueLabel;
    QLabel *fkLabel;
    QLineEdit *nameEdit;
    QLineEdit *valueEdit;
    QLineEdit *fkEdit;
    QPushButton *insertButton;

    QStandardItemModel *model;
    QDataWidgetMapper *mapper;

    int server_socket;

private slots:
    void buttonClicked(bool checked);
};