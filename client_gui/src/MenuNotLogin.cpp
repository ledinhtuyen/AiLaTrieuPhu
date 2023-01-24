#ifndef MENUNOTLOGIN_H
#include "./headers/MenuNotLogin.h"
#endif // MENUNOTLOGIN_H

#include <QDesktopWidget>

MenuNotLogin::MenuNotLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuNotLogin)
{
    ui->setupUi(this);
    move(QApplication::desktop()->availableGeometry(this).center().x() - width() / 2, QApplication::desktop()->availableGeometry(this).center().y() - height() / 2);
}

MenuNotLogin::~MenuNotLogin()
{
    delete ui;
}

void MenuNotLogin::on_backBtn_clicked()
{
    emit switchToStart();
}