#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H
#include <QTreeView>
#include "mytableview.h"
#include <QtSql/QSqlDatabase>


class MyTreeView : public QTreeView
{
    QPoint dragStartPosition;
    QSqlDatabase* dbMaterials;
    QSqlDatabase* dbTask;
    MyTableView* Materials;
public:
    MyTreeView(QWidget*& w);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QString getFullPath(const QModelIndex& index);
    void initialize(QSqlDatabase* p_dbMaterials, QSqlDatabase* p_dbTask, MyTableView* p_Materials);
    QString getScheme(const QString& path);
};

#endif // MYTREEVIEW_H
