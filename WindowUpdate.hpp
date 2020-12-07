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

class WindowUpdate : public QWidget {
        Q_OBJECT
    
public: 
    WindowUpdate(int server_socket, QWidget *parent = nullptr);
private:

    int server_socket;

    void setupModel();
    QLabel *idLabel;
    QLabel *newNameLabel;
    QLabel *newValueLabel;
    QLabel *newFkLabel;
    QLineEdit *idEdit;
    QLineEdit *newNameEdit;
    QLineEdit *newValueEdit;
    QLineEdit *newFkEdit;
    QPushButton *updateButton;

    QStandardItemModel *model;
    QDataWidgetMapper *mapper;

private slots:
    void buttonClicked(bool checked);
    void on_lineEdit_textEdited_newNameEdit(const QString &str);
    void on_lineEdit_textEdited_newValueEdit(const QString &str);
    void on_lineEdit_textEdited_newFkEdit(const QString &str);
    void on_lineEdit_textEdited_idEdit(const QString &str);
};