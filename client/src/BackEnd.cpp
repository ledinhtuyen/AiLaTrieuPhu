extern "C"{
  #include "../headers/Utils.h"
}
#include "../headers/BackEnd.h"

std::string BackEnd::server_ip = "127.0.0.1";
int BackEnd::server_port = 5500;

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
}

QString BackEnd::getUserName() const
{
  return user_name;
}

void BackEnd::setUserName(const QString &value)
{
  user_name = value;
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
  char user[100];
  char pass[100];
  strcpy(user, username.toStdString().c_str());
  strcpy(pass, password.toStdString().c_str());
  int loginStatus = login(user, pass);
  if (loginStatus == LOGIN_SUCCESS)
  {
    user_name = username;
    emit loginSuccess();
  }
  else if (loginStatus == LOGGED_IN)
  {
    emit loggedIn();
  }
  else if (loginStatus == ACCOUNT_BLOCKED)
  {
    emit accountBlocked();
  }
  else if (loginStatus == ACCOUNT_NOT_EXIST)
  {
    emit accountNotExist();
  }
  else if (loginStatus == WRONG_PASSWORD)
  {
    emit wrongPassword();
  }
}

void BackEnd::signUp(QString username, QString password){
  char user_name[100];
  char pass_word[100];
  strcpy(user_name, username.toStdString().c_str());
  strcpy(pass_word, password.toStdString().c_str());
  int registerStatus = signup(user_name, pass_word);
  if (registerStatus == SIGNUP_SUCCESS)
  {
    emit signupSuccess();
  }
  else if (registerStatus == ACCOUNT_EXIST)
  {
    emit accountExist();
  }
}

void BackEnd::logOut(){
  logout();
}

void BackEnd::changePassword(QString newPassword){
  char password[100];
  strcpy(password, newPassword.toStdString().c_str());
  int re = change_password(password);
  if (re == CHANGE_PASSWORD_SUCCESS)
  {
    emit changePasswordSuccess();
  }
  else if (re == SAME_OLD_PASSWORD)
  {
    emit sameOldPassword();
  }
}