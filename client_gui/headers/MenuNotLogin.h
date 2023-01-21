#ifndef MENUNOTLOGIN_H
#define MENUNOTLOGIN_H
#include "./ui_MenuNotLogin.h"

class MenuNotLogin : public QWidget
{
    Q_OBJECT
    
public:
    explicit MenuNotLogin(QWidget *parent = 0);
    ~MenuNotLogin();


private slots:
    void on_backBtn_clicked();

private:
    Ui::MenuNotLogin *ui;

signals:
    void switchToStart();
};
#endif // MENUNOTLOGIN_H