/********************************************************************************
** Form generated from reading UI file 'properyvaluechangedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERYVALUECHANGEDIALOG_H
#define UI_PROPERYVALUECHANGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ProperyValueChangeDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *pushButton;

    void setupUi(QDialog *ProperyValueChangeDialog)
    {
        if (ProperyValueChangeDialog->objectName().isEmpty())
            ProperyValueChangeDialog->setObjectName(QStringLiteral("ProperyValueChangeDialog"));
        ProperyValueChangeDialog->resize(400, 93);
        horizontalLayout = new QHBoxLayout(ProperyValueChangeDialog);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(ProperyValueChangeDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 80));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        doubleSpinBox = new QDoubleSpinBox(ProperyValueChangeDialog);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        verticalLayout->addWidget(doubleSpinBox);

        pushButton = new QPushButton(ProperyValueChangeDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(ProperyValueChangeDialog);

        QMetaObject::connectSlotsByName(ProperyValueChangeDialog);
    } // setupUi

    void retranslateUi(QDialog *ProperyValueChangeDialog)
    {
        ProperyValueChangeDialog->setWindowTitle(QApplication::translate("ProperyValueChangeDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("ProperyValueChangeDialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\262\320\276\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265 \321\201\320\262\320\276\320\271\321\201\321\202\320\262\320\260", nullptr));
        pushButton->setText(QApplication::translate("ProperyValueChangeDialog", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProperyValueChangeDialog: public Ui_ProperyValueChangeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERYVALUECHANGEDIALOG_H
