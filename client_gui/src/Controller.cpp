#ifndef INCLUDES_MENU_H
#define INCLUDES_MENU_H
#include "./headers/MenuStart.h"
#include "./headers/MenuNotLogin.h"
#endif // INCLUDES_MENU_H

#include "./headers/Controller.h"

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
