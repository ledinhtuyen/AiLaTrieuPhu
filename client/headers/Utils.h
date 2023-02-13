#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE 1024
#define BUFF_SIZE 1024

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

typedef struct _message
{
  enum msg_type type;
  char data_type[25];
  int length;
  char value[BUFF_SIZE];
} Message;

typedef struct _account
{
  char username[MAX_LINE];
  int login_status; // 0: not login; 1: logged in
} Account;

/*--------------------- Function Declaration -------------------------*/
// int is_number(const char *s);
// int validate_ip(char *ip);
// int menu_start();
// int menu_not_login();
// int menu_logged();
int connect_to_server(char ip[], int port);
int disconnect_to_server();
int login(char username[], char password[]);
int signup(char username[], char password[]);
int logout();
int change_password(char password[]);
// int show_menu_not_login();
// int show_menu_logged();
// int play_alone();
// int play_pvp();
#endif /* CLIENT_H_ */