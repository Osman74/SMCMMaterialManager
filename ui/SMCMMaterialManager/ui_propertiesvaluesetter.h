/********************************************************************************
** Form generated from reading UI file 'propertiesvaluesetter.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTIESVALUESETTER_H
#define UI_PROPERTIESVALUESETTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_PropertiesValueSetter
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox;
    QComboBox *comboBox_2;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton;
    QLabel *label_4;

    void setupUi(QDialog *PropertiesValueSetter)
    {
        if (PropertiesValueSetter->objectName().isEmpty())
            PropertiesValueSetter->setObjectName(QStringLiteral("PropertiesValueSetter"));
        PropertiesValueSetter->resize(400, 300);
        horizontalLayout = new QHBoxLayout(PropertiesValueSetter);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(PropertiesValueSetter);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 2, 1, 1);

        label_3 = new QLabel(PropertiesValueSetter);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 3, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(PropertiesValueSetter);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        gridLayout->addWidget(doubleSpinBox, 2, 3, 1, 1);

        comboBox_2 = new QComboBox(PropertiesValueSetter);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 2, 2, 1, 1);

        label_2 = new QLabel(PropertiesValueSetter);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 3, 3, 1, 1);

        pushButton = new QPushButton(PropertiesValueSetter);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 4, 1, 1, 3);

        label_4 = new QLabel(PropertiesValueSetter);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 2, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(PropertiesValueSetter);

        QMetaObject::connectSlotsByName(PropertiesValueSetter);
    } // setupUi

    void retranslateUi(QDialog *PropertiesValueSetter)
    {
        PropertiesValueSetter->setWindowTitle(QApplication::translate("PropertiesValueSetter", "Dialog", nullptr));
        label->setText(QApplication::translate("PropertiesValueSetter", "\320\241\320\262\320\276\320\271\321\201\321\202\320\262\320\276", nullptr));
        label_3->setText(QApplication::translate("PropertiesValueSetter", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
        label_2->setText(QApplication::translate("PropertiesValueSetter", "\320\234\320\260\321\202\320\265\321\200\320\270\320\260\320\273", nullptr));
        pushButton->setText(QApplication::translate("PropertiesValueSetter", "\320\227\320\260\320\264\320\260\321\202\321\214 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
        label_4->setText(QApplication::translate("PropertiesValueSetter", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PropertiesValueSetter: public Ui_PropertiesValueSetter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTIESVALUESETTER_H
