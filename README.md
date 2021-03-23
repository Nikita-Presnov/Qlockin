# Qlockin
## RU
Небольшая улитка для запрашивания данных с SR830 LockInAmplifier по RS232.

Ситемные требования
ОС: семейства GNU Linux, порт под винду будет в мае.
2 свободных USB порта.
25-пиновый переходник нa с RS232 на USB 2 штуки.
qmake >=3.1
QT >=  5.9.5
qwt >= 6.1.3
G++ >= 7.3.0

Для использования вне нашей лаборатории измените maкросы IDN1 и IDN2 в locin.h на серийные номера ваших устройств перед компиляцией. 

## EN

A small app for requesting data from SR830 LockInAmplifier via RS232.

System requirements
OS: GNU Linux family, Windows port will be available in may.
2 free USB ports.
25-pin RS232 to USB adapter, 2 devices.

For use outside of our lab, change the IDN1 and IDN2 macros in locin.h to the serial numbers of your devices before compiling.

## requirements

qmake >=3.1
QT >=  5.9.5
qwt >= 6.1.3
G++ >= 7.3.0

## build
```bash
qmake
make -jN
```
