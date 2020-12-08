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
#include <QMessageBox>

class WindowDeleteCatById : public QWidget
{
    Q_OBJECT

public:
    WindowDeleteCatById(int server_socket, QWidget *parent = nullptr);

private:
    void setupModel();

    int server_socket;
    
    QLabel *idLabel;
    QLineEdit *idEdit;
    QPushButton *deleteButton;

    QStandardItemModel *model;
    QDataWidgetMapper *mapper;

private slots:
    void buttonClicked(bool checked);
    void on_lineEdit_textEdited_idEdit(const QString &str);
};