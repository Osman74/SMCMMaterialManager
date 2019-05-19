/********************************************************************************
** Form generated from reading UI file 'correlatedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CORRELATEDIALOG_H
#define UI_CORRELATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_CorrelateDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *CorrelateDialog)
    {
        if (CorrelateDialog->objectName().isEmpty())
            CorrelateDialog->setObjectName(QStringLiteral("CorrelateDialog"));
        CorrelateDialog->resize(400, 300);
        horizontalLayout = new QHBoxLayout(CorrelateDialog);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(CorrelateDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 20));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        pushButton = new QPushButton(CorrelateDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 4, 0, 1, 2);

        label_2 = new QLabel(CorrelateDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(16777215, 20));
        label_2->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        label_3 = new QLabel(CorrelateDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        comboBox_2 = new QComboBox(CorrelateDialog);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(CorrelateDialog);

        QMetaObject::connectSlotsByName(CorrelateDialog);
    } // setupUi

    void retranslateUi(QDialog *CorrelateDialog)
    {
        CorrelateDialog->setWindowTitle(QApplication::translate("CorrelateDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("CorrelateDialog", "TextLabel", nullptr));
        pushButton->setText(QApplication::translate("CorrelateDialog", "\321\201\320\276\320\277\320\276\321\201\321\202\320\260\320\262\320\270\321\202\321\214", nullptr));
        label_2->setText(QApplication::translate("CorrelateDialog", "TextLabel", nullptr));
        label_3->setText(QApplication::translate("CorrelateDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CorrelateDialog: public Ui_CorrelateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CORRELATEDIALOG_H
