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

class WindowRenameCatById : public QWidget {
        Q_OBJECT
    
public: 
    WindowRenameCatById(int server_socket, QWidget *parent = nullptr);
private:
    int server_socket;

    void setupModel();
    QLabel *catIdLabel;
    QLabel *catNewNameLabel;
    QLineEdit *catIdEdit;
    QLineEdit *catNewNameEdit;
    QPushButton *updateButton;

    QStandardItemModel *model;
    QDataWidgetMapper *mapper;

private slots:
    void buttonClicked(bool clicked);
    void on_lineEdit_textEdited_catIdEdit(const QString &str);
    void on_lineEdit_textEdited_catNewNameEdit(const QString &str);
};