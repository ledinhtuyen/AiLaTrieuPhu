#ifndef MENUSTART_H
#include "./headers/MenuStart.h"
#endif // MENUSTART_H

#ifndef GUIDEDIALOG_H
#include "./headers/GuideDialog.h"
#endif // GUIDEDIALOG_H

#ifndef CREDITDIALOG_H
#include "./headers/CreditDialog.h"
#endif // CREDITDIALOG_H

#ifndef MENUNOTLOGIN_H
#include "./headers/MenuNotLogin.h"
#endif // MENUNOTLOGIN_H

#ifndef CONTROLLER_H
#include "./headers/Controller.h"
#endif  // CONTROLLER_H

Controller::Controller() {
  menuStart = new MenuStart();
  connect(menuStart, SIGNAL(showMenuNotLogin()), this, SLOT(showMenuNotLogin()));
  connect(menuStart, SIGNAL(showGuide()), this, SLOT(showGuide()));
  connect(menuStart, SIGNAL(showCredit()), this, SLOT(showCredit()));
  connect(menuStart, SIGNAL(quit()), qApp, SLOT(quit()));

  menuNotLogin = new MenuNotLogin();
  connect(menuNotLogin, SIGNAL(switchToStart()), this, SLOT(showMenuStart()));
}

Controller::~Controller() {
  delete menuStart;
  delete menuNotLogin;
}

void Controller::showMenuStart() {
  menuNotLogin->hide();
  menuStart->show();
}

void Controller::showGuide() {
  GuideDialog *guideDialog = new GuideDialog();
  guideDialog->exec();
  delete guideDialog;
}

void Controller::showCredit() {
  CreditDialog *creditDialog = new CreditDialog();
  creditDialog->exec();
  delete creditDialog;
}

void Controller::showMenuNotLogin() {
  menuStart->hide();
  menuNotLogin->show();
}
