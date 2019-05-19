/********************************************************************************
** Form generated from reading UI file 'connectiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONDIALOG_H
#define UI_CONNECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectionDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QRadioButton *rb_local;
    QRadioButton *rb_global;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QPushButton *bnt_fileExplorer;
    QLineEdit *line_path;
    QSpacerItem *verticalSpacer;
    QPushButton *btn_localConnect;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *lbl_dbName;
    QLineEdit *line_dbName;
    QLabel *lbl_userName;
    QLineEdit *line_userName;
    QLabel *lb_host;
    QLineEdit *line_host;
    QLabel *lbl_port;
    QLineEdit *line_port;
    QLabel *lbl_password;
    QLineEdit *line_password;
    QPushButton *btn_globalConnect;

    void setupUi(QDialog *ConnectionDialog)
    {
        if (ConnectionDialog->objectName().isEmpty())
            ConnectionDialog->setObjectName(QStringLiteral("ConnectionDialog"));
        ConnectionDialog->resize(301, 320);
        horizontalLayout = new QHBoxLayout(ConnectionDialog);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        rb_local = new QRadioButton(ConnectionDialog);
        rb_local->setObjectName(QStringLiteral("rb_local"));

        gridLayout->addWidget(rb_local, 0, 1, 1, 1);

        rb_global = new QRadioButton(ConnectionDialog);
        rb_global->setObjectName(QStringLiteral("rb_global"));

        gridLayout->addWidget(rb_global, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(ConnectionDialog);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        verticalLayout_4 = new QVBoxLayout(page);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label);

        bnt_fileExplorer = new QPushButton(page);
        bnt_fileExplorer->setObjectName(QStringLiteral("bnt_fileExplorer"));

        verticalLayout_3->addWidget(bnt_fileExplorer);

        line_path = new QLineEdit(page);
        line_path->setObjectName(QStringLiteral("line_path"));

        verticalLayout_3->addWidget(line_path);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        btn_localConnect = new QPushButton(page);
        btn_localConnect->setObjectName(QStringLiteral("btn_localConnect"));

        verticalLayout_3->addWidget(btn_localConnect);


        verticalLayout_4->addLayout(verticalLayout_3);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lbl_dbName = new QLabel(page_2);
        lbl_dbName->setObjectName(QStringLiteral("lbl_dbName"));
        lbl_dbName->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lbl_dbName);

        line_dbName = new QLineEdit(page_2);
        line_dbName->setObjectName(QStringLiteral("line_dbName"));

        verticalLayout->addWidget(line_dbName);

        lbl_userName = new QLabel(page_2);
        lbl_userName->setObjectName(QStringLiteral("lbl_userName"));

        verticalLayout->addWidget(lbl_userName);

        line_userName = new QLineEdit(page_2);
        line_userName->setObjectName(QStringLiteral("line_userName"));

        verticalLayout->addWidget(line_userName);

        lb_host = new QLabel(page_2);
        lb_host->setObjectName(QStringLiteral("lb_host"));
        lb_host->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lb_host);

        line_host = new QLineEdit(page_2);
        line_host->setObjectName(QStringLiteral("line_host"));

        verticalLayout->addWidget(line_host);

        lbl_port = new QLabel(page_2);
        lbl_port->setObjectName(QStringLiteral("lbl_port"));
        lbl_port->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lbl_port);

        line_port = new QLineEdit(page_2);
        line_port->setObjectName(QStringLiteral("line_port"));

        verticalLayout->addWidget(line_port);

        lbl_password = new QLabel(page_2);
        lbl_password->setObjectName(QStringLiteral("lbl_password"));
        lbl_password->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lbl_password);

        line_password = new QLineEdit(page_2);
        line_password->setObjectName(QStringLiteral("line_password"));

        verticalLayout->addWidget(line_password);

        btn_globalConnect = new QPushButton(page_2);
        btn_globalConnect->setObjectName(QStringLiteral("btn_globalConnect"));

        verticalLayout->addWidget(btn_globalConnect);


        verticalLayout_2->addLayout(verticalLayout);

        stackedWidget->addWidget(page_2);

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 2);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(ConnectionDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ConnectionDialog);
    } // setupUi

    void retranslateUi(QDialog *ConnectionDialog)
    {
        ConnectionDialog->setWindowTitle(QApplication::translate("ConnectionDialog", "Dialog", nullptr));
        rb_local->setText(QApplication::translate("ConnectionDialog", "\320\233\320\276\320\272\320\260\320\273\321\214\320\275\320\260\321\217", nullptr));
        rb_global->setText(QApplication::translate("ConnectionDialog", "\320\223\320\273\320\276\320\261\320\260\320\273\321\214\320\275\320\260\321\217", nullptr));
        label->setText(QApplication::translate("ConnectionDialog", "\320\243\320\272\320\260\320\266\320\270\321\202\320\265 \320\277\321\203\321\202\321\214 \320\272 \320\261\320\260\320\267\320\265 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        bnt_fileExplorer->setText(QApplication::translate("ConnectionDialog", "\320\236\320\261\320\267\320\276\321\200...", nullptr));
        btn_localConnect->setText(QApplication::translate("ConnectionDialog", "Connect", nullptr));
        lbl_dbName->setText(QApplication::translate("ConnectionDialog", "Database name", nullptr));
        line_dbName->setText(QApplication::translate("ConnectionDialog", "fn1132_2016", nullptr));
        lbl_userName->setText(QApplication::translate("ConnectionDialog", "User name", nullptr));
        line_userName->setText(QApplication::translate("ConnectionDialog", "student", nullptr));
        lb_host->setText(QApplication::translate("ConnectionDialog", "Host", nullptr));
        line_host->setText(QApplication::translate("ConnectionDialog", "195.19.32.74", nullptr));
        lbl_port->setText(QApplication::translate("ConnectionDialog", "Port", nullptr));
        line_port->setText(QApplication::translate("ConnectionDialog", "5432", nullptr));
        lbl_password->setText(QApplication::translate("ConnectionDialog", "Password", nullptr));
        line_password->setText(QApplication::translate("ConnectionDialog", "bmstu", nullptr));
        btn_globalConnect->setText(QApplication::translate("ConnectionDialog", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectionDialog: public Ui_ConnectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONDIALOG_H
