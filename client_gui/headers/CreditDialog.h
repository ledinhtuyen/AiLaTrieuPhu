#define CREDITDIALOG_H
#include "./ui_CreditDialog.h"

class CreditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreditDialog(QWidget *parent = 0);
    ~CreditDialog();

private:
    Ui::CreditDialog *ui;
};