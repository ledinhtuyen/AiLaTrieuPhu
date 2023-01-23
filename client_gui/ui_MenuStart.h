/********************************************************************************
** Form generated from reading UI file 'MenuStart.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUSTART_H
#define UI_MENUSTART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuStart
{
public:
    QGridLayout *gridLayout;
    QPushButton *startBtn;

    void setupUi(QWidget *MenuStart)
    {
        if (MenuStart->objectName().isEmpty())
            MenuStart->setObjectName(QString::fromUtf8("MenuStart"));
        MenuStart->resize(640, 480);
        gridLayout = new QGridLayout(MenuStart);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        startBtn = new QPushButton(MenuStart);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));

        gridLayout->addWidget(startBtn, 0, 0, 1, 1);


        retranslateUi(MenuStart);

        QMetaObject::connectSlotsByName(MenuStart);
    } // setupUi

    void retranslateUi(QWidget *MenuStart)
    {
        MenuStart->setWindowTitle(QApplication::translate("MenuStart", "AiLaTrieuPhu - Menu Start", nullptr));
        startBtn->setText(QApplication::translate("MenuStart", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuStart: public Ui_MenuStart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUSTART_H
