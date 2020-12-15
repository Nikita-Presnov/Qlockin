#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include "lockin.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);

  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QTimer *tmr; //Адресная переменная таймера
  lockin *loc1;
  lockin *loc2;
  FILE *file;
  int numberframes = 0;
  int progressframes = 0;
  int period;

private slots:
  void on_start_botton_clicked();
  void on_stop_botton_clicked();
  void updateval();
};

#endif // MAINWINDOW_H
