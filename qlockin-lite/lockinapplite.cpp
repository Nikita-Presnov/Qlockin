// #define OFFLINE_DEBUG 0
#define ENABLE_TIME 1

#include "lockinapplite.h"
#include "ui_lockinapplite.h"
#include <QFileDialog>
#include <QTime>
#include <QMessageBox>
#include <qwt_picker_machine.h>
#include <malloc.h>
#include <time.h>
#include <string.h>

LockinAPPlite::LockinAPPlite(QWidget *parent) : QMainWindow(parent),
                                                ui(new Ui::LockinAPPlite)
{
    // char idn2[] = IDN2; //{'7','0','2','5','9'};
    // char idn1[] = IDN1; //{'8','1','5','9','5'};
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // QStandardItemModel* model=  new QStandardItemModel(0, 4);
    // model->setHeaderData(0, Qt::Horizontal, "Time");
    // model->setHeaderData(0, Qt::Horizontal, "reference");
    // model->setHeaderData(0, Qt::Horizontal, "signal");
    // model->setHeaderData(0, Qt::Horizontal, "R");
    ui->stop_botton->setEnabled(false);
    tmr = new QTimer(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateval()));

    dirname = QFileDialog::getExistingDirectory(this,
                                                tr("Open Directory"),
                                                "Documents");
    grid2 = new QwtPlotGrid();
    grid2->setMajorPen(QPen(Qt::lightGray, 1));
    grid2->enableX(true);
    grid2->enableY(true);
    grid2->attach(ui->qwtPlot_reference_signal);

    QwtPlotPicker *d_picker2 = new QwtPlotPicker(
        QwtPlot::xBottom, QwtPlot::yLeft,
        QwtPlotPicker::CrossRubberBand,
        QwtPicker::ActiveOnly,
        ui->qwtPlot_reference_signal->canvas());
    d_picker2->setRubberBandPen(QColor(Qt::red));
    d_picker2->setTrackerPen(QColor(Qt::black));
    d_picker2->setStateMachine(new QwtPickerDragPointMachine());

    cruve_reference_signal = new QwtPlotCurve();
    cruve_reference_signal->setPen(Qt::green, 3);
    QwtSymbol *symbol2 = new QwtSymbol(QwtSymbol::Ellipse,
                                       QBrush(Qt::blue),
                                       QPen(Qt::red, 0),
                                       QSize(4, 4));
    cruve_reference_signal->setSymbol(symbol2);

    cruve_reference_signal->attach(ui->qwtPlot_reference_signal);

    ui->qwtPlot_reference_signal->setAxisTitle(QwtPlot::yLeft, "Signal, mV");
    ui->qwtPlot_reference_signal->setAxisTitle(QwtPlot::xBottom, "Time, s");
    ui->qwtPlot_reference_signal->replot();

    char name1[PORT_NAME_LEN];
    char name2[PORT_NAME_LEN];
    loc2 = new lockin();
    // loc1 = new lockin();
    QString idn2 = ui->lockin_ser->text();
#ifndef OFFLINE_DEBUG
    screach_lockin(idn2.toUtf8().data(), name2);
    if (!loc2->init(idn2.toUtf8().data(), name2))
    {
        QMessageBox msbox;
        QString text = QString("No locin with id %1 for signal.").arg(idn2);
        msbox.setText(text);
        msbox.exec();
    }
#endif
}

LockinAPPlite::~LockinAPPlite()
{
#ifndef OFFLINE_DEBUG
    loc2->close_lockin();
#endif
    delete ui;
}

void LockinAPPlite::updateval()
{
    char outr[7] = {'O', 'U', 'T', 'P', '?', '1', '\r'};

#ifdef ENABLE_TIME
#define BILLION 1000000000.0
    timespec meshtime;
    static timespec starttime;
    if (progressframes == 0)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &starttime);
    }
#endif

#ifndef OFFLINE_DEBUG
    loc2->send_command(outr, 7);
    if (!loc2->get_data())
    {
        QMessageBox msbox;
        QString text = QString("No connection with locin %1 (signal).").arg(loc2->id_n);
        msbox.setText(text);
        msbox.exec();
        progressframes = numberframes;
    }
#endif
#ifdef ENABLE_TIME
    clock_gettime(CLOCK_MONOTONIC_RAW, &meshtime);
    double timenow = (double)(meshtime.tv_sec - starttime.tv_sec) + (double)(meshtime.tv_nsec - starttime.tv_nsec) / BILLION;
#endif
    QTextStream outdata(&outputfile);

    QString qdata2 = QString(loc2->data);
#ifdef ENABLE_TIME
    // Timeval[progressframes] = timenow;
#endif
    // printf("%f\n", timenow);
    X[progressframes] = timenow;
    Y1[progressframes] = qdata2.toDouble() * 1000;

    ui->tableWidget->insertRow(progressframes);
    ui->tableWidget->setItem(progressframes, 0, new QTableWidgetItem());
    ui->tableWidget->setItem(progressframes, 1, new QTableWidgetItem());
    outdata << progressframes << '\t';
#ifdef ENABLE_TIME
    ui->tableWidget->item(progressframes, 0)->setText(QString::number(timenow, 'g', 3));
    outdata << timenow << '\t';
#endif
    ui->tableWidget->item(progressframes, 1)->setText(QString::number(Y1[progressframes], 'g', 3));
    outdata << Y1[progressframes] << '\n';
    ui->tableWidget->setCurrentCell(progressframes, 0);
    if (progressframes != 0)
    {
        cruve_reference_signal->setSamples(&X[1], &Y1[1], progressframes - 1);
        ui->qwtPlot_reference_signal->replot();
    }
    ui->progresslcdNumber->display(progressframes);
    progressframes++;
    if (numberframes <= progressframes)
    {
        progressframes = 0;
        tmr->stop();
        ui->start_botton->setEnabled(true);
        ui->stop_botton->setEnabled(false);
        ui->dir_button->setEnabled(true);
        outputfile.close();
        free((void *)X);
    }
}

void LockinAPPlite::on_start_botton_clicked()
{
    QString filename = dirname;
    filename.append(QString::fromStdString("/"));
    filename.append(ui->prename->text());
    filename.append(QDateTime::currentDateTime().toString("_dd-MM-yyyy_HH-mm-ss"));
    filename.append(QString::fromStdString(".csv"));
    //   qDebug() << filename;
    outputfile.setFileName(filename);
    if (!outputfile.open(QIODevice::WriteOnly))
    {
        QMessageBox msbox;
        msbox.setText("Error while touch file. No directory.");
        msbox.exec();
    }
    else
    {
        outputfile.write("n\ttime\tsignal\n");
        while (ui->tableWidget->rowCount() > 0)
        {
            ui->tableWidget->removeRow(0);
        }
        period = (int)((ui->period_value->value()) * 1000);
        tmr->setInterval(period);
        tmr->start();
        progressframes = 0;
        numberframes = ui->numer_frame->text().toInt();
        ui->start_botton->setEnabled(false);
        ui->stop_botton->setEnabled(true);
        ui->dir_button->setEnabled(false);
        X = (double *)malloc((2 * numberframes) * sizeof(double));
        // Timeval = X + numberframes;
        Y1 = X + numberframes;
        // Y2 = Y1 + numberframes;
    }
}

void LockinAPPlite::on_stop_botton_clicked()
{
    tmr->stop();
    ui->start_botton->setEnabled(true);
    ui->stop_botton->setEnabled(false);
    ui->dir_button->setEnabled(true);
    free((void *)X);
    outputfile.close();
}

void LockinAPPlite::on_dir_button_clicked()
{
    dirname = QFileDialog::getExistingDirectory(this,
                                                tr("Open Directory"),
                                                "Documents");
}

void LockinAPPlite::on_rescan_button_clicked()
{
#ifndef OFFLINE_DEBUG
    // char idn2[] = IDN2; //{'7','0','2','5','9'};
    QString idn2 = ui->lockin_ser->text();

    char name2[PORT_NAME_LEN];
    loc2->close_lockin();
    screach_lockin(idn2.toUtf8().data(), name2);

    if (!loc2->init(idn2.toUtf8().data(), name2))
    {
        QMessageBox msbox;
        QString text = QString("No locin with id %1 for signal.").arg(idn2);
        msbox.setText(text);
        msbox.exec();
    }
#endif
}
