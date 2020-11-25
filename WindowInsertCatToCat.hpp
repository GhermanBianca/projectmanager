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

class WindowInsertCatToCat : public QWidget
{
    Q_OBJECT

public:
    WindowInsertCatToCat(int server_socket, QWidget *parent = nullptr);

private:
    void setupModel();

    QLabel *idChildLabel;
    QLabel *idPrtLabel;
    QLineEdit *idChildEdit;
    QLineEdit *idPrtEdit;
    QPushButton *insertCatToCatButton;

    QStandardItemModel *model;
    QDataWidgetMapper *mapper;

    int server_socket;

private slots:
    void buttonClickedInsertCatToCat(bool checked);
};