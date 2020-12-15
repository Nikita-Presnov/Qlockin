#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  char idn2[] = "70259";/*{'7','0','2','5','9'};*/
  char idn1[] = "81595";/*{'8','1','5','9','5'};*/
  ui->setupUi(this);
  ui->lineEdit->setText("400");
  ui->textBrowser->setReadOnly(true);
  ui->stop_botton->setEnabled(false);
  ui->period_value->setValue(1.0);
  tmr = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
  connect(tmr, SIGNAL(timeout()), this, SLOT(updateval())); // Подключаем сигнал таймера к нашему слоту

  char name1[PORT_NAME_LEN];
  char name2[PORT_NAME_LEN];
  screach_lockin(idn1, name1);
  screach_lockin(idn2, name2);

  loc1 = new lockin(name1);
  loc2 = new lockin(name2);
}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::updateval()
{
  char outr[7] = {'O','U','T','R','?','1','\r'};
  loc1->get_data(outr);
  loc2->get_data(outr);
  fprintf(file, "%s\t%s\n", loc1->data, loc1->data);
  ui->textBrowser->insertPlainText(QString::number(progressframes));
  ui->textBrowser->insertPlainText(QString::fromStdString("\t"));

  ui->textBrowser->insertPlainText(QString::fromStdString(loc1->data));
  ui->textBrowser->insertPlainText(QString::fromStdString("\t"));
  ui->textBrowser->insertPlainText(QString::fromStdString(loc2->data));
  ui->textBrowser->insertPlainText(QString::fromStdString("\n"));

  progressframes++;
  if (numberframes<=progressframes)
    {
      progressframes = 0;
      tmr->stop();
      ui->start_botton->setEnabled(true);
      ui->stop_botton->setEnabled(false);
      fclose(file);
    }
}
void MainWindow::on_start_botton_clicked()
{
  struct tm* ptr;

  time_t lt;

  lt = time(NULL);

  ptr = gmtime(&lt);

  char* prefirst = asctime(ptr);
  prefirst[strlen(prefirst)-1]=0;
  prefirst[13] = '-';
  prefirst[16] = '-';

  const char* first = prefirst; // const явно указывает, что такие данные менять нельзя
  const char* second = ".dat";
  char name[64]={0};
  strcat(name, first);
  strcat(name, second);

  file = fopen(name, "w");
  fprintf(file,"opora_81595\tsignal_70259\n");

  ui->textBrowser->clear();
  ui->textBrowser->insertPlainText(QString::fromStdString("number\topora_81595\tsignal_70259\n"));
  period = (int)((ui->period_value->value())*1000);
  tmr->setInterval(period);
  tmr->start(); // Запускаем таймер
  progressframes = 0;
  numberframes = ui->lineEdit->text().toInt();
  ui->start_botton->setEnabled(false);
  ui->stop_botton->setEnabled(true);

}
void MainWindow::on_stop_botton_clicked()
{
  tmr->stop();
  ui->start_botton->setEnabled(true);
  ui->stop_botton->setEnabled(false);
  fclose(file);
}
