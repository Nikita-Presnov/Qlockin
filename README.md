# Qlockin
## RU
Небольшая программа для запрашивания данных с SR830 LockInAmplifier по GPIP.

Ситемные требования
* ОС: семейства GNU Linux.
* 2 свободных USB порта.
* 25-пиновый переходник нa с RS232 на USB 2 штуки.
* qmake >=3.1 или cmake >= 3.0
* QT >=  5.9.5
* qwt >= 6.1.3
* gcc >= 7.3.0

Для использования вне нашей лаборатории измените мaкросы IDN1 и IDN2 в locin.h на серийные номера ваших устройств перед компиляцией. 

Порт под винду ~~будет в мае после дождичка в четверг когда рак на горе свиснет~~ пока не будет так как решено перенести программу на одноплатный компьютер.

## Сборка
```bash
git clone https://github.com/Nikita-Presnov/Qlockin.git
cd Qlockin
mkdir build
cd build
cmake ..
make -jN
```
## Обновление 
```bash
ssh laborant@***.***.*.**
cd Qlockin
git pull
mkdir build
cd build
cmake ..
make -jN
```