/********************************************************************************
** Form generated from reading UI file 'mytreewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYTREEWIDGET_H
#define UI_MYTREEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyTreeWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;
    QLabel *label;
    QPushButton *pushButton;
    QTreeView *treeView;

    void setupUi(QWidget *MyTreeWidget)
    {
        if (MyTreeWidget->objectName().isEmpty())
            MyTreeWidget->setObjectName(QStringLiteral("MyTreeWidget"));
        MyTreeWidget->resize(396, 304);
        horizontalLayout = new QHBoxLayout(MyTreeWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 31, 0, 0);
        vLayout = new QVBoxLayout();
        vLayout->setSpacing(0);
        vLayout->setObjectName(QStringLiteral("vLayout"));
        hLayout = new QHBoxLayout();
        hLayout->setSpacing(0);
        hLayout->setObjectName(QStringLiteral("hLayout"));
        label = new QLabel(MyTreeWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        label->setAutoFillBackground(false);
        label->setLineWidth(37);
        label->setMidLineWidth(37);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        hLayout->addWidget(label);

        pushButton = new QPushButton(MyTreeWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(50, 16777215));
        pushButton->setAutoFillBackground(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/resources/FAQ.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setCheckable(false);
        pushButton->setAutoDefault(true);
        pushButton->setFlat(false);

        hLayout->addWidget(pushButton);


        vLayout->addLayout(hLayout);

        treeView = new QTreeView(MyTreeWidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setMidLineWidth(0);

        vLayout->addWidget(treeView);


        horizontalLayout->addLayout(vLayout);


        retranslateUi(MyTreeWidget);

        pushButton->setDefault(false);


        QMetaObject::connectSlotsByName(MyTreeWidget);
    } // setupUi

    void retranslateUi(QWidget *MyTreeWidget)
    {
        MyTreeWidget->setWindowTitle(QApplication::translate("MyTreeWidget", "Form", nullptr));
        label->setText(QApplication::translate("MyTreeWidget", "text", nullptr));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MyTreeWidget: public Ui_MyTreeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYTREEWIDGET_H
