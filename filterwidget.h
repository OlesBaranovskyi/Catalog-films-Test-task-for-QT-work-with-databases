#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include<QPushButton>
#include<QComboBox>
#include<QHBoxLayout>
class filterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit filterWidget(QWidget *parent = nullptr);
QLabel* label_film;
QLabel* label_year;
QLabel* label_rait;
///////////////////
QLineEdit* line_edit_film;
QLineEdit* line_edit_year;
QLineEdit* line_edit_rait;
//////////////////
QPushButton* button_find;
QPushButton* button_reset;
//QPushButton* button_add;
/////////////////////
QHBoxLayout* lay;

signals:

public slots:
};

#endif // FILTERWIDGET_H
