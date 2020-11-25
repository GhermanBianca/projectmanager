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

class WindowDisplay : public QWidget
{
    Q_OBJECT

public:
    WindowDisplay(int server_socket, QWidget *parent = nullptr);

private:
    void setupModel();

    int server_socket;

    QLabel *idLabel;
    QLineEdit *idEdit;
    QPushButton *displayButton;

    QStandardItemModel *model;
    QDataWidgetMapper *mapper;

private slots:
    void buttonClicked(bool checked);
};