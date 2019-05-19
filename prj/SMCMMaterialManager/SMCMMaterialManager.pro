#-------------------------------------------------
#
# Project created by QtCreator 2018-11-27T11:51:31
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMCMMaterialManager
TEMPLATE = app

INCLUDEPATH += ../..

SOURCES += main.cpp \
    ../../src/SMCMMaterialManager/ConnectionForm/connectionform.cpp \
    ../../src/SMCMMaterialManager/Dialog/dialog.cpp \
    ../../src/SMCMMaterialManager/MyTableWidget/mytablewidget.cpp \
    ../../src/SMCMMaterialManager/MyTreeWidget/mytreewidget.cpp \
    ../../src/SMCMMaterialManager/SH_Tree/sh_tree.cpp \
    ../../src/SMCMMaterialManager/SMCMMaterialManager.cpp \
    ../../src/SMCMMaterialManager/TreeItem/treeitem.cpp \
    ../../src/SMCMMaterialManager/ExportForm/exportform.cpp \
    ../../src/SMCMMaterialManager/InsertForm/insertform.cpp \
    ../../src/SMCMMaterialManager/ConnectionDialog/connectiondialog.cpp \
    ../../src/SMCMMaterialManager/CorrelateDialog/correlatedialog.cpp \
    ../../src/SMCMMaterialManager/HelpBrowser/helpbrowser.cpp \
    ../../src/SMCMMaterialManager/PropertiesValueSetter/propertiesvaluesetter.cpp \
    ../../src/SMCMMaterialManager/PropertyValueChangeDialog/propertyvaluechangedialog.cpp \  #\
    mysqlmodel.cpp \
    mytableview.cpp
#    ui_connectiondialog.h \
#    ui_correlatedialog.h \
#    ui_dialog.h \
#    ui_mytablewidget.h \
#    ui_mytreewidget.h \
#    ui_propertiesvaluesetter.h \
#    ui_properyvaluechangedialog.h \

FORMS    += \
    ../../ui/SMCMMaterialManager/connectiondialog.ui \
    ../../ui/SMCMMaterialManager/correlatedialog.ui \
    ../../ui/SMCMMaterialManager/dialog.ui \
    ../../ui/SMCMMaterialManager/mytablewidget.ui \
    ../../ui/SMCMMaterialManager/mytreewidget.ui \
    ../../ui/SMCMMaterialManager/propertiesvaluesetter.ui \
    ../../ui/SMCMMaterialManager/properyvaluechangedialog.ui \
    ../../ui/SMCMMaterialManager/connectiondialog.ui \
    ../../ui/SMCMMaterialManager/correlatedialog.ui \
    ../../ui/SMCMMaterialManager/dialog.ui \
    ../../ui/SMCMMaterialManager/mytablewidget.ui \
    ../../ui/SMCMMaterialManager/mytreewidget.ui \
    ../../ui/SMCMMaterialManager/propertiesvaluesetter.ui \
    ../../ui/SMCMMaterialManager/properyvaluechangedialog.ui

RESOURCES += \
    ../../qrc/SMCMMaterialManager/resources.qrc

DISTFILES += \
    ../../qrc/SMCMMaterialManager/resources/Thumbs.db \
    ../../qrc/SMCMMaterialManager/resources/addData.png \
    ../../qrc/SMCMMaterialManager/resources/addDB.png \
    ../../qrc/SMCMMaterialManager/resources/ConnectDB.png \
    ../../qrc/SMCMMaterialManager/resources/export.png \
    ../../qrc/SMCMMaterialManager/resources/FAQ.png \
    ../../qrc/SMCMMaterialManager/resources/global.png \
    ../../qrc/SMCMMaterialManager/resources/global_database-512.png \
    ../../qrc/SMCMMaterialManager/resources/iconfinder_Database_65996.png \
    ../../qrc/SMCMMaterialManager/resources/iconfinder_Web_Database_66065.png \
    ../../qrc/SMCMMaterialManager/resources/import.png \
    ../../qrc/SMCMMaterialManager/resources/local.png \
    ../../qrc/SMCMMaterialManager/resources/localdb.png \
    ../../qrc/SMCMMaterialManager/resources/Plus.png \
    ../../qrc/SMCMMaterialManager/resources/SQL.png \
    ../../qrc/SMCMMaterialManager/resources/sqldevops.png

HEADERS += \
    ../../src/SMCMMaterialManager/ConnectionDialog/connectiondialog.h \
    ../../src/SMCMMaterialManager/ConnectionForm/connectionform.h \
    ../../src/SMCMMaterialManager/CorrelateDialog/correlatedialog.h \
    ../../src/SMCMMaterialManager/Dialog/dialog.h \
    ../../src/SMCMMaterialManager/ExportForm/exportform.h \
    ../../src/SMCMMaterialManager/HelpBrowser/helpbrowser.h \
    ../../src/SMCMMaterialManager/InsertForm/insertform.h \
    ../../src/SMCMMaterialManager/LibTreeItem/libtreeitem.h \
    ../../src/SMCMMaterialManager/MyTableWidget/mytablewidget.h \
    ../../src/SMCMMaterialManager/MyTreeWidget/mytreewidget.h \
    ../../src/SMCMMaterialManager/PropertiesValueSetter/propertiesvaluesetter.h \
    ../../src/SMCMMaterialManager/PropertyValueChangeDialog/propertyvaluechangedialog.h \
    ../../src/SMCMMaterialManager/SH_Tree/sh_tree.h \
    ../../src/SMCMMaterialManager/SMCMMaterialManager.h \
    ../../src/SMCMMaterialManager/TreeItem/treeitem.h \
    ../../ui/SMCMMaterialManager/ui_connectiondialog.h \
    ../../ui/SMCMMaterialManager/ui_correlatedialog.h \
    ../../ui/SMCMMaterialManager/ui_dialog.h \
    ../../ui/SMCMMaterialManager/ui_mytablewidget.h \
    ../../ui/SMCMMaterialManager/ui_mytreewidget.h \
    ../../ui/SMCMMaterialManager/ui_propertiesvaluesetter.h \
    ../../ui/SMCMMaterialManager/ui_properyvaluechangedialog.h \
    mysqlmodel.h \
    mytableview.h
