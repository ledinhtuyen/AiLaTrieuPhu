#include <QApplication>
#include "./headers/Controller.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Controller c;
  c.showMenuStart();
  return a.exec();
}