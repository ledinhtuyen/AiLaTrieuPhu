#include "client.h"

int main(int argc, char const *argv[])
{

  if (argc != 3)
  {
    printf("Usage: %s <Server IP> <Server Port>\n", argv[0]);
    return 1;
  }

  strcpy(serverIP, argv[1]);
  if (!validate_ip(serverIP))
  {
    printf("\nInvalid IP address\n");
    exit(-1);
  }
  strcpy(serverIP, argv[1]);
  
  if ((!is_number(argv[2])) || atoi(argv[2]) > 65535 || atoi(argv[2]) < 0)
  {
    printf("\nInvalid port number\n\n");
    exit(-1);
  }

  serverPort = atoi(argv[2]);

  printf(
      "            _    _                                               \n"
      "/'\\_/`\\ _  (_)  (_)  _                       _                 \n"
      "|     |(_) | |  | | (_)   _     ___     _ _ (_) _ __   __        \n"
      "| (_) || | | |  | | | | /'_`\\ /' _ `\\ /'_` )| |( '__)/'__`\\   \n"
      "| | | || | | |  | | | |( (_) )| ( ) |( (_| || || |  (  ___/      \n"
      "(_) (_)(_)(___)(___)(_)`\\___/'(_) (_)`\\__,_)(_)(_)  `\\____) \n\n");

  while (1)
  {
    choice1 = menu_start();
    switch (choice1)
    {
    case 1:
      if(connect_to_server()) show_menu_not_login();
      break;
    case 2:
      printf("\n***** How to play *****\n");
      printf("1. Chọn bắt đầu.\n");
      printf("2. Chọn chơi online hoặc chơi offline.\n");
      printf("3. Nhập A, B, C, D để chọn đáp án đúng;\n");
      break;
    case 3:
      printf("\n********* Credit *********\n");
      printf("1. Le Dinh Tuyen\n");
      printf("2. Pham Thi Anh\n");
      printf("3. Ha Van Duc\n");
      break;
    case 4:
      printf("Goodbye!\n");
      exit(0);
      break;
    default:
      printf("Chức năng chưa được cài đặt.\n");
      break;
    }
  }

  return 0;
}
