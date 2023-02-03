#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

#define BACKLOG 6
#define BUFF_SIZE 1024
#define TRUE 1
#define FALSE 0

enum msg_type
{
  DISCONNECT,
  LOGIN,
  LOGIN_SUCCESS,
  LOGGED_IN,
  WRONG_PASSWORD,
  ACCOUNT_NOT_EXIST,
  ACCOUNT_BLOCKED,
  SIGNUP,
  ACCOUNT_EXIST,
  SIGNUP_SUCCESS,
  CHANGE_PASS,
  CHANGE_PASS_SUCCESS,
  PLAY_ALONE,
  PLAY_PVP,
  QUESTION,
  CHOICE_ANSWER,
  CORRECT_ANSWER,
  FOUND_PLAYER,
  ENTERED_ROOM,
  WAIT_OTHER_PLAYER,
  NOT_FOUND_PLAYER,
  OTHER_PLAYER_IS_PLAYING,
  WIN,
  LOSE,
  DRAW,
  LOGOUT
};

enum login_status
{
  AUTH,
  UN_AUTH
};

typedef struct _message
{
  enum msg_type type;
  char data_type[25];
  int length;
  char value[BUFF_SIZE];
} Message;

typedef struct _account
{
  char username[BUFF_SIZE];
  char password[BUFF_SIZE];
  int status; // 0 (blocked), 1 (active)
  int count;  // // number of times of wrong-password's typing
  struct _account *next;
} Account;
Account *head_account = NULL;

typedef struct _client
{
  char login_account[BUFF_SIZE];
  int conn_fd;
  int login_status; // [0: not login yet] & [1: logged in]
  int room_id;      // 0: in offline mode, 1: in room 1, 2: in room 2, 3: in room 3
  struct _client *next;
} Client;
Client *head_client = NULL;

typedef struct _question
{
  int index;
  char question[BUFF_SIZE];
  char choiceA[BUFF_SIZE];
  char choiceB[BUFF_SIZE];
  char choiceC[BUFF_SIZE];
  char choiceD[BUFF_SIZE];
  char answer[BUFF_SIZE];
  int reward;
} Question;

typedef struct _list_quest
{
  Question easy_question[5];
  Question medium_question[5];
  Question hard_question[5];
} ListQuest;

typedef struct _room
{
  int room_id;
  int client_fd[2];              // set default all = 0
  int status;                    // 0: no player enter, 1: waiting, 2: playing, 3: end
  int play_status[2];            // 0: playing, 1: end or out of room
  int index_current_question[2]; // start from 1 to 15
  ListQuest list_quest;
  int reward[2]; // set default all = 0
  struct _room *next;
} Room;
Room *head_room = NULL;
int current_id_room = 0;

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*------------ Function Declare ----------------*/
Account *new_account();
Client *new_client();
Room *new_room();
void read_user_file();
void read_question_file(Question q[], char *file_name);
void catch_ctrl_c_and_exit(int sig);
void add_account(char username[BUFF_SIZE], char password[BUFF_SIZE], int status);
void add_client(int conn_fd);
Room *add_room();
void delete_room(int room_id);
Room *find_room_is_blank_or_waiting();
void add_question(int index, int level, char question[BUFF_SIZE], char answerA[BUFF_SIZE], char answerB[BUFF_SIZE],
                  char answerC[BUFF_SIZE], char answerD[BUFF_SIZE], int true);
void delete_client(int conn_fd);
int add_client_to_room(int conn_fd, Room *room);
void update_user_file(char name[BUFF_SIZE], char new_pass[BUFF_SIZE], int new_status);
int is_number(const char *s);
void *thread_start(void *client_fd);
int login(int conn_fd, char msg_data[BUFF_SIZE]);
int check_account_exist(char username[BUFF_SIZE]);
int signup(char username[BUFF_SIZE], char password[BUFF_SIZE]);
int handle_play_alone(int);
int handle_play_pvp(int);

/*---------------- Utilities -------------------*/
Account *new_account()
{
  Account *new = (Account *)malloc(sizeof(Account));
  new->next = NULL;
  return new;
}

Client *new_client()
{
  Client *new = (Client *)malloc(sizeof(Client));
  new->login_status = UN_AUTH;
  new->room_id = 0;
  new->next = NULL;
  return new;
}

Room *new_room()
{
  Room *new = (Room *)malloc(sizeof(Room));
  new->room_id = ++current_id_room;
  new->client_fd[0] = 0;
  new->client_fd[1] = 0;
  new->status = 0;
  new->index_current_question[0] = 0;
  new->index_current_question[1] = 0;
  new->play_status[0] = -1;
  new->play_status[1] = -1;
  new->reward[0] = 0;
  new->reward[1] = 0;
  new->next = NULL;
  return new;
}

void read_user_file()
{
  char str[100];
  FILE *f = fopen("account.txt", "r");
  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  while (fgets(str, sizeof(str), f) != NULL)
  {
    char *name = strtok(str, " ");
    char *pass = strtok(NULL, " ");
    int status = atoi(strtok(NULL, " "));
    add_account(name, pass, status);
  }

  fclose(f);
}

void read_question_file(Question q[], char *file_name)
{
  FILE *f;
  if ((f = fopen(file_name, "r")) == NULL)
  {
    printf("Not find %s\n", file_name);
    return;
  }
  else
  {
    for (int x = 0; x < 5; x++)
    { // Reads the questions from file
      fgets(q[x].question, 120, f);
      fgets(q[x].choiceA, 70, f);
      fgets(q[x].choiceB, 70, f);
      fgets(q[x].choiceC, 70, f);
      fgets(q[x].choiceD, 70, f);
      fgets(q[x].answer, 70, f);
      q[x].answer[1] = '\0';
    }
  }

  fclose(f);
}

void catch_ctrl_c_and_exit(int sig)
{
  char mesg[] = "\nServer is closing...\n";
  while (head_client != NULL)
  {
    if (send(head_client->conn_fd, mesg, strlen(mesg), 0) < 0)
    {
      perror("Send error");
      delete_client(head_client->conn_fd);
    }
    printf("\nClose socketfd: %d\n", head_client->conn_fd);
    delete_client(head_client->conn_fd);
  }
  printf("\nBye\n");
  exit(0);
}

void add_account(char username[BUFF_SIZE], char password[BUFF_SIZE], int status)
{
  Account *new = new_account();
  strcpy(new->username, username);
  strcpy(new->password, password);
  new->status = status;
  if (head_account == NULL)
    head_account = new; // if linked list is empty
  else
  {
    Account *tmp = head_account; // assign head to p
    while (tmp->next != NULL)
      tmp = tmp->next; // traverse the list until the last node
    tmp->next = new;   // Point the previous last node to the new node created.
  }
}

void add_client(int conn_fd)
{
  Client *new = new_client();
  new->conn_fd = conn_fd;
  if (head_client == NULL)
    head_client = new; // if linked list is empty
  else
  {
    Client *tmp = head_client; // assign head to p
    while (tmp->next != NULL)
      tmp = tmp->next; // traverse the list until the last node
    tmp->next = new;   // Point the previous last node to the new node created.
  }
}

void delete_client(int conn_fd)
{
  Client *tmp = head_client;
  Client *prev = NULL;
  while (tmp != NULL)
  {
    if (tmp->conn_fd == conn_fd)
    {
      if (prev == NULL)
        head_client = tmp->next;
      else
        prev->next = tmp->next;
      free(tmp);
      break;
    }
    prev = tmp;
    tmp = tmp->next;
  }
}

Room *add_room()
{
  Room *new = new_room();
  if (head_room == NULL)
    head_room = new; // if linked list is empty
  else
  {
    Room *tmp = head_room; // assign head to p
    while (tmp->next != NULL)
      tmp = tmp->next; // traverse the list until the last node
    tmp->next = new;   // Point the previous last node to the new node created.
  }

  return new;
}

void delete_room(int room_id)
{
  Room *tmp = head_room;
  Room *prev = NULL;
  while (tmp != NULL)
  {
    if (tmp->room_id == room_id)
    {
      if (prev == NULL)
        head_room = tmp->next;
      else
        prev->next = tmp->next;
      free(tmp);
      return;
    }
    prev = tmp;
    tmp = tmp->next;
  }
}

Room *find_room_is_blank_or_waiting()
{
  Room *tmp = head_room;
  while (tmp != NULL)
  {
    if (tmp->status == 0 || tmp->status == 1)
      return tmp;
    tmp = tmp->next;
  }
  return NULL;
}

int add_client_to_room(int conn_fd, Room *room)
{
  if (room->client_fd[0] == 0)
  {
    room->client_fd[0] = conn_fd;
    room->status = 1;
    return 0;
  }
  else if (room->client_fd[1] == 0)
  {
    room->client_fd[1] = conn_fd;
    room->status = 2;
    return 1;
  }
  return -1;
}
// {
//   Room *tmp = head_room;
//   while (tmp != NULL)
//   {
//     if (tmp->room_id == room_id)
//     {
//       if (tmp->client_fd[0] == 0)
//       {
//         tmp->client_fd[0] = conn_fd;
//         tmp->status = 1;
//         return 0;
//       }
//       else if (tmp->client_fd[1] == 0)
//       {
//         tmp->client_fd[1] = conn_fd;
//         tmp->status = 2;
//         return 1;
//       }
//       else
//         return -1;
//     }
//     tmp = tmp->next;
//   }
//   return -1;
// }

void update_user_file(char name[BUFF_SIZE], char new_pass[BUFF_SIZE], int new_status)
{
  FILE *f = fopen("account.txt", "w");
  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  Account *tmp = head_account;
  while (tmp != NULL)
  {
    if (strcmp(tmp->username, name) == 0)
    {
      if (strcmp(new_pass, "") != 0)
        strcpy(tmp->password, new_pass);
    }
    fprintf(f, "%s %s %d\n", tmp->username, tmp->password, tmp->status);
    tmp = tmp->next;
  }
  fclose(f);
}

int is_number(const char *s)
{
  while (*s != '\0')
  {
    if (!isdigit((unsigned char)*s))
      return 0; // string is not number
    s++;
  }
  return 1; // string is number
}

int login(int conn_fd, char msg_data[BUFF_SIZE])
{
  char *username = strtok(msg_data, " ");
  char *password = strtok(NULL, " ");

  Client *cli = head_client, *cli_tmp = head_client;
  while (cli->conn_fd != conn_fd && cli != NULL)
    cli = cli->next;

  Account *tmp = head_account;
  while (tmp != NULL)
  {
    if (strcmp(tmp->username, username) == 0)
    {
      cli_tmp = head_client;
      while (cli_tmp != NULL)
      {
        if (strcmp(cli_tmp->login_account, username) == 0 && cli_tmp->login_status == AUTH)
        {
          return LOGGED_IN;
        }
        cli_tmp = cli_tmp->next;
      }
      if (strcmp(tmp->password, password) == 0)
      {
        if (tmp->status == 0)
        {
          return ACCOUNT_BLOCKED;
        }
        if (cli != NULL)
        {
          cli->login_status = AUTH;
          strcpy(cli->login_account, tmp->username);
          return LOGIN_SUCCESS;
        }
      }
      else
        return WRONG_PASSWORD;
    }
    tmp = tmp->next;
  }
  return ACCOUNT_NOT_EXIST;
}

int check_account_exist(char username[BUFF_SIZE])
{
  Account *tmp = head_account;
  while (tmp != NULL)
  {
    if (strcmp(tmp->username, username) == 0)
    {
      return 1;
    }
    tmp = tmp->next;
  }
  return 0;
}

int signup(char username[], char password[])
{
  add_account(username, password, 1);
  update_user_file(username, password, 1);
  return 1;
}

int handle_play_alone(int conn_fd)
{
  Message msg;
  ListQuest lst;
  Question q;
  char str[10];
  int current_question = 0;

  read_question_file(lst.easy_question, "easy_question.txt");
  read_question_file(lst.medium_question, "medium_question.txt");
  read_question_file(lst.hard_question, "hard_question.txt");

  while (current_question < 15)
  {
    if (current_question / 5 == 0)
    {
      q = lst.easy_question[current_question];
    }
    else if (current_question / 5 == 1)
    {
      q = lst.medium_question[current_question - 5];
    }
    else
    {
      q = lst.hard_question[current_question - 10];
    }

    msg.type = QUESTION;
    strcpy(msg.value, "Question ");
    sprintf(str, "%d", current_question + 1);
    strcat(msg.value, str);
    strcat(msg.value, ": ");
    strcat(msg.value, q.question);
    strcat(msg.value, q.choiceA);
    strcat(msg.value, q.choiceB);
    strcat(msg.value, q.choiceC);
    strcat(msg.value, q.choiceD);
    send(conn_fd, &msg, sizeof(msg), 0);
    current_question++;

    recv(conn_fd, &msg, sizeof(msg), 0);
    if (strcmp(msg.value, q.answer) == 0)
    {
      if (current_question == 15)
      {
        msg.type = WIN;
        strcpy(msg.value, "Chuc mung ban da tra loi dung 15 cau hoi!");
        send(conn_fd, &msg, sizeof(msg), 0);
        return 1;
      }
      else
      {
        msg.type = CORRECT_ANSWER;
        strcpy(msg.value, "Chinh xac!");
        send(conn_fd, &msg, sizeof(msg), 0);
        continue;
      }
    }
    else
    {
      msg.type = LOSE;
      strcpy(msg.value, "Sai! Dap an la: ");
      strcat(msg.value, q.answer);
      strcat(msg.value, ". Chuc mung ban da tra loi dung ");
      sprintf(str, "%d cau hoi", current_question - 1);
      strcat(msg.value, str);
      send(conn_fd, &msg, sizeof(msg), 0);
      return 1;
    }
  }

  return 1;
}

int handle_play_pvp(int conn_fd)
{
  Message msg, tmp;
  int is_found = 0, index_in_room = -1, index_doi_thu_in_room = -1, is_me_win = -1;
  Room *room;
  char str[BUFF_SIZE];
  time_t start, endwait, seconds, start_reply, end_reply;
  Question q;

  msg.type = WAIT_OTHER_PLAYER;
  strcpy(msg.value, "Đang tìm kiếm người chơi khác, xin chờ chút...\n");
  if (send(conn_fd, &msg, sizeof(msg), 0) < 0)
  {
    perror("Send error!");
    delete_client(conn_fd);
    return 0;
  }

  room = find_room_is_blank_or_waiting();

  if (room == NULL)
  {
    is_found = 0;
    room = add_room();

    read_question_file(room->list_quest.easy_question, "easy_question.txt");
    read_question_file(room->list_quest.medium_question, "medium_question.txt");
    read_question_file(room->list_quest.hard_question, "hard_question.txt");

    add_client_to_room(conn_fd, room);

    start = time(NULL);
    seconds = 10; // end loop after this time has elapsed

    endwait = start + seconds;

    printf("Find opponent for room %d...\n", room->room_id);

    printf("start time is: %s", ctime(&start));

    while (start < endwait)
    {
      if (room->client_fd[1] != 0)
      {
        is_found = 1;
        index_in_room = 0;
        index_doi_thu_in_room = 1;
        break;
      }
      sleep(1); // sleep 1s.
      start = time(NULL);
      printf("loop time is: %s", ctime(&start));
    }
    printf("end time is: %s", ctime(&endwait));

    printf("Found opponent for room %d...\n", room->room_id);
  }
  else
  {
    is_found = 1;
    add_client_to_room(conn_fd, room);
    index_in_room = 1;
    index_doi_thu_in_room = 0;
  }

  if (is_found == 1)
  {
    msg.type = FOUND_PLAYER;
    strcpy(msg.value, "Đã tìm thấy người chơi khác, bắt đầu trò chơi!");
    if (send(conn_fd, &msg, sizeof(msg), 0) < 0)
    {
      perror("Send error!");
      delete_client(conn_fd);
      return 0;
    }

    room->play_status[index_in_room] = 0;

    msg.type = ENTERED_ROOM;
    sprintf(str, "%d", room->room_id);
    strcpy(msg.value, str);

    if (send(conn_fd, &msg, sizeof(msg), 0) < 0)
    {
      perror("Send error!");
      delete_client(conn_fd);
      return 0;
    }

    while (room->index_current_question[index_in_room] < 15)
    {
      if (room->index_current_question[index_in_room] / 5 == 0)
      {
        q = room->list_quest.easy_question[room->index_current_question[index_in_room]];
      }
      else if (room->index_current_question[index_in_room] / 5 == 1)
      {
        q = room->list_quest.medium_question[room->index_current_question[index_in_room] - 5];
      }
      else
      {
        q = room->list_quest.hard_question[room->index_current_question[index_in_room] - 10];
      }

      msg.type = QUESTION;
      strcpy(msg.value, "Question ");
      sprintf(str, "%d", room->index_current_question[index_in_room] + 1);
      strcat(msg.value, str);
      strcat(msg.value, ": ");
      strcat(msg.value, q.question);
      strcat(msg.value, q.choiceA);
      strcat(msg.value, q.choiceB);
      strcat(msg.value, q.choiceC);
      strcat(msg.value, q.choiceD);
      send(conn_fd, &msg, sizeof(msg), 0);
      start_reply = time(NULL);
      room->index_current_question[index_in_room]++;

      recv(conn_fd, &msg, sizeof(msg), 0);
      end_reply = time(NULL);
      seconds = end_reply - start_reply;
      if (strcmp(msg.value, q.answer) == 0 && seconds <= 15)
      {
        room->reward[index_in_room] += 10000;
        if (room->index_current_question[index_in_room] == 15)
        {
          msg.type = WIN;
          strcpy(msg.value, "Chuc mung ban da tra loi dung 15 cau hoi va nhan duoc !");
          sprintf(str, "%dd\n", room->reward[index_in_room]);
          strcat(msg.value, str);
          room->play_status[index_in_room] = 1;
          break;
        }
        else
        {
          msg.type = CORRECT_ANSWER;
          strcpy(msg.value, "Chinh xac!");
          send(conn_fd, &msg, sizeof(msg), 0);
          continue;
        }
      }
      else
      {
        msg.type = LOSE;
        if (seconds > 15)
        {
          strcpy(msg.value, "Het thoi gian tra loi!");
        }
        else
        {
          strcpy(msg.value, "Sai! Dap an la: ");
          strcat(msg.value, q.answer);
        }

        strcat(msg.value, ". Chuc mung ban da tra loi dung ");
        sprintf(str, "%d cau hoi va nhan duoc %dd\n", room->index_current_question[index_in_room] - 1, room->reward[index_in_room]);
        strcat(msg.value, str);
        room->play_status[index_in_room] = 1;
        break;
      }
    }

    int sent = 0;

    while (room->play_status[index_doi_thu_in_room] == 0)
    {
      if (!sent)
      {
        tmp.type = OTHER_PLAYER_IS_PLAYING;
        strcpy(tmp.value, msg.value);
        strcat(tmp.value, "Đối thủ đang chơi, vui lòng chờ!");
        send(conn_fd, &tmp, sizeof(tmp), 0);
        sent = 1;
      }
    }

    if (room->index_current_question[index_in_room] > room->index_current_question[index_doi_thu_in_room])
      strcpy(msg.value, "Ban da thang doi thu!");
    else if (room->index_current_question[index_in_room] < room->index_current_question[index_doi_thu_in_room])
    {
      strcpy(msg.value, "Ban da thua doi thu!");
    }
    else
      strcpy(msg.value, "Ban va doi thu hoa nhau!");
    send(conn_fd, &msg, sizeof(msg), 0);

    delete_room(room->room_id);
    return 1;
  }
  else
  {
    msg.type = NOT_FOUND_PLAYER;
    strcpy(msg.value, "Không tìm thấy người chơi khác, vui lòng thử lại sau!");
    if (send(conn_fd, &msg, sizeof(msg), 0) < 0)
    {
      perror("Send error!");
      delete_client(conn_fd);
      return 0;
    }
    delete_room(room->room_id);
    return 0;
  }

  return 1;
}

void *thread_start(void *client_fd)
{
  pthread_detach(pthread_self());

  int recvBytes, sendBytes, re;
  Message msg;
  int conn_fd = *((int *)client_fd);
  Client *cli = head_client;

  while (cli->conn_fd != conn_fd && cli != NULL)
    cli = cli->next;

  while ((recvBytes = recv(conn_fd, &msg, sizeof(msg), 0)) > 0)
  {
    if (msg.type == DISCONNECT)
    {
      recvBytes = 0;
      break;
    }

    switch (cli->login_status)
    {
    case AUTH:
      switch (msg.type)
      {
      case CHANGE_PASS:
        update_user_file(cli->login_account, msg.value, 1);
        msg.type = CHANGE_PASS_SUCCESS;
        strcpy(msg.value, "Change password successfully!");
        send(conn_fd, &msg, sizeof(msg), 0);
        printf("[%d] Change %s's password.\n", conn_fd, cli->login_account);
        break;
      case PLAY_ALONE:
        printf("[%d] %s is playing alone.\n", conn_fd, cli->login_account);
        handle_play_alone(conn_fd);
        break;
      case PLAY_PVP:
        handle_play_pvp(conn_fd);
        break;
      case LOGOUT:
        printf("[%d]: Bye %s\n", conn_fd, cli->login_account);
        cli->login_status = UN_AUTH;
        break;
      }
      break;
    case UN_AUTH:
      switch (msg.type)
      {
      case LOGIN:
        re = login(conn_fd, msg.value);
        if (re == LOGIN_SUCCESS)
        {
          msg.type = LOGIN_SUCCESS;
          strcpy(msg.value, "Login success");
          printf("[%d]: Login success!\n", conn_fd);
          send(conn_fd, &msg, sizeof(msg), 0);
        }
        else if (re == LOGGED_IN)
        {
          msg.type = LOGGED_IN;
          strcpy(msg.value, "Account is logged in");
          printf("[%d] Account is logged in\n", conn_fd);
          send(conn_fd, &msg, sizeof(msg), 0);
        }
        else if (re == ACCOUNT_BLOCKED)
        {
          msg.type = ACCOUNT_BLOCKED;
          strcpy(msg.value, "Account is blocked");
          printf("[%d] Account is blocked\n", conn_fd);
          send(conn_fd, &msg, sizeof(msg), 0);
        }
        else if (re == ACCOUNT_NOT_EXIST)
        {
          msg.type = ACCOUNT_NOT_EXIST;
          strcpy(msg.value, "Account not exist");
          printf("[%d] Account not exist\n", conn_fd);
          send(conn_fd, &msg, sizeof(msg), 0);
        }
        else if (re == WRONG_PASSWORD)
        {
          msg.type = WRONG_PASSWORD;
          strcpy(msg.value, "Wrong password");
          printf("[%d] Wrong password\n", conn_fd);
          send(conn_fd, &msg, sizeof(msg), 0);
        }
        break;
      case SIGNUP:
        {
          char username[BUFF_SIZE];
          char password[BUFF_SIZE];
          sprintf(username, "%s", strtok(msg.value, " "));
          sprintf(password, "%s", strtok(NULL, " "));
          if (check_account_exist(username) == 1)
          {
            msg.type = ACCOUNT_EXIST;
            printf("[%d]: Account %s exist!\n", conn_fd, username);
            strcpy(msg.value, "Account exist");
            send(conn_fd, &msg, sizeof(msg), 0);
          }
          else
          {
            signup(username, password);
            msg.type = SIGNUP_SUCCESS;
            printf("[%d]: Signup %s success!\n", conn_fd, username);
            strcpy(msg.value, "Signup success");
            send(conn_fd, &msg, sizeof(msg), 0);
          }
          break;
        }
      }
      break;
    }
  }
  if (recvBytes <= 0)
  {
    printf("[%d]: Client disconnected!\n", conn_fd);
    close(conn_fd);
    delete_client(conn_fd);
  }

  pthread_exit(NULL);
}