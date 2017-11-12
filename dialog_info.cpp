#include "dialog_info.h"

dialog_info::dialog_info(QDialog *parent) : QDialog(parent)
{
      text = new QTextEdit(this);
      button_ok= new QPushButton("&Ok",this);
      layout = new QVBoxLayout;
      layout->addWidget(text);
      layout->addWidget(button_ok);
      setLayout(layout);
      resize(200,150);
      connect(button_ok,SIGNAL(pressed()),this,SLOT(accept()));
}
void dialog_info::set_text(QString str)
{
    text->setText(str);

}

QString dialog_info::get_text()
{//QTextDocument
    return text->toPlainText();
}
