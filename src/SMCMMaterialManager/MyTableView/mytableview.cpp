#include "MyTableView.h"

MyTableView::MyTableView(QWidget*& w) : QTableView(w)
{}

void MyTableView::setName(QString p_Name)
{
    name = p_Name;
}

void MyTableView::initialize(QSqlDatabase* p_dbMaterials, QSqlDatabase* p_dbTask, MyTableView* p_Materials, MyTableView* p_Model,
                             MyTableView* p_TaskMat, MyTableView* p_TaskModel, QTreeView* p_Tree)
{
    dbMaterials = p_dbMaterials;
    dbTask = p_dbTask;
    Materials = p_Materials;
    Model = p_Model;
    taskMat = p_TaskMat;
    taskModel = p_TaskModel;
    Tree = p_Tree;
}

QString MyTableView::getScheme(const QString& path){
      QString scheme;
      QStringList l = path.split(QString("."));
      if(l.count() > 1)
        scheme = l[1];
      return scheme;
}

QString MyTableView::getFullPath(const QModelIndex& index){
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


void MyTableView::mousePressEvent(QMouseEvent *event)
 {
    dragStartPosition = event->pos();
    QTableView::mousePressEvent(event);
    qDebug() << "mousePressEvent";
 }
QByteArray* bute= new QByteArray;
void MyTableView::mouseMoveEvent(QMouseEvent *event)
 {
    if(( event->buttons() & Qt::RightButton) &&
                QApplication::startDragDistance() <= ( event->pos() - dragStartPosition ).manhattanLength())
    {
            dragStartPosition = event->pos();
            QDrag* drag = new QDrag(this);
            QMimeData* mimeData = new QMimeData;
            mimeData->setData(QString("application/x-qabstractitemmodeldatalist"),*bute ) ;
            mimeData->setText(name);
            drag->setMimeData(mimeData);
            Qt::DropAction result = drag->exec(Qt::CopyAction);
            qDebug() << "Drop action result: " << result;

            QTableView::mouseMoveEvent(event);
            qDebug() << "mouseMoveEvent";
    }
 }

void MyTableView::dragEnterEvent(QDragEnterEvent *event)
{
    QStringList formats = event->mimeData()->formats();
        qDebug() << "formats: " << formats;
        if(true) {
            event->acceptProposedAction();
            //setnameDragTable(name);
        }
    qDebug() << "dragEnterEvent" << event->mimeData()->text();
}

void MyTableView::dropEvent(QDropEvent *event)
 {
//     textBrowser->setPlainText(event->mimeData()->text());
//     mimeTypeCombo->clear();
//     mimeTypeCombo->addItems(event->mimeData()->formats());

    event->acceptProposedAction();
    QString nameSenderTable = event->mimeData()->text();
    qDebug() << "dropEvent" << nameSenderTable;
    if((nameSenderTable == "Materials") && (name == "TaskMaterials")){
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
            globalQuery->exec("SELECT * FROM materials WHERE id ='"+ nameMaterial +"';");
            while(globalQuery->next())
            {
                str = "INSERT INTO materials(id, description) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
                if(!localQuery->exec(str)){
                    qDebug() << str;
                    qDebug() << localQuery->lastError().text();
                }
            }
                //str = "SELECT name, description FROM materialsModels RIGHT JOIN models on materialsModels.materials_name = '"+ nameMaterial +"');";
            str = "SELECT * FROM models";
            if(!globalQuery->exec(str)){
                    qDebug() << globalQuery->lastQuery();
                    qDebug() << globalQuery->lastError().text();
                }
                while(globalQuery->next())
                {
                    str = "INSERT INTO models(name, description) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
                if(!localQuery->exec(str)){
                    qDebug() << str;
                    qDebug() << localQuery->lastError().text();
                }
                }
                if(!globalQuery->exec("select properties_name from propertyValueScalar WHERE materials_name = '"+ nameMaterial +"';")){
                    qDebug()<<globalQuery->lastQuery();
                    qDebug()<<globalQuery->lastError().text();

                }
                while(globalQuery->next())
                {
                    str = "INSERT INTO properties(name) values ('" + globalQuery->value(0).toString() + "');";
                    if(!localQuery->exec(str)){
                        qDebug() << str;
                        qDebug() << localQuery->lastError().text();;
                    }
                }
                globalQuery->exec("SELECT * FROM materialsModels WHERE materials_name = '" + nameMaterial + "';");
                while(globalQuery->next())
                {
                    str = "INSERT INTO materialsModels(materials_name, models_name) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
                    if(!localQuery->exec(str)){
                        qDebug() << str;
                        qDebug() << localQuery->lastError().text();;
                    }
                }
        globalQuery->exec("SELECT * FROM propertyValueScalar WHERE materials_name = '" + nameMaterial + "';");
        while(globalQuery->next())
        {
            str = "INSERT INTO propertyValueScalar(materials_name, properties_name, value) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "', '" + globalQuery->value(2).toString() + "');";
            if(!localQuery->exec(str)){
                qDebug() << str;
                qDebug() << localQuery->lastError().text();;
            }
        }
        MySqlModel* model = dynamic_cast<MySqlModel*>(taskMat->model());
        str ="SELECT id, description  FROM materials;";
        model->setQuery(str, *dbTask);
        }
    }
    if((nameSenderTable == "TaskMaterials") && (name == "Materials")){
        QSqlQuery* localQuery;
        QSqlQuery* globalQuery;
        globalQuery = new QSqlQuery(*dbMaterials);
        localQuery = new QSqlQuery(*dbTask);
        QModelIndex index;
        QModelIndexList items = taskMat->selectionModel()->selectedIndexes();
        QString str;
        QString path = getFullPath(Tree->currentIndex());
        foreach (index, items) {
                  QString nameMaterial = taskMat->model()->data(index).toString();
                  if(!localQuery->exec("SELECT * FROM models")){
                      qDebug() << globalQuery->lastQuery();
                      qDebug() << globalQuery->lastError().text();
                  }
                  while(localQuery->next())
                  {
                      str = "INSERT INTO models(name, description) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(1).toString() + "');";
                      if(!globalQuery->exec(str)){
                          qDebug() << str;
                          qDebug() << globalQuery->lastError().text();
                      }
                  }



       // qDebug() << nameMaterial;
        localQuery->exec("SELECT * FROM materials WHERE id ='"+ nameMaterial +"';");

        while(localQuery->next())
        {
            str = "INSERT INTO materials(id, description) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(2).toString() + "');";
            if(!globalQuery->exec(str)){
                qDebug() << str;
                qDebug() << globalQuery->lastError().text();
            }
        }
        localQuery->exec("SELECT * FROM materials WHERE id ='"+ nameMaterial +"';");
            while(localQuery->next())
            {
                str = "INSERT INTO material_branch(scheme, branch, id_material) VALUES ('" + getScheme(path) + "', '" + path + "', '" + localQuery->value(0).toString() + "');";
                if(!globalQuery->exec(str)){
                     qDebug() << str;
                     qDebug() << globalQuery->lastError().text();;
                 }
             }
            if(!localQuery->exec("select  DISTINCT properties_name as property, value from  (select materials_name, models_name , propertyValueScalar.properties_name, value from  propertyValueScalar join modelComposition  on propertyValueScalar.properties_name = modelComposition.properties_name )  as allProp  join materialsModels on  allProp.materials_name = materialsModels.materials_name and allProp.models_name = materialsModels.models_name where materialsModels.materials_name = '" + nameMaterial +"';")){
                qDebug()<<localQuery->lastQuery();
                qDebug()<<localQuery->lastError().text();

            }
            while(localQuery->next())
            {
                str = "INSERT INTO properties(name) values ('" + localQuery->value(0).toString() + "');";
                if(!globalQuery->exec(str)){
                    qDebug() << str;
                    qDebug() << globalQuery->lastError().text();;
                }
            }
            localQuery->exec("SELECT * FROM materialsModels WHERE materials_name = '" + nameMaterial + "';");
            while(localQuery->next())
            {
                str = "INSERT INTO materialsModels(materials_name, models_name) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(1).toString() + "');";
                if(!globalQuery->exec(str)){
                    qDebug() << str;
                    qDebug() << globalQuery->lastError().text();;
                }
            }
        localQuery->exec("SELECT * FROM propertyValueScalar WHERE materials_name = '" + nameMaterial + "';");
        while(localQuery->next())
        {
            str = "INSERT INTO propertyValueScalar(materials_name, properties_name, value) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(1).toString() + "', '" + localQuery->value(2).toString() + "');";
            if(!globalQuery->exec(str)){
                qDebug() << str;
                qDebug() << globalQuery->lastError().text();;
            }
        }
        }
        MySqlModel* model = dynamic_cast<MySqlModel*>(Materials->model());
        str ="SELECT id, description FROM material_branch RIGHT JOIN materials ON material_branch.id_material = materials.id WHERE material_branch.branch  <@ '" + path + "';";
        model->setQuery(str, *dbMaterials);
        }
    if((nameSenderTable == "Model") && (name == "TaskModel")){
        QSqlQuery* localQuery;
        QSqlQuery* globalQuery;
        globalQuery = new QSqlQuery(*dbMaterials);
        localQuery = new QSqlQuery(*dbTask);
        QString nameMaterial = Materials->model()->data(Materials->model()->index(Materials->currentIndex().row(), 0)).toString();
        QModelIndex index;
        QModelIndexList items = Model->selectionModel()->selectedIndexes();
        QString str;
        foreach (index, items) {
                  QString nameModel = Model->model()->data(index).toString();
                  while(globalQuery->next())
                  {
                      str = "INSERT INTO models(name, description) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
                      if(!localQuery->exec(str)){
                          qDebug() << str;
                          qDebug() << localQuery->lastError().text();
                      }
                  }
                  if(!globalQuery->exec("SELECT * FROM models WHERE name ='"+ nameModel  +"';")){
                      qDebug() << globalQuery->lastQuery();
                      qDebug() << globalQuery->lastError().text();
                  }

        }
        QSqlQuery q(*dbTask);
       // qDebug() << nameMaterial;
        globalQuery->exec("SELECT * FROM materials WHERE id ='"+ nameMaterial +"';");

        while(globalQuery->next())
        {
            str = "INSERT INTO materials(id, description) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(2).toString() + "');";
            if(!localQuery->exec(str)){
                qDebug() << str;
                qDebug() << localQuery->lastError().text();
            }
        }


        foreach (index, items) {
                  QString nameModel = Model->model()->data(index).toString();
            if(!globalQuery->exec("select  DISTINCT properties_name as property, value from  (select materials_name, models_name , propertyValueScalar.properties_name, value from  propertyValueScalar join modelComposition  on propertyValueScalar.properties_name = modelComposition.properties_name )  as allProp  join materialsModels on  allProp.materials_name = materialsModels.materials_name and allProp.models_name = materialsModels.models_name where materialsModels.models_name = '" + nameModel + "' and materialsModels.materials_name = '" + nameMaterial +"';")){
                qDebug()<<globalQuery->lastQuery();
                qDebug()<<globalQuery->lastError().text();

            }
            while(globalQuery->next())
            {
                str = "INSERT INTO properties(name) values ('" + globalQuery->value(0).toString() + "');";
                if(!localQuery->exec(str)){
                    qDebug() << str;
                    qDebug() << localQuery->lastError().text();;
                }
            }
            globalQuery->exec("SELECT * FROM materialsModels WHERE models_name = '" + nameModel + "' AND materials_name = '" + nameMaterial + "';");
            while(globalQuery->next())
            {
                str = "INSERT INTO materialsModels(materials_name, models_name) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
                if(!localQuery->exec(str)){
                    qDebug() << str;
                    qDebug() << localQuery->lastError().text();;
                }
            }
        }
        globalQuery->exec("SELECT * FROM propertyValueScalar WHERE materials_name = '" + nameMaterial + "';");
        while(globalQuery->next())
        {
            str = "INSERT INTO propertyValueScalar(materials_name, properties_name, value) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "', '" + globalQuery->value(2).toString() + "');";
            if(!localQuery->exec(str)){
                qDebug() << str;
                qDebug() << localQuery->lastError().text();;
            }
        }
        MySqlModel* model = dynamic_cast<MySqlModel*>(taskMat->model());
        str ="SELECT id, description  FROM materials;";
        model->setQuery(str, *dbTask);

    }
    if((nameSenderTable == "TaskModel") && (name == "Model"))
    {
        QString nameMaterial = taskMat->model()->data(taskMat->model()->index(taskMat->currentIndex().row(), 0)).toString();
        QModelIndexList items = taskModel->selectionModel()->selectedIndexes();
        qDebug() << "Модель " << taskModel->model()->data(items[0]).toString();
        QSqlQuery* globalQuery = new QSqlQuery(*dbMaterials);
        QSqlQuery* localQuery = new QSqlQuery(*dbTask);
        QModelIndex index;
        localQuery->exec("SELECT * FROM materials WHERE id ='"+ nameMaterial +"';");
        QString str;

        while(localQuery->next())
        {
           // qDebug() << localQuery->value(0).toString();
            str = "INSERT INTO materials(id, description ) VALUES ('" + localQuery->value(0).toString() + "', '"+ localQuery->value(2).toString() +"');";
            if(!globalQuery->exec(str)){
                qDebug()<<globalQuery->lastQuery();
                qDebug()<<globalQuery->lastError().text();
            }
        }
        foreach (index, items) {
                  QString nameModel = taskModel->model()->data(index).toString();
                  localQuery->exec("SELECT * FROM models WHERE name ='"+ nameModel  +"';");
                  while(localQuery->next())
                  {
                      str = "INSERT INTO models(name, description) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(1).toString() + "');";
                      if(!globalQuery->exec(str)){
                          qDebug()<<globalQuery->lastQuery();
                          qDebug()<<globalQuery->lastError().text();
                      }
                  }


        localQuery->exec("select  DISTINCT properties_name as property, value from  (select materials_name, models_name , propertyValueScalar.properties_name, value from  propertyValueScalar join modelComposition  on propertyValueScalar.properties_name = modelComposition.properties_name )  as allProp  join materialsModels on  allProp.materials_name = materialsModels.materials_name and allProp.models_name = materialsModels.models_name where materialsModels.models_name = '" + nameModel + "' and materialsModels.materials_name = '" + nameMaterial +"';");
        while(localQuery->next())
        {
            str = "INSERT INTO properties(name) values ('" + localQuery->value(0).toString() + "');";
            if(!globalQuery->exec(str)){
                qDebug()<<globalQuery->lastQuery();
                qDebug()<<globalQuery->lastError().text();
            }
        }
            localQuery->exec("SELECT * FROM modelComposition WHERE models_name ='"+ nameModel  +"';");
            while(localQuery->next())
            {
                str = "INSERT INTO modelComposition(models_name, properties_name) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(1).toString() + "');";
                if(!globalQuery->exec(str)){
                    qDebug()<<globalQuery->lastQuery();
                    qDebug()<<globalQuery->lastError().text();
                }
            }
            localQuery->exec("SELECT * FROM materialsModels WHERE models_name = '" + nameModel + "' AND materials_name = '" + nameMaterial + "';");
            while(localQuery->next())
            {
                str = "INSERT INTO materialsModels(materials_name, models_name) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(1).toString() + "');";
                if(!globalQuery->exec(str)){
                    qDebug() << str;
                    qDebug() << globalQuery->lastError().text();;
                }
            }
        }
        localQuery->exec("SELECT * FROM propertyValueScalar WHERE materials_name = '" + nameMaterial + "';");
        while(localQuery->next())
        {
            str = "INSERT INTO propertyValueScalar(materials_name, properties_name, value) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(1).toString() + "', '" + localQuery->value(2).toString() + "');";
            if(!globalQuery->exec(str)){
                qDebug()<<globalQuery->lastQuery();
                qDebug()<<globalQuery->lastError().text();
            }
        }
        QString path = getFullPath(Tree->currentIndex());
        localQuery->exec("SELECT * FROM materials WHERE id = '"+ nameMaterial + "';");
        while(localQuery->next())
        {
            str = "INSERT INTO material_branch(scheme, branch, id_material) VALUES ('" + getScheme(path) + "', '" + path + "', '" + localQuery->value(0).toString() + "');";
            if(!globalQuery->exec(str)){
                qDebug()<<globalQuery->lastQuery();
                qDebug()<<globalQuery->lastError().text();
            }
        }
        delete globalQuery;
        delete localQuery;
    }
 }

