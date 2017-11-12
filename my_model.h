#ifndef MY_MODEL_H
#define MY_MODEL_H
#include <QSqlTableModel>
#include <QWidget>

class my_model : public QSqlTableModel
{
public:
    my_model();
Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // MY_MODEL_H
