#include "widget_window.h"

widget_window::widget_window(QWidget *parent) : QWidget(parent)
{   /*if(create_database())
    {
    create_table();
    }*/
    lay_button=new QVBoxLayout;
    lay = new QHBoxLayout;
    lay_all = new QVBoxLayout;

    button_add = new QPushButton("&Добавить",this);
    button_info = new QPushButton("&Информация",this);
    button_close = new QPushButton("&Закрыть",this);
    lay_button->addWidget(button_add);
    lay_button->addWidget(button_info);
    lay_button->addWidget(button_close);
    lay_button->setAlignment(this,Qt::AlignRight);

    filter = new filterWidget(this);
    w_info = new dialog_info;
    lay_all->addWidget(filter);
    resize(700,50);



model = new QSqlTableModel;

myModel = new my_model;
my_dialog_add = new my_dialog;
myModel->setTable("films");
myModel->select();
myModel->removeColumn(4);
model->setTable("films");
model->select();
model->setEditStrategy(QSqlTableModel::OnManualSubmit);
myModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
view = new QTableView;
view->setModel(myModel);
//view->setModel(model);
view->setParent(this);
view->move(0,50);
view->resize(700,250);

lay->addWidget(view);
lay->addLayout(lay_button);
lay_all->addLayout(lay);
setLayout(lay_all);

resize(750,400);
connect(button_add,SIGNAL(clicked(bool)),this,SLOT(slot_show_add_dialog()));
connect(my_dialog_add->button_ok,SIGNAL(pressed()),this,SLOT(slot_add_new()));
connect(button_close,SIGNAL(pressed()),this,SLOT(slot_close()));
connect(filter->button_find,SIGNAL(pressed()),this,SLOT(slot_find()));
connect(filter->button_reset,SIGNAL(pressed()),this,SLOT(slot_reset_filter()));

connect(button_info,SIGNAL(pressed()),this,SLOT(slot_show_info()));
}

bool widget_window::add_new_row() // добавление новой записи
{
    QString temp_name_film = my_dialog_add->line_edit_name_film->text();
    QString temp_producer = my_dialog_add->line_edit_producer->text();
    int temp_year=my_dialog_add->line_edit_year->text().toInt();
    int temp_rait=my_dialog_add->line_edit_raiting->text().toInt();

    QSqlTableModel tempmodel;
    tempmodel.setTable("films");
tempmodel.setFilter("название = '"+temp_name_film+"'");
tempmodel.select();

if(tempmodel.rowCount())QMessageBox::information(0,"Информация","Такое название есть в базе");

    tempmodel.setTable("films");
    tempmodel.setFilter("режиссер = '"+temp_producer+"'");
    tempmodel.select();


    if(tempmodel.rowCount()==0 )
{

     QMessageBox* message= new QMessageBox(QMessageBox::Information,"Информация","Такого режиссера нет в базе!  Добавить режиссера? ",QMessageBox::Yes | QMessageBox::No);
     int yes_or_no=message->exec();

    if(yes_or_no==QMessageBox::Yes)
    {
      add(temp_name_film,temp_producer,temp_year,temp_rait);
      myModel->select();
      myModel->removeColumn(4);
      my_dialog_add->clear_lines();
      my_dialog_add->hide();
      return true;
    }
 my_dialog_add->clear_lines();
 my_dialog_add->hide();
    return false;

}
   add(temp_name_film,temp_producer,temp_year,temp_rait);
    myModel->select();
    myModel->removeColumn(4);
    my_dialog_add->clear_lines();
    my_dialog_add->hide();
    return true;
}

bool widget_window::add(QString name, QString producer, int year, int reit=0)
{
    model->insertRow(0);
    model->setData(model->index(0,0),name);
    model->setData(model->index(0,1),producer);
    model->setData(model->index(0,2),year);
    model->setData(model->index(0,3),reit);
    model->submitAll();
    model->select();

    myModel->select();
    myModel->removeColumn(4);
    return true;
}

void widget_window::show_info()
{

    QSqlTableModel temp_model;
    temp_model.setEditStrategy(QSqlTableModel::OnManualSubmit);
    temp_model.setTable("films");

    QModelIndex tmpindex=view->currentIndex();
    int row=tmpindex.row();

    QSqlRecord rec=myModel->record(row);
    temp_model.setFilter("название = '"+rec.value("название").toString()+"'");
    temp_model.select();

    QSqlRecord rec2=temp_model.record(0);

    w_info->set_text(rec2.value("описание").toString());
    w_info->show();
    if(w_info->exec()==QDialog::Accepted){

   temp_model.setData(temp_model.index(0,4),w_info->get_text());


temp_model.submitAll();

    myModel->select();
    myModel->removeColumn(4);
    }


}

 bool widget_window::create_database()
{



     db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("testFilms");

   if(!db.open()){
      QMessageBox::information(0,"Ошибка ","Ошибка открытия базы");
       qDebug()<<"Eror open database";
    return false;
   }
   return true;
}

 bool widget_window::create_table()
    {
        QSqlQuery query;
        QString str="create table films (название text not null, режиссер text not null,год integer,рейтинг integer, описание text);";
        if(!query.exec(str)){
    QMessageBox::information(0,"Ошибка ","Ошибка содания таблицы");
       return false;
        }
    QMessageBox::information(0,"Ok ","Таблица создана ");
    return true;
    }






void widget_window::slot_add_new()
{
    add_new_row();

}

void widget_window::slot_show_add_dialog()
{
    my_dialog_add->show();
}

void widget_window::slot_close()
{
    model->submitAll();
    this->close();
    myModel->submitAll();
    this->close();

}

void widget_window::slot_find() // слот поиска
{
    QString name_film=filter->line_edit_film->text();
   QString year =filter->line_edit_year->text();
    QString rait=filter->line_edit_rait->text();

    if(name_film!="" && year!="" && rait !="" ){ // поиск по всем полям
  myModel->setFilter(" название = '"+name_film+"' And год = '"+year+"' and рейтинг = '"+rait+"' ");
}

if(name_film!="" && year!="" && rait =="" ){  //поиск по названию и году
  myModel->setFilter(" название = '"+name_film+"' And год = '"+year+"' ");
}

if(name_film!="" && year=="" && rait !="" ){ // поиск по названию и рейтингу
  myModel->setFilter(" название = '"+name_film+"'  and рейтинг = '"+rait+"' ");
}

if(name_film=="" && year!="" && rait !="" ){  // поиск по году и рейтингу
  myModel->setFilter("  год = '"+year+"' and рейтинг = '"+rait+"' ");
}

if(name_film=="" && year=="" && rait !="" ){ // поиск по рейтингу
  myModel->setFilter("  рейтинг = '"+rait+"' ");
}

if(name_film=="" && year!="" && rait =="" ){ // поиск по году
  myModel->setFilter("  год = '"+year+"'  ");
}

if(name_film!="" && year=="" && rait =="" ){ // поиск по названию
  myModel->setFilter(" название = '"+name_film+"'");
}


myModel->select();

}

void widget_window::slot_reset_filter() // слот сброса полей поиска
{

    filter->line_edit_film->clear();
    filter->line_edit_year->clear();
    filter->line_edit_rait->clear();
    myModel->setTable("films");
    myModel->select();
    myModel->removeColumn(4);

}

void widget_window::slot_show_info()
{
    show_info();
}
