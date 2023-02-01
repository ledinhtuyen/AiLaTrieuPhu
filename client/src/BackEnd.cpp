extern "C"{
  #include "../headers/Utils.h"
}
#include "../headers/BackEnd.h"

std::string BackEnd::server_ip = "127.0.0.1";
int BackEnd::server_port = 5500;

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
}

void BackEnd::connectToServer(){
  char ip[16];
  strcpy(ip, this->server_ip.c_str());
  if (connect_to_server(ip, this->server_port))
  {
    emit connectSuccess();
  }
  else
  {
    emit connectFail();
  }
  // printf("%s %d\n", BackEnd::server_ip, BackEnd::server_port);
}

void BackEnd::disconnectToServer(){
  disconnect_to_server();
}

void BackEnd::signIn(QString username, QString password){
  int loginStatus = login(username.toLocal8Bit().data(), password.toLocal8Bit().data());
  if (loginStatus == LOGIN_SUCCESS)
  {
    emit loginSuccess();
  }
  else if (loginStatus == LOGGED_IN)
  {
    emit loggedIn();
  }
  else if (loginStatus == LOGIN_FAIL)
  {
    emit loginFail();
  }
}

void BackEnd::signUp(QString username, QString password){
  int registerStatus = signup(username.toLocal8Bit().data(), password.toLocal8Bit().data());
  if (registerStatus == SIGNUP_SUCCESS)
  {
    emit signupSuccess();
  }
  else if (registerStatus == ACCOUNT_EXIST)
  {
    emit accountExist();
  }
}