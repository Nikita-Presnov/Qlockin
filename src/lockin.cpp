#include "lockin.h"

#ifdef __MINGW32__
#include <windows.h>
#endif

#ifdef __linux
#include <stdio.h>
#include <unistd.h>  /* Объявления стандартных функций UNIX */
#include <fcntl.h>   /* Объявления управления файлами */
#include <errno.h>   /* Объявления кодов ошибок */
#include <termios.h> /* Объявления управления POSIX-терминалом */
#include <string.h>
#include <stdlib.h>

/*!
 * @brief Search SR830 with the given ID and write the name of its copy-port in locname.
 * @param idn: lock-in ID.
 * @param locname: string to write lock-in COM port.
 * @return Screach status.
 */
bool screach_lockin(char *idn, char *locname)
{
    //  if(strlen(locname)!=12)
    //  {
    //    printf("Incorrect size of array\n");
    //    return 0;
    //  }
    char idns[6] = {'*', 'I', 'D', 'N', '?', '\r'};
    char outx[6] = {'O', 'U', 'T', 'X', '0', '\r'};
    char comname[] = "/dev/ttyUSB0";
    char buff[64];
    int F_ID = -1, number = 11;
    for (int i = 0; i < 10; i++)
    {
        F_ID = open(comname, O_RDWR | O_NOCTTY); // | O_NONBLOCK);
        if (F_ID == -1)
            ;
        else
        {
            struct termios options;
            tcgetattr(F_ID, &options);
            cfsetispeed(&options, B9600);
            options.c_cc[VTIME] = 20;
            options.c_cc[VMIN] = 0;

            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
            options.c_cflag &= ~CSIZE;
            options.c_cflag |= CS8;

            options.c_lflag = 0;
            options.c_oflag &= ~OPOST;

            options.c_iflag = 0;
            options.c_iflag &= ~(INLCR | IGNCR | ICRNL);

            tcsetattr(F_ID, TCSANOW, &options);
            int n = write(F_ID, outx, 6);
            tcdrain(F_ID);
            n = write(F_ID, idns, 6);
            tcdrain(F_ID);
            for (int i = 0; n != 0 && i < 64; i++)
            {
                n = read(F_ID, &buff[i], 1);
                if (buff[i] == '\r')
                    break;
            }
            close(F_ID);
            if (strstr(buff, idn) && strstr(buff, "Stanford_Research_Systems,SR830,"))
            {
                for (int j = 0; j < PORT_NAME_LEN; j++)
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

/*!
 * @brief Opening of the com port.
 *        Use it after screach_lockin().
 * @param comname: string with locin comport.
 * @return Status of connection.
 */
bool lockin::init(char *comname)
{
    F_ID = open(comname, O_RDWR); // | O_NOCTTY | O_NONBLOCK);
    if (F_ID == -1)
    {
        return false;
    }
    struct termios options;
    tcgetattr(F_ID, &options);
    cfsetispeed(&options, B9600);
    options.c_cc[VTIME] = 20;
    options.c_cc[VMIN] = 0;

    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    options.c_lflag = 0;
    options.c_oflag &= ~OPOST;

    options.c_iflag = 0;
    options.c_iflag &= ~(INLCR | IGNCR | ICRNL);
    tcsetattr(F_ID, TCSANOW, &options);
    return true;
}

/*!
 * @brief Sending a command to the SR830.
 *        Returns the number of bytes sent if sending was successful.
 * @param command: string with command to sending. Send OUTR?1\\r to get data from first display.
 * @return Number of bytes sent . If -1, then sending failed.
 */
int lockin::send_command(char *command, int comlen)
{
    int n = write(F_ID, command, comlen);
    tcdrain(F_ID);
    return n;
}

/*!
 * Reading data from a buffer into lockin::data.
 * @return Is data read? true or false.
 */
bool lockin::get_data()
{
    int i = 0;
    bool f = true;
    char buff[20];
    int n = read(F_ID, &buff[i], 1);
    // printf("%i\n", n);
    if (n == -1)
    {
        close(F_ID);
        return false;
    }
    i++;
    for (; i < 20; i++)
    {
        if (buff[i - 1] != 13 && f && n != 0)
        {
            n = read(F_ID, &buff[i], 1);
        }
        else if (buff[i - 1] == 13) // find '\r'
        {
            buff[i] = 0;
            buff[i - 1] = 0;
            f = false;
        }
        else
        {
            buff[i] = 0;
        }
    }
    strcpy(data, buff);
    return true;
}

void lockin::close_lockin()
{
    close(F_ID);
}
#endif

#ifdef __MINGW32__
bool screach_lockin(char *idn, char *locname)
{
    HANDLE hSerial = CreateFile("COM1", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE)
    {
        printf("Error opening port\r\n");
        return -1;
    }
    CloseHandle(hSerial);
}
#endif