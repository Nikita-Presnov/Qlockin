#include "lockin.h"
#ifdef QTSERIAL
#include <QSerialPort>
#include <QSerialPortInfo>

/*!
 * @brief Search SR830 with the given ID and write the name of its copy-port in locname.
 * @param idn: lock-in ID.
 * @param locname: string to write lock-in COM port.
 * @return Screach status.
 */
bool screach_lockin(char *idn, char *locname)
{
    if(strlen(locname)!=12)
    {
        printf("Incorrect size of array\n");
        return 0;
    }
    char idns[6] = {'*', 'I', 'D', 'N', '?', '\r'};
    char outx[6] = {'O', 'U', 'T', 'X', '0', '\r'};
    char comname[] = "/dev/ttyUSB0";
    char buff[64];
    int F_ID, number = 11;
    for (int i = 0; i < 10; i++)
    {
        if (true)
            ;
        else
        {
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
    }
    return false;
}

lockin::lockin()
{
    this->serialPort = new QSerialPort();

    // this->portName = portName;

    //  this->serialPort->setPortName(portName);
    this->serialPort->setBaudRate(QSerialPort::Baud9600);
    this->serialPort->setDataBits(QSerialPort::Data8);
    this->serialPort->setStopBits(QSerialPort::OneStop);
    this->serialPort->setParity(QSerialPort::NoParity);
    this->serialPort->setFlowControl(QSerialPort::NoFlowControl);
}
lockin::~lockin()
{
    this->serialPort->close();
}
/*!
 * @brief Opening of the com port.
 *        Use it after screach_lockin().
 * @param comname: string with locin comport.
 * @return Status of connection.
 */
bool lockin::init(char *comname)
{
    return true;
}

/*!
 * @brief Sending a command to the SR830.
 *        Returns the number of bytes sent if sending was successful.
 * @param command: string with command to sending. Send OUTR?1\\r to get data from first display.
 * @return Number of bytes sent . If -1, then sending failed.
 */
int lockin::send_command(char *command)
{
    // return write(F_ID, command, strlen(command));
}

/*!
 * Reading data from a buffer into lockin::data.
 * @return Is data read? true or false.
 */
bool lockin::get_data()
{
    return true;
}

void lockin::close_lockin()
{
    // close(F_ID);
    this->serialPort->close();
}
#endif //QTSERIAL