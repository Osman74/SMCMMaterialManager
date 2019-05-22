#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H

#include <QtWidgets>
#include "src/SMCMMaterialManager/SH_Tree/sh_tree.h"
#include <mytreeview.h>


namespace Ui {
class MyTreeWidget;
}

class MyTreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyTreeWidget(const QString& p_tableName = "", TreeModel* p_model = nullptr, QWidget *parent = nullptr);
    ~MyTreeWidget();
    MyTreeView* getView();
    QAbstractItemModel* getModel();
    QLabel* getLabel();
    void setModel(QSqlQueryModel* p_model);
    void setText(const QString& p_text);
    QPushButton* getButton();
    void setStyleSheet(const QString& p_qss);

private:
    Ui::MyTreeWidget *ui;
};

#endif // MYTREEWIDGET_H
