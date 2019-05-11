#-------------------------------------------------
#
# Project created by QtCreator 2018-11-27T11:51:31
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMCMMaterialManager
TEMPLATE = app


SOURCES += prj/main.cpp \
    src/ConnectionForm/connectionform.cpp \
    src/Dialog/dialog.cpp \
    src/MyTableWidget/mytablewidget.cpp \
    src/MyTreeWidget/mytreewidget.cpp \
    src/SH_Tree/sh_tree.cpp \
    src/SMCMMaterialManager/SMCMMaterialManager.cpp \
    src/TreeItem/treeitem.cpp \
    src/ExportForm/exportform.cpp \
    src/InsertForm/insertform.cpp \
    src/ConnectionDialog/connectiondialog.cpp \
    src/CorrelateDialog/correlatedialog.cpp \
    src/HelpBrowser/helpbrowser.cpp \
    src/PropertiesValueSetter/propertiesvaluesetter.cpp \
    src/PropertyValueChangeDialog/propertyvaluechangedialog.cpp \
    ui_connectiondialog.h \
    ui_correlatedialog.h \
    ui_dialog.h \
    ui_mytablewidget.h \
    ui_mytreewidget.h \
    ui_propertiesvaluesetter.h \
    ui_properyvaluechangedialog.h \

FORMS    += \
    ui/connectiondialog.ui \
    ui/correlatedialog.ui \
    ui/dialog.ui \
    ui/mytablewidget.ui \
    ui/mytreewidget.ui \
    ui/propertiesvaluesetter.ui \
    ui/properyvaluechangedialog.ui \
    ui/connectiondialog.ui \
    ui/correlatedialog.ui \
    ui/dialog.ui \
    ui/mytablewidget.ui \
    ui/mytreewidget.ui \
    ui/propertiesvaluesetter.ui \
    ui/properyvaluechangedialog.ui

RESOURCES += \
    qrc/resources.qrc

DISTFILES += \
    resources/Thumbs.db \
    resources/addData.png \
    resources/addDB.png \
    resources/ConnectDB.png \
    resources/export.png \
    resources/FAQ.png \
    resources/global.png \
    resources/global_database-512.png \
    resources/iconfinder_Database_65996.png \
    resources/iconfinder_Web_Database_66065.png \
    resources/import.png \
    resources/local.png \
    resources/localdb.png \
    resources/Plus.png \
    resources/SQL.png \
    resources/sqldevops.png

HEADERS += \
    src/ConnectionDialog/connectiondialog.h \
    src/ConnectionForm/connectionform.h \
    src/CorrelateDialog/correlatedialog.h \
    src/Dialog/dialog.h \
    src/ExportForm/exportform.h \
    src/HelpBrowser/helpbrowser.h \
    src/InsertForm/insertform.h \
    src/LibTreeItem/libtreeitem.h \
    src/MyTableWidget/mytablewidget.h \
    src/MyTreeWidget/mytreewidget.h \
    src/PropertiesValueSetter/propertiesvaluesetter.h \
    src/PropertyValueChangeDialog/propertyvaluechangedialog.h \
    src/SH_Tree/sh_tree.h \
    src/SMCMMaterialManager/SMCMMaterialManager.h \
    src/TreeItem/treeitem.h \
    ui/ui_connectiondialog.h \
    ui/ui_correlatedialog.h \
    ui/ui_dialog.h \
    ui/ui_mytablewidget.h \
    ui/ui_mytreewidget.h \
    ui/ui_propertiesvaluesetter.h \
    ui/ui_properyvaluechangedialog.h
