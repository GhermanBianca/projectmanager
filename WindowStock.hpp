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

class WindowStock : public QWidget
{
    Q_OBJECT

public:
    WindowStock(int server_socket, QWidget *parent = nullptr);
    
private:
    void setupModel();

    QLabel *idLabel;
    QLabel *stockLabel;
    QLabel *priceLabel;
    QLabel *fkLabel;
    QLineEdit *idEdit;
    QLineEdit *stockEdit;
    QLineEdit *priceEdit;
    QLineEdit *fkEdit;
    QPushButton *insertButton;

    QStandardItemModel *model;
    QDataWidgetMapper *mapper;

    int server_socket;

private slots:
    void buttonClicked(bool checked);
    //void stockIncrement(bool checked);
};