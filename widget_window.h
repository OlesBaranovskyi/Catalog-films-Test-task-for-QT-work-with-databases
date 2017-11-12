#ifndef WIDGET_WINDOW_H
#define WIDGET_WINDOW_H
#include <QWidget>
#include "filterwidget.h"
#include <QSql>
#include <QtSql>
#include <QTableView>
#include<QSqlTableModel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include"my_model.h"
#include "my_dialog.h"
#include<QRegExp>
#include <QMessageBox>
#include"widget_show_info.h"
#include "dialog_info.h"
class widget_window : public QWidget
{
    Q_OBJECT

    QSqlDatabase db;//:: dbQSqlDatabase::addDatabase("QSQLITE");
    filterWidget* filter;
    QSqlTableModel* model;
    my_model* myModel;
    QTableView* view;
    //QSqlDatabase db;
    dialog_info* w_info;
    my_dialog* my_dialog_add;

    QVBoxLayout* lay_button;
    QHBoxLayout* lay;
    QVBoxLayout* lay_all;

    QPushButton* button_add;
    QPushButton* button_info;
    QPushButton* button_close;
public:
    explicit widget_window(QWidget *parent = nullptr);
bool add_new_row();
bool add(QString name, QString producer, int year, int reit);
void show_info();
bool create_database();
bool create_table();


signals:

public slots:
void slot_add_new();
void slot_show_add_dialog();
void slot_close();
void slot_find();
void slot_reset_filter();
void slot_show_info();

};

#endif // WIDGET_WINDOW_H
