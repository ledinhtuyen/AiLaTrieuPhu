#include "../headers/Utils.h"
#include "../headers/BackEnd.h"

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
}

void BackEnd::connectToServer(){
  if (connect_to_server("127.0.0.1", 5500))
  {
    emit connectSuccess();
  }
  else
  {
    emit connectFail();
  }
}

void BackEnd::disconnectToServer(){
  disconnect_to_server();
}