// #define OFFLINE_DEBUG 0
#define ENABLE_TIME 1

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QMessageBox>
#include <qwt_picker_machine.h>
#include <malloc.h>
#include <time.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    char idn2[] = IDN2; //{'7','0','2','5','9'};
    char idn1[] = IDN1; //{'8','1','5','9','5'};
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
    grid1 = new QwtPlotGrid();
    grid1->setMajorPen(QPen(Qt::lightGray, 1));

    grid1->enableX(true);
    grid1->enableY(true);
    grid1->attach(ui->qwtPlot_reference_r);
    grid2 = new QwtPlotGrid();
    grid2->setMajorPen(QPen(Qt::lightGray, 1));

    grid2->enableX(true);
    grid2->enableY(true);
    grid2->attach(ui->qwtPlot_reference_signal);

    QwtPlotPicker *d_picker1 = new QwtPlotPicker(
        QwtPlot::xBottom, QwtPlot::yLeft,
        QwtPlotPicker::CrossRubberBand,
        QwtPicker::ActiveOnly,
        ui->qwtPlot_reference_r->canvas());
    d_picker1->setRubberBandPen(QColor(Qt::red));
    d_picker1->setTrackerPen(QColor(Qt::black));
    d_picker1->setStateMachine(new QwtPickerDragPointMachine());

    QwtPlotPicker *d_picker2 = new QwtPlotPicker(
        QwtPlot::xBottom, QwtPlot::yLeft,
        QwtPlotPicker::CrossRubberBand,
        QwtPicker::ActiveOnly,
        ui->qwtPlot_reference_signal->canvas());
    d_picker2->setRubberBandPen(QColor(Qt::red));
    d_picker2->setTrackerPen(QColor(Qt::black));
    d_picker2->setStateMachine(new QwtPickerDragPointMachine());

    cruve_reference_r = new QwtPlotCurve();
    cruve_reference_signal = new QwtPlotCurve();
    cruve_reference_r->setPen(Qt::blue, 3);
    QwtSymbol *symbol1 = new QwtSymbol(QwtSymbol::Ellipse,
                                       QBrush(Qt::yellow),
                                       QPen(Qt::red, 0),
                                       QSize(4, 4));
    cruve_reference_r->setSymbol(symbol1);

    cruve_reference_signal->setPen(Qt::green, 3);
    QwtSymbol *symbol2 = new QwtSymbol(QwtSymbol::Ellipse,
                                       QBrush(Qt::blue),
                                       QPen(Qt::red, 0),
                                       QSize(4, 4));
    cruve_reference_signal->setSymbol(symbol2);

    cruve_reference_r->attach(ui->qwtPlot_reference_r);
    cruve_reference_signal->attach(ui->qwtPlot_reference_signal);

    ui->qwtPlot_reference_r->setAxisTitle(QwtPlot::yLeft, "R");
    ui->qwtPlot_reference_r->setAxisTitle(QwtPlot::xBottom, "Reference, 81595, mV");
    ui->qwtPlot_reference_r->replot();

    ui->qwtPlot_reference_signal->setAxisTitle(QwtPlot::yLeft, "Signal, 70259, mV");
    ui->qwtPlot_reference_signal->setAxisTitle(QwtPlot::xBottom, "Reference, 81595, mV");
    ui->qwtPlot_reference_signal->replot();

    char name1[PORT_NAME_LEN];
    char name2[PORT_NAME_LEN];
    loc2 = new lockin();
    loc1 = new lockin();
#ifndef OFFLINE_DEBUG
    screach_lockin(idn1, name1);
    screach_lockin(idn2, name2);

    // loc1 = new lockin();
    if (!loc1->init(name1))
    {
        QMessageBox msbox;
        msbox.setText("No locin with id 81595 for reference.");
        msbox.exec();
    }
    // loc2 = new lockin();
    if (!loc2->init(name2))
    {
        QMessageBox msbox;
        msbox.setText("No locin with id 70259 for signal.");
        msbox.exec();
    }
#endif
}

MainWindow::~MainWindow()
{
#ifndef OFFLINE_DEBUG
    loc1->close_lockin();
    loc2->close_lockin();
#endif
    // delete loc1;
    // delete loc2;
    // delete tmr;
    // delete cruve_reference_r;
    // delete cruve_reference_signal;
    // delete grid1;
    // delete grid2;
    delete ui;
}

void MainWindow::updateval()
{
    char outr[7] = {'O', 'U', 'T', 'R', '?', '1', '\r'};

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
    loc1->send_command(outr);
    loc2->send_command(outr);
    if (!loc1->get_data())
    {
        QMessageBox msbox;
        msbox.setText("No connection with locin 81595 (reference).");
        msbox.exec();
        progressframes = numberframes;
    }
    if (!loc2->get_data())
    {
        QMessageBox msbox;
        msbox.setText("No connection with locin 70259 (signal).");
        msbox.exec();
        progressframes = numberframes;
    }
#endif
#ifdef ENABLE_TIME
    clock_gettime(CLOCK_MONOTONIC_RAW, &meshtime);
    double timenow = (double)(meshtime.tv_sec - starttime.tv_sec) + (double)(meshtime.tv_nsec - starttime.tv_nsec) / BILLION;
#endif
    QTextStream outdata(&outputfile);

    QString qdata1 = QString(loc1->data);
    QString qdata2 = QString(loc2->data);
#ifdef ENABLE_TIME
    Timeval[progressframes] = timenow;
#endif
    // printf("%f\n", timenow);
    X[progressframes] = qdata1.toDouble() * 1000;
    Y1[progressframes] = qdata2.toDouble() * 1000;

    ui->tableWidget->insertRow(progressframes);
    ui->tableWidget->setItem(progressframes, 0, new QTableWidgetItem());
    ui->tableWidget->setItem(progressframes, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(progressframes, 2, new QTableWidgetItem());
    ui->tableWidget->setItem(progressframes, 3, new QTableWidgetItem());
    outdata << progressframes << '\t';
#ifdef ENABLE_TIME
    ui->tableWidget->item(progressframes, 0)->setText(QString::number(timenow, 'g', 3));
    outdata << timenow << '\t';
#endif
        ui->tableWidget->item(progressframes, 1)->setText(QString::number(X[progressframes], 'g', 3));
        outdata << X[progressframes] << '\t';
        ui->tableWidget->item(progressframes, 2)->setText(QString::number(Y1[progressframes], 'g', 3));
        outdata << Y1[progressframes] << '\t';
        if (X[progressframes] != 0)
        {
            Y2[progressframes] = Y1[progressframes] / X[progressframes];
            ui->tableWidget->item(progressframes, 3)->setText(QString::number(Y2[progressframes], 'g', 3));
            outdata << Y2[progressframes] << '\n';
        }
        else
        {
            if (progressframes != 0)
            {
                Y2[progressframes] = Y2[progressframes - 1];
            }
            else
            {
                Y2[progressframes] = 0;
            }
            ui->tableWidget->item(progressframes, 3)->setText(QString::fromStdString("inf"));
            outdata << "inf" << '\n';
        }
    ui->tableWidget->setCurrentCell(progressframes, 0);

    cruve_reference_r->setSamples(X, Y2, progressframes);
    cruve_reference_signal->setSamples(X, Y1, progressframes);
    ui->qwtPlot_reference_r->replot();
    ui->qwtPlot_reference_signal->replot();

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

void MainWindow::on_start_botton_clicked()
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
        outputfile.write("n\ttime\treference\tsignal\tR\n");
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
        X = (double *)malloc((4 * numberframes) * sizeof(double));
        Timeval = X + numberframes;
        Y1 = Timeval + numberframes;
        Y2 = Y1 + numberframes;
    }
}

void MainWindow::on_stop_botton_clicked()
{
    tmr->stop();
    ui->start_botton->setEnabled(true);
    ui->stop_botton->setEnabled(false);
    ui->dir_button->setEnabled(true);
    free((void *)X);
    outputfile.close();
}

void MainWindow::on_dir_button_clicked()
{
    dirname = QFileDialog::getExistingDirectory(this,
                                                tr("Open Directory"),
                                                "Documents");
}

void MainWindow::on_rescan_button_clicked()
{
#ifndef OFFLINE_DEBUG
    char idn2[] = IDN2; //{'7','0','2','5','9'};
    char idn1[] = IDN1; //{'8','1','5','9','5'};

    char name1[PORT_NAME_LEN];
    char name2[PORT_NAME_LEN];
    loc1->close_lockin();
    loc2->close_lockin();
    screach_lockin(idn1, name1);
    screach_lockin(idn2, name2);

    if (!loc1->init(name1))
    {
        QMessageBox msbox;
        msbox.setText("No locin with id 81595 for reference.");
        msbox.exec();
    }

    if (!loc2->init(name2))
    {
        QMessageBox msbox;
        msbox.setText("No locin with id 70259 for signal.");
        msbox.exec();
    }
#endif
}
