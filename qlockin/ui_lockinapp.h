/********************************************************************************
** Form generated from reading UI file 'lockinapp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKINAPP_H
#define UI_LOCKINAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_LockinAPP
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QwtPlot *qwtPlot_reference_signal;
    QGridLayout *gridLayout;
    QLabel *label;
    QLCDNumber *progresslcdNumber;
    QLabel *period_label;
    QLabel *label_2;
    QDoubleSpinBox *period_value;
    QLabel *label_3;
    QPushButton *dir_button;
    QLineEdit *numer_frame;
    QSpacerItem *horizontalSpacer;
    QLineEdit *prename;
    QComboBox *comboBox;
    QLabel *label_4;
    QPushButton *rescan_button;
    QPushButton *start_botton;
    QPushButton *stop_botton;
    QTableWidget *tableWidget;
    QwtPlot *qwtPlot_reference_r;

    void setupUi(QMainWindow *LockinAPP)
    {
        if (LockinAPP->objectName().isEmpty())
            LockinAPP->setObjectName(QString::fromUtf8("LockinAPP"));
        LockinAPP->resize(1176, 544);
        QFont font;
        font.setPointSize(14);
        LockinAPP->setFont(font);
        centralWidget = new QWidget(LockinAPP);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        qwtPlot_reference_signal = new QwtPlot(centralWidget);
        qwtPlot_reference_signal->setObjectName(QString::fromUtf8("qwtPlot_reference_signal"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qwtPlot_reference_signal->sizePolicy().hasHeightForWidth());
        qwtPlot_reference_signal->setSizePolicy(sizePolicy);
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        qwtPlot_reference_signal->setCanvasBackground(brush);

        gridLayout_2->addWidget(qwtPlot_reference_signal, 3, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        progresslcdNumber = new QLCDNumber(centralWidget);
        progresslcdNumber->setObjectName(QString::fromUtf8("progresslcdNumber"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(progresslcdNumber->sizePolicy().hasHeightForWidth());
        progresslcdNumber->setSizePolicy(sizePolicy2);
        progresslcdNumber->setMinimumSize(QSize(0, 36));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setWeight(50);
        progresslcdNumber->setFont(font1);
        progresslcdNumber->setDigitCount(5);
        progresslcdNumber->setProperty("intValue", QVariant(0));

        gridLayout->addWidget(progresslcdNumber, 1, 3, 1, 1);

        period_label = new QLabel(centralWidget);
        period_label->setObjectName(QString::fromUtf8("period_label"));
        sizePolicy1.setHeightForWidth(period_label->sizePolicy().hasHeightForWidth());
        period_label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(period_label, 0, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        period_value = new QDoubleSpinBox(centralWidget);
        period_value->setObjectName(QString::fromUtf8("period_value"));
        period_value->setSingleStep(0.100000000000000);
        period_value->setValue(0.200000000000000);

        gridLayout->addWidget(period_value, 1, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 3, 1, 1);

        dir_button = new QPushButton(centralWidget);
        dir_button->setObjectName(QString::fromUtf8("dir_button"));

        gridLayout->addWidget(dir_button, 1, 6, 1, 1);

        numer_frame = new QLineEdit(centralWidget);
        numer_frame->setObjectName(QString::fromUtf8("numer_frame"));
        sizePolicy2.setHeightForWidth(numer_frame->sizePolicy().hasHeightForWidth());
        numer_frame->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(numer_frame, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 5, 1, 1);

        prename = new QLineEdit(centralWidget);
        prename->setObjectName(QString::fromUtf8("prename"));
        sizePolicy2.setHeightForWidth(prename->sizePolicy().hasHeightForWidth());
        prename->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(prename, 1, 2, 1, 1);

        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEnabled(false);

        gridLayout->addWidget(comboBox, 1, 4, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 4, 1, 1);

        rescan_button = new QPushButton(centralWidget);
        rescan_button->setObjectName(QString::fromUtf8("rescan_button"));

        gridLayout->addWidget(rescan_button, 0, 6, 1, 1);

        start_botton = new QPushButton(centralWidget);
        start_botton->setObjectName(QString::fromUtf8("start_botton"));
        sizePolicy2.setHeightForWidth(start_botton->sizePolicy().hasHeightForWidth());
        start_botton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(start_botton, 0, 7, 1, 1);

        stop_botton = new QPushButton(centralWidget);
        stop_botton->setObjectName(QString::fromUtf8("stop_botton"));
        sizePolicy2.setHeightForWidth(stop_botton->sizePolicy().hasHeightForWidth());
        stop_botton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(stop_botton, 1, 7, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 2);

        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy3);
        tableWidget->setMinimumSize(QSize(500, 0));
        tableWidget->setRowCount(1);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setMinimumSectionSize(100);
        tableWidget->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(true);
        tableWidget->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setStretchLastSection(false);

        gridLayout_2->addWidget(tableWidget, 1, 0, 3, 1);

        qwtPlot_reference_r = new QwtPlot(centralWidget);
        qwtPlot_reference_r->setObjectName(QString::fromUtf8("qwtPlot_reference_r"));
        sizePolicy.setHeightForWidth(qwtPlot_reference_r->sizePolicy().hasHeightForWidth());
        qwtPlot_reference_r->setSizePolicy(sizePolicy);
        qwtPlot_reference_r->setCanvasBackground(brush);

        gridLayout_2->addWidget(qwtPlot_reference_r, 2, 1, 1, 1);

        LockinAPP->setCentralWidget(centralWidget);

        retranslateUi(LockinAPP);

        QMetaObject::connectSlotsByName(LockinAPP);
    } // setupUi

    void retranslateUi(QMainWindow *LockinAPP)
    {
        LockinAPP->setWindowTitle(QCoreApplication::translate("LockinAPP", "Qlock-in", nullptr));
        label->setText(QCoreApplication::translate("LockinAPP", "Frames", nullptr));
        period_label->setText(QCoreApplication::translate("LockinAPP", "Period, sec", nullptr));
        label_2->setText(QCoreApplication::translate("LockinAPP", "Output name", nullptr));
        label_3->setText(QCoreApplication::translate("LockinAPP", "Number", nullptr));
        dir_button->setText(QCoreApplication::translate("LockinAPP", "Open Derictory", nullptr));
        numer_frame->setText(QCoreApplication::translate("LockinAPP", "2000", nullptr));
        prename->setText(QCoreApplication::translate("LockinAPP", "test", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("LockinAPP", "R", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("LockinAPP", "Nolinar", nullptr));

        label_4->setText(QCoreApplication::translate("LockinAPP", "Disp mode", nullptr));
        rescan_button->setText(QCoreApplication::translate("LockinAPP", "Rescan lockins", nullptr));
        start_botton->setText(QCoreApplication::translate("LockinAPP", "Start", nullptr));
        stop_botton->setText(QCoreApplication::translate("LockinAPP", "Stop", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LockinAPP", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LockinAPP", "Reference", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("LockinAPP", "Signal", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("LockinAPP", "R", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LockinAPP: public Ui_LockinAPP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKINAPP_H
