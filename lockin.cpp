#include "lockin.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h> 
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool screach_lockin(char *idn, char *locname)
{
//  if(strlen(locname)!=12)
//  {
//    printf("Incorrect size of array\n");
//    return 0;
//  }
  char idns[6] = {'*','I','D','N','?','\r'};
  char outx[6] = {'O','U','T','X','0','\r'};
  char comname[] = "/dev/ttyUSB0";
  char buff[64];
  int F_ID, number = 11;
  for(int i=0; i<10; i++)
  {
    F_ID = open(comname, O_RDWR | O_NOCTTY);// | O_NONBLOCK);
    if(F_ID == -1);
    else{
      struct termios options; 
      tcgetattr(F_ID, &options); 
      cfsetispeed(&options, B9600);
      options.c_cc[VTIME]    = 20;
      options.c_cc[VMIN]     = 0;

      options.c_cflag &= ~PARENB;
      options.c_cflag &= ~CSTOPB;
      options.c_cflag &= ~CSIZE;
      options.c_cflag |= CS8;

      options.c_lflag = 0;
      options.c_oflag &= ~OPOST;

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
      if(strstr(buff, idn) && strstr(buff,"Stanford_Research_Systems,SR830,"))
        {
          for(int j=0; j < PORT_NAME_LEN; j++)
            {
              locname[j] = comname[j];
            }
          return true;
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
  return false;
}

lockin::lockin()
{
}
bool lockin::init(char *comname)
{
  F_ID = open(comname, O_RDWR | O_NOCTTY);// | O_NONBLOCK);
  if(F_ID == -1)
    {
      return false;
    }
  struct termios options; 
  tcgetattr(F_ID, &options); 
  cfsetispeed(&options, B9600);
  options.c_cc[VTIME]    = 20; 
  options.c_cc[VMIN]     = 0;

  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;

  options.c_lflag = 0;
  options.c_oflag &= ~OPOST;

  options.c_iflag = 0;
  options.c_iflag &= ~ (INLCR | IGNCR | ICRNL);
  tcsetattr(F_ID, TCSANOW, &options);
  return true;
}

int lockin::send_command(char *command)
{
  return write(F_ID, command, strlen(command));
}

bool lockin::get_data()
{
  int i=0;
  bool f=true;
  int n = read(F_ID, &data[i], 1);
//   printf("%i\n", n);
  if(n == -1)
    return false;
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
  return true;
}
