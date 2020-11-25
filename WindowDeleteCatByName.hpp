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

class WindowDeleteCatByName : public QWidget
{
    Q_OBJECT

public:
    WindowDeleteCatByName(int server_socket,QWidget *parent = nullptr);

private:
    void setupModel();
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QPushButton *deleteButton;

    QStandardItemModel *model;
    QDataWidgetMapper *mapper;

    int server_socket;

private slots:
    void buttonClicked(bool checked);
};