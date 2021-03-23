#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QTime>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QFile>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_picker.h>
#include <qwt_symbol.h>


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
//  QSerialPort *locin1;
//  QSerialPort *locin2;
  QwtPlotPicker *d_picker1;
  QwtPlotPicker *d_picker2;
  QwtPlotCurve *cruve_refrence_r;
  QwtPlotCurve *cruve_refrence_signal;
  QwtPlotGrid *grid1;
  QwtPlotGrid *grid2;
  double *X;
  double *Y1;
  double *Y2;
  QFile outputfile;
  QString dirname;
  int numberframes = 0;
  int progressframes = 0;
  int period;

private slots:
  void on_start_botton_clicked();
  void on_stop_botton_clicked();
  void on_dir_button_clicked();
  void on_rescan_button_clicked();
  void updateval();
};

#endif // MAINWINDOW_H
