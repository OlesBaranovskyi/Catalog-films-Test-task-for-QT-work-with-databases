#ifndef MY_DIALOG_H
#define MY_DIALOG_H

#include <QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include<QGridLayout>
#include<QDialog>

class my_dialog : public QDialog
{
    Q_OBJECT
public:

        QPushButton* button_cancel;
        QPushButton*  button_ok;

        QLineEdit* line_edit_name_film;
        QLineEdit* line_edit_producer;
        QLineEdit* line_edit_year;
        QLineEdit* line_edit_raiting;

        QLabel* label_name_film;
        QLabel* label_producer;
        QLabel* label_year;
        QLabel* label_raiting;



        QGridLayout* layout;
        bool button_activ = false;
        bool switch_button();
        void clear_lines();
        my_dialog();
public slots:

        void slot_switch_button();


};

#endif // MY_DIALOG_H
