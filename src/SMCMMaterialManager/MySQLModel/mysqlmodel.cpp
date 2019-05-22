#include "MySqlModel.h"

MySqlModel::MySqlModel()
{
   QSqlQueryModel();
}


Qt::DropActions MySqlModel::supportedDropActions() const
{
    return Qt::CopyAction;
}

Qt::DropActions MySqlModel::supportedDragActions() const{
    return Qt::CopyAction;
}

Qt::ItemFlags MySqlModel::flags(const QModelIndex &index) const
 {
     Qt::ItemFlags defaultFlags = QSqlQueryModel::flags(index);

     if (index.isValid())
         return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
     else
         return Qt::ItemIsDropEnabled | defaultFlags;
 }

bool MySqlModel::dropMimeData(const QMimeData *data,Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

//    if (!data->hasFormat("application/vnd.text.list"))
//        return false;

    if (column > 0)
        return false;
}
