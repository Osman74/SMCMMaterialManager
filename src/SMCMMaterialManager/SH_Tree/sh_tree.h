#ifndef SH_TREE_H
#define SH_TREE_H

#include <QVariant>
#include <QAbstractItemModel>
#include "src/SMCMMaterialManager/TreeItem/treeitem.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDebug>
#include <QDropEvent>
#include <QDebug>
#include <QDrag>
#include <QMimeData>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(const QStringList &headers, QSqlDatabase& db,
              QObject *parent = 0);
    ~TreeModel();
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    TreeItem* getRootItem() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    void addData(const QStringList &lines, TreeItem *parent, int i = 0);

    Qt::DropActions supportedDropActions() const;
    Qt::DropActions supportedDragActions() const;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
private:
    void setupModelData(QSqlDatabase& global_db, TreeItem *parent);
    TreeItem *getItem(const QModelIndex &index) const;

    TreeItem *rootItem;
};

#endif // SH_TREE_H
