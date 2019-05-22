#ifndef MyMySqlModel_H
#define MySqlModel_H
#include <QtSql/QSqlQueryModel>
#include <QStringListModel>
#include <QDropEvent>
#include <QDebug>
#include <QDrag>
#include <QMimeData>
class MySqlModel : public QSqlQueryModel
{
public:
    MySqlModel();
    MySqlModel(QSqlDatabase db);
    Qt::DropActions supportedDropActions() const;
    Qt::DropActions supportedDragActions() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

};
#endif // MySqlModel_H
