#include "./headers/MenuStart.h"

MenuStart::MenuStart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuStart)
{
    ui->setupUi(this);
}

MenuStart::~MenuStart()
{
    delete ui;
}

void MenuStart::on_startBtn_clicked()
{
    emit switchToNotLogin();
}

