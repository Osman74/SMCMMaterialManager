#ifndef MyTableView_H
#define MyTableView_H
#include <QTableView>
#include <QDebug>
#include <QDrag>
#include <QDragEnterEvent>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>
#include <QString>
#include <QPoint>
#include <QApplication>
#include "QTreeView"
#include "src/SMCMMaterialManager/MySQLModel/mysqlmodel.h"

class MyTableView : public QTableView
{
private:
    QPoint dragStartPosition;
    QSqlDatabase* dbMaterials;
    QSqlDatabase* dbTask;
    QTreeView* Tree;
    MyTableView* Materials;
    MyTableView* Model;
    MyTableView* taskMat;
    MyTableView* taskModel;

public:
    QString name;
    MyTableView(QWidget*& w);
    void setName(QString name);
    void initialize(QSqlDatabase* p_dbMaterials, QSqlDatabase* dbTask, MyTableView* p_Materials, MyTableView* p_Model,
                     MyTableView* p_TaskMat, MyTableView* p_TaskModel, QTreeView* Tree);
    QString getScheme(const QString& path);
    QString getFullPath(const QModelIndex& index);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MyTableView_H
