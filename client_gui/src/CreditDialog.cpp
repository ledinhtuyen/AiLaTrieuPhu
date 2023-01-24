#ifndef CREDDIALOG_H
#include "./headers/CreditDialog.h"
#endif // CREDDIALOG_H

CreditDialog::CreditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditDialog)
{
    ui->setupUi(this);
}

CreditDialog::~CreditDialog()
{
    delete ui;
}