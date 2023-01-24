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
    void on_guideBtn_clicked();
    void on_creditBtn_clicked();
    void on_quitBtn_clicked();

private:
    Ui::MenuStart *ui;

signals:
    void showMenuNotLogin();
    void showCredit();
    void showGuide();
    void quit();
};