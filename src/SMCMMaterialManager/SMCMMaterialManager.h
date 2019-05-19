#ifndef SMCMMaterialManager_H
#define SMCMMaterialManager_H

#include <QtGui>
#include <QtWidgets>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QCommonStyle>
#include <QListWidget>
#include <QTableView>
#include <QSqlQuery>
#include <QTreeWidget>
#include <QCommandLinkButton>
#include <QSqlTableModel>
#include <QTreeWidgetItem>
#include<QList>
#include <QSqlDriver>
#include <QStringListModel>
#include "src/SMCMMaterialManager/ConnectionForm/connectionform.h"
#include "src/SMCMMaterialManager/InsertForm/insertform.h"
#include "src/SMCMMaterialManager/ExportForm/exportform.h"
#include "src/SMCMMaterialManager/SH_Tree/sh_tree.h"
#include "src/SMCMMaterialManager/Dialog/dialog.h"
#include "src/SMCMMaterialManager/MyTableWidget/mytablewidget.h"
#include "src/SMCMMaterialManager/MyTreeWidget/mytreewidget.h"
#include "src/SMCMMaterialManager/CorrelateDialog/correlatedialog.h"
#include "src/SMCMMaterialManager/PropertiesValueSetter/propertiesvaluesetter.h"
#include "src/SMCMMaterialManager/ConnectionDialog/connectiondialog.h"
#include "src/SMCMMaterialManager/HelpBrowser/helpbrowser.h"
#include "src/SMCMMaterialManager/PropertyValueChangeDialog/propertyvaluechangedialog.h"
#include "mytableview.h"

class SMCMMaterialManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit SMCMMaterialManager(const QString& pathToDB,QWidget *parent = nullptr);
    ~SMCMMaterialManager();


private:
    QString nameMaterial;

    bool properiesIsGlobal;

    ConnectionDialog* connectionForm;
    cls_insert_form* insertForm;
    cls_export_form* exportForm;

    QGridLayout* m_Layout;
    QSqlDatabase dbMaterials;
    QSqlDatabase dbTask;

    QTreeView* Tree;
    QTreeWidget* classification;
    MyTableView* materials;
    MyTableView* Model;
    MyTableView* Properties;
    MyTableView* taskMat;
    MyTableView* taskModel;

    MyTableWidget* materialTable;
    MyTableWidget* modelTable;
    MyTableWidget* propertiesTable;
    MyTableWidget* taskMaterialTable;
    MyTableWidget* taskModelTable;
    MyTreeWidget* classificationTree;

    //QAtion которые в верхнем меню
    QAction* pactImport;
    QAction* pactExport;
    QAction* pactAddData;
    QAction* pactDeleteMat;
    QAction* pactDeleteModel;
    QAction* pactSQLQuery;
    QAction* pactFAQ;

    //QActioin которыые используются в дереве
    QAction* pAct_tree_add_branch;
    QAction* pAct_tree_remove_branch;
    QAction* pAct_tree_add_classification;
    QAction* pAct_tree_remove_classification;
    QAction* pAct_tree_add_material;

    QAction* pAct_LocalAddMat;
    QAction* pAct_LocalAddModel;
    QAction* pAct_AddMat;
    QAction* pAct_AddModel;
    QAction* pAct_ChangeProperty;

    QAction* pAct_LocalRemoveMat;
    QAction* pAct_LocalRevoveModel;
    QAction* pAct_RemoveMat;
    QAction* pAct_RemoveModel;
    QAction* pAct_RemoveProp;

    //M and M = Material and model
    QAction* pAct_local_MandM_Correlate;
    QAction* pAct_MandM_Correlate;
    //M and P = model and properties
    QAction* pAct_local_MandP_Correlate;
    QAction* pAct_MandP_Correlate;

    QAction* pAct_SetLocalPropertiesValue;
    QAction* pAct_SetPropertiesValue;

    QString newLib;
    QTextEdit* InputLib;

    void setColumnWidth();
    QString getFullPath(const QModelIndex& index);
    QString getScheme(const QString& path);
    void initTree();
    void initdbTask(const QString& pathToDB);
    void initBody();
    void initMenu();
public slots:

    void slot_TreeContextMenu(const QPoint&);
    void slot_MatContextMenu(const QPoint&);
    void slot_ModelContextMenu(const QPoint&);
    void slot_PropertiesContextMenu(const QPoint&);

    void slot_Local_MatContextMenu(const QPoint&);
    void slot_Local_ModelContextMenu(const QPoint&);

    //cлоты к контекстному меню дерева
    void slot_AddClassification();
    void slot_AddBranch();
    void slot_AddMaterial();
    void slot_RemoveClassification();
    void slot_RemoveBranch();

    //слоты к остальным представлениям
    void slot_local_add_model();
    void slot_local_add_mat();
    void slot_add_properties();
    void slot_add_model();

    void slot_local_remove_model();
    void slot_local_remove_mat();
    void slot_remove_properties();
    void slot_remove_model();
    void slot_remove_mat();

    void slot_ChangePropertyValue();

    void slot_createConnectionDialog();
    void slot_createConnection();


    void slot_SelectMat();
    void slot_SelectModel();
    void slot_SelectProperties();
    void slot_Import();
    void slot_Export();
    void slot_LocalSelectModel();
    void slot_LocalSelectProperties();

    void slot_AddLib(const QString &);

    void slot_LocalCorrelateMaterialAndModel();
    void slot_CorrelateMaterialAndModel();

    void slot_LocalCorrelateModelAndProperties();
    void slot_CorrelateModelAndProperties();

    void slot_SetLocalPropertiesValue();
    void slot_SetPropertiesValue();

    void slot_DeleteMat();
    void slot_DeleteModel();

    void slot_ShowInsertForm();
    void slot_CloseInsertForm();

    void slot_UpdateTableView();

    void slot_About();
    void slot_Help();

    //слоты для выборки всех элементов таблицы
    void slot_SelectAllMaterials();
    void slot_SelectAllModels();
    void slot_SelectAllProperties();
    void slot_SelectAllTaskModels();


signals:
    void needUpdateTableView();
};

#endif // SMCMMaterialManager_H
