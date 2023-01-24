/********************************************************************************
** Form generated from reading UI file 'CreditDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREDITDIALOG_H
#define UI_CREDITDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreditDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_11;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_12;
    QLabel *label_7;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_10;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_16;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_14;
    QLabel *label_13;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QDialog *CreditDialog)
    {
        if (CreditDialog->objectName().isEmpty())
            CreditDialog->setObjectName(QString::fromUtf8("CreditDialog"));
        CreditDialog->setWindowModality(Qt::ApplicationModal);
        CreditDialog->resize(480, 480);
        CreditDialog->setModal(true);
        gridLayout = new QGridLayout(CreditDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(CreditDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(15);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(20, 143, 119);"));

        verticalLayout->addWidget(label_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_11 = new QLabel(CreditDialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMaximumSize(QSize(70, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(13);
        font1.setBold(true);
        font1.setWeight(75);
        label_11->setFont(font1);
        label_11->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_7->addWidget(label_11);

        label_6 = new QLabel(CreditDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(32, 74, 135);"));
        label_6->setScaledContents(false);

        horizontalLayout_7->addWidget(label_6);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_12 = new QLabel(CreditDialog);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMaximumSize(QSize(70, 16777215));
        label_12->setFont(font1);

        horizontalLayout_9->addWidget(label_12);

        label_7 = new QLabel(CreditDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(32, 74, 135);"));

        horizontalLayout_9->addWidget(label_7);


        verticalLayout->addLayout(horizontalLayout_9);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_2, 2, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_4 = new QLabel(CreditDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(20, 143, 119);"));

        verticalLayout_3->addWidget(label_4);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_10 = new QLabel(CreditDialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMaximumSize(QSize(70, 16777215));
        label_10->setFont(font1);

        horizontalLayout_12->addWidget(label_10);

        label_9 = new QLabel(CreditDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font1);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(32, 74, 135);"));

        horizontalLayout_12->addWidget(label_9);


        verticalLayout_3->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_16 = new QLabel(CreditDialog);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMaximumSize(QSize(70, 16777215));
        label_16->setFont(font1);

        horizontalLayout_13->addWidget(label_16);

        label_15 = new QLabel(CreditDialog);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font1);
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(32, 74, 135);"));

        horizontalLayout_13->addWidget(label_15);


        verticalLayout_3->addLayout(horizontalLayout_13);


        horizontalLayout_4->addLayout(verticalLayout_3);


        gridLayout->addLayout(horizontalLayout_4, 5, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(CreditDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Times New Roman"));
        font2.setPointSize(24);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8("color: rgb(239, 41, 41);"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_3, 4, 0, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(CreditDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(20, 143, 119);"));

        verticalLayout_2->addWidget(label_2);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_8 = new QLabel(CreditDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMaximumSize(QSize(70, 16777215));
        label_8->setFont(font1);

        horizontalLayout_10->addWidget(label_8);

        label_3 = new QLabel(CreditDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(32, 74, 135);"));

        horizontalLayout_10->addWidget(label_3);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_14 = new QLabel(CreditDialog);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMaximumSize(QSize(70, 16777215));
        label_14->setFont(font1);

        horizontalLayout_11->addWidget(label_14);

        label_13 = new QLabel(CreditDialog);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font1);
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(32, 74, 135);"));

        horizontalLayout_11->addWidget(label_13);


        verticalLayout_2->addLayout(horizontalLayout_11);


        horizontalLayout_3->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 2);

        verticalSpacer_5 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout->addItem(verticalSpacer_5, 6, 0, 1, 2);


        retranslateUi(CreditDialog);

        QMetaObject::connectSlotsByName(CreditDialog);
    } // setupUi

    void retranslateUi(QDialog *CreditDialog)
    {
        CreditDialog->setWindowTitle(QApplication::translate("CreditDialog", "Dialog", nullptr));
        label_5->setText(QApplication::translate("CreditDialog", "1. L\303\252 \304\220\303\254nh Tuy\303\252n", nullptr));
        label_11->setText(QApplication::translate("CreditDialog", "Github:", nullptr));
        label_6->setText(QApplication::translate("CreditDialog", "https://github.com/tuyenldhust", nullptr));
        label_12->setText(QApplication::translate("CreditDialog", "Facebook:", nullptr));
        label_7->setText(QApplication::translate("CreditDialog", "https:/fb.me/le.tuyen.hust", nullptr));
        label_4->setText(QApplication::translate("CreditDialog", "3. H\303\240 V\304\203n \304\220\341\273\251c", nullptr));
        label_10->setText(QApplication::translate("CreditDialog", "Github:", nullptr));
        label_9->setText(QApplication::translate("CreditDialog", "https://github.com/VanDucKun", nullptr));
        label_16->setText(QApplication::translate("CreditDialog", "Facebook:", nullptr));
        label_15->setText(QApplication::translate("CreditDialog", "https://fb.me/100024461410153", nullptr));
        label->setText(QApplication::translate("CreditDialog", "Credit", nullptr));
        label_2->setText(QApplication::translate("CreditDialog", "2. Ph\341\272\241m Th\341\273\213 \303\201nh", nullptr));
        label_8->setText(QApplication::translate("CreditDialog", "Github:", nullptr));
        label_3->setText(QApplication::translate("CreditDialog", "https://github.com/Anhpham2802", nullptr));
        label_14->setText(QApplication::translate("CreditDialog", "Facebook:", nullptr));
        label_13->setText(QApplication::translate("CreditDialog", "https://fb.me/PhamAnh2802", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreditDialog: public Ui_CreditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREDITDIALOG_H
