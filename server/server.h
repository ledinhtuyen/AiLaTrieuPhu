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
#include <mysql/mysql.h>

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
  CHANGE_PASSWORD,
  SAME_OLD_PASSWORD,
  CHANGE_PASSWORD_SUCCESS,
  PLAY_ALONE,
  PLAY_PVP,
  STOP_GAME,
  QUESTION,
  CHOICE_ANSWER,
  CORRECT_ANSWER,
  FOUND_PLAYER,
  WAIT_OTHER_PLAYER,
  NOT_FOUND_PLAYER,
  OTHER_PLAYER_IS_PLAYING,
  WIN,
  LOSE,
  DRAW,
  OVER_TIME,
  LOGOUT,
  FIFTY_FIFTY,
  CALL_PHONE,
  VOTE,
  CHANGE_QUESTION
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
  char question[15][BUFF_SIZE];
  char a[15][BUFF_SIZE];
  char b[15][BUFF_SIZE];
  char c[15][BUFF_SIZE];
  char d[15][BUFF_SIZE];
  int answer[15];
  int reward[15];
} Question;

typedef struct _room
{
  int room_id;
  int client_fd[2];              // set default all = 0
  int status;                    // 0: no player enter, 1: waiting, 2: playing, 3: end
  int play_status[2];            // 0: playing, 1: end or out of room
  int index_current_question[2]; // start from 1 to 15
  Question questions[2];
  int reward[2]; // set default all = 0
  struct _room *next;
} Room;
Room *head_room = NULL;
int current_id_room = 0;

pthread_mutex_t mutex;

MYSQL *conn;

/*------------ Function Declare ----------------*/
int connect_to_database();
int execute_query(char *query);
Question get_questions();
int fifty_fifty(Question q, int level, int incorrect_answer[2]);
int call_phone(Question q, int level);
int vote(Question q, int level, int percent[4]);
int change_question(Question *q, int level);
int help(int type, Question *questions, int level, int conn_fd);
Client *new_client();
Room *new_room();
void catch_ctrl_c_and_exit(int sig);
void add_client(int conn_fd);
Room *add_room();
void delete_room(int room_id);
Room *find_room_is_blank_or_waiting();
void delete_client(int conn_fd);
int add_client_to_room(int conn_fd, Room *room);
Client *find_client(int conn_fd);
int is_number(const char *s);
void *thread_start(void *client_fd);
int login(int conn_fd, char msg_data[BUFF_SIZE]);
int signup(char username[BUFF_SIZE], char password[BUFF_SIZE]);
int change_password(char username[BUFF_SIZE], char msg_data[BUFF_SIZE]);
int handle_play_game(Message msg, int conn_fd, Question *questions, int level);
int handle_play_alone(int);
int handle_play_pvp(int);

/*---------------- Utilities -------------------*/
int connect_to_database()
{
  char server[50], username[50], password[50], database[50];
  int port;

  FILE *f = fopen("config", "r");
  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  fscanf(f, "DB_HOST=%s\nDB_PORT=%d\nDB_DATABASE=%s\nDB_USERNAME=%s\nDB_PASSWORD=%s", server, &port, database, username, password);
  fclose(f);

  conn = mysql_init(NULL);
  if (!mysql_real_connect(conn, server, username, password, database, port, NULL, 0)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  return 1;
}

int execute_query(char *query)
{
  if (mysql_query(conn, query)) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }
  return 1;
}

Question get_questions(){
  MYSQL_RES *res;
  MYSQL_ROW row;

  Question questions;
  char query[1000];

  for (int i = 0; i < 15; i++)
  {
    sprintf(query, "SELECT question, a, b, c, d, answer, reward FROM questions WHERE level = %d ORDER BY RAND() LIMIT 1", i + 1);
    execute_query(query);
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    strcpy(questions.question[i], row[0]);
    strcpy(questions.a[i], row[1]);
    strcpy(questions.b[i], row[2]);
    strcpy(questions.c[i], row[3]);
    strcpy(questions.d[i], row[4]);
    questions.answer[i] = atoi(row[5]);
    questions.reward[i] = atoi(row[6]);
    mysql_free_result(res);
  }

  printf("Get question success\n");
  return questions;
}

int fifty_fifty(Question q, int level, int incorrect_answers[2]){
  srand(time(0));
  int i, j, incorrect;
  for (i = 0; i < 2; i++) {
    incorrect = rand() % 4 + 1;
    while (incorrect == q.answer[level - 1]) {
      incorrect = rand() % 4 + 1;
    }
    incorrect_answers[i] = incorrect;
    for (j = 0; j < i; j++) {
      if (incorrect_answers[j] == incorrect) {
        i--;
        break;
      }
    }
  }
  return 1;
}

int call_phone(Question q, int level){
  return q.answer[level - 1];
}

int vote(Question q, int level, int percent[4]){
    int i = 0, j = 0, sum = 0, random_number, max;
    srand(time(0));
    for (i = 0; i < 3; i++) {
        random_number = rand() % (100 - sum + 1);
        percent[i] = random_number;
        sum += random_number;
    }
    percent[3] = 100 - sum;

    max = percent[0];

    for (i = 1; i < 4; i++) {
        if (percent[i] > max) {
            max = percent[i];
            j = i;
        }
    }

    int tmp = percent[q.answer[level - 1] - 1];
    percent[q.answer[level - 1] - 1] = max;
    percent[j] = tmp;

    return 1;
}

int change_question(Question *q, int level) {
  MYSQL_RES *res;
  MYSQL_ROW row;

  char query[1000];
  sprintf(query, "SELECT question, a, b, c, d, answer, reward FROM questions WHERE level = %d ORDER BY RAND() LIMIT 1", level);
  execute_query(query);
  res = mysql_store_result(conn);
  if((row = mysql_fetch_row(res)) != NULL){
    strcpy(q->question[level - 1], row[0]);
    strcpy(q->a[level - 1], row[1]);
    strcpy(q->b[level - 1], row[2]);
    strcpy(q->c[level - 1], row[3]);
    strcpy(q->d[level - 1], row[4]);
    q->answer[level - 1] = atoi(row[5]);
    q->reward[level - 1] = atoi(row[6]);
    mysql_free_result(res);
  }
  else {
    return 0;
  }
  return 1;
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

Client *find_client(int conn_fd)
{
  Client *tmp = head_client;
  while (tmp != NULL)
  {
    if (tmp->conn_fd == conn_fd)
      return tmp;
    tmp = tmp->next;
  }
  return NULL;
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
  MYSQL_RES *res;
  MYSQL_ROW row;

  Client *cli = head_client, *tmp = head_client;
  char username[50], password[50];
  char query[100];
  int re = -1;

  strcpy(username, strtok(msg_data, " "));
  strcpy(password, strtok(NULL, " "));

  while (cli->conn_fd != conn_fd && cli != NULL)
    cli = cli->next;

  sprintf(query, "SELECT * FROM account WHERE username = '%s'", username);
  execute_query(query);
  res = mysql_use_result(conn);
  if ((row = mysql_fetch_row(res)) == NULL)
  {
    re = ACCOUNT_NOT_EXIST;
  }
  else
  {
    if (strcmp(row[2], password) == 0){
      if (strcmp(row[3], "1") == 0){
        while (tmp != NULL)
        {
          if (strcmp(tmp->login_account, username) == 0 && tmp->login_status == AUTH)
          {
            re = LOGGED_IN;
            break;
          }
          tmp = tmp->next;
        }
        if (re != LOGGED_IN)
        {
          strcpy(cli->login_account, username);
          cli->login_status = AUTH;
          re = LOGIN_SUCCESS;
        }
      }
      else
        re = ACCOUNT_BLOCKED;
    }
    else
      re = WRONG_PASSWORD;
  }

  mysql_free_result(res);
  return re;
}

int signup(char username[], char password[])
{
  MYSQL_RES *res;
  MYSQL_ROW row;

  char query[100];
  int re;

  sprintf(query, "SELECT * FROM account WHERE username = '%s'", username);
  execute_query(query);
  res = mysql_use_result(conn);
  if ((row = mysql_fetch_row(res)) == NULL)
  {
    mysql_free_result(res);
    sprintf(query, "INSERT INTO account(username, password, status) VALUES('%s', '%s', 1)", username, password);
    execute_query(query);
    res = mysql_use_result(conn);
    re = SIGNUP_SUCCESS;
  }
  else
    re = ACCOUNT_EXIST;

  mysql_free_result(res);
  return re;
}

int change_password(char username[], char new_password[])
{
  MYSQL_RES *res;
  MYSQL_ROW row;

  char query[100];
  int re;

  sprintf(query, "SELECT * FROM account WHERE username = '%s'", username);
  execute_query(query);
  res = mysql_use_result(conn);
  if ((row = mysql_fetch_row(res)) != NULL)
  {
    if (strcmp(row[2], new_password) == 0)
    {
      re = SAME_OLD_PASSWORD;
    }
    else {
      mysql_free_result(res);
      sprintf(query, "UPDATE account SET password = '%s' WHERE username = '%s'", new_password, username);
      execute_query(query);
      res = mysql_use_result(conn);
      re = CHANGE_PASSWORD_SUCCESS;
    }
  }
  else
    re = ACCOUNT_NOT_EXIST;

  mysql_free_result(res);
  return re;
}

int handle_play_game(Message msg,int conn_fd, Question *questions, int level){
    char str[100];

    switch (msg.type)
    {
    case OVER_TIME:
      msg.type = OVER_TIME;
      send(conn_fd, &msg, sizeof(msg), 0);
      printf("[%d]: Over time\n", conn_fd);
      break;
    case STOP_GAME:
      msg.type = STOP_GAME;
      send(conn_fd, &msg, sizeof(msg), 0);
      printf("[%d]: Stopped play alone\n", conn_fd);
      break;
    case CHOICE_ANSWER:
      if (questions->answer[level - 1] == atoi(msg.value))
      {
        sleep(2);
        sprintf(str, "%d %d", questions->answer[level - 1], questions->reward[level - 1]);
        strcpy(msg.value, str);
        if (level == 15)
        {
          msg.type = WIN;
          send(conn_fd, &msg, sizeof(msg), 0);
          printf("[%d]: Win\n", conn_fd);
        }
        else{
          msg.type = CORRECT_ANSWER;
          send(conn_fd, &msg, sizeof(msg), 0);
          printf("[%d]: Correct answer question %d\n", conn_fd, level - 1);
          return 0;
        }
      }
      else
      {
        sleep(2);
        msg.type = LOSE;
        sprintf(str, "%d", questions->answer[level - 1]);
        strcpy(msg.value, str);
        send(conn_fd, &msg, sizeof(msg), 0);
        printf("[%d]: Lose\n", conn_fd);
      }
      break;
    case FIFTY_FIFTY:
      help(FIFTY_FIFTY, questions, level, conn_fd);
      break;
    case CALL_PHONE:
      help(CALL_PHONE, questions, level, conn_fd);
      break;
    case VOTE:
      help(VOTE, questions, level, conn_fd);
      break;
    case CHANGE_QUESTION:
      help(CHANGE_QUESTION, questions, level, conn_fd);
      break;
    default:
      break;
    }

    return 1;
}

int handle_play_alone(int conn_fd)
{
  Message msg;
  Question questions = get_questions();
  char str[100];
  int level = 0;
  int re;

  while (level < 15)
  {
initQuestion:
    msg.type = QUESTION;
    sprintf(str, "%d", level + 1);
    strcpy(msg.value, str);
    strcat(msg.value, "|");
    strcat(msg.value, questions.question[level]);
    strcat(msg.value, "|");
    strcat(msg.value, questions.a[level]);
    strcat(msg.value, "|");
    strcat(msg.value, questions.b[level]);
    strcat(msg.value, "|");
    strcat(msg.value, questions.c[level]);
    strcat(msg.value, "|");
    strcat(msg.value, questions.d[level]);
    send(conn_fd, &msg, sizeof(msg), 0);
    level++;

recvLabel:
    recv(conn_fd, &msg, sizeof(msg), 0);

    switch (msg.type)
    {
    case OVER_TIME:
    case STOP_GAME:
      handle_play_game(msg, conn_fd, &questions, level);
      return 0;
    case CHOICE_ANSWER:
      re = handle_play_game(msg, conn_fd, &questions, level);
      if(re == 0) continue;
      break;
    case FIFTY_FIFTY:
    case CALL_PHONE:
    case VOTE:
      handle_play_game(msg, conn_fd, &questions, level);
      msg.type = -1;
      goto recvLabel;
    case CHANGE_QUESTION:
      handle_play_game(msg, conn_fd, &questions, level);
      level--;
      goto initQuestion;
    default:
      break;
    }
  }
  return 1;
}

int help(int type, Question *questions, int level, int conn_fd){
  Message msg;
  int incorrect_answer[2];
  int percent[4];
  char str[100];

  switch (type)
  {
    case FIFTY_FIFTY:
      printf("[%d]: 50_50 question %d\n", conn_fd, level);
      fifty_fifty(*questions, level, incorrect_answer);
      msg.type = FIFTY_FIFTY;
      sprintf(str, "%d %d", incorrect_answer[0], incorrect_answer[1]);
      strcpy(msg.value, str);
      send(conn_fd, &msg, sizeof(msg), 0);
      break;
    case CALL_PHONE:
      printf("[%d]: Call phone question %d\n", conn_fd, level);
      msg.type = CALL_PHONE;
      int answer = call_phone(*questions, level);
      sprintf(str, "%d", answer);
      strcpy(msg.value, str);
      send(conn_fd, &msg, sizeof(msg), 0);
      break;
    case VOTE:
      printf("[%d]: Vote question %d\n", conn_fd, level);
      vote(*questions, level, percent);
      msg.type = VOTE;
      sprintf(str, "%d %d %d %d", percent[0], percent[1], percent[2], percent[3]);
      strcpy(msg.value, str);
      send(conn_fd, &msg, sizeof(msg), 0);
      break;
    case CHANGE_QUESTION:
      printf("[%d]: Changed question %d\n", conn_fd, level);
      change_question(questions, level);
      break;
  }
  return 1;
}

int handle_play_pvp(int conn_fd)
{
  Message msg, tmp;
  int is_found = 0, index_in_room = -1, index_doi_thu_in_room = -1, is_me_win = -1, re;
  Room *room;
  char str[BUFF_SIZE];
  time_t start, endwait, seconds, start_reply, end_reply;
  Question questions;

  room = find_room_is_blank_or_waiting();

  if (room == NULL)
  {
    is_found = 0;
    room = add_room();

    add_client_to_room(conn_fd, room);
    room->questions[0] = get_questions();
    room->questions[1] = room->questions[0];

    while (1)
    {
      if (room->client_fd[1] != 0)
      {
        is_found = 1;
        index_in_room = 0;
        index_doi_thu_in_room = 1;
        printf("Found opponent for room %d...\n", room->room_id);
        break;
      }
    }
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
    sleep(2);

    Client *client = find_client(room->client_fd[index_doi_thu_in_room]);

    msg.type = FOUND_PLAYER;
    sprintf(str, "%s", client->login_account);
    strcpy(msg.value, str);
    printf("[%d]: Found opponent %s\n", conn_fd, msg.value);
    if (send(conn_fd, &msg, sizeof(msg), 0) < 0)
    {
      perror("Send error!");
      delete_client(conn_fd);
      return 0;
    }

    room->play_status[index_in_room] = 0;

    while (room->index_current_question[index_in_room] < 15)
    {
initQuestion2:
      msg.type = QUESTION;
      sprintf(str, "%d", room->index_current_question[index_in_room] + 1);
      strcpy(msg.value, str);
      strcat(msg.value, "|");
      strcat(msg.value, room->questions[index_in_room].question[room->index_current_question[index_in_room]]);
      strcat(msg.value, "|");
      strcat(msg.value, room->questions[index_in_room].a[room->index_current_question[index_in_room]]);
      strcat(msg.value, "|");
      strcat(msg.value, room->questions[index_in_room].b[room->index_current_question[index_in_room]]);
      strcat(msg.value, "|");
      strcat(msg.value, room->questions[index_in_room].c[room->index_current_question[index_in_room]]);
      strcat(msg.value, "|");
      strcat(msg.value, room->questions[index_in_room].d[room->index_current_question[index_in_room]]);
      send(conn_fd, &msg, sizeof(msg), 0);
      room->index_current_question[index_in_room]++;

recvLabel2:
      recv(conn_fd, &msg, sizeof(msg), 0);

      switch (msg.type)
      {
      case OVER_TIME:
      case STOP_GAME:
        handle_play_game(msg, conn_fd, &(room->questions[index_in_room]), room->index_current_question[index_in_room]);
        return 0;
      case CHOICE_ANSWER:
        re = handle_play_game(msg, conn_fd, &(room->questions[index_in_room]), room->index_current_question[index_in_room]);
        if(re == 0) continue;
        break;
      case FIFTY_FIFTY:
      case CALL_PHONE:
      case VOTE:
        handle_play_game(msg, conn_fd, &(room->questions[index_in_room]), room->index_current_question[index_in_room]);
        msg.type = -1;
        goto recvLabel2;
      case CHANGE_QUESTION:
        handle_play_game(msg, conn_fd, &(room->questions[index_in_room]), room->index_current_question[index_in_room]);
        room->index_current_question[index_in_room]--;
        goto initQuestion2;
      default:
        break;
      }

      // if (strcmp(msg.value, q.answer) == 0 && seconds <= 15)
      // {
      //   room->reward[index_in_room] += 10000;
      //   if (room->index_current_question[index_in_room] == 15)
      //   {
      //     msg.type = WIN;
      //     strcpy(msg.value, "Chuc mung ban da tra loi dung 15 cau hoi va nhan duoc !");
      //     sprintf(str, "%dd\n", room->reward[index_in_room]);
      //     strcat(msg.value, str);
      //     room->play_status[index_in_room] = 1;
      //     break;
      //   }
      //   else
      //   {
      //     msg.type = CORRECT_ANSWER;
      //     strcpy(msg.value, "Chinh xac!");
      //     send(conn_fd, &msg, sizeof(msg), 0);
      //     continue;
      //   }
      // }
      // else
      // {
      //   msg.type = LOSE;
      //   if (seconds > 15)
      //   {
      //     strcpy(msg.value, "Het thoi gian tra loi!");
      //   }
      //   else
      //   {
      //     strcpy(msg.value, "Sai! Dap an la: ");
      //     strcat(msg.value, q.answer);
      //   }

      //   strcat(msg.value, ". Chuc mung ban da tra loi dung ");
      //   sprintf(str, "%d cau hoi va nhan duoc %dd\n", room->index_current_question[index_in_room] - 1, room->reward[index_in_room]);
      //   strcat(msg.value, str);
      //   room->play_status[index_in_room] = 1;
      //   break;
      // }
    }

  //   int sent = 0;

  //   while (room->play_status[index_doi_thu_in_room] == 0)
  //   {
  //     if (!sent)
  //     {
  //       tmp.type = OTHER_PLAYER_IS_PLAYING;
  //       strcpy(tmp.value, msg.value);
  //       strcat(tmp.value, "Đối thủ đang chơi, vui lòng chờ!");
  //       send(conn_fd, &tmp, sizeof(tmp), 0);
  //       sent = 1;
  //     }
  //   }

  //   if (room->index_current_question[index_in_room] > room->index_current_question[index_doi_thu_in_room])
  //     strcpy(msg.value, "Ban da thang doi thu!");
  //   else if (room->index_current_question[index_in_room] < room->index_current_question[index_doi_thu_in_room])
  //   {
  //     strcpy(msg.value, "Ban da thua doi thu!");
  //   }
  //   else
  //     strcpy(msg.value, "Ban va doi thu hoa nhau!");
  //   send(conn_fd, &msg, sizeof(msg), 0);

  //   delete_room(room->room_id);
  //   return 1;
  // }
  // else
  // {
  //   msg.type = NOT_FOUND_PLAYER;
  //   strcpy(msg.value, "Không tìm thấy người chơi khác, vui lòng thử lại sau!");
  //   if (send(conn_fd, &msg, sizeof(msg), 0) < 0)
  //   {
  //     perror("Send error!");
  //     delete_client(conn_fd);
  //     return 0;
  //   }
  //   delete_room(room->room_id);
  //   return 0;
  // }
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
      case CHANGE_PASSWORD:
        re = change_password(cli->login_account, msg.value);

        if (re == SAME_OLD_PASSWORD)
          printf("[%d] %s's password is the same as old password.\n", conn_fd, cli->login_account);
        else if (re == CHANGE_PASSWORD_SUCCESS)
          printf("[%d] %s's password is changed.\n", conn_fd, cli->login_account);

        msg.type = re;
        send(conn_fd, &msg, sizeof(msg), 0);
        break;
      case PLAY_ALONE:
        printf("[%d]: %s is playing alone.\n", conn_fd, cli->login_account);
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
          printf("[%d]: Login success!\n", conn_fd);
          send(conn_fd, &msg, sizeof(msg), 0);
        }
        else if (re == LOGGED_IN)
        {
          msg.type = LOGGED_IN;
          printf("[%d] Account is logged in\n", conn_fd);
          send(conn_fd, &msg, sizeof(msg), 0);
        }
        else if (re == ACCOUNT_BLOCKED)
        {
          msg.type = ACCOUNT_BLOCKED;
          printf("[%d] Account is blocked\n", conn_fd);
          send(conn_fd, &msg, sizeof(msg), 0);
        }
        else if (re == ACCOUNT_NOT_EXIST)
        {
          msg.type = ACCOUNT_NOT_EXIST;
          printf("[%d] Account not exist\n", conn_fd);
          send(conn_fd, &msg, sizeof(msg), 0);
        }
        else if (re == WRONG_PASSWORD)
        {
          msg.type = WRONG_PASSWORD;
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
          
          re = signup(username, password);

          if (re == SIGNUP_SUCCESS)
          {
            msg.type = SIGNUP_SUCCESS;
            printf("[%d]: Signup success!\n", conn_fd);
            send(conn_fd, &msg, sizeof(msg), 0);
          }
          else if (re == ACCOUNT_EXIST)
          {
            msg.type = ACCOUNT_EXIST;
            printf("[%d] Account exist\n", conn_fd);
            send(conn_fd, &msg, sizeof(msg), 0);
          }
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