#include "mytreeview.h"

MyTreeView::MyTreeView(QWidget*& w) : QTreeView(w)
{
}

void MyTreeView::mousePressEvent(QMouseEvent *event)
 {
    dragStartPosition = event->pos();
    QTreeView::mousePressEvent(event);
    qDebug() << "mousePressEvent";
 }
void MyTreeView::mouseMoveEvent(QMouseEvent *event)
 {
    QByteArray* bute= new QByteArray;
    if(( event->buttons() & Qt::RightButton) &&
                QApplication::startDragDistance() <= ( event->pos() - dragStartPosition ).manhattanLength())
    {
            dragStartPosition = event->pos();
            QDrag* drag = new QDrag(this);
            QMimeData* mimeData = new QMimeData;
            mimeData->setData(QString("application/x-qabstractitemmodeldatalist"),*bute ) ;
            drag->setMimeData(mimeData);
            Qt::DropAction result = drag->exec(Qt::CopyAction);
            qDebug() << "Drop action result: " << result;
            QTreeView::mouseMoveEvent(event);
            qDebug() << "mouseMoveEvent";
    }
 }

void MyTreeView::dragEnterEvent(QDragEnterEvent *event)
{
    QStringList formats = event->mimeData()->formats();
        qDebug() << "formats: " << formats;
        if(true) {
            event->acceptProposedAction();
            //setnameDragTable(name);
        }
    qDebug() << "dragEnterEvent" << event->mimeData()->text();
}

QString MyTreeView::getFullPath(const QModelIndex& index)
{
      QStringList res;
      QStringList lst = index.data().toStringList();
      for(auto a:lst){
        res+=a;
      }

      QModelIndex p_id = index;
      while(p_id.parent().isValid()){
          p_id = p_id.parent();
          lst = p_id.data().toStringList();
          for(auto a:lst){
                 res += a;
          }
      }

      QString path;
      for(int i = res.length()-1; i!=0; i--){
            path += res[i] + ".";
      }

      path += res[0];
      return path;
}

QString MyTreeView::getScheme(const QString& path){
      QString scheme;
      QStringList l = path.split(QString("."));
      if(l.count() > 1)
        scheme = l[1];
      return scheme;
}

void MyTreeView::dropEvent(QDropEvent *event)
 {
    if(!currentIndex().isValid())
        return;
    event->acceptProposedAction();
    if(event->mimeData()->text() == "Materials")
    {

    }
    QString path = getFullPath(currentIndex());
    QStringList l = path.split(QString("."));
    QString nameBranch = l.last();
    qDebug() << "dropEvent" << nameBranch;
    QSqlQuery* localQuery;
    QSqlQuery* globalQuery;
    globalQuery = new QSqlQuery(*dbMaterials);
    localQuery = new QSqlQuery(*dbTask);
    QModelIndex indexMat;
    QModelIndexList itemsMat = Materials->selectionModel()->selectedIndexes();

    QString str;
    foreach (indexMat, itemsMat) {
        QString nameMaterial = Materials->model()->data(indexMat).toString();
        qDebug() << nameMaterial;
        str = "INSERT INTO material_branch(scheme, branch, id_material) VALUES ('" + getScheme(path) + "', '" + path + "', '" + nameMaterial + "');";
        if(!globalQuery->exec(str)){
            qDebug() << str;
            qDebug() << localQuery->lastError().text();
        }
    }
 }

void MyTreeView::initialize(QSqlDatabase* p_dbMaterials, QSqlDatabase* p_dbTask,MyTableView* p_Materials)
{
    dbMaterials = p_dbMaterials;
    dbTask = p_dbTask;
    Materials = p_Materials;
}
