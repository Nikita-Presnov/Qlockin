#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QTime>
//#include <QtSerialPort/QSerialPort>
//#include <QtSerialPort/QSerialPortInfo>
#include <QFile>
#include <QThread>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_picker.h>
#include <qwt_symbol.h>
#include <QStandardItemModel>
// #include <time.h>

#include "lockin.h"

namespace Ui {
    class LockinAPP;
}

class LockinAPP : public QMainWindow
{
    Q_OBJECT

public:
    explicit LockinAPP(QWidget *parent = 0);

    ~LockinAPP();

private:
    Ui::LockinAPP *ui;
    QTimer *tmr;
    lockin *loc2;
    // QSerialPort *locin1;
    // QSerialPort *locin2;
    QwtPlotPicker *d_picker2;
    QwtPlotCurve *cruve_reference_signal;
    QwtPlotGrid *grid2;
    // QStandardItemModel* model;
    double *X;
    double *Y1;
    double *Y2;
    double *Timeval;
    // timespec time;
    // timespec starttime;
    QFile outputfile;
    QString dirname;
    int numberframes = 0;
    int progressframes = 0;
    int period;
    QThread lockinThread;

private slots:
    void on_start_botton_clicked();
    void on_stop_botton_clicked();
    void on_dir_button_clicked();
    void on_rescan_button_clicked();
    void updateval();
};

#endif // MAINWINDOW_H
