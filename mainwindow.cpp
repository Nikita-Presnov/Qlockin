#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTime>
#include <QMessageBox>
#include <math.h>
#include <malloc.h>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  char idn2[] = "70259";/*{'7','0','2','5','9'};*/
  char idn1[] = "81595";/*{'8','1','5','9','5'};*/
  ui->setupUi(this);
  ui->textBrowser->setReadOnly(true);
  ui->stop_botton->setEnabled(false);
  tmr = new QTimer(this);
  connect(tmr, SIGNAL(timeout()), this, SLOT(updateval()));

  dirname = QFileDialog::getExistingDirectory(this,
                                              tr("Open Directory"),
                                              "~/Documents");
  QwtPlotGrid *grid1 = new QwtPlotGrid();
  grid1->setMajorPen(QPen(Qt::lightGray, 1));
//  grid->setMinorPen(QPen(Qt::gray, 2 ));

  grid1->enableX(true);
  grid1->enableY(true);
//  grid->setXAxis();
  grid1->attach(ui->qwtPlot_opora_r);
  QwtPlotGrid *grid2 = new QwtPlotGrid();
  grid2->setMajorPen(QPen(Qt::lightGray, 1));
//  grid->setMinorPen(QPen(Qt::gray, 2 ));

  grid2->enableX(true);
  grid2->enableY(true);
  grid2->attach(ui->qwtPlot_opora_signal);

  // opora r
  cruve_opora_r = new QwtPlotCurve();
  cruve_opora_signal = new QwtPlotCurve();

  cruve_opora_r->setPen(Qt::blue, 6);
  QwtSymbol *symbol1 = new QwtSymbol( QwtSymbol::Ellipse,
                                     QBrush( Qt::yellow ),
                                     QPen( Qt::red, 2 ),
                                     QSize( 8, 8 ) );
  cruve_opora_r->setSymbol(symbol1);
//  data_opora_r = new QPolygonF;
//  cruve_opora_r->setSamples(data_opora_r);

  // opora signal
  cruve_opora_signal->setPen(Qt::green, 6);
  QwtSymbol *symbol2 = new QwtSymbol( QwtSymbol::Ellipse,
                                     QBrush( Qt::yellow ),
                                     QPen( Qt::red, 2 ),
                                     QSize( 8, 8 ) );
//  data_opora_signal = new QPolygonF;
  cruve_opora_signal->setSymbol(symbol2);
//  cruve_opora_signal->setSamples(data_opora_signal);

  cruve_opora_r->attach(ui->qwtPlot_opora_r);
  cruve_opora_signal->attach(ui->qwtPlot_opora_signal);

  ui->qwtPlot_opora_r->enableAxis(QwtPlot::yRight, true);
  ui->qwtPlot_opora_r->enableAxis(QwtPlot::xBottom, false);
  ui->qwtPlot_opora_r->enableAxis(QwtPlot::xTop, true);
  ui->qwtPlot_opora_r->setAxisTitle(QwtPlot::yLeft, "R");
  ui->qwtPlot_opora_r->setAxisTitle(QwtPlot::xTop, "Opora");
  ui->qwtPlot_opora_r->replot();

  ui->qwtPlot_opora_signal->enableAxis(QwtPlot::yRight, true);
  ui->qwtPlot_opora_signal->enableAxis(QwtPlot::xBottom, true);
  ui->qwtPlot_opora_signal->setAxisTitle(QwtPlot::yLeft, "Signal");
  ui->qwtPlot_opora_signal->setAxisTitle(QwtPlot::xBottom, "Opora");
  ui->qwtPlot_opora_signal->replot();



  char name1[PORT_NAME_LEN];
  char name2[PORT_NAME_LEN];
  screach_lockin(idn1, name1);
  screach_lockin(idn2, name2);

  loc1 = new lockin(name1);
  loc2 = new lockin(name2);
}

MainWindow::~MainWindow()
{
  delete loc1;
  delete loc2;
  delete ui;
}

void MainWindow::updateval()
{
  char outr[7] = {'O','U','T','R','?','1','\r'};
  loc1->get_data(outr);
  loc2->get_data(outr);
  QTextStream outdata (&outputfile);
  outdata << loc1->data << '\t' << loc1->data << '\n';
  // Данные для первой кривой
  double h = 8./(numberframes-1);
  for (int k = 0; k < numberframes; k++)
  {
    X1[k] = k*h;
    Y1[k] = cos(M_PI*X1[k]-5*M_PI/12+0.01*M_PI*double(progressframes));
  }
  // Данные для второй кривой
  h = 8./(numberframes-1);
  for (int k = 0; k < numberframes; k++)
  {
    X2[k] = k*h;
    Y2[k] = 0.7 * cos(8*M_PI*X2[k]+M_PI/9+0.01*M_PI*double(progressframes));
  }
  ui->textBrowser->insertPlainText(QString::number(progressframes));
  ui->textBrowser->insertPlainText(QString::fromStdString("\t"));
  ui->textBrowser->insertPlainText(QString::fromStdString(loc1->data));
  ui->textBrowser->insertPlainText(QString::fromStdString("\t"));
  ui->textBrowser->insertPlainText(QString::fromStdString(loc2->data));
  ui->textBrowser->insertPlainText(QString::fromStdString("\n"));
  ui->textBrowser->moveCursor(QTextCursor::End);
//  data_opora_r << QPointF( progressframes, progressframes );
//  cruve_opora_r->setSamples(data_opora_r);
//  data_opora_signal << QPointF( progressframes, progressframes );
//  cruve_opora_r->setData();
//  cruve_opora_signal->setData();
  cruve_opora_r->setSamples(X1,Y1,numberframes);
  cruve_opora_signal->setSamples(X2,Y2,numberframes);
  ui->qwtPlot_opora_r->replot();
  ui->qwtPlot_opora_signal->replot();
  progressframes++;
  if (numberframes<=progressframes)
    {
      progressframes = 0;
      tmr->stop();
      ui->start_botton->setEnabled(true);
      ui->stop_botton->setEnabled(false);
      outputfile.close();
      free((void *)X1);
      free((void *)X2);
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

      outputfile.write("opora_81595\tsignal_70259\n");
      ui->textBrowser->clear();
      ui->textBrowser->insertPlainText(QString::fromStdString("number\topora_81595\tsignal_70259\n"));
      period = (int)((ui->period_value->value())*1000);
      tmr->setInterval(period);
      tmr->start(); // Запускаем таймер
      progressframes = 0;
      numberframes = ui->lineEdit->text().toInt();
      ui->start_botton->setEnabled(false);
      ui->stop_botton->setEnabled(true);
      ui->dir_button->setEnabled(false);
      X1 = (double *)malloc((2*numberframes)*sizeof(double));
      Y1 = X1 + numberframes;
      X2 = (double *)malloc((2*numberframes)*sizeof(double));
      Y2 = X2 + numberframes;
//      data_opora_r = new QPolygonF;
//      cruve_opora_r->setSamples(data_opora_r);
    }
}

void MainWindow::on_stop_botton_clicked()
{
  tmr->stop();
  ui->start_botton->setEnabled(true);
  ui->stop_botton->setEnabled(false);
  ui->dir_button->setEnabled(true);
  free((void *)X1);
  free((void *)X2);
  outputfile.close();
}

void MainWindow::on_dir_button_clicked()
{
  dirname = QFileDialog::getExistingDirectory(this,
                                              tr("Open Directory"),
                                              "~/Documents");
}
