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
#include <poll.h>

#define MAX_LINE 1024

int choice1, choice2, choice3, sockfd, show1, show2, show3;
int recvBytes, sendBytes;
char sendBuff[MAX_LINE] = {0}, recvBuff[MAX_LINE];
struct sockaddr_in server, client;
char serverIP[20];
int serverPort;

enum msg_type{
  LOGIN,
  LOGIN_SUCCESS,
  LOGIN_FAIL,
  SIGNUP,
  SIGNUP_SUCCESS,
  SIGNUP_FAIL,
  CHANGE_PASS,
  CHANGE_PASS_SUCCESS,
  PLAY_OFFLINE,
  PLAY_ONLINE,
  LOGOUT
};

typedef struct _message{
  enum msg_type type;
  char data_type[25];
  int length;
  char value[100];
} Message;

typedef struct _account
{
  char username[MAX_LINE];
  int login_status; // 0: not login; 1: logged in
} Account;
Account acc;

int is_number(const char *s)
{
  while (*s)
  {
    if (!isdigit(*s))
    { // if the character is not a number, return false
      return 0;
    }
    s++; // point to next character
  }
  return 1;
}

int validate_ip(char *ip)
{ // check whether the IP is valid or not
  int i, num, dots = 0;
  char *ptr;
  if (ip == NULL)
    return 0;
  ptr = strtok(ip, "."); // cut the string using dor delimiter
  if (ptr == NULL)
    return 0;
  while (ptr)
  {
    if (!is_number(ptr)) // check whether the sub string is holding only number or not
      return 0;
    num = atoi(ptr); // convert substring to number
    if (num >= 0 && num <= 255)
    {
      ptr = strtok(NULL, "."); // cut the next part of the string
      if (ptr != NULL)
        dots++; // increase the dot count
    }
    else
      return 1;
  }
  if (dots != 3) // if the number of dots are not 3, return false
    return 0;
  return 1;
}

int menu_start()
{
  int op;
  char input[MAX_LINE];
  do
  {
    printf("\n------------------------------\n");
    printf("1. Bắt đầu.\n");
    printf("2. Cách chơi.\n");
    printf("3. Tác giả.\n");
    printf("4. Kết thúc.\n");
    printf("Nhập lựa chọn của bạn: ");
    scanf(" %[^\n]", input);
    if (strlen(input) != 1 || !isdigit(input[0]))
      break;
    op = atoi(input);
  } while (op > 5 || op < 1);
  return op;
}

int menu_not_login()
{
  char input[MAX_LINE];
  int op;
  do
  {
    printf("\n************************************\n");
    printf("\t1. Đăng nhập\n");
    printf("\t2. Đăng ký\n");
    printf("\t3. Trở về\n");
    printf("\t4. Thoát.\n");
    scanf(" %[^\n]", input);
    if (strlen(input) != 1 || !isdigit(input[0]))
      break;
    op = atoi(input);
  } while (op > 3 || op < 1);
  return op;
}

int menu_logged()
{
  char input[MAX_LINE];
  int op;
  do
  {
    printf("\n************************************\n");
    printf("\t1. Thay đổi mật khẩu.\n");
    printf("\t2. Choi Offline.\n");
    printf("\t3. Choi Online.\n");
    printf("\t4. Đăng xuất.\n");
    scanf(" %[^\n]", input);
    if (strlen(input) != 1 || !isdigit(input[0]))
      break;
    op = atoi(input);
  } while (op > 4 || op < 1);
  return op;
}

int connect_to_server()
{
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Socket creation error \n");
    return 0;
  }
  printf("Server Address: %s", serverIP);

  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(serverIP);
  inet_aton(serverIP, &server.sin_addr);
  server.sin_port = htons(serverPort);

  printf("\n************************************\n\nConnecting....\n\n");
  if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
  {
    printf("\nConnection Failed \n");
    return 0;
  }
  return 1;
}

int show_menu_not_login()
{
  int show_menu_start = 0;
  while (!show_menu_start)
  {
    int choice = menu_not_login();

    switch (choice)
    {
    case 1:
      Message msg;
      char username[100], password[100];
      msg.type = LOGIN;
      printf("Username: "); scanf(" %[^\n]", username);
      printf("Password: "); scanf(" %[^\n]", password);
      strcpy(msg.data_type, "string");
      strcpy(msg.value, username);
      strcat(msg.value, "|");
      strcat(msg.value, password);
      msg.length = strlen(msg.value);
      sendBytes = send(sockfd, &msg, sizeof(msg), 0);
      if (sendBytes < 0)
      {
        printf("Send failed");
      }
      else
      {
        recvBytes = recv(sockfd, &msg, sizeof(msg), 0);
        if (recvBytes < 0)
        {
          printf("Receive failed");
        }
        else
        {
          if (msg.type == LOGIN_SUCCESS)
          {
            acc.login_status = 1;
            strcpy(acc.username, username);
            printf("Login success\n");
            show_menu_logged();
          }
          else
          {
            printf("Login failed\n");
          }
        }
      }
      break;
    case 2:
      printf("Đăng ký\n");
      break;
    case 3:
      printf("Trở về\n");
      show_menu_start = 1;
      break;
    case 4:
      printf("Thoát\n");
      exit(0);
    default:
      printf("Lựa chọn không hợp lệ\n");
      break;
    }
  }
  return 0;
}

int show_menu_logged()
{
  int show_menu_login = 0;
  while (!show_menu_login)
  {
    int choice = menu_logged();
    switch (choice)
    {
    case 1:
      printf("Thay đổi mật khẩu\n");
      break;
    case 2:
      printf("Choi Offline\n");
      break;
    case 3:
      printf("Choi Online\n");
      break;
    case 4:
      printf("Đăng xuất\n");
      acc.login_status = 0;
      show_menu_login = 1;
      break;
    default:
      printf("Lựa chọn không hợp lệ\n");
      break;
    }
  }
  return 0;
}