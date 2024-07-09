#include "lockin.h"
threadlockin::threadlockin(QObject *parent) : QObject(parent), m_message("")
{

}

bool threadlockin::running() const
{
    return m_running;
}
 
QString threadlockin::message() const
{
    return m_message;
}
 
// Самый важный метод, в котором будет выполняться "полезная" работа объекта
void threadlockin::run()
{
    count = 0;
    // Переменная m_running отвечает за работу объекта в потоке.
    // При значении false работа завершается
    while (m_running)
    {
        count++;
        emit sendMessage(m_message); // Высылаем данные, которые будут передаваться в другой поток
        // qDebug() << m_message << " " << m_message_2 << " " << count;
    }
    emit finished();
}
 
void threadlockin::setRunning(bool running)
{
    if (m_running == running)
        return;
 
    m_running = running;
    emit runningChanged(running);
}
 
void threadlockin::setMessage(QString message)
{
    if (m_message == message)
        return;
 
    m_message = message;
    emit messageChanged(message);
}
 