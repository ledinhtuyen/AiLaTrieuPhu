/********************************************************************************
** Form generated from reading UI file 'GuideDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIDEDIALOG_H
#define UI_GUIDEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GuideDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *GuideDialog)
    {
        if (GuideDialog->objectName().isEmpty())
            GuideDialog->setObjectName(QString::fromUtf8("GuideDialog"));
        GuideDialog->setWindowModality(Qt::ApplicationModal);
        GuideDialog->resize(397, 240);
        GuideDialog->setModal(true);
        gridLayout = new QGridLayout(GuideDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(GuideDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(25);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(239, 41, 41);"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_2 = new QLabel(GuideDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(15);
        label_2->setFont(font1);

        horizontalLayout_2->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(10, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        retranslateUi(GuideDialog);

        QMetaObject::connectSlotsByName(GuideDialog);
    } // setupUi

    void retranslateUi(QDialog *GuideDialog)
    {
        GuideDialog->setWindowTitle(QApplication::translate("GuideDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("GuideDialog", "Guide", nullptr));
        label_2->setText(QApplication::translate("GuideDialog", "1. Ch\341\273\215n b\341\272\257t \304\221\341\272\247u.\n"
"2. Ch\341\273\215n ch\306\241i online ho\341\272\267c ch\306\241i offline.\n"
"3. Nh\341\272\255p A, B, C, D \304\221\341\273\203 ch\341\273\215n \304\221\303\241p \303\241n \304\221\303\272ng;", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GuideDialog: public Ui_GuideDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIDEDIALOG_H
