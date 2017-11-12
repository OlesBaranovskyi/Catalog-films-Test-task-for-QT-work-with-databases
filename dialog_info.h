#ifndef DIALOG_INFO_H
#define DIALOG_INFO_H
#include<QDialog>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include<QVBoxLayout>
class dialog_info: public QDialog
{
    Q_OBJECT
    QTextEdit* text;
    QPushButton* button_ok;

    QVBoxLayout* layout;
public:
    explicit dialog_info(QDialog *parent = nullptr);
    void set_text(QString str);
    QString get_text();

signals:

public slots:

};

#endif // DIALOG_INFO_H
