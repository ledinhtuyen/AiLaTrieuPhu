/********************************************************************************
** Form generated from reading UI file 'MenuStart.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUSTART_H
#define UI_MENUSTART_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuStart
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QPushButton *startBtn;
    QSpacerItem *verticalSpacer;
    QLabel *logo;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *guideBtn;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *creditBtn;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *quitBtn;

    void setupUi(QWidget *MenuStart)
    {
        if (MenuStart->objectName().isEmpty())
            MenuStart->setObjectName(QString::fromUtf8("MenuStart"));
        MenuStart->setEnabled(true);
        MenuStart->resize(480, 640);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MenuStart->sizePolicy().hasHeightForWidth());
        MenuStart->setSizePolicy(sizePolicy);
        MenuStart->setMinimumSize(QSize(480, 640));
        MenuStart->setMaximumSize(QSize(480, 640));
        gridLayout = new QGridLayout(MenuStart);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        startBtn = new QPushButton(MenuStart);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));
        startBtn->setMaximumSize(QSize(240, 50));
        startBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(46, 52, 54);"));
        startBtn->setLocale(QLocale(QLocale::Vietnamese, QLocale::Vietnam));

        horizontalLayout->addWidget(startBtn);


        gridLayout->addLayout(horizontalLayout, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(10, 30, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);

        logo = new QLabel(MenuStart);
        logo->setObjectName(QString::fromUtf8("logo"));
        logo->setMaximumSize(QSize(320, 320));
        logo->setPixmap(QPixmap(QString::fromUtf8(":/ALTP_LOGO_2021.png")));
        logo->setScaledContents(true);

        gridLayout->addWidget(logo, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        guideBtn = new QPushButton(MenuStart);
        guideBtn->setObjectName(QString::fromUtf8("guideBtn"));
        guideBtn->setMaximumSize(QSize(240, 50));
        guideBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(46, 52, 54);"));
        guideBtn->setLocale(QLocale(QLocale::Vietnamese, QLocale::Vietnam));

        horizontalLayout_4->addWidget(guideBtn);


        gridLayout->addLayout(horizontalLayout_4, 4, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        creditBtn = new QPushButton(MenuStart);
        creditBtn->setObjectName(QString::fromUtf8("creditBtn"));
        creditBtn->setMaximumSize(QSize(240, 50));
        creditBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(46, 52, 54);"));
        creditBtn->setLocale(QLocale(QLocale::Vietnamese, QLocale::Vietnam));

        horizontalLayout_5->addWidget(creditBtn);


        gridLayout->addLayout(horizontalLayout_5, 5, 1, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        quitBtn = new QPushButton(MenuStart);
        quitBtn->setObjectName(QString::fromUtf8("quitBtn"));
        quitBtn->setMaximumSize(QSize(240, 50));
        quitBtn->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(46, 52, 54);"));
        quitBtn->setLocale(QLocale(QLocale::Vietnamese, QLocale::Vietnam));

        horizontalLayout_6->addWidget(quitBtn);


        gridLayout->addLayout(horizontalLayout_6, 6, 1, 1, 1);


        retranslateUi(MenuStart);

        QMetaObject::connectSlotsByName(MenuStart);
    } // setupUi

    void retranslateUi(QWidget *MenuStart)
    {
        MenuStart->setWindowTitle(QApplication::translate("MenuStart", "AiLaTrieuPhu - Menu Start", nullptr));
        startBtn->setText(QApplication::translate("MenuStart", "B\341\272\257t \304\221\341\272\247u", nullptr));
        logo->setText(QString());
        guideBtn->setText(QApplication::translate("MenuStart", "C\303\241ch ch\306\241i", nullptr));
        creditBtn->setText(QApplication::translate("MenuStart", "T\303\241c gi\341\272\243", nullptr));
        quitBtn->setText(QApplication::translate("MenuStart", "Tho\303\241t", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuStart: public Ui_MenuStart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUSTART_H
