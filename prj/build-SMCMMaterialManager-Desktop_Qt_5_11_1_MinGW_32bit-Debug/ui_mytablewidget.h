/********************************************************************************
** Form generated from reading UI file 'mytablewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYTABLEWIDGET_H
#define UI_MYTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mytableview.h>

QT_BEGIN_NAMESPACE

class Ui_MyTableWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout;
    QLabel *label;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    MyTableView *tableView;

    void setupUi(QWidget *MyTableWidget)
    {
        if (MyTableWidget->objectName().isEmpty())
            MyTableWidget->setObjectName(QStringLiteral("MyTableWidget"));
        MyTableWidget->resize(458, 302);
        horizontalLayout = new QHBoxLayout(MyTableWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, -1, 0);
        vLayout = new QVBoxLayout();
        vLayout->setSpacing(0);
        vLayout->setObjectName(QStringLiteral("vLayout"));
        vLayout->setContentsMargins(-1, -1, -1, 6);
        hLayout = new QHBoxLayout();
        hLayout->setSpacing(0);
        hLayout->setObjectName(QStringLiteral("hLayout"));
        label = new QLabel(MyTableWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        label->setAutoFillBackground(false);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        hLayout->addWidget(label);

        pushButton_2 = new QPushButton(MyTableWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(9, 20));
        pushButton_2->setMaximumSize(QSize(50, 16777215));
        pushButton_2->setAutoFillBackground(true);
        pushButton_2->setAutoDefault(true);

        hLayout->addWidget(pushButton_2, 0, Qt::AlignBottom);

        pushButton = new QPushButton(MyTableWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(50, 16777215));
        pushButton->setAutoFillBackground(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/resources/Plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setCheckable(false);
        pushButton->setAutoDefault(true);
        pushButton->setFlat(false);

        hLayout->addWidget(pushButton);


        vLayout->addLayout(hLayout);

        tableView = new MyTableView(MyTableWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setEnabled(true);
        tableView->setStyleSheet(QStringLiteral(""));

        vLayout->addWidget(tableView);


        horizontalLayout->addLayout(vLayout);


        retranslateUi(MyTableWidget);

        pushButton->setDefault(false);


        QMetaObject::connectSlotsByName(MyTableWidget);
    } // setupUi

    void retranslateUi(QWidget *MyTableWidget)
    {
        MyTableWidget->setWindowTitle(QApplication::translate("MyTableWidget", "Form", nullptr));
        label->setText(QApplication::translate("MyTableWidget", "text", nullptr));
        pushButton_2->setText(QApplication::translate("MyTableWidget", "\320\222\321\201\320\265", nullptr));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MyTableWidget: public Ui_MyTableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYTABLEWIDGET_H
