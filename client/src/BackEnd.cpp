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
  int incorrect_answer[2];
  int i = 0;
  int numQuestion = 0;

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
      case CHANGE_QUESTION:
      case QUESTION:
        numQuestion = atoi(strtok(msg.value, "|"));
        BackEnd::instance->question = strtok(NULL, "|");
        BackEnd::instance->a = strtok(NULL, "|");
        BackEnd::instance->b = strtok(NULL, "|");
        BackEnd::instance->c = strtok(NULL, "|");
        BackEnd::instance->d = strtok(NULL, "|");

        if ((i == 0) || (BackEnd::instance->prize + 1 == numQuestion)){
          BackEnd::instance->questionChanged();
          BackEnd::instance->aChanged();
          BackEnd::instance->bChanged();
          BackEnd::instance->cChanged();
          BackEnd::instance->dChanged();
          i++;
        }
        break;
      case CORRECT_ANSWER:
        BackEnd::instance->correct_answer = atoi(strtok(msg.value, " "));
        BackEnd::instance->reward = atoi(strtok(NULL, " "));
        BackEnd::instance->rewardChanged();
        BackEnd::instance->correctAnswer();
        break;
      case WIN:
        BackEnd::instance->correct_answer = atoi(strtok(msg.value, " "));
        BackEnd::instance->reward = atoi(strtok(NULL, " "));
        BackEnd::instance->rewardChanged();
        BackEnd::instance->prize++;
        BackEnd::instance->correctAnswer();
        return NULL;
      case LOSE:
        BackEnd::instance->correct_answer = atoi(msg.value);
        BackEnd::instance->lose();
        return NULL;
      case STOP_GAME:
      case OVER_TIME:
        return NULL;
      case FIFTY_FIFTY:
        incorrect_answer[0] = atoi(strtok(msg.value, " "));
        incorrect_answer[1] = atoi(strtok(NULL, " "));
        switch (incorrect_answer[0])
        {
        case 1:
          BackEnd::instance->a = "";
          BackEnd::instance->aChanged();
          break;
        case 2:
          BackEnd::instance->b = "";
          BackEnd::instance->bChanged();
          break;
        case 3:
          BackEnd::instance->c = "";
          BackEnd::instance->cChanged();
          break;
        case 4:
          BackEnd::instance->d = "";
          BackEnd::instance->dChanged();
          break;
        }

        switch (incorrect_answer[1])
        {
        case 1:
          BackEnd::instance->a = "";
          BackEnd::instance->aChanged();
          break;
        case 2:
          BackEnd::instance->b = "";
          BackEnd::instance->bChanged();
          break;
        case 3:
          BackEnd::instance->c = "";
          BackEnd::instance->cChanged();
          break;
        case 4:
          BackEnd::instance->d = "";
          BackEnd::instance->dChanged();
          break;
        }
        break;
      case CALL_PHONE:
        if (msg.value[0] == '1')
        {
          BackEnd::instance->call_phone_answer = "A";
        }
        else if (msg.value[0] == '2')
        {
          BackEnd::instance->call_phone_answer = "B";
        }
        else if (msg.value[0] == '3')
        {
          BackEnd::instance->call_phone_answer = "C";
        }
        else if (msg.value[0] == '4')
        {
          BackEnd::instance->call_phone_answer = "D";
        }
        BackEnd::instance->callPhoneAnswerChanged();
        BackEnd::instance->openCallPhone();
        break;
      case VOTE:
        BackEnd::instance->voteA = atoi(strtok(msg.value, " "));
        BackEnd::instance->voteB = atoi(strtok(NULL, " "));
        BackEnd::instance->voteC = atoi(strtok(NULL, " "));
        BackEnd::instance->voteD = atoi(strtok(NULL, " "));

        BackEnd::instance->voteAChanged();
        BackEnd::instance->voteBChanged();
        BackEnd::instance->voteCChanged();
        BackEnd::instance->voteDChanged();

        BackEnd::instance->openVote();
        break;
      case FOUND_PLAYER:
        BackEnd::instance->setEnemyName(msg.value);
        BackEnd::instance->enemyNameChanged();
        BackEnd::instance->foundPlayer();
        break;
      }
    }
  }

  pthread_exit(NULL);
}

BackEnd *BackEnd::instance = nullptr;

BackEnd::BackEnd(QObject *parent) : QObject(parent)
{
  user_name = "";
  prize = 0;
  reward = 0;
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

void BackEnd::setPrize(int value)
{
  prize = value;
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

QString BackEnd::getCallPhoneAnswer()
{
  return call_phone_answer;
}

int BackEnd::getCorrectAnswer()
{
  return correct_answer;
}

int BackEnd::getReward()
{
  return reward;
}

void BackEnd::setReward(int value)
{
  reward = value;
}

int BackEnd::getVoteA()
{
  return voteA;
}

int BackEnd::getVoteB()
{
  return voteB;
}

int BackEnd::getVoteC()
{
  return voteC;
}

int BackEnd::getVoteD()
{
  return voteD;
}

void BackEnd::setUserName(const QString &value)
{
  user_name = value;
}

QString BackEnd::getEnemyName() const
{
  return enemy_name;
}

void BackEnd::setEnemyName(const QString &value)
{
  enemy_name = value;
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

void BackEnd::playPvP()
{
  Message msg;
  int sendBytes;

  msg.type = PLAY_PVP;
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

void BackEnd::fiftyFifty()
{
  Message msg;
  int sendBytes;

  msg.type = FIFTY_FIFTY;
  sendBytes = send(sockfd, &msg, sizeof(msg), 0);
  if (sendBytes < 0)
  {
    perror("The server terminated prematurely");
    exit(0);
    return;
  }
}

void BackEnd::callPhone()
{
  Message msg;
  int sendBytes;

  msg.type = CALL_PHONE;
  sendBytes = send(sockfd, &msg, sizeof(msg), 0);
  if (sendBytes < 0)
  {
    perror("The server terminated prematurely");
    exit(0);
    return;
  }
}

void BackEnd::vote()
{
  Message msg;
  int sendBytes;

  msg.type = VOTE;
  sendBytes = send(sockfd, &msg, sizeof(msg), 0);
  if (sendBytes < 0)
  {
    perror("The server terminated prematurely");
    exit(0);
    return;
  }
}

void BackEnd::changeQuestion()
{
  Message msg;
  int sendBytes;

  msg.type = CHANGE_QUESTION;
  sendBytes = send(sockfd, &msg, sizeof(msg), 0);
  if (sendBytes < 0)
  {
    perror("The server terminated prematurely");
    exit(0);
    return;
  }
}

void BackEnd::stopGame()
{
  Message msg;
  int sendBytes;

  msg.type = STOP_GAME;
  sendBytes = send(sockfd, &msg, sizeof(msg), 0);
  if (sendBytes < 0)
  {
    perror("The server terminated prematurely");
    exit(0);
    return;
  }
}

void BackEnd::overTime()
{
  Message msg;
  int sendBytes;

  msg.type = OVER_TIME;
  sendBytes = send(sockfd, &msg, sizeof(msg), 0);
  if (sendBytes < 0)
  {
    perror("The server terminated prematurely");
    exit(0);
    return;
  }
}