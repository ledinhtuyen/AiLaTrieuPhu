#define MENUSTART_H

#include "./ui_MenuStart.h"

class MenuStart : public QWidget
{
    Q_OBJECT
  
public:
    explicit MenuStart(QWidget *parent = 0);
    ~MenuStart();

private slots:
    void on_startBtn_clicked();

private:
    Ui::MenuStart *ui;

signals:
    void switchToNotLogin();
};