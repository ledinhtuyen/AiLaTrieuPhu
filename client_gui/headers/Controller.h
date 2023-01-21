#ifndef INCLUDES_MENU_H
#define INCLUDES_MENU_H
#include "./headers/MenuStart.h"
#include "./headers/MenuNotLogin.h"
#endif // INCLUDES_MENU_H

#ifndef CONTROLLER_H
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
#endif // CONTROLLER_H