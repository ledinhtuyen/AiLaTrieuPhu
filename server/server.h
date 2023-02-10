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
  ENTERED_ROOM,
  WAIT_OTHER_PLAYER,
  NOT_FOUND_PLAYER,
  OTHER_PLAYER_IS_PLAYING,
  WIN,
  LOSE,
  DRAW,
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
  Question questions;
  int reward[2]; // set default all = 0
  struct _room *next;
} Room;
Room *head_room = NULL;
int current_id_room = 0;

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
int is_number(const char *s);
void *thread_start(void *client_fd);
int login(int conn_fd, char msg_data[BUFF_SIZE]);
int signup(char username[BUFF_SIZE], char password[BUFF_SIZE]);
int change_password(char username[BUFF_SIZE], char msg_data[BUFF_SIZE]);
int handle_play_alone(int);
// int handle_play_pvp(int);

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
    int i, j, sum = 0, random_number, max;
    srand(time(0));
    for (i = 0; i < 3; i++) {
        random_number = rand() % (100 - sum + 1);
        percent[i] = random_number;
        sum += random_number;
    }
    percent[3] = 100 - sum;

    max = percent[0];

    for (i = 0; i < 4; i++) {
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

int handle_play_alone(int conn_fd)
{
  Message msg;
  Question questions = get_questions();
  char str[10];
  int level = 0;
  int reward = 0;
  int incorrect_answer[2];

  while (level < 15)
  {
    msg.type = QUESTION;

initQuestion:
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
    case STOP_GAME:
      printf("[%d]: Stopped play alone\n", conn_fd);
      break;
    case CHOICE_ANSWER:
      if (questions.answer[level - 1] == atoi(msg.value))
      {
        if (level == 15)
        {
          msg.type = WIN;
          send(conn_fd, &msg, sizeof(msg), 0);
          return 1;
        }
        else
        {
          sleep(2);
          msg.type = CORRECT_ANSWER;
          send(conn_fd, &msg, sizeof(msg), 0);
          continue;
        }
      }
      else
      {
        msg.type = LOSE;
        sprintf(str, "%d", questions.answer[level - 1]);
        strcpy(msg.value, str);
        send(conn_fd, &msg, sizeof(msg), 0);
        return 0;
      }
      break;
    case FIFTY_FIFTY:
      help(FIFTY_FIFTY, &questions, level, conn_fd);
      goto recvLabel;
    case CALL_PHONE:
      help(CALL_PHONE, &questions, level, conn_fd);
      goto recvLabel;
    case VOTE:
      help(VOTE, &questions, level, conn_fd);
      goto recvLabel;
    case CHANGE_QUESTION:
      help(CHANGE_QUESTION, &questions, level, conn_fd);
      level--;
      msg.type = CHANGE_QUESTION;
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
  char str[10];

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
}

// int handle_play_pvp(int conn_fd)
// {
//   Message msg, tmp;
//   int is_found = 0, index_in_room = -1, index_doi_thu_in_room = -1, is_me_win = -1;
//   Room *room;
//   char str[BUFF_SIZE];
//   time_t start, endwait, seconds, start_reply, end_reply;
//   Question q;

//   msg.type = WAIT_OTHER_PLAYER;
//   strcpy(msg.value, "Đang tìm kiếm người chơi khác, xin chờ chút...\n");
//   if (send(conn_fd, &msg, sizeof(msg), 0) < 0)
//   {
//     perror("Send error!");
//     delete_client(conn_fd);
//     return 0;
//   }

//   room = find_room_is_blank_or_waiting();

//   if (room == NULL)
//   {
//     is_found = 0;
//     room = add_room();

//     add_client_to_room(conn_fd, room);

//     start = time(NULL);
//     seconds = 10; // end loop after this time has elapsed

//     endwait = start + seconds;

//     printf("Find opponent for room %d...\n", room->room_id);

//     printf("start time is: %s", ctime(&start));

//     while (start < endwait)
//     {
//       if (room->client_fd[1] != 0)
//       {
//         is_found = 1;
//         index_in_room = 0;
//         index_doi_thu_in_room = 1;
//         break;
//       }
//       sleep(1); // sleep 1s.
//       start = time(NULL);
//       printf("loop time is: %s", ctime(&start));
//     }
//     printf("end time is: %s", ctime(&endwait));

//     printf("Found opponent for room %d...\n", room->room_id);
//   }
//   else
//   {
//     is_found = 1;
//     add_client_to_room(conn_fd, room);
//     index_in_room = 1;
//     index_doi_thu_in_room = 0;
//   }

//   if (is_found == 1)
//   {
//     msg.type = FOUND_PLAYER;
//     strcpy(msg.value, "Đã tìm thấy người chơi khác, bắt đầu trò chơi!");
//     if (send(conn_fd, &msg, sizeof(msg), 0) < 0)
//     {
//       perror("Send error!");
//       delete_client(conn_fd);
//       return 0;
//     }

//     room->play_status[index_in_room] = 0;

//     msg.type = ENTERED_ROOM;
//     sprintf(str, "%d", room->room_id);
//     strcpy(msg.value, str);

//     if (send(conn_fd, &msg, sizeof(msg), 0) < 0)
//     {
//       perror("Send error!");
//       delete_client(conn_fd);
//       return 0;
//     }

//     while (room->index_current_question[index_in_room] < 15)
//     {
//       if (room->index_current_question[index_in_room] / 5 == 0)
//       {
//         q = room->list_quest.easy_question[room->index_current_question[index_in_room]];
//       }
//       else if (room->index_current_question[index_in_room] / 5 == 1)
//       {
//         q = room->list_quest.medium_question[room->index_current_question[index_in_room] - 5];
//       }
//       else
//       {
//         q = room->list_quest.hard_question[room->index_current_question[index_in_room] - 10];
//       }

//       msg.type = QUESTION;
//       strcpy(msg.value, "Question ");
//       sprintf(str, "%d", room->index_current_question[index_in_room] + 1);
//       strcat(msg.value, str);
//       strcat(msg.value, ": ");
//       strcat(msg.value, q.question);
//       strcat(msg.value, q.choiceA);
//       strcat(msg.value, q.choiceB);
//       strcat(msg.value, q.choiceC);
//       strcat(msg.value, q.choiceD);
//       send(conn_fd, &msg, sizeof(msg), 0);
//       start_reply = time(NULL);
//       room->index_current_question[index_in_room]++;

//       recv(conn_fd, &msg, sizeof(msg), 0);
//       end_reply = time(NULL);
//       seconds = end_reply - start_reply;
//       if (strcmp(msg.value, q.answer) == 0 && seconds <= 15)
//       {
//         room->reward[index_in_room] += 10000;
//         if (room->index_current_question[index_in_room] == 15)
//         {
//           msg.type = WIN;
//           strcpy(msg.value, "Chuc mung ban da tra loi dung 15 cau hoi va nhan duoc !");
//           sprintf(str, "%dd\n", room->reward[index_in_room]);
//           strcat(msg.value, str);
//           room->play_status[index_in_room] = 1;
//           break;
//         }
//         else
//         {
//           msg.type = CORRECT_ANSWER;
//           strcpy(msg.value, "Chinh xac!");
//           send(conn_fd, &msg, sizeof(msg), 0);
//           continue;
//         }
//       }
//       else
//       {
//         msg.type = LOSE;
//         if (seconds > 15)
//         {
//           strcpy(msg.value, "Het thoi gian tra loi!");
//         }
//         else
//         {
//           strcpy(msg.value, "Sai! Dap an la: ");
//           strcat(msg.value, q.answer);
//         }

//         strcat(msg.value, ". Chuc mung ban da tra loi dung ");
//         sprintf(str, "%d cau hoi va nhan duoc %dd\n", room->index_current_question[index_in_room] - 1, room->reward[index_in_room]);
//         strcat(msg.value, str);
//         room->play_status[index_in_room] = 1;
//         break;
//       }
//     }

//     int sent = 0;

//     while (room->play_status[index_doi_thu_in_room] == 0)
//     {
//       if (!sent)
//       {
//         tmp.type = OTHER_PLAYER_IS_PLAYING;
//         strcpy(tmp.value, msg.value);
//         strcat(tmp.value, "Đối thủ đang chơi, vui lòng chờ!");
//         send(conn_fd, &tmp, sizeof(tmp), 0);
//         sent = 1;
//       }
//     }

//     if (room->index_current_question[index_in_room] > room->index_current_question[index_doi_thu_in_room])
//       strcpy(msg.value, "Ban da thang doi thu!");
//     else if (room->index_current_question[index_in_room] < room->index_current_question[index_doi_thu_in_room])
//     {
//       strcpy(msg.value, "Ban da thua doi thu!");
//     }
//     else
//       strcpy(msg.value, "Ban va doi thu hoa nhau!");
//     send(conn_fd, &msg, sizeof(msg), 0);

//     delete_room(room->room_id);
//     return 1;
//   }
//   else
//   {
//     msg.type = NOT_FOUND_PLAYER;
//     strcpy(msg.value, "Không tìm thấy người chơi khác, vui lòng thử lại sau!");
//     if (send(conn_fd, &msg, sizeof(msg), 0) < 0)
//     {
//       perror("Send error!");
//       delete_client(conn_fd);
//       return 0;
//     }
//     delete_room(room->room_id);
//     return 0;
//   }

//   return 1;
// }

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
      // case PLAY_PVP:
      //   handle_play_pvp(conn_fd);
      //   break;
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