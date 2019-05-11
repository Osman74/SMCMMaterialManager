/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *labelMaterial;
    QLineEdit *lineEditMaterial;
    QLabel *labelDescription;
    QLineEdit *lineEditDescription;
    QDialogButtonBox *buttonBox_2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(349, 216);
        horizontalLayout = new QHBoxLayout(Dialog);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelMaterial = new QLabel(Dialog);
        labelMaterial->setObjectName(QStringLiteral("labelMaterial"));
        labelMaterial->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelMaterial);

        lineEditMaterial = new QLineEdit(Dialog);
        lineEditMaterial->setObjectName(QStringLiteral("lineEditMaterial"));

        verticalLayout->addWidget(lineEditMaterial);

        labelDescription = new QLabel(Dialog);
        labelDescription->setObjectName(QStringLiteral("labelDescription"));
        labelDescription->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelDescription);

        lineEditDescription = new QLineEdit(Dialog);
        lineEditDescription->setObjectName(QStringLiteral("lineEditDescription"));
        lineEditDescription->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(lineEditDescription);

        buttonBox_2 = new QDialogButtonBox(Dialog);
        buttonBox_2->setObjectName(QStringLiteral("buttonBox_2"));
        buttonBox_2->setLayoutDirection(Qt::RightToLeft);
        buttonBox_2->setOrientation(Qt::Horizontal);
        buttonBox_2->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox_2->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        labelMaterial->setText(QApplication::translate("Dialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\274\320\260\321\202\320\265\321\200\320\270\320\260\320\273\320\260", nullptr));
        lineEditMaterial->setText(QApplication::translate("Dialog", "material_name", nullptr));
        labelDescription->setText(QApplication::translate("Dialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\276\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        lineEditDescription->setText(QApplication::translate("Dialog", "description", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
