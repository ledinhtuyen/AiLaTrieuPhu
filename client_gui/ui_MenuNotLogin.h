/********************************************************************************
** Form generated from reading UI file 'MenuNotLogin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUNOTLOGIN_H
#define UI_MENUNOTLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuNotLogin
{
public:
    QGridLayout *gridLayout;
    QPushButton *backBtn;

    void setupUi(QWidget *MenuNotLogin)
    {
        if (MenuNotLogin->objectName().isEmpty())
            MenuNotLogin->setObjectName(QString::fromUtf8("MenuNotLogin"));
        MenuNotLogin->resize(640, 480);
        gridLayout = new QGridLayout(MenuNotLogin);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        backBtn = new QPushButton(MenuNotLogin);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));

        gridLayout->addWidget(backBtn, 0, 0, 1, 1);


        retranslateUi(MenuNotLogin);

        QMetaObject::connectSlotsByName(MenuNotLogin);
    } // setupUi

    void retranslateUi(QWidget *MenuNotLogin)
    {
        MenuNotLogin->setWindowTitle(QApplication::translate("MenuNotLogin", "AiLaTrieuPhu - MenuNotLogin", nullptr));
        backBtn->setText(QApplication::translate("MenuNotLogin", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuNotLogin: public Ui_MenuNotLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUNOTLOGIN_H
