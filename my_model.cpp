
#include "my_model.h"

my_model::my_model()
{

}
Qt::ItemFlags my_model::flags ( const QModelIndex & index ) const
{
   if (index.column() == 3) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
   else return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
