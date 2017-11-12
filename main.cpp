
#include <QApplication>
#include <QSql>
#include"widget_window.h"
#include"my_dialog.h"
#include"widget_show_info.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


widget_window win;
win.show();

return a.exec();
}


