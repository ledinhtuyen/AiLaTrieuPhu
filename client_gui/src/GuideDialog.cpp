#ifndef GUIDEDIALOG_H
#include "./headers/GuideDialog.h"
#endif // GUIDEDIALOG_H

GuideDialog::GuideDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuideDialog)
{
    ui->setupUi(this);
}

GuideDialog::~GuideDialog()
{
    delete ui;
}