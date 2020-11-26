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

class WindowRenameCatByName : public QWidget {
        Q_OBJECT
    
public: 
    WindowRenameCatByName(int server_socket, QWidget *parent = nullptr);
private:
    int server_socket;

    void setupModel();
    QLabel *newCatNameLabel;
    QLabel *catNameLabel;
    QLineEdit *newCatNameEdit;
    QLineEdit *catNameEdit;
    QPushButton *updateButton;

    QStandardItemModel *model;
    QDataWidgetMapper *mapper;

private slots:
    void buttonClicked(bool clicked);
};