#define GUIDEDIALOG_H
#include "./ui_GuideDialog.h"

class GuideDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GuideDialog(QWidget *parent = 0);
    ~GuideDialog();

private:
    Ui::GuideDialog *ui;
};