extern "C"
{
#include "../headers/Utils.h"
}

extern "C" int sockfd;
#include "../headers/BackEnd.h"

std::string BackEnd::server_ip = "127.0.0.1";
int BackEnd::server_port = 5500;

void *thread_recv(void *arg)
{
  pthread_detach(pthread_self());

  Message msg;
  int recvBytes;
  while (1)
  {
    recvBytes = recv(sockfd, &msg, sizeof(msg), 0);
    if (recvBytes < 0)
    {
      perror("The server terminated prematurely\n");
      exit(0);
      return NULL;
    }
    else
    {
      switch (msg.type)
      {
      case QUESTION:
        strtok(msg.value, "|");
        BackEnd::instance->question = strtok(NULL, "|");
        BackEnd::instance->a = strtok(NULL, "|");
        BackEnd::instance->b = strtok(NULL, "|");
        BackEnd::instance->c = strtok(NULL, "|");
        BackEnd::instance->d = strtok(NULL, "|");

        emit BackEnd::instance->questionChanged();
        emit BackEnd::instance->aChanged();
        emit BackEnd::instance->bChanged();
        emit BackEnd::instance->cChanged();
        emit BackEnd::instance->dChanged();
        break;
      case CORRECT_ANSWER:
        BackEnd::instance->prize++;

        emit BackEnd::instance->prizeChanged();

        printf("%d - %s\n", BackEnd::instance->prize, msg.value);
        break;
      case WIN:
        printf("WIN\n", msg.value);
        return NULL;
      case LOSE:
        printf("LOSE - Correct answer: %d\n", atoi(msg.value));
        return NULL;
      }
    }
  }
}

BackEnd *BackEnd::instance = nullptr;

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
  user_name = "";
  prize = 0;
  question = "";
  a = "";
  b = "";
  c = "";
  d = "";

  if (instance == nullptr)
  {
    instance = this;
  }
}

BackEnd::~BackEnd()
{
  delete instance;
}

QString BackEnd::getUserName() const
{
  return user_name;
}

int BackEnd::getPrize()
{
  return prize;
}

QString BackEnd::getQuestion()
{
  return question;
}

QString BackEnd::getA()
{
  return a;
}

QString BackEnd::getB()
{
  return b;
}

QString BackEnd::getC()
{
  return c;
}

QString BackEnd::getD()
{
  return d;
}

void BackEnd::setUserName(const QString &value)
{
  user_name = value;
}

void BackEnd::connectToServer()
{
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

void BackEnd::disconnectToServer()
{
  disconnect_to_server();
}

void BackEnd::signIn(QString username, QString password)
{
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

void BackEnd::signUp(QString username, QString password)
{
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

void BackEnd::logOut()
{
  logout();
}

void BackEnd::changePassword(QString newPassword)
{
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

void BackEnd::playAlone()
{
  printf("play alone\n");
  Message msg;
  int sendBytes;

  msg.type = PLAY_ALONE;
  sendBytes = send(sockfd, &msg, sizeof(msg), 0);
  if (sendBytes < 0)
  {
    perror("The server terminated prematurely");
    exit(0);
    return;
  }

  pthread_t tid;
  pthread_create(&tid, NULL, thread_recv, NULL);
}

void BackEnd::choiceAnswer(int answer)
{
  Message msg;
  int sendBytes;

  printf("choice answer %d\n", answer);

  msg.type = CHOICE_ANSWER;
  msg.value[0] = answer + '0';
  msg.value[1] = '\0';
  sendBytes = send(sockfd, &msg, sizeof(msg), 0);
  if (sendBytes < 0)
  {
    perror("The server terminated prematurely");
    exit(0);
    return;
  }
}