#include "./headers/MenuNotLogin.h"

MenuNotLogin::MenuNotLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuNotLogin)
{
    ui->setupUi(this);
}

MenuNotLogin::~MenuNotLogin()
{
    delete ui;
}

void MenuNotLogin::on_backBtn_clicked()
{
    emit switchToStart();
}