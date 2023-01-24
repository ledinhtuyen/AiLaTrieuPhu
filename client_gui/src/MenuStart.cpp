#ifndef MENUSTART_H
#include "./headers/MenuStart.h"
#endif // MENUSTART_H

#include <QDesktopWidget>

MenuStart::MenuStart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuStart)
{
    ui->setupUi(this);
    move(QApplication::desktop()->availableGeometry(this).center().x() - width() / 2, QApplication::desktop()->availableGeometry(this).center().y() - height() / 2);
}

MenuStart::~MenuStart()
{
    delete ui;
}

void MenuStart::on_startBtn_clicked()
{
    emit showMenuNotLogin();
}

void MenuStart::on_guideBtn_clicked()
{
    emit showGuide();
}

void MenuStart::on_creditBtn_clicked()
{
    emit showCredit();
}

void MenuStart::on_quitBtn_clicked()
{
    emit quit();
}