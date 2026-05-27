/********************************************************************************
** Form generated from reading UI file 'lockinapplite.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKINAPPLITE_H
#define UI_LOCKINAPPLITE_H

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

class Ui_LockinAPPlite
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QwtPlot *qwtPlot_reference_signal;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer;
    QLCDNumber *progresslcdNumber;
    QPushButton *start_botton;
    QLabel *label_3;
    QLabel *period_label;
    QLabel *label_2;
    QPushButton *rescan_button;
    QLineEdit *numer_frame;
    QPushButton *stop_botton;
    QComboBox *lockin_ser;
    QDoubleSpinBox *period_value;
    QPushButton *dir_button;
    QLineEdit *prename;
    QLabel *label;
    QPushButton *add_button;
    QTableWidget *tableWidget;

    void setupUi(QMainWindow *LockinAPPlite)
    {
        if (LockinAPPlite->objectName().isEmpty())
            LockinAPPlite->setObjectName(QString::fromUtf8("LockinAPPlite"));
        LockinAPPlite->resize(920, 473);
        QFont font;
        font.setPointSize(14);
        LockinAPPlite->setFont(font);
        centralWidget = new QWidget(LockinAPPlite);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        qwtPlot_reference_signal = new QwtPlot(centralWidget);
        qwtPlot_reference_signal->setObjectName(QString::fromUtf8("qwtPlot_reference_signal"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qwtPlot_reference_signal->sizePolicy().hasHeightForWidth());
        qwtPlot_reference_signal->setSizePolicy(sizePolicy);
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        qwtPlot_reference_signal->setCanvasBackground(brush);

        gridLayout_2->addWidget(qwtPlot_reference_signal, 2, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font1;
        font1.setPointSize(12);
        label_5->setFont(font1);

        gridLayout->addWidget(label_5, 0, 5, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 4, 1, 1);

        progresslcdNumber = new QLCDNumber(centralWidget);
        progresslcdNumber->setObjectName(QString::fromUtf8("progresslcdNumber"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(progresslcdNumber->sizePolicy().hasHeightForWidth());
        progresslcdNumber->setSizePolicy(sizePolicy1);
        progresslcdNumber->setMinimumSize(QSize(0, 36));
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(false);
        font2.setWeight(50);
        progresslcdNumber->setFont(font2);
        progresslcdNumber->setDigitCount(5);
        progresslcdNumber->setProperty("intValue", QVariant(0));

        gridLayout->addWidget(progresslcdNumber, 1, 3, 1, 1);

        start_botton = new QPushButton(centralWidget);
        start_botton->setObjectName(QString::fromUtf8("start_botton"));
        sizePolicy1.setHeightForWidth(start_botton->sizePolicy().hasHeightForWidth());
        start_botton->setSizePolicy(sizePolicy1);
        start_botton->setFont(font1);

        gridLayout->addWidget(start_botton, 0, 8, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 0, 3, 1, 1);

        period_label = new QLabel(centralWidget);
        period_label->setObjectName(QString::fromUtf8("period_label"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(period_label->sizePolicy().hasHeightForWidth());
        period_label->setSizePolicy(sizePolicy2);
        period_label->setFont(font1);

        gridLayout->addWidget(period_label, 0, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        rescan_button = new QPushButton(centralWidget);
        rescan_button->setObjectName(QString::fromUtf8("rescan_button"));
        rescan_button->setFont(font1);

        gridLayout->addWidget(rescan_button, 0, 7, 1, 1);

        numer_frame = new QLineEdit(centralWidget);
        numer_frame->setObjectName(QString::fromUtf8("numer_frame"));
        sizePolicy1.setHeightForWidth(numer_frame->sizePolicy().hasHeightForWidth());
        numer_frame->setSizePolicy(sizePolicy1);
        numer_frame->setFont(font1);

        gridLayout->addWidget(numer_frame, 1, 1, 1, 1);

        stop_botton = new QPushButton(centralWidget);
        stop_botton->setObjectName(QString::fromUtf8("stop_botton"));
        sizePolicy1.setHeightForWidth(stop_botton->sizePolicy().hasHeightForWidth());
        stop_botton->setSizePolicy(sizePolicy1);
        stop_botton->setFont(font1);

        gridLayout->addWidget(stop_botton, 1, 8, 1, 1);

        lockin_ser = new QComboBox(centralWidget);
        lockin_ser->addItem(QString());
        lockin_ser->addItem(QString());
        lockin_ser->addItem(QString());
        lockin_ser->setObjectName(QString::fromUtf8("lockin_ser"));
        lockin_ser->setEnabled(false);
        lockin_ser->setEditable(true);

        gridLayout->addWidget(lockin_ser, 1, 5, 1, 1);

        period_value = new QDoubleSpinBox(centralWidget);
        period_value->setObjectName(QString::fromUtf8("period_value"));
        period_value->setFont(font1);
        period_value->setSingleStep(0.100000000000000);
        period_value->setValue(0.200000000000000);

        gridLayout->addWidget(period_value, 1, 0, 1, 1);

        dir_button = new QPushButton(centralWidget);
        dir_button->setObjectName(QString::fromUtf8("dir_button"));
        dir_button->setFont(font1);

        gridLayout->addWidget(dir_button, 1, 7, 1, 1);

        prename = new QLineEdit(centralWidget);
        prename->setObjectName(QString::fromUtf8("prename"));
        sizePolicy1.setHeightForWidth(prename->sizePolicy().hasHeightForWidth());
        prename->setSizePolicy(sizePolicy1);
        prename->setFont(font1);

        gridLayout->addWidget(prename, 1, 2, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        add_button = new QPushButton(centralWidget);
        add_button->setObjectName(QString::fromUtf8("add_button"));
        add_button->setMinimumSize(QSize(40, 0));
        add_button->setMaximumSize(QSize(40, 16777215));
        add_button->setFont(font1);

        gridLayout->addWidget(add_button, 1, 6, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 2);

        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy3);
        tableWidget->setMinimumSize(QSize(0, 0));
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

        gridLayout_2->addWidget(tableWidget, 1, 0, 2, 1);

        LockinAPPlite->setCentralWidget(centralWidget);

        retranslateUi(LockinAPPlite);

        QMetaObject::connectSlotsByName(LockinAPPlite);
    } // setupUi

    void retranslateUi(QMainWindow *LockinAPPlite)
    {
        LockinAPPlite->setWindowTitle(QCoreApplication::translate("LockinAPPlite", "Qlock-in Lite", nullptr));
        label_5->setText(QCoreApplication::translate("LockinAPPlite", "Lockin ser", nullptr));
        start_botton->setText(QCoreApplication::translate("LockinAPPlite", "Start", nullptr));
        label_3->setText(QCoreApplication::translate("LockinAPPlite", "Number", nullptr));
        period_label->setText(QCoreApplication::translate("LockinAPPlite", "Period, sec", nullptr));
        label_2->setText(QCoreApplication::translate("LockinAPPlite", "Output name", nullptr));
        rescan_button->setText(QCoreApplication::translate("LockinAPPlite", "Rescan lockins", nullptr));
        numer_frame->setText(QCoreApplication::translate("LockinAPPlite", "2000", nullptr));
        stop_botton->setText(QCoreApplication::translate("LockinAPPlite", "Stop", nullptr));
        lockin_ser->setItemText(0, QCoreApplication::translate("LockinAPPlite", "81579", nullptr));
        lockin_ser->setItemText(1, QCoreApplication::translate("LockinAPPlite", "70259", nullptr));
        lockin_ser->setItemText(2, QCoreApplication::translate("LockinAPPlite", "81595", nullptr));

        dir_button->setText(QCoreApplication::translate("LockinAPPlite", "Open Derictory", nullptr));
        prename->setText(QCoreApplication::translate("LockinAPPlite", "test", nullptr));
        label->setText(QCoreApplication::translate("LockinAPPlite", "Frames", nullptr));
        add_button->setText(QCoreApplication::translate("LockinAPPlite", "+", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("LockinAPPlite", "Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("LockinAPPlite", "Signal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LockinAPPlite: public Ui_LockinAPPlite {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKINAPPLITE_H
