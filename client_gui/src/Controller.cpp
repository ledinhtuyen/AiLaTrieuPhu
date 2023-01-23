#ifndef MENUSTART_H
#include "./headers/MenuStart.h"
#endif // MENUSTART_H

#ifndef MENUNOTLOGIN_H
#include "./headers/MenuNotLogin.h"
#endif // MENUNOTLOGIN_H

#ifndef CONTROLLER_H
#include "./headers/Controller.h"
#endif  // CONTROLLER_H

Controller::Controller() {
  menuStart = new MenuStart();
  menuNotLogin = new MenuNotLogin();
}

Controller::~Controller() {
  delete menuStart;
  delete menuNotLogin;
}

void Controller::showMenuStart() {
  menuNotLogin->hide();
  connect(menuStart, SIGNAL(switchToNotLogin()), this, SLOT(showMenuNotLogin()));
  menuStart->show();
}

void Controller::showMenuNotLogin() {
  menuStart->hide();
  connect(menuNotLogin, SIGNAL(switchToStart()), this, SLOT(showMenuStart()));
  menuNotLogin->show();
}
