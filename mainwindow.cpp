#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QMessageBox>
#include <qwt_picker_machine.h>
#include <malloc.h>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  char idn2[] = IDN2;//{'7','0','2','5','9'};
  char idn1[] = IDN1;//{'8','1','5','9','5'};
  ui->setupUi(this);
  ui->textBrowser->setReadOnly(true);
  ui->stop_botton->setEnabled(false);
  tmr = new QTimer(this);
  connect(tmr, SIGNAL(timeout()), this, SLOT(updateval()));

  dirname = QFileDialog::getExistingDirectory(this,
                                              tr("Open Directory"),
                                              "Documents");
  grid1 = new QwtPlotGrid();
  grid1->setMajorPen(QPen(Qt::lightGray, 1));
//  grid->setMinorPen(QPen(Qt::gray, 2 ));

  grid1->enableX(true);
  grid1->enableY(true);
  grid1->attach(ui->qwtPlot_refrence_r);
  grid2 = new QwtPlotGrid();
  grid2->setMajorPen(QPen(Qt::lightGray, 1));

  grid2->enableX(true);
  grid2->enableY(true);
  grid2->attach(ui->qwtPlot_refrence_signal);

  QwtPlotPicker *d_picker1 = new QwtPlotPicker(
      QwtPlot::xBottom, QwtPlot::yLeft, // ассоциация с осями
      QwtPlotPicker::CrossRubberBand, // стиль перпендикулярных линий
      QwtPicker::ActiveOnly, // включение/выключение
      ui->qwtPlot_refrence_r->canvas() ); // ассоциация с полем
  d_picker1->setRubberBandPen( QColor( Qt::red ) );
  d_picker1->setTrackerPen( QColor( Qt::black ) );
  d_picker1->setStateMachine( new QwtPickerDragPointMachine() );

  QwtPlotPicker *d_picker2 = new QwtPlotPicker(
      QwtPlot::xBottom, QwtPlot::yLeft, // ассоциация с осями
      QwtPlotPicker::CrossRubberBand, // стиль перпендикулярных линий
      QwtPicker::ActiveOnly, // включение/выключение
      ui->qwtPlot_refrence_signal->canvas() ); // ассоциация с полем
  d_picker2->setRubberBandPen( QColor( Qt::red ) );
  d_picker2->setTrackerPen( QColor( Qt::black ) );
  d_picker2->setStateMachine( new QwtPickerDragPointMachine() );

  cruve_refrence_r = new QwtPlotCurve();
  cruve_refrence_signal = new QwtPlotCurve();
  cruve_refrence_r->setPen(Qt::blue, 3);
  QwtSymbol *symbol1 = new QwtSymbol(QwtSymbol::Ellipse,
                                     QBrush( Qt::yellow ),
                                     QPen( Qt::red, 0 ),
                                     QSize( 4, 4 ) );
  cruve_refrence_r->setSymbol(symbol1);

  cruve_refrence_signal->setPen(Qt::green, 3);
  QwtSymbol *symbol2 = new QwtSymbol(QwtSymbol::Ellipse,
                                     QBrush( Qt::blue ),
                                     QPen( Qt::red, 0 ),
                                     QSize( 4, 4 ) );
  cruve_refrence_signal->setSymbol(symbol2);

  cruve_refrence_r->attach(ui->qwtPlot_refrence_r);
  cruve_refrence_signal->attach(ui->qwtPlot_refrence_signal);


  ui->qwtPlot_refrence_r->setAxisTitle(QwtPlot::yLeft, "R");
  ui->qwtPlot_refrence_r->setAxisTitle(QwtPlot::xBottom, "Refrence, 81595, mV");
  ui->qwtPlot_refrence_r->replot();

  ui->qwtPlot_refrence_signal->setAxisTitle(QwtPlot::yLeft, "Signal, 70259, mV");
  ui->qwtPlot_refrence_signal->setAxisTitle(QwtPlot::xBottom, "Refrence, 81595, mV");
  ui->qwtPlot_refrence_signal->replot();



  char name1[PORT_NAME_LEN];
  char name2[PORT_NAME_LEN];
  screach_lockin(idn1, name1);
  screach_lockin(idn2, name2);

  loc1 = new lockin();
  if(!loc1->init(name1))
    {
      QMessageBox msbox;
      msbox.setText("No locin with id 81595 for refrence.");
      msbox.exec();
    }
  loc2 = new lockin();
  if(!loc2->init(name2))
    {
      QMessageBox msbox;
      msbox.setText("No locin with id 70259 for signal.");
      msbox.exec();
    }
}

MainWindow::~MainWindow()
{
//  delete loc1;
//  delete loc2;
//  delete tmr;
//  delete cruve_refrence_r;
//  delete cruve_refrence_signal;
//  delete grid1;
//  delete grid2;
  delete ui;
}

void MainWindow::updateval()
{
  char outr[7] = {'O','U','T','R','?','1','\r'};
  loc1->send_command(outr);
  loc2->send_command(outr);
  if(!loc1->get_data())
    {
      QMessageBox msbox;
      msbox.setText("No connection with locin 81595 (refrence).");
      msbox.exec();
      progressframes = numberframes;
    }
  if(!loc2->get_data())
    {
      QMessageBox msbox;
      msbox.setText("No connection with locin 70259 (signal).");
      msbox.exec();
      progressframes = numberframes;
    }
  QTextStream outdata (&outputfile);

  QString qdata1 = QString(loc1->data);
  QString qdata2 = QString(loc2->data);
  X[progressframes] = qdata1.toDouble()*1000;
  Y1[progressframes] = qdata2.toDouble()*1000;
  if(X[progressframes]!=0)
    {
      Y2[progressframes] = Y1[progressframes]/X[progressframes];
      ui->textBrowser->insertPlainText(QString::number(progressframes));
      ui->textBrowser->insertPlainText(QString::fromStdString(" "));
      ui->textBrowser->insertPlainText(QString::number(X[progressframes], 'g', 3));
      ui->textBrowser->insertPlainText(QString::fromStdString(" "));
      ui->textBrowser->insertPlainText(QString::number(Y1[progressframes], 'g', 3));
      ui->textBrowser->insertPlainText(QString::fromStdString(" "));
      ui->textBrowser->insertPlainText(QString::number(Y2[progressframes], 'g', 3));
      ui->textBrowser->insertPlainText(QString::fromStdString("\n"));
      ui->textBrowser->moveCursor(QTextCursor::End);
      outdata << progressframes << '\t';
      outdata << X[progressframes] << '\t';
      outdata << Y1[progressframes] << '\t';
      outdata << Y2[progressframes] << '\n';

      cruve_refrence_r->setSamples(X,Y2,progressframes);
      cruve_refrence_signal->setSamples(X,Y1,progressframes);
      ui->qwtPlot_refrence_r->replot();
      ui->qwtPlot_refrence_signal->replot();
    }
  progressframes++;
  if (numberframes<=progressframes)
    {
      progressframes = 0;
      tmr->stop();
      ui->start_botton->setEnabled(true);
      ui->stop_botton->setEnabled(false);
      ui->dir_button->setEnabled(true);
      outputfile.close();
      free((void *)X);
//      fclose(file);
    }
}

void MainWindow::on_start_botton_clicked()
{
  QString filename = dirname;
  filename.append(QDateTime::currentDateTime().toString("/dd-MM-yyyy_HH-mm-ss"));
  filename.append(QString::fromStdString(".dat"));
//  qDebug() << filename;
  outputfile.setFileName(filename);
  if(!outputfile.open(QIODevice::WriteOnly))
    {
      QMessageBox msbox;
      msbox.setText("Error while touch file. No directory.");
      msbox.exec();
    }
  else
    {

      outputfile.write("n\trefrence\tsignal\tR\n");
      ui->textBrowser->clear();
      ui->textBrowser->insertPlainText(QString::fromStdString("number refrence signal R\n"));
      period = (int)((ui->period_value->value())*1000);
      tmr->setInterval(period);
      tmr->start(); // Запускаем таймер
      progressframes = 0;
      numberframes = ui->lineEdit->text().toInt();
      ui->start_botton->setEnabled(false);
      ui->stop_botton->setEnabled(true);
      ui->dir_button->setEnabled(false);
      X = (double *)malloc((3*numberframes)*sizeof(double));
      Y1 = X + numberframes;
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
  char idn2[] = IDN2;//{'7','0','2','5','9'};
  char idn1[] = IDN1;//{'8','1','5','9','5'};

  char name1[PORT_NAME_LEN];
  char name2[PORT_NAME_LEN];

  screach_lockin(idn1, name1);
  screach_lockin(idn2, name2);

  if(!loc1->init(name1))
    {
      QMessageBox msbox;
      msbox.setText("No locin with id 81595 for refrence.");
      msbox.exec();
    }

  if(!loc2->init(name2))
    {
      QMessageBox msbox;
      msbox.setText("No locin with id 70259 for signal.");
      msbox.exec();
    }
}
