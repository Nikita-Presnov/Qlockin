// #include <QSerialPort>
#ifndef LOCKIN_H
#define LOCKIN_H

#include <QObject>

#define PORT_NAME_LEN 13
#define IDN1 "81595"
#define IDN2 "70259"
class threadlocin  : public QObject, public lockin
{
    Q_OBJECT
    // Свойство, управляющее работой потока
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    // Первое сообщение в объекте
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
    
    bool m_running;
    QString m_message;
    int count; 
public:
    explicit threadlocin(QObject *parent = 0);
    bool running() const;
    QString message() const;
    // QSerialPort *serialPort;
    // QString portName;
signals:
    void finished(); // Сигнал, по которому будем завершать поток, после завершения метода run
    void runningChanged(bool running);
    void messageChanged(QString message);
    void sendMessage(QString message);

public slots:
    void run(); // Метод с полезной нагрузкой, который может выполняться в цикле
    void setRunning(bool running);
    void setMessage(QString message);
};

bool screach_lockin(char *idn, char *locname);

class lockin
{
public:
    lockin();
    bool init(char *comname);
    bool get_data(); // char *command);
    int send_command(char *command, int comlen);
    void close_lockin();
    int F_ID;
    char data[20];
};

#endif // LOCKIN_H
