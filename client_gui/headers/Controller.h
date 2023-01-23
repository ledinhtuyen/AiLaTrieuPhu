#ifndef MENUSTART_H
#include "./headers/MenuStart.h"
#endif // MENUSTART_H

#ifndef MENUNOTLOGIN_H
#include "./headers/MenuNotLogin.h"
#endif // MENUNOTLOGIN_H

#define CONTROLLER_H
class Controller: public QObject {
    Q_OBJECT
public:
    Controller();
    ~Controller();

public slots:
    void showMenuStart();
    void showMenuNotLogin();

private:
    MenuStart *menuStart;
    MenuNotLogin *menuNotLogin;
};