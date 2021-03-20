#include "lockin.h"
#include <termios.h>
#include <unistd.h>  /* Объявления стандартных функций UNIX */
#include <fcntl.h>   /* Объявления управления файлами */
#include <errno.h>   /* Объявления кодов ошибок */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int screach_lockin(char *idn, char *locname)
{
//  if(strlen(locname)!=12)
//  {
//    printf("Incorrect size of array\n");
//    return 0;
//  }
  char idns[6] = {'*','I','D','N','?','\r'};
  char outx[6] = {'O','U','T','X','0','\r'};
  char comname[] = "/dev/ttyUSB0";/*{'/','d','e','v','/','t','t','y','U','S','B','0'};*/
//  comname[11]=0;
  char buff[64];
  int F_ID, number = 11;
  for(int i=0;i<10;i++)
  {
    F_ID = open(comname, O_RDWR | O_NOCTTY);// | O_NONBLOCK);
    if(F_ID == -1)
    {
       printf("It is not correct port\r");
      }else{
    struct termios options; /*структура для установки порта*/
    tcgetattr(F_ID, &options); /*читает пораметры порта*/
    cfsetispeed(&options, B9600); /*установка скорости порта*/
    cfsetospeed(&options, B9600); /*установка скорости порта*/
    options.c_cc[VTIME]    = 20; /*Время ожидания байта 20*0.1 = 2 секунды */
    options.c_cc[VMIN]     = 0; /*минимальное число байт для чтения*/

    options.c_cflag &= ~PARENB; /*бит четности не используется*/
    options.c_cflag &= ~CSTOPB; /*1 стоп бит */
    options.c_cflag &= ~CSIZE;  /*Размер байта*/
    options.c_cflag |= CS8;  /*8 бит*/

    options.c_lflag = 0;
    options.c_oflag &= ~OPOST; /*Обязательно отключить постобработку*/

    options.c_iflag = 0;
    options.c_iflag &= ~ (INLCR | IGNCR | ICRNL);



    tcsetattr(F_ID, TCSANOW, &options);
    int n = write(F_ID, outx, 6);
    n = write(F_ID, idns, 6);
    for (int i=0 ;n!=0 && i<64;i++)
    {
      n = read(F_ID, &buff[i], 1);
      if(buff[i] == '\r')
        break;
    }
    close(F_ID);
    if(strstr(buff, idn) &&
       strstr(buff,"Stanford_Research_Systems,SR830,"))
    {
      for(int j=0; j < PORT_NAME_LEN; j++)
        {
          locname[j] = comname[j];
        }
      return 1;
    }
      }
    comname[number]++;
//    if(comname[number]>'9' && number == 10)
//    {
//      comname[number] = '1';
//      number++;
//      comname[number] = '0';
//    }
//    else if(comname[number]>'9')
//    {
//      comname[number] = '0';
//      comname[number-1]++;
//    }
  }

  printf("No locins with this id\n");
  return 0;
}

lockin::lockin(char *comname)
{
  F_ID = open(comname, O_RDWR | O_NOCTTY);// | O_NONBLOCK);
  if(F_ID == -1)
  {
     printf("connection lost\n");
  }
  struct termios options; /*структура для установки порта*/
  tcgetattr(F_ID, &options); /*читает пораметры порта*/
  cfsetispeed(&options, B9600); /*установка скорости порта*/
  cfsetospeed(&options, B9600); /*установка скорости порта*/
  options.c_cc[VTIME]    = 20; /*Время ожидания байта 20*0.1 = 2 секунды */
  options.c_cc[VMIN]     = 0; /*минимальное число байт для чтения*/

  options.c_cflag &= ~PARENB; /*бит четности не используется*/
  options.c_cflag &= ~CSTOPB; /*1 стоп бит */
  options.c_cflag &= ~CSIZE;  /*Размер байта*/
  options.c_cflag |= CS8;  /*8 бит*/

  options.c_lflag = 0;
  options.c_oflag &= ~OPOST; /*Обязательно отключить постобработку*/

  options.c_iflag = 0;
  options.c_iflag &= ~ (INLCR | IGNCR | ICRNL);
  tcsetattr(F_ID, TCSANOW, &options);
}
int lockin::send_command(char *command)
{
  return write(F_ID, command, strlen(command));
}
int lockin::get_data(char *command)
{
  int n = write(F_ID, command, strlen(command));
  int i=0;
  bool f=true;
  n = read(F_ID, &data[i], 1);
  i++;
  for (;i<20;i++)
  {
    if(data[i-1]!=13 && f && n!=0)
    {
        n = read(F_ID, &data[i], 1);
    }
    else if(data[i-1]==13)//find '\r'
    {
      data[i] = 0;
      data[i-1]=0;
      f = false;
    }
    else
    {
      data[i] = 0;
    }
  }
  return 0;
}
