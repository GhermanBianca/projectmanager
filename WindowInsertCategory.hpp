#pragma once

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

class WindowInsertCategory : public QWidget
{
    Q_OBJECT

public:
    WindowInsertCategory(int server_socket, QWidget *parent = nullptr);

private:
    void setupModel();

    QLabel *categoryNameLabel;
    QLineEdit *categoryNameEdit;
    QPushButton *insertCategoryButton;
    QPushButton *showCategoryIdButton;

    QStandardItemModel *model;
    QDataWidgetMapper *mapper;

    int server_socket;

private slots:
    void buttonClickedInsert(bool checked);
    void findIdNewCategoryNamebuttonClicked(bool checked);
    void on_lineEdit_textEdited_categoryNameEdit(const QString &str);
};