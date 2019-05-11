#include "src/SMCMMaterialManager/SMCMMaterialManager.h"
#include <algorithm>
#include <QSize>
#include <QTimer>
#include <QTime>
SMCMMaterialManager::SMCMMaterialManager(const QString& pathToDB, QWidget *parent) :
    QMainWindow(parent)
{
    setWindowIcon(QIcon(":resources/sqldevops.png"));

    flagImport=false;
    flagSQLQuery = false;

    initTree();

    QStringList headers;
    headers << tr("Title") << tr("Description");

    materialTable = new MyTableWidget("Материалы");
    materialTable->setStyleSheet("background:#1dacd6");
    //materialTable->getButton()->setStyleSheet("background:#3fcef8");
    connect(materialTable->getView(), SIGNAL(clicked(QModelIndex)), this, SLOT(slot_SelectModel()));
    connect(materialTable->getSelectButton(), SIGNAL(clicked()), this, SLOT(slot_SelectAllMaterials()));
    materialTable->getSelectButton()->setToolTip("Показать все материалы");
    materialTable->getButton()->setToolTip("Добавить материал к ветке");
    connect(materialTable->getButton(),SIGNAL(clicked()),this,SLOT(slot_AddMaterial()));
    materials = materialTable->getView();
    materials->setModel(new QSqlQueryModel());
    materials->setAlternatingRowColors(true);
    materials->setContextMenuPolicy(Qt::CustomContextMenu);
    materials->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(materials,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_MatContextMenu(const QPoint&)));

    modelTable = new MyTableWidget("Модели");
    modelTable->setStyleSheet("background: #1dacd6");
    connect(modelTable->getButton(),SIGNAL(clicked()),this,SLOT(slot_add_model()));
    connect(modelTable->getSelectButton(), SIGNAL(clicked()), this, SLOT(slot_SelectAllModels()));
    modelTable->getSelectButton()->setToolTip("Показать все модели");
    modelTable->getButton()->setToolTip("Добавить модель");
    Model = modelTable->getView();
    Model->setAlternatingRowColors(true);
    Model->setModel(new QSqlQueryModel());
    Model->setContextMenuPolicy(Qt::CustomContextMenu);
    Model->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(Model, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_SelectProperties()));
    connect(Model,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_ModelContextMenu(const QPoint&)));

    propertiesTable = new MyTableWidget("Свойства");
    propertiesTable->getButton()->setDisabled(true);
    Properties = propertiesTable->getView();
    Properties->setModel(new QSqlQueryModel());
    Properties->setAlternatingRowColors(true);
    Properties->setContextMenuPolicy(Qt::CustomContextMenu);
    Properties->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(propertiesTable->getButton(),SIGNAL(clicked()),this,SLOT(slot_add_properties()));
    connect(propertiesTable->getSelectButton(), SIGNAL(clicked()), this, SLOT(slot_SelectAllProperties()));
    propertiesTable->getSelectButton()->setDisabled(true);
    connect(Properties,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_PropertiesContextMenu(const QPoint&)));

    taskMaterialTable = new MyTableWidget("Материалы");
    taskMaterialTable->setStyleSheet("background:#1cd3a2");
    taskMaterialTable->getSelectButton()->hide();
    taskMaterialTable->getButton()->setToolTip("Добавить материал");
    connect(taskMaterialTable->getButton(),SIGNAL(clicked()),this,SLOT(slot_local_add_mat()));

    taskMat = taskMaterialTable->getView();
    taskMat->setSelectionMode(QTableView::SelectionMode::SingleSelection);
    taskMat->setModel(new QSqlQueryModel());
    taskMat->setAlternatingRowColors(true);
    taskMat->setContextMenuPolicy(Qt::CustomContextMenu);
    taskMat->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(taskMat,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_Local_MatContextMenu(const QPoint&)));

    taskModelTable = new MyTableWidget("Модели");
    connect(taskModelTable->getButton(),SIGNAL(clicked()),this,SLOT(slot_local_add_model()));
    connect(taskModelTable->getSelectButton(), SIGNAL(clicked()), this, SLOT(slot_SelectAlltaskModels()));
    taskModelTable->getSelectButton()->setToolTip("Показать все модели");
    taskModelTable->getButton()->setToolTip("Добавить модель");
    taskModelTable->setStyleSheet("background:#1cd3a2");
    taskModel = taskModelTable->getView();
    taskModel->setModel(new QSqlQueryModel());
    taskModel->setAlternatingRowColors(true);
    taskModel->setContextMenuPolicy(Qt::CustomContextMenu);
    taskModel->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(taskModel,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_Local_ModelContextMenu(const QPoint&)));

    initBody();

    initMenu();

    initdbTask(pathToDB);

    dbMaterials = QSqlDatabase::addDatabase("QPSQL");
    insertForm = new cls_insert_form();
    insertForm->dbMaterials = &dbMaterials;
    insertForm->dbTask = &dbTask;

    materials->verticalHeader()->setDefaultSectionSize(28);
    Model->verticalHeader()->setDefaultSectionSize(28);
    Properties->verticalHeader()->setDefaultSectionSize(28);
    taskMat->verticalHeader()->setDefaultSectionSize(28);
    taskModel->verticalHeader()->setDefaultSectionSize(28);

    connect(this,SIGNAL(needUpdateTableView()),this,SLOT(slot_UpdateTableView()));
    connect(insertForm,SIGNAL(needUpdateTableView()),this,SLOT(slot_UpdateTableView()));

    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(taskMat->model());
    QString str ="SELECT id, description  FROM materials;";
    model->setQuery(str, dbTask);
    connect(taskMat, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_LocalSelectModel()));

    modelTable->setModel(dynamic_cast<QSqlQueryModel*>(Model->model()));

    connect(taskModel, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_LocalSelectProperties()));

    connectionForm = new ConnectionDialog(&dbMaterials);
    connectionForm->setWindowIcon(QIcon(":resources/addDB.png"));
    connect(connectionForm->get_btn_globalConnect(),SIGNAL(clicked()), this, SLOT(slot_createConnection()));

    //statusBar()->setStyleSheet("background: #0A0FFF");
    statusBar()->showMessage("Подключите БД", 10000);
    slot_createConnection();
}

void SMCMMaterialManager::initMenu(){
    QToolBar* ptb = new QToolBar("Панель инструментов");
    QMenu* pmnuConnect = new QMenu("&Подключение");
    QAction* pactConnect = new QAction ("Подключение к серверу...", nullptr) ;
    pactConnect -> setText ("&Подключение к серверу...");
    pactConnect -> setShortcut ( QKeySequence ("CTRL+O"));
    pactConnect->setIcon (QPixmap(":resources/addDB.png"));
    ptb->addAction(pactConnect);
    pmnuConnect->addAction(pactConnect);
    connect(pactConnect, SIGNAL(triggered(bool)) , this, SLOT(slot_createConnectionDialog()));
    menuBar()->addMenu(pmnuConnect);
    ptb->addSeparator();
    QMenu* pmnuTools = new QMenu("Инструменты");
    pactImport = new QAction ("Импорт", nullptr) ;
    pactImport -> setText ("&Импорт");
    pactImport -> setShortcut ( QKeySequence ("CTRL+I"));
    pactImport->setIcon (QPixmap(":resources/import.png"));
    pactImport->setEnabled(false);
    ptb->addAction(pactImport);
    pmnuTools->addAction(pactImport);
    pactExport = new QAction ("Экспорт", nullptr) ;
    pactExport -> setText ("&Экспорт");
    pactExport -> setShortcut ( QKeySequence ("CTRL+E"));
    pactExport->setIcon (QPixmap(":resources/export.png"));
    ptb->addAction(pactExport);
    pmnuTools->addAction(pactExport);

    pactAddData = new QAction ("Добавить данные", nullptr) ;
    pactAddData -> setText ("&Добавить данные");
    pactAddData -> setIcon (QIcon(":resources/addData.png"));
    ptb->addAction(pactAddData);
    pmnuTools->addAction(pactAddData);
    pactDeleteMat = new QAction ("Удалить материал", nullptr) ;
    pactDeleteMat -> setText ("&Удалить материал");
    pmnuTools->addAction(pactDeleteMat);
    pactDeleteModel = new QAction ("Удалить модель", nullptr) ;
    pactDeleteModel -> setText ("&Удалить модель");
    pmnuTools->addAction(pactDeleteModel);

    menuBar()->addMenu(pmnuTools);
    addToolBar(Qt::TopToolBarArea, ptb);
    QMenu* pmnuFAQ = new QMenu("Справка");
    pactFAQ = new QAction("О программе");

    QAction* pactHelp = new QAction("Помощь");
    pactHelp->setIcon(QIcon(":resources/FAQ.png"));

    ptb->addSeparator();
    ptb->addAction(pactHelp);
    pmnuFAQ->addAction(pactFAQ);
    pmnuFAQ->addAction(pactHelp);
    menuBar()->addMenu(pmnuFAQ);

    connect(pactHelp, SIGNAL(triggered(bool)), this, SLOT(slot_Help()));

    connect(pactImport, SIGNAL(triggered(bool)), this, SLOT(slot_Import()));
    connect(pactExport, SIGNAL(triggered(bool)), this, SLOT(slot_Export()));
    connect(pactAddData, SIGNAL(triggered(bool)), this, SLOT(slot_ShowInsertForm()));
    connect(pactDeleteMat, SIGNAL(triggered(bool)), this, SLOT(slot_DeleteMat()));
    connect(pactDeleteModel, SIGNAL(triggered(bool)), this, SLOT(slot_DeleteModel()));
    connect(pactFAQ, SIGNAL(triggered(bool)), this, SLOT(slot_About()));

    pAct_LocalAddMat = new QAction("Добавить материал");
    connect(pAct_LocalAddMat,SIGNAL(triggered()),this, SLOT(slot_local_add_mat()));

    pAct_LocalAddModel = new QAction("Добавить модель");
    connect(pAct_LocalAddModel,SIGNAL(triggered()),this, SLOT(slot_local_add_model()));

    pAct_AddMat = new QAction("Добавить материал");
    connect(pAct_AddMat,SIGNAL(triggered()),this, SLOT(slot_AddMaterial()));

    pAct_AddModel = new QAction("Добавить Модель");
    connect(pAct_AddModel,SIGNAL(triggered()),this, SLOT(slot_add_model()));

    pAct_ChangeProperty = new QAction;
    pAct_ChangeProperty->setDisabled(true);

    connect(pAct_ChangeProperty,SIGNAL(triggered()),this, SLOT(slot_ChangePropertyValue()));

    pAct_local_MandM_Correlate =new QAction("Сопоставить материал и модель");
    connect(pAct_local_MandM_Correlate,SIGNAL(triggered()),this, SLOT(slot_LocalCorrelateMaterialAndModel()));

    pAct_MandM_Correlate = new QAction("Сопоставить материал и модель");
    connect(pAct_MandM_Correlate,SIGNAL(triggered()),this, SLOT(slot_CorrelateMaterialAndModel()));

    pAct_local_MandP_Correlate = new QAction("Сопоставить модель и свойства");
    connect(pAct_local_MandP_Correlate,SIGNAL(triggered()),this, SLOT(slot_LocalCorrelateModelAndProperties()));

    pAct_MandP_Correlate = new QAction("Сопоставить модель и свойства");
    connect(pAct_MandP_Correlate,SIGNAL(triggered()),this, SLOT(slot_CorrelateModelAndProperties()));


    pAct_SetLocalPropertiesValue = new QAction("Задать значение свойству материала");
    connect(pAct_SetLocalPropertiesValue,SIGNAL(triggered()),this, SLOT(slot_SetLocalPropertiesValue()));

    pAct_SetPropertiesValue = new QAction("Задать значение свойству материала");
    connect(pAct_SetPropertiesValue,SIGNAL(triggered()),this, SLOT(slot_SetPropertiesValue()));

    pAct_LocalRemoveMat = new QAction("Удалить материал");
    connect(pAct_LocalRemoveMat,SIGNAL(triggered()),this, SLOT(slot_local_remove_mat()));

    pAct_LocalRevoveModel = new QAction("Удалить модель");
    connect(pAct_LocalRevoveModel,SIGNAL(triggered()),this, SLOT(slot_local_remove_model()));

    pAct_RemoveMat = new QAction("Удалить материал");
    connect(pAct_RemoveMat,SIGNAL(triggered()),this, SLOT(slot_remove_mat()));

    pAct_RemoveModel = new QAction("Удалить модель");
    connect(pAct_RemoveModel,SIGNAL(triggered()),this, SLOT(slot_remove_model()));

    pAct_RemoveProp = new QAction("Удалить свойство");
    connect(pAct_RemoveProp,SIGNAL(triggered()),this, SLOT(slot_remove_properties()));


}

void SMCMMaterialManager::initBody(){
    m_Layout = new QGridLayout;
    QWidget* body = new QWidget;
    body->setLayout(m_Layout);
    setCentralWidget(body);

    QWidget* glb_area = new QWidget();
    QGridLayout* glb_layout = new QGridLayout();
    QLabel* lbl_glb = new QLabel("База данных материалов");
    QFont font = lbl_glb->font();
    font.setPixelSize(18);
    lbl_glb->setFont(font);
    lbl_glb->setMargin(0);
    glb_layout->addWidget(lbl_glb,0,0,1,2,Qt::AlignHCenter);
    glb_layout->setContentsMargins(0,0,0,0);
    //glb_layout->addWidget(classificationTree,1,0);
    glb_layout->addWidget(materialTable,1,0);
    glb_layout->addWidget(modelTable,1,1);
    glb_area->setLayout(glb_layout);
    QWidget* local_area = new QWidget();
    QLabel* lbl_loc = new QLabel("Постановка задачи");
    lbl_loc->setMargin(0);
    lbl_loc->setFont(font);
    QGridLayout* local_layout = new QGridLayout();
    local_layout->setContentsMargins(0,0,0,0);
    local_layout->addWidget(lbl_loc,0,0,1,3,Qt::AlignHCenter);
    local_layout->addWidget(taskMaterialTable,1,0,1,1);
    local_layout->addWidget(taskModelTable,1,2,1,1);
    local_area->setLayout(local_layout);

    QSplitter* vSplit1 = new QSplitter(Qt::Vertical);
    vSplit1->addWidget(glb_area);
    vSplit1->addWidget(local_area);

    QWidget* prop = new QWidget();
    QVBoxLayout* lt = new QVBoxLayout();
    prop->setLayout(lt);
    QLabel* kostil = new QLabel("    ");
    kostil->setMargin(0);
    kostil->setFont(font);
    lt->addWidget(kostil);
    lt->addWidget(propertiesTable);
    lt->setContentsMargins(0,0,0,0);

    prop->setMaximumWidth(300);
    classificationTree->setMaximumWidth(300);

    m_Layout->addWidget(classificationTree,0,0,2,1);
    m_Layout->addWidget(vSplit1,0,1,1,1);
    m_Layout->addWidget(prop,0,2,1,1);

}

void SMCMMaterialManager::initTree(){
    classification = new QTreeWidget();
    classification->setAlternatingRowColors(true);
    classification->setStyleSheet("border: 1px solid lightgray;");
    QStringList lst;
    lst << "Name" << "Description";
    classification->setHeaderLabels(lst);

    classificationTree = new MyTreeWidget("Классификации");
    classificationTree->setStyleSheet("background:#1dacd6");
    Tree = classificationTree->getView();
    Tree->setAlternatingRowColors(true);
    Tree->setContextMenuPolicy(Qt::CustomContextMenu);
    Tree->setEditTriggers(QAbstractItemView::NoEditTriggers);

    pAct_tree_add_branch = new QAction("Добавить ветку");
    pAct_tree_remove_branch = new QAction("Удалить ветку");
    pAct_tree_add_classification = new QAction("Добавить классификацию");
    pAct_tree_remove_classification = new QAction("Удалить классификацию");
    pAct_tree_add_material = new QAction("Добавить материал");

    connect(Tree,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(slot_TreeContextMenu(const QPoint&)));
    connect(pAct_tree_add_classification,SIGNAL(triggered()),this,SLOT(slot_AddClassification()));
    connect(pAct_tree_remove_classification,SIGNAL(triggered()),this, SLOT(slot_RemoveClassification()));
    connect(pAct_tree_add_branch,SIGNAL(triggered()),this,SLOT(slot_AddBranch()));
    connect(pAct_tree_remove_branch,SIGNAL(triggered()),this, SLOT(slot_RemoveBranch()));
    connect(pAct_tree_add_material,SIGNAL(triggered()),this,SLOT(slot_AddMaterial()));
}

void SMCMMaterialManager::initdbTask(const QString& pathToDB){
    dbTask = QSqlDatabase::addDatabase("QSQLITE", "Local");
    dbTask.setDatabaseName(pathToDB);
    dbTask.open();

    QSqlQuery* localQuery;
    localQuery = new QSqlQuery(dbTask);
    QString str = "PRAGMA foreign_keys = on";
    if(!localQuery->exec(str)){
        //qDebug() << localQuery->lastQuery();
        //qDebug() << localQuery->lastError().text();
    }

    str = "CREATE TABLE materials(id primary key, description text);";
    if(!localQuery->exec(str)){
      //  qDebug() << localQuery->lastQuery();
        //qDebug() << localQuery->lastError().text();
    }

    str = "create table models(name text primary key, description text);";
    if(!localQuery->exec(str)){
       // qDebug() << localQuery->lastQuery();
        //qDebug() << localQuery->lastError().text();
    }

    str = "create table properties (name text primary key, description text);";
    if(!localQuery->exec(str)){
       // qDebug() << localQuery->lastQuery();
        //qDebug() << localQuery->lastError().text();
    }

    str = "create table modelComposition(models_name text references models(name) ON DELETE CASCADE, properties_name text  references properties(name));";
    if(!localQuery->exec(str)){
       // qDebug() << localQuery->lastQuery();
       // qDebug() << localQuery->lastError().text();
    }

    str = "CREATE TABLE materialsModels(materials_name text references materials(id) ON DELETE CASCADE, models_name text references models(name) ON DELETE CASCADE,  primary key(materials_name, models_name));";
    if(!localQuery->exec(str)){
        //qDebug() << localQuery->lastQuery();
        //qDebug() << localQuery->lastError().text();
    }

    str = "CREATE TABLE propertyValueScalar(materials_name text references materials(id) ON DELETE CASCADE, properties_name text, value float not null, primary key(materials_name, properties_name));";
    if(!localQuery->exec(str)){
        //qDebug() << localQuery->lastQuery();
        //qDebug() << localQuery->lastError().text();
    }
}

void SMCMMaterialManager::slot_TreeContextMenu(const QPoint& pos){
    QModelIndex index = Tree->indexAt(pos);
    if(index.isValid()){
        QString path = getFullPath(index);
        QMenu* context_menu = new QMenu;
        int len = path.split('.').length();
        if(len == 1){
            context_menu->addAction(pAct_tree_add_classification);
         }

        if(len == 2){
            context_menu->addAction(pAct_tree_add_branch);
            context_menu->addAction(pAct_tree_remove_classification);
        }

        if(len>2){
            context_menu->addAction(pAct_tree_add_branch);
            context_menu->addAction(pAct_tree_remove_branch);

        }

        if(!index.child(0,0).isValid() && len!=1){
            context_menu->addAction(pAct_tree_add_material);
        }
        context_menu->popup(Tree->mapToGlobal(pos));
    }
}

void SMCMMaterialManager::slot_MatContextMenu(const QPoint& pos){
    QModelIndex index = materials->indexAt(pos);
    if(!index.isValid() || index.column()!=0){
        return;
    }
    QMenu* context_menu = new QMenu;
    context_menu->addAction(pAct_MandM_Correlate);
    context_menu->addAction(pAct_SetPropertiesValue);
    context_menu->addAction(pAct_RemoveMat);
    context_menu->popup(materials->mapToGlobal(pos));
}

void SMCMMaterialManager::slot_ModelContextMenu(const QPoint& pos){
    QModelIndex index = Model->indexAt(pos);
    if(!index.isValid() || index.column()!=0){
        return;
    }

    QMenu* context_menu = new QMenu;
    context_menu->addAction(pAct_MandP_Correlate);
    context_menu->addAction(pAct_RemoveModel);
    context_menu->popup(Model->mapToGlobal(pos));
}

void SMCMMaterialManager::slot_PropertiesContextMenu(const QPoint& pos){
    QModelIndex index = Properties->indexAt(pos);
    if(!index.isValid() || index.column()!=0){
        return;
    }
    QMenu* context_menu = new QMenu;
    if(properiesIsGlobal){
        pAct_ChangeProperty->setText("Изменить свойство в глобальной БД");
        pAct_RemoveProp->setText("Удалить свойство из глобальной БД");
    }
    else{
        pAct_ChangeProperty->setText("Изменить свойство в локальной БД");
        pAct_RemoveProp->setText("Удалить свойство из локальной БД");
    }
    context_menu->addAction(pAct_ChangeProperty);
    context_menu->addAction(pAct_RemoveProp);
    context_menu->popup(Properties->mapToGlobal(pos));
}

void SMCMMaterialManager::slot_Local_MatContextMenu(const QPoint& pos){
    QModelIndex index = taskMat->indexAt(pos);
    if(!index.isValid() || index.column()!=0){
        return;
    }

    QMenu* context_menu = new QMenu();
    context_menu->addAction(pAct_local_MandM_Correlate);
    context_menu->addAction(pAct_SetLocalPropertiesValue);
    context_menu->addAction(pAct_LocalRemoveMat);
    context_menu->popup(taskMat->mapToGlobal(pos));
}

void SMCMMaterialManager::slot_Local_ModelContextMenu(const QPoint& pos){
    QModelIndex index = taskModel->indexAt(pos);
    if(!index.isValid() || index.column()!=0){
        return;
    }
    QMenu* context_menu = new QMenu;
    context_menu->addAction(pAct_local_MandP_Correlate);
    context_menu->addAction(pAct_LocalRevoveModel);
    context_menu->popup(taskModel->mapToGlobal(pos));
}



/*
!!!
TODO
!!!
*/
void SMCMMaterialManager::slot_local_remove_model(){
    QSqlQuery* Query;
    Query = new QSqlQuery(dbTask);
    QString str;
    QString nameModel =taskModel->model()->data(taskModel->model()->index(taskModel->currentIndex().row(), 0)).toString();
    str= "DELETE FROM materialsModels WHERE materials_name  = '" + nameMaterial + "' AND models_name = '" + nameModel + "';";
    if(!Query->exec(str)){
        qDebug() << Query->lastQuery();
        qDebug() << Query->lastError().text();
    }
    dynamic_cast<QSqlQueryModel*>(taskModel->model())->setQuery("SELECT models_name, description FROM materialsModels LEFT JOIN models ON materialsModels.models_name = models.name WHERE  materials_name ='"+ nameMaterial +"';",dbTask);
    qDebug()<<"slot_local_remove_model";
}

void SMCMMaterialManager::slot_local_remove_mat(){
    QSqlQuery* Query;
    Query = new QSqlQuery(dbTask);
    QString str;
    QString nameMaterial =taskMat->model()->data(taskMat->model()->index(taskMat->currentIndex().row(), 0)).toString();
    str= "DELETE FROM materials WHERE id  = '" + nameMaterial + "';";
    if(!Query->exec(str)){
        qDebug() << Query->lastQuery();
        qDebug() << Query->lastError().text();
    }
    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(taskMat->model());
    model->setQuery("SELECT id, description FROM materials;",dbTask);
    qDebug()<<"slot_local_remove_mat";
}

void SMCMMaterialManager::slot_remove_properties(){
    if(properiesIsGlobal){
        QSqlQuery* Query;
        Query = new QSqlQuery(dbMaterials);
        QString str;
        QString nameMaterial = materials->model()->data(materials->model()->index(materials->currentIndex().row(), 0)).toString();
        QString nameModel = Model->model()->data(Model->model()->index(Model->currentIndex().row(), 0)).toString();
        QString namePropertie =Properties->model()->data(Properties->model()->index(Properties->currentIndex().row(), 0)).toString();
        str= "DELETE FROM propertyValueScalar WHERE properties_name  = '" + namePropertie + "';";
        if(!Query->exec(str)){
            qDebug() << Query->lastQuery();
            qDebug() << Query->lastError().text();
        }
        QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(Properties->model());
        model->setQuery("select  DISTINCT properties_name as property, value from  (select materials_name, models_name , propertyValueScalar.properties_name, value from  propertyValueScalar join modelComposition  on propertyValueScalar.properties_name = modelComposition.properties_name )  as allProp  join materialsModels on  allProp.materials_name = materialsModels.materials_name and allProp.models_name = materialsModels.models_name where materialsModels.models_name = '" + nameModel + "' and materialsModels.materials_name = '" + nameMaterial +"';",dbMaterials);
        qDebug()<<"slot_local_remove_propertir";
    }
    else{
        QSqlQuery* Query;
        Query = new QSqlQuery(dbTask);
        QString str;
        QString nameMaterial = taskMat->model()->data(taskMat->model()->index(taskMat->currentIndex().row(), 0)).toString();
        QString nameModel = taskModel->model()->data(taskModel->model()->index(taskModel->currentIndex().row(), 0)).toString();
        QString namePropertie =Properties->model()->data(Properties->model()->index(Properties->currentIndex().row(), 0)).toString();
        str= "DELETE FROM propertyValueScalar WHERE properties_name  = '" + namePropertie + "';";
        if(!Query->exec(str)){
            qDebug() << Query->lastQuery();
            qDebug() << Query->lastError().text();
        }
        QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(Properties->model());
        model->setQuery("select  DISTINCT properties_name as property, value from  (select materials_name, models_name , propertyValueScalar.properties_name, value from  propertyValueScalar join modelComposition  on propertyValueScalar.properties_name = modelComposition.properties_name )  as allProp  join materialsModels on  allProp.materials_name = materialsModels.materials_name and allProp.models_name = materialsModels.models_name where materialsModels.models_name = '" + nameModel + "' and materialsModels.materials_name = '" + nameMaterial +"';",dbTask);
        qDebug()<<"slot_local_remove_propertir";
    }
    qDebug()<<"slot_remove_properties";
}

void SMCMMaterialManager::slot_remove_model(){
    QSqlQuery* Query;
    Query = new QSqlQuery(dbMaterials);
    QString str;
    QString nameModel =Model->model()->data(Model->model()->index(Model->currentIndex().row(), 0)).toString();
    str= "DELETE FROM materialsModels WHERE materials_name  = '" + nameMaterial + "' AND models_name = '" + nameModel + "';";
    if(!Query->exec(str)){
        qDebug() << Query->lastQuery();
        qDebug() << Query->lastError().text();
    }
    dynamic_cast<QSqlQueryModel*>(Model->model())->setQuery("SELECT models_name, description FROM materialsModels LEFT JOIN models ON materialsModels.models_name = models.name WHERE  materials_name ='"+ nameMaterial +"';",dbMaterials);
    qDebug()<<"slot_remove_model";
}

void SMCMMaterialManager::slot_remove_mat(){
    QSqlQuery* Query;
    Query = new QSqlQuery(dbMaterials);
    QString str;
    QString nameMaterial =materials->model()->data(materials->model()->index(materials->currentIndex().row(), 0)).toString();
    str= "DELETE FROM material_branch WHERE id_material  = '" + nameMaterial + "';";
    if(!Query->exec(str)){
        qDebug() << Query->lastQuery();
        qDebug() << Query->lastError().text();
    }
    QString path = getFullPath(Tree->currentIndex());
    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(materials->model());
    model->setQuery("SELECT id, description FROM material_branch RIGHT JOIN materials ON material_branch.id_material = materials.id WHERE material_branch.branch  <@ '" + path + "';",dbMaterials);
    qDebug()<<"slot_remove_mat";

}

//нужно дорабатывать
void SMCMMaterialManager::slot_LocalCorrelateMaterialAndModel(){
    QModelIndex index = taskMat->currentIndex();
    if(!index.isValid())
        return;
    CorrelateDialog dialog;
    dialog.getLabel1()->setText("Материал");
    dialog.getLabel2()->setText("Модель");
    QSqlQuery query(dbTask);
    dialog.getLabel3()->setText(index.data().toString());
    query.exec("SELECT * FROM models");
    while(query.next())
        dialog.getComboBox()->addItem(query.value(0).toString());
    dialog.resize(400,140);
    dialog.exec();
    //не была нажата кнопка сопоставить
    if(!CorrelateDialog::needCorrelate)
        return;
    QString material = CorrelateDialog::getField1();
    QString model = CorrelateDialog::getField2();
    qDebug()<<material<<model;
    query.exec("INSERT INTO materialsmodels(materials_name, models_name) VALUES ('" + material + "', '" + model + "')");
}

//нужно поправить
void SMCMMaterialManager::slot_CorrelateMaterialAndModel(){
    QModelIndex index = materials->currentIndex();
    if(!index.isValid())
        return;
    CorrelateDialog dialog;
    dialog.getLabel1()->setText("Материал");
    dialog.getLabel2()->setText("Модель");
    QSqlQuery query(dbMaterials);
    dialog.getLabel3()->setText(index.data().toString());
    query.exec("SELECT * FROM models");
    while(query.next())
        dialog.getComboBox()->addItem(query.value(0).toString());
    dialog.resize(400,140);
    dialog.exec();
    //не была нажата кнопка сопоставить
    if(!CorrelateDialog::needCorrelate)
        return;
    QString material = CorrelateDialog::getField1();
    QString model = CorrelateDialog::getField2();
    qDebug()<<material<<model;
    query.exec("INSERT INTO materialsmodels(materials_name, models_name) VALUES ('" + material + "', '" + model + "')");
}

void SMCMMaterialManager::slot_LocalCorrelateModelAndProperties(){
    qDebug()<<"local CorrelateModelAndProperties";
    QModelIndex index = taskModel->currentIndex();
    if(!index.isValid())
        return;
    CorrelateDialog dialog;
    dialog.getLabel1()->setText("Модель");
    dialog.getLabel2()->setText("Свойство");
    QSqlQuery query(dbTask);
    dialog.getLabel3()->setText(index.data().toString());
    query.exec("SELECT * FROM properties");
    while(query.next())
        dialog.getComboBox()->addItem(query.value(0).toString());
    dialog.resize(400,140);
    dialog.exec();
    //не была нажата кнопка сопоставить
    if(!CorrelateDialog::needCorrelate)
        return;
    QString model = CorrelateDialog::getField1();
    QString properties = CorrelateDialog::getField2();
    qDebug()<<model<<properties;
    if(!query.exec("INSERT INTO modelComposition(models_name, properties_name) VALUES ('" + model + "', '" + properties + "')")){
        qDebug() << "error";
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }
}

void SMCMMaterialManager::slot_CorrelateModelAndProperties(){
    qDebug()<<"global";
    QModelIndex index = Model->currentIndex();
    if(!index.isValid())
        return;
    CorrelateDialog dialog;
    dialog.getLabel1()->setText("Модель");
    dialog.getLabel2()->setText("Свойство");
    QSqlQuery query(dbMaterials);
    dialog.getLabel3()->setText(index.data().toString());
    query.exec("SELECT * FROM properties");
    while(query.next())
        dialog.getComboBox()->addItem(query.value(0).toString());
    dialog.resize(400,140);
    dialog.exec();
    //не была нажата кнопка сопоставить
    if(!CorrelateDialog::needCorrelate)
        return;
    QString model = CorrelateDialog::getField1();
    QString properties = CorrelateDialog::getField2();
    qDebug()<<model<<properties;
    if(!query.exec("INSERT INTO modelComposition(models_name, properties_name) VALUES ('" + model + "', '" + properties + "')")){
        qDebug() << "error";
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }

}

void SMCMMaterialManager::slot_SetLocalPropertiesValue(){

    qDebug()<<"local";
    QModelIndex index = taskMat->currentIndex();
    if(!index.isValid())
        return;
    PropertiesValueSetter dialog;
    QSqlQuery query(dbTask);
    dialog.getLabel()->setText(index.data().toString());
    query.exec("SELECT * FROM properties");
    while(query.next())
        dialog.getComboBox1()->addItem(query.value(0).toString());
    dialog.resize(400,140);
    dialog.exec();
    //не была нажата кнопка сопоставить
    if(!PropertiesValueSetter::needSetValue)
        return;
    QString material = PropertiesValueSetter::getField1();
    QString properties = PropertiesValueSetter::getField2();
    double value = PropertiesValueSetter::getValue();
    qDebug()<<material<<properties<<value;

    QString str = "insert into propertyValueScalar(materials_name, properties_name, value) values('"+
                                                                        material+"','"
                                                                       +properties+"',"
                                                                       +QString::number(value,'g',6)+");";

    if(!query.exec(str)){
        qDebug() << "error";
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }

}

void SMCMMaterialManager::slot_SetPropertiesValue(){
    qDebug()<<"global";
    QModelIndex index = materials->currentIndex();
    if(!index.isValid())
        return;
    PropertiesValueSetter dialog;
    QSqlQuery query(dbMaterials);
    dialog.getLabel()->setText(index.data().toString());
    query.exec("SELECT * FROM properties");
    while(query.next())
        dialog.getComboBox1()->addItem(query.value(0).toString());
    dialog.resize(400,140);
    dialog.exec();
    //не была нажата кнопка сопоставить
    if(!PropertiesValueSetter::needSetValue)
        return;
    QString material = PropertiesValueSetter::getField1();
    QString properties = PropertiesValueSetter::getField2();
    double value = PropertiesValueSetter::getValue();
    qDebug()<<material<<properties<<value;

    QString str = "insert into propertyValueScalar(materials_name, properties_name, value) values('"+
                                                                        material+"','"
                                                                       +properties+"',"
                                                                       +QString::number(value,'g',6)+");";

    if(!query.exec(str)){
        qDebug() << "error";
        qDebug() << query.lastQuery();
        qDebug() << query.lastError().text();
    }
}

void SMCMMaterialManager::slot_local_add_model(){
    Dialog inputDialog;
    inputDialog.getLabel1()->setText("Введите название модели");
    inputDialog.getLineEdit1()->setText("Model_name");
    inputDialog.resize(400,140);
    inputDialog.exec();
    if(!Dialog::needInsert){
        return;
    }

    QString modelName = Dialog::getName();
    QString description = Dialog::getDescription();
    QString str = "insert into models(name, description) values('"+ modelName +"','"
                                                                   + description+"');";
    QSqlQuery q(dbTask);
    if(!q.exec(str)){
        qDebug() <<q.lastQuery();
        qDebug() << q.lastError();
    }

    str ="SELECT name, description  FROM models;";
    dynamic_cast<QSqlQueryModel*>(taskModel->model())->setQuery(str,dbTask);
}

void SMCMMaterialManager::slot_local_add_mat(){
    Dialog inputDialog;
    inputDialog.resize(400,140);
    inputDialog.exec();
    if(!Dialog::needInsert){
        return;
    }

    QString material = Dialog::getName();
    QString description = Dialog::getDescription();
    QString str = "insert into materials(id, description) values('"+ material +"','"
                                                                   + description+"');";
    QSqlQuery q(dbTask);
    if(!q.exec(str)){
        qDebug() <<q.lastQuery();
        qDebug() << q.lastError();
    }

    str ="SELECT id, description  FROM materials;";
    dynamic_cast<QSqlQueryModel*>(taskMat->model())->setQuery(str,dbTask);
}

void SMCMMaterialManager::slot_add_properties(){
    qDebug()<<"добавление свойств";
    Dialog inputDialog;
    inputDialog.getLabel1()->setText("Введите название свойства");
    inputDialog.getLineEdit1()->setText("Properties_name");
    inputDialog.resize(400,140);
    inputDialog.exec();
    if(!Dialog::needInsert){
        return;
    }


    QString modelName = Dialog::getName();
    QString description = Dialog::getDescription();
    QString str = "insert into properties(name, description) values('"+ modelName +"','"
            + description+"');";

     if(properiesIsGlobal){
        QSqlQuery q(dbMaterials);
        if(!q.exec(str)){
            qDebug() <<q.lastQuery();
            qDebug() << q.lastError();
        }

        str ="SELECT name, description  FROM properties;";
        dynamic_cast<QSqlQueryModel*>(Properties->model())->setQuery(str,dbMaterials);
    }
     if(!properiesIsGlobal){
         QSqlQuery q(dbTask);
         if(!q.exec(str)){
             qDebug() <<q.lastQuery();
             qDebug() << q.lastError();
         }

         str ="SELECT name, description  FROM properties;";
         dynamic_cast<QSqlQueryModel*>(Properties->model())->setQuery(str,dbTask);
     }

}

void SMCMMaterialManager::slot_add_model(){
    qDebug()<<"slot add model";
    Dialog inputDialog;
    inputDialog.getLabel1()->setText("Введите название модели");
    inputDialog.getLineEdit1()->setText("Model_name");
    inputDialog.resize(400,140);
    inputDialog.exec();
    if(!Dialog::needInsert){
        return;
    }

    QString modelName = Dialog::getName();
    QString description = Dialog::getDescription();
    QString str = "insert into models(name, description) values('"+ modelName +"','"
                                                                   + description+"');";
    QSqlQuery q(dbMaterials);
    if(!q.exec(str)){
        qDebug() <<q.lastQuery();
        qDebug() << q.lastError();
    }

    str ="SELECT name, description  FROM models;";
    dynamic_cast<QSqlQueryModel*>(Model->model())->setQuery(str,dbMaterials);
}

void SMCMMaterialManager::slot_RemoveClassification(){
    if(!Tree->currentIndex().isValid())
        return;
    QString path = getFullPath(Tree->currentIndex());
    qDebug()<<"remove classifications "<< path;
    QSqlQuery q(dbMaterials);
    if(!q.exec("DELETE FROM tree WHERE path <@ '" + path + "';")){
        qDebug() << q.lastQuery();
        qDebug() << q.lastError().text();
    }
    TreeModel* model = dynamic_cast<TreeModel*>(Tree->model());
    model->addData(path.split(QString(".")), model->getRootItem());
    QStringList headers;
    headers << tr("Title") << tr("Description");
    Tree->setModel(new TreeModel(headers, dbMaterials));
    Tree->setColumnWidth(0, 250);
}

void SMCMMaterialManager::slot_RemoveBranch(){
    if(!Tree->currentIndex().isValid())
        return;
    QString path = getFullPath(Tree->currentIndex());
    //qDebug()<<"remove branch "<< path;
    QSqlQuery q(dbMaterials);
    if(!q.exec("DELETE FROM tree WHERE path <@ '" + path + "';")){
        qDebug() << q.lastQuery();
        qDebug() << q.lastError().text();
    }
    TreeModel* model = dynamic_cast<TreeModel*>(Tree->model());
    model->addData(path.split(QString(".")), model->getRootItem());
    QStringList headers;
    headers << tr("Title") << tr("Description");
    Tree->setModel(new TreeModel(headers, dbMaterials));
    Tree->setColumnWidth(0, 250);
}

void SMCMMaterialManager::slot_AddClassification(){
    if(!Tree->currentIndex().isValid())
        return;
    QString path = getFullPath(Tree->currentIndex());
    QInputDialog inputDialog;
    inputDialog.resize(400,140);
    inputDialog.setWindowTitle("Добавление классфикации");
    inputDialog.setLabelText("Введите название классификации");
    inputDialog.setTextValue("New classification");
    QFont font;
    font.setPixelSize(12);
    inputDialog.setFont(font);
    inputDialog.setTextEchoMode(QLineEdit::Normal);
    bool ok = !!inputDialog.exec();
    if(!ok)
        return;
    QString str = inputDialog.textValue();
   // qDebug()<<str;
    QSqlQuery q(dbMaterials);
    if(!q.exec("INSERT INTO schemes(scheme) VALUES ('" + str + "');")){
        qDebug()<<  q.lastQuery();
        qDebug() << q.lastError().text();
    }

    if(!q.exec("INSERT INTO tree(path) VALUES ('" + path + "." + str + "');")){
        qDebug()<<  q.lastQuery();
        qDebug() << q.lastError().text();
    }

    TreeModel* model = dynamic_cast<TreeModel*>(Tree->model());
    model->addData(str.split(QString(".")), model->getRootItem());
    QStringList headers;
    headers << tr("Title") << tr("Description");
    Tree->setModel(new TreeModel(headers, dbMaterials));
}

void SMCMMaterialManager::slot_AddBranch(){
    if(!Tree->currentIndex().isValid())
        return;
    QString path = getFullPath(Tree->currentIndex());
    //qDebug()<<"Branch  "<<getFullPath(Tree->currentIndex());
    QInputDialog inputDialog;
    inputDialog.resize(400,140);
    inputDialog.setWindowTitle("Добавление ветки");
    inputDialog.setLabelText("Введите название ветки");
    inputDialog.setTextValue("New branch");
    QFont font;
    font.setPixelSize(12);
    inputDialog.setFont(font);
    inputDialog.setTextEchoMode(QLineEdit::Normal);
    bool ok = !!inputDialog.exec();
    if(!ok)
        return;
    QString str = inputDialog.textValue();
    //qDebug()<<str;
    QSqlQuery q(dbMaterials);
    if(!q.exec("INSERT INTO tree(path) VALUES ('" + path + "." + str + "');")){
        qDebug() <<q.lastQuery();
        qDebug() << q.lastError();
    }
    TreeModel* model = dynamic_cast<TreeModel*>(Tree->model());
    model->addData(str.split(QString(".")), model->getRootItem());
    QStringList headers;
    headers << tr("Title") << tr("Description");
    Tree->setModel(new TreeModel(headers, dbMaterials));
    Tree->setColumnWidth(0, 250);
}

void SMCMMaterialManager::slot_AddMaterial(){
    QModelIndex index = Tree->currentIndex();
    if(!index.isValid()){
        statusBar()->showMessage("Выберите в дереве узел, в который можно добавлять",3000);
        return;
    }
    if(index.child(0,0).isValid()){
        statusBar()->showMessage("Выберите в дереве узел, в который можно добавлять",3000);
        return;
    }
    //qDebug()<<"Material  "<<getFullPath(Tree->currentIndex());

    Dialog inputDialog;
    inputDialog.resize(400,140);
    qDebug()<<"exec";
    inputDialog.exec();
    qDebug()<<"exec end";
    if(!Dialog::needInsert){
        qDebug()<<"dont need insert";
        return;
    }
    QString str = inputDialog.getName();
    QString descr = inputDialog.getDescription();
   // qDebug()<<"data"<<str<<descr;
    QString path = getFullPath(Tree->currentIndex());
    QSqlQuery q(dbMaterials);
    if(!q.exec("INSERT INTO materials(id,description) VALUES ('" + str + "','" + descr + "');")){
        qDebug() <<q.lastQuery();
        qDebug() << q.lastError();
    }
    //SMCVPropertiesManager
    if(!q.exec("INSERT INTO material_branch(scheme, branch, id_material) VALUES ('" + getScheme(path) + "', '" + path + "', '" + str + "');")){
        qDebug() <<q.lastQuery();
        qDebug() << q.lastError();
    }
}

void SMCMMaterialManager::slot_ChangePropertyValue(){
    qDebug()<<"Изменение свойств";

    ProperyValueChangeDialog inputDialog;
    inputDialog.adjustSize();
    inputDialog.exec();
    if(!ProperyValueChangeDialog::needUpdate)
        return;

    float val = inputDialog.getValue();
    QString str = "UPDATE " + QString::number(val);
    qDebug()<<str;

     if(properiesIsGlobal){
        QSqlQuery q(dbMaterials);
        if(!q.exec(str)){
            qDebug() <<q.lastQuery();
            qDebug() << q.lastError();
        }

        str ="SELECT name, description  FROM properties;";
        dynamic_cast<QSqlQueryModel*>(Properties->model())->setQuery(str,dbMaterials);
    }

     if(!properiesIsGlobal){
         QSqlQuery q(dbTask);
         if(!q.exec(str)){
             qDebug() <<q.lastQuery();
             qDebug() << q.lastError();
         }

         str ="SELECT name, description  FROM properties;";
         dynamic_cast<QSqlQueryModel*>(Properties->model())->setQuery(str,dbTask);
     }

}

QString SMCMMaterialManager::getFullPath(const QModelIndex& index){
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

QString SMCMMaterialManager::getScheme(const QString& path){
      QString scheme;
      QStringList l = path.split(QString("."));
      if(l.count() > 1)
        scheme = l[1];
      return scheme;
}

void SMCMMaterialManager::slot_createConnectionDialog()
{
    connectionForm->show();
}

void SMCMMaterialManager::slot_createConnection()
{
    qDebug()<<"create connection";
    QString c = connectionForm->getHost();
    dbMaterials.setDatabaseName(connectionForm->getNameDB());
    dbMaterials.setUserName(connectionForm->getUserName());
    dbMaterials.setHostName(connectionForm->getHost());
    dbMaterials.setPort(connectionForm->getPort());
    dbMaterials.setPassword(connectionForm->getPassword());
    if (!dbMaterials.open()) {
        qDebug()<<"db not open";
        QMessageBox* pmbx =
         new QMessageBox(QMessageBox::Warning,
         "Warning",
         "Ошибка открытия БД, попробуйте снова\n\n" + dbMaterials.lastError().text());
        pmbx->show();
        statusBar()->showMessage("Ошибка открытия БД", 3000);
        statusBar()->showMessage("Ошибка подключения", 3000);
     }

    QSqlQuery query(dbMaterials);
    query.exec("SELECT * FROM materialTypes;");
    QStringList lst;
    classification->clear();
    while(query.next())
    {
        QTreeWidgetItem *ptwgItem = new QTreeWidgetItem(classification);
        ptwgItem->setText(0,query.value(0).toString());
        QTreeWidgetItem *ptwgItemDir = new QTreeWidgetItem(ptwgItem);
        ptwgItemDir->setText(1, query.value(1).toString());
    }
    connect(Tree, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_SelectMat()));
    this->insertForm->dbMaterials=&dbMaterials;
    this->insertForm->dbTask=&dbTask;
    setColumnWidth();
    statusBar()->showMessage("Готово", 3000);

    QStringList headers;
    headers << tr("Title") << tr("Description");
    TreeModel *Tree_Model = new TreeModel(headers, dbMaterials);
    Tree->setModel(Tree_Model);
    Tree->setColumnWidth(0, 500);
   // qDebug() << Tree_Model->getRootItem()->data(0);
    Tree->header()->hide();

    connectionForm->close();
}

void SMCMMaterialManager::slot_SelectMat()
{
  //  qDebug()<<"slot select mat";
    QString path = getFullPath(Tree->currentIndex());
    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(materials->model());
    model->setQuery("SELECT id, description FROM material_branch RIGHT JOIN materials ON material_branch.id_material = materials.id WHERE material_branch.branch  <@ '" + path + "';");
    dynamic_cast<QSqlQueryModel*>(Model->model())->setQuery("select from nothing");
    dynamic_cast<QSqlQueryModel*>(Properties->model())->setQuery("select from nothing");
    setColumnWidth();
    pactImport->setEnabled(false);
}

void SMCMMaterialManager::slot_SelectModel()
{
    //qDebug()<<"select model";
    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(Model->model());
    nameMaterial = materials->model()->data(materials->model()->index(materials->currentIndex().row(), 0)).toString();
    QString str = "SELECT models_name, description FROM materialsModels LEFT JOIN models ON materialsModels.models_name = models.name WHERE  materials_name ='"+ nameMaterial +"';";
    dbMaterials.open();
    model->setQuery(str, dbMaterials);
    modelTable->getLabel()->setText("Модели (" + nameMaterial + ")" );
    dynamic_cast<QSqlQueryModel*>(Properties->model())->setQuery("select from nothign");
    setColumnWidth();
    pactImport->setEnabled(false);
}

void SMCMMaterialManager::slot_SelectProperties()
{
    qDebug()<<"select properties";
    QString nameModel =Model->model()->data(Model->model()->index(Model->currentIndex().row(), 0)).toString();
    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(Properties->model());
    QString str = "select  DISTINCT properties_name as property, value from  (select materials_name, models_name , propertyValueScalar.properties_name, value from  propertyValueScalar join modelComposition  on propertyValueScalar.properties_name = modelComposition.properties_name )  as allProp  join materialsModels on  allProp.materials_name = materialsModels.materials_name and allProp.models_name = materialsModels.models_name where materialsModels.models_name = '" + nameModel + "' and materialsModels.materials_name = '" + nameMaterial +"';";
    model->setQuery(str, dbMaterials);
    propertiesTable->getButton()->setDisabled(false);
    propertiesTable->getSelectButton()->setDisabled(false);
    propertiesTable->setStyleSheet("background: #1dacd6");
    propertiesTable->getLabel()->setText("Свойства (" + nameModel + ")" );
    propertiesTable->getButton()->setToolTip("Добавить свойство в глобальню таблицу");
    propertiesTable->getSelectButton()->setToolTip("Показать все глобальные свойства");
    properiesIsGlobal = true;
    pactImport->setEnabled(true);
    pAct_ChangeProperty->setDisabled(false);
    setColumnWidth();

}

void SMCMMaterialManager::slot_LocalSelectModel()
{
    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(taskModel->model());
    nameMaterial = taskMat->model()->data(taskMat->model()->index(taskMat->currentIndex().row(), 0)).toString();
    QString str = "SELECT models_name, description "
                  "FROM materialsModels LEFT JOIN models ON materialsModels.models_name = models.name WHERE  materials_name ='"+ nameMaterial +"';";
    model->setQuery(str, dbTask);
    taskModelTable->getLabel()->setText("Модели (" + nameMaterial + ")" );
    dynamic_cast<QSqlQueryModel*>(Properties->model())->setQuery("select from nothing");
    setColumnWidth();
}

void SMCMMaterialManager::slot_LocalSelectProperties()
{
    QString nameModel =taskModel->model()->data(taskModel->model()->index(taskModel->currentIndex().row(), 0)).toString();
    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(Properties->model());
    QString str = "select DISTINCT properties_name as property, value from  (select materials_name, models_name , propertyValueScalar.properties_name, value from  propertyValueScalar join modelComposition  on propertyValueScalar.properties_name = modelComposition.properties_name )  as allProp  join materialsModels on  allProp.materials_name = materialsModels.materials_name and allProp.models_name = materialsModels.models_name where materialsModels.models_name = '" + nameModel + "' and materialsModels.materials_name = '" + nameMaterial +"';";
    model->setQuery(str, dbTask);
    qDebug() << model->lastError().text();
    propertiesTable->getLabel()->setText("Свойства (" + nameModel + ")" );
    propertiesTable->getButton()->setToolTip("Добавить свойство в локальную таблицу");
    propertiesTable->getSelectButton()->setToolTip("Показать все локальные свойства");
    propertiesTable->getButton()->setDisabled(false);
    propertiesTable->getSelectButton()->setDisabled(false);
    propertiesTable->setStyleSheet("background: #1cd3a2");
    properiesIsGlobal = false;
    pAct_ChangeProperty->setDisabled(false);
    setColumnWidth();
}

void SMCMMaterialManager::slot_Import()
{
    dbMaterials.close();
    QSqlQuery* localQuery;
    QSqlQuery* globalQuery;
    if (dbMaterials.open())
        globalQuery = new QSqlQuery(dbMaterials);
    else return;
    localQuery = new QSqlQuery(dbTask);
    QString nameMaterial = materials->model()->data(materials->model()->index(materials->currentIndex().row(), 0)).toString();
    QString nameModel = Model->model()->data(Model->model()->index(Model->currentIndex().row(), 0)).toString();
    QString str;
    QSqlQuery q(dbTask);
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
    if(!globalQuery->exec("SELECT * FROM models WHERE name ='"+ nameModel  +"';")){
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

    if(!globalQuery->exec("SELECT * FROM modelComposition WHERE models_name='"+ nameModel  +"';")){
        qDebug()<<globalQuery->lastQuery();
        qDebug()<<globalQuery->lastError().text();
    }
    while(globalQuery->next())
    {
        str = "INSERT INTO modelComposition(models_name, properties_name) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "');";
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

    globalQuery->exec("SELECT * FROM propertyValueScalar WHERE materials_name = '" + nameMaterial + "';");
    while(globalQuery->next())
    {
        str = "INSERT INTO propertyValueScalar(materials_name, properties_name, value) VALUES ('" + globalQuery->value(0).toString() + "', '" + globalQuery->value(1).toString() + "', '" + globalQuery->value(2).toString() + "');";
        if(!localQuery->exec(str)){
            qDebug() << str;
            qDebug() << localQuery->lastError().text();;
        }
    }
    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(taskMat->model());
    str ="SELECT id, description  FROM materials;";
    model->setQuery(str, dbTask);
    flagImport = true;
    setColumnWidth();
    statusBar()->showMessage("Успешно", 3000);
}

void SMCMMaterialManager::slot_Export()
{
    QString nameMaterial = taskMat->model()->data(taskMat->model()->index(taskMat->currentIndex().row(), 0)).toString();
    QString nameModel = taskModel->model()->data(taskModel->model()->index(taskModel->currentIndex().row(), 0)).toString();
    QSqlQuery* globalQuery = new QSqlQuery(dbMaterials);
    QSqlQuery* localQuery = new QSqlQuery(dbTask);
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
//    localQuery->exec("SELECT * FROM materialsModels;");
//    while(localQuery->next())
//    {
//        qDebug() << localQuery->value(0).toString();
//        qDebug() << localQuery->value(1).toString();
//        str = "INSERT INTO materialsModels(materials_name, models_name) VALUES ('" + localQuery->value(0).toString() + "', '" + localQuery->value(1).toString() + "');";
//        if(!globalQuery->exec(str)){
//            qDebug()<<globalQuery->lastQuery();
//            qDebug()<<globalQuery->lastError().text();
//        }
//    }

    localQuery->exec("SELECT * FROM materialsModels WHERE models_name = '" + nameModel + "' AND materials_name = '" + nameMaterial + "';");
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
            qDebug()<<globalQuery->lastQuery();
            qDebug()<<globalQuery->lastError().text();
        }
    }
    QString path = getFullPath(Tree->currentIndex());
    localQuery->exec("SELECT * FROM materials;");
    while(localQuery->next())
    {
        str = "INSERT INTO material_branch(scheme, branch, id_material) VALUES ('" + getScheme(path) + "', '" + path + "', '" + localQuery->value(0).toString() + "');";
        if(!globalQuery->exec(str)){
            qDebug()<<globalQuery->lastQuery();
            qDebug()<<globalQuery->lastError().text();
        }
    }
    if(!globalQuery->exec(str)){
        qDebug()<<globalQuery->lastQuery();
        qDebug()<<globalQuery->lastError().text();
    }
    delete globalQuery;
    delete localQuery;
}

void SMCMMaterialManager::slot_AddLib(const QString & newLib)
{
   exportForm->close();
   QSqlQuery* globalQuery;
   if(!dbMaterials.open())
       return;
    globalQuery = new QSqlQuery(dbMaterials);
   //newLib = InputLib->toPlainText();
   QString str = "INSERT INTO material_branch(name) VALUES ('" + newLib +"');";
   if(!globalQuery->exec(str)){
       qDebug()<<globalQuery->lastQuery();
       qDebug()<<globalQuery->lastError().text();
   }
  // QSqlQueryModel* model = new QSqlQueryModel();
   //QSqlQuery* localQuery = new QSqlQuery(dbTask);

   QSqlQuery* query = new QSqlQuery(dbMaterials);
   query->exec("SELECT * FROM materialTypes;");
   classification->clear();
   while(query->next())
   {
       QTreeWidgetItem *ptwgItem = new QTreeWidgetItem(classification);
       ptwgItem->setText(0,query->value(0).toString());
       QTreeWidgetItem *ptwgItemDir = new QTreeWidgetItem(ptwgItem);
       ptwgItemDir->setText(1, query->value(1).toString());
   }

    setColumnWidth();
    statusBar()->showMessage("Успешно", 3000);
    delete globalQuery;
}

void SMCMMaterialManager::slot_UpdateTableView(){
    qDebug()<<"\nBegin update";
    if(taskMat->model())
    dynamic_cast<QSqlQueryModel*>(taskMat->model())->setQuery("SELECT id, description FROM materials;",dbTask);


    QSqlQuery query(dbMaterials);
    query.exec("SELECT * FROM materialTypes;");
    QStringList lst;
    lst << "Name" << "Description";
    classification->setHeaderLabels(lst);
    classification->clear();
    while(query.next())
    {
        QTreeWidgetItem *ptwgItem = new QTreeWidgetItem(classification);
        ptwgItem->setText(0,query.value(0).toString());
        QTreeWidgetItem *ptwgItemDir = new QTreeWidgetItem(ptwgItem);
        ptwgItemDir->setText(1, query.value(1).toString());
    }
    setColumnWidth();

}

void SMCMMaterialManager::slot_ShowInsertForm()
{
     insertForm->show();
     setEnabled(false);
     connect(insertForm, SIGNAL(closed()), this, SLOT(slot_CloseInsertForm()));
}

void SMCMMaterialManager::slot_CloseInsertForm()
{
    insertForm->close();
    setEnabled(true);
}

void SMCMMaterialManager::slot_DeleteMat()
{
    QSqlQuery* localQuery;
    localQuery = new QSqlQuery(dbTask);
    QString str;
    str= "DELETE FROM materials WHERE name = '" + nameMaterial + "';";
    if(!localQuery->exec(str)){
        qDebug() << localQuery->lastError().text();
    }
    dynamic_cast<QSqlQueryModel*>(taskMat->model())->setQuery("SELECT name, description FROM materials;",dbTask);
    dynamic_cast<QSqlQueryModel*>(taskModel->model())->setQuery("select from nothing");
    dynamic_cast<QSqlQueryModel*>(Properties->model())->setQuery("select from nothing");

    setColumnWidth();
}

void SMCMMaterialManager::slot_DeleteModel()
{
    QSqlQuery* localQuery;
    localQuery = new QSqlQuery(dbTask);
    QString str;
    QString nameModel =taskModel->model()->data(taskModel->model()->index(taskModel->currentIndex().row(), 0)).toString();
    str= "DELETE FROM materialsModels WHERE materials_name  = '" + nameMaterial + "' AND models_name = '" + nameModel + "';";
    if(!localQuery->exec(str)){
        qDebug() <<localQuery->lastQuery();
        qDebug() << localQuery->lastError().text();
    }
    dynamic_cast<QSqlQueryModel*>(taskModel->model())->setQuery("SELECT models_name, description FROM materialsModels LEFT JOIN models ON materialsModels.models_name = models.name WHERE  materials_name ='"+ nameMaterial +"';",dbTask);
    Properties->setModel(nullptr);
    setColumnWidth();
}

void SMCMMaterialManager::setColumnWidth() {
    materials->setColumnWidth(1, 220);
    Model->setColumnWidth(1,220);
    Properties->setColumnWidth(1,160);
    taskModel->setColumnWidth(1,220);
    taskMat->setColumnWidth(1,220);
}

void SMCMMaterialManager::slot_About()
{
    QMessageBox::about(this, "О программе", "Шамшидов О.\nЧепурной С. \nПетров А. \nФН11");
}

void SMCMMaterialManager::slot_Help(){
    qDebug()<<"help";
    HelpBrowser::showPage("index.html");
}

/*!!!
 * !!!
 * !!!
 * TODO
 *!!!
 * !!!
 * !!!
*/
void SMCMMaterialManager::slot_SelectAllMaterials()
{
    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(materials->model());
    model->setQuery("SELECT id, description FROM materials;");
    qDebug()<<"выбрать все материалы";
}

void SMCMMaterialManager::slot_SelectAllModels()
{
    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(Model->model());
    QString str = "SELECT name, description FROM models;";
    model->setQuery(str, dbMaterials);
    qDebug()<<"выбрать все модели";

}

void SMCMMaterialManager::slot_SelectAllProperties()
{
    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(Properties->model());
    QString str = "SELECT name, description FROM properties;";
    model->setQuery(str, dbMaterials);
    qDebug()<<"выбрать все свойства";
}

void SMCMMaterialManager::slot_SelectAllTaskModels()
{
    QSqlQueryModel* model = dynamic_cast<QSqlQueryModel*>(taskModel->model());
    QString str = "SELECT name, description FROM models;";
    model->setQuery(str, dbTask);
    qDebug()<<"выбрать все локальные модели";
}


SMCMMaterialManager::~SMCMMaterialManager()
{

    insertForm->close();
    delete connectionForm;
    delete m_Layout;
    delete classification;
    delete materials;
    delete Model;
    delete Properties;
    delete taskMat;
    delete taskModel;
    dbTask.close();
    dbMaterials.close();
    dbMaterials.removeDatabase("qt_sql_default_connection");
    dbTask.removeDatabase("qt_sql_default_connection");
    dbTask.~QSqlDatabase();
    dbMaterials.~QSqlDatabase();
}


