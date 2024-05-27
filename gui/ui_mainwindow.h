/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_turnOn;
    QPushButton *pushButton_turnOff;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_cold;
    QPushButton *pushButton_hot;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_high;
    QPushButton *pushButton_middle;
    QPushButton *pushButton_low;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_temperature;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_ok;
    QWidget *widget_back;
    QFrame *frame_line1;
    QFrame *frame_line2;
    QFrame *frame_line3;
    QFrame *frame_line4;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_speedText;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_speed1;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_speed2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_speed3;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_6;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_workModeText;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_workMode_hot;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_workMode_cold;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *verticalSpacer_9;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_workStatusText;
    QSpacerItem *verticalSpacer_11;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_workStatus_working;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *verticalSpacer_12;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_16;
    QLabel *label_workStatus_waiting;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *verticalSpacer_13;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_room;
    QSpacerItem *verticalSpacer_15;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_20;
    QLabel *label_off;
    QSpacerItem *horizontalSpacer_21;
    QSpacerItem *verticalSpacer_16;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_22;
    QLabel *label_on;
    QSpacerItem *horizontalSpacer_23;
    QSpacerItem *verticalSpacer_17;
    QLabel *label_currTemp;
    QLabel *label_currTempData;
    QLabel *label_desTempData;
    QLabel *label_desTemp;
    QLabel *label_currCostData;
    QLabel *label_currCost;
    QLabel *label_allinCostData;
    QLabel *label_allinCost;
    QLabel *label_errorTip;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setMaximumSize(QSize(800, 600));
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(800, 578));
        centralwidget->setMaximumSize(QSize(800, 578));
        centralwidget->setContextMenuPolicy(Qt::NoContextMenu);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(690, 50, 82, 461));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton_turnOn = new QPushButton(layoutWidget);
        pushButton_turnOn->setObjectName(QString::fromUtf8("pushButton_turnOn"));
        pushButton_turnOn->setMinimumSize(QSize(78, 40));
        pushButton_turnOn->setMaximumSize(QSize(78, 40));

        verticalLayout->addWidget(pushButton_turnOn);

        pushButton_turnOff = new QPushButton(layoutWidget);
        pushButton_turnOff->setObjectName(QString::fromUtf8("pushButton_turnOff"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_turnOff->sizePolicy().hasHeightForWidth());
        pushButton_turnOff->setSizePolicy(sizePolicy1);
        pushButton_turnOff->setMinimumSize(QSize(78, 40));
        pushButton_turnOff->setMaximumSize(QSize(78, 40));

        verticalLayout->addWidget(pushButton_turnOff);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        pushButton_cold = new QPushButton(layoutWidget);
        pushButton_cold->setObjectName(QString::fromUtf8("pushButton_cold"));
        pushButton_cold->setMinimumSize(QSize(78, 40));
        pushButton_cold->setMaximumSize(QSize(78, 40));

        verticalLayout_2->addWidget(pushButton_cold);

        pushButton_hot = new QPushButton(layoutWidget);
        pushButton_hot->setObjectName(QString::fromUtf8("pushButton_hot"));
        pushButton_hot->setMinimumSize(QSize(78, 40));
        pushButton_hot->setMaximumSize(QSize(78, 40));

        verticalLayout_2->addWidget(pushButton_hot);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pushButton_high = new QPushButton(layoutWidget);
        pushButton_high->setObjectName(QString::fromUtf8("pushButton_high"));
        pushButton_high->setMinimumSize(QSize(78, 40));
        pushButton_high->setMaximumSize(QSize(78, 40));

        verticalLayout_3->addWidget(pushButton_high);

        pushButton_middle = new QPushButton(layoutWidget);
        pushButton_middle->setObjectName(QString::fromUtf8("pushButton_middle"));
        pushButton_middle->setMinimumSize(QSize(78, 40));
        pushButton_middle->setMaximumSize(QSize(78, 40));

        verticalLayout_3->addWidget(pushButton_middle);

        pushButton_low = new QPushButton(layoutWidget);
        pushButton_low->setObjectName(QString::fromUtf8("pushButton_low"));
        pushButton_low->setMinimumSize(QSize(78, 40));
        pushButton_low->setMaximumSize(QSize(78, 40));

        verticalLayout_3->addWidget(pushButton_low);


        verticalLayout_4->addLayout(verticalLayout_3);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(40, 470, 601, 61));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_temperature = new QLineEdit(layoutWidget1);
        lineEdit_temperature->setObjectName(QString::fromUtf8("lineEdit_temperature"));
        lineEdit_temperature->setMinimumSize(QSize(450, 40));

        horizontalLayout->addWidget(lineEdit_temperature);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_ok = new QPushButton(layoutWidget1);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setMinimumSize(QSize(120, 40));

        horizontalLayout->addWidget(pushButton_ok);

        widget_back = new QWidget(centralwidget);
        widget_back->setObjectName(QString::fromUtf8("widget_back"));
        widget_back->setGeometry(QRect(40, 40, 601, 391));
        frame_line1 = new QFrame(widget_back);
        frame_line1->setObjectName(QString::fromUtf8("frame_line1"));
        frame_line1->setGeometry(QRect(236, 15, 2, 362));
        frame_line1->setFrameShape(QFrame::StyledPanel);
        frame_line1->setFrameShadow(QFrame::Raised);
        frame_line2 = new QFrame(widget_back);
        frame_line2->setObjectName(QString::fromUtf8("frame_line2"));
        frame_line2->setGeometry(QRect(15, 195, 205, 2));
        frame_line2->setFrameShape(QFrame::StyledPanel);
        frame_line2->setFrameShadow(QFrame::Raised);
        frame_line3 = new QFrame(widget_back);
        frame_line3->setObjectName(QString::fromUtf8("frame_line3"));
        frame_line3->setGeometry(QRect(256, 195, 329, 2));
        frame_line3->setFrameShape(QFrame::StyledPanel);
        frame_line3->setFrameShadow(QFrame::Raised);
        frame_line4 = new QFrame(widget_back);
        frame_line4->setObjectName(QString::fromUtf8("frame_line4"));
        frame_line4->setGeometry(QRect(425, 213, 2, 163));
        frame_line4->setFrameShape(QFrame::StyledPanel);
        frame_line4->setFrameShadow(QFrame::Raised);
        layoutWidget2 = new QWidget(widget_back);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(253, 20, 331, 171));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(-1, -1, -1, 12);
        label_speedText = new QLabel(layoutWidget2);
        label_speedText->setObjectName(QString::fromUtf8("label_speedText"));
        label_speedText->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_speedText);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_speed1 = new QLabel(layoutWidget2);
        label_speed1->setObjectName(QString::fromUtf8("label_speed1"));
        label_speed1->setMinimumSize(QSize(20, 20));
        label_speed1->setMaximumSize(QSize(20, 20));
        label_speed1->setLayoutDirection(Qt::LeftToRight);
        label_speed1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_speed1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        label_speed2 = new QLabel(layoutWidget2);
        label_speed2->setObjectName(QString::fromUtf8("label_speed2"));
        label_speed2->setMinimumSize(QSize(20, 20));
        label_speed2->setMaximumSize(QSize(20, 20));

        horizontalLayout_3->addWidget(label_speed2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_5->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        label_speed3 = new QLabel(layoutWidget2);
        label_speed3->setObjectName(QString::fromUtf8("label_speed3"));
        label_speed3->setMinimumSize(QSize(20, 20));
        label_speed3->setMaximumSize(QSize(20, 20));

        horizontalLayout_4->addWidget(label_speed3);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_5->addLayout(horizontalLayout_4);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_6);


        gridLayout->addLayout(verticalLayout_5, 0, 0, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(-1, -1, -1, 12);
        label_workModeText = new QLabel(layoutWidget2);
        label_workModeText->setObjectName(QString::fromUtf8("label_workModeText"));
        label_workModeText->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_workModeText);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);

        label_workMode_hot = new QLabel(layoutWidget2);
        label_workMode_hot->setObjectName(QString::fromUtf8("label_workMode_hot"));
        label_workMode_hot->setMinimumSize(QSize(36, 36));
        label_workMode_hot->setMaximumSize(QSize(36, 36));
        label_workMode_hot->setLayoutDirection(Qt::LeftToRight);
        label_workMode_hot->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_workMode_hot);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);


        verticalLayout_6->addLayout(horizontalLayout_5);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_10);

        label_workMode_cold = new QLabel(layoutWidget2);
        label_workMode_cold->setObjectName(QString::fromUtf8("label_workMode_cold"));
        label_workMode_cold->setMinimumSize(QSize(36, 36));
        label_workMode_cold->setMaximumSize(QSize(36, 36));

        horizontalLayout_6->addWidget(label_workMode_cold);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_11);


        verticalLayout_6->addLayout(horizontalLayout_6);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_9);


        gridLayout->addLayout(verticalLayout_6, 0, 1, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(-1, -1, -1, 12);
        label_workStatusText = new QLabel(layoutWidget2);
        label_workStatusText->setObjectName(QString::fromUtf8("label_workStatusText"));
        label_workStatusText->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_workStatusText);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_11);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_14);

        label_workStatus_working = new QLabel(layoutWidget2);
        label_workStatus_working->setObjectName(QString::fromUtf8("label_workStatus_working"));
        label_workStatus_working->setMinimumSize(QSize(36, 36));
        label_workStatus_working->setMaximumSize(QSize(36, 36));
        label_workStatus_working->setLayoutDirection(Qt::LeftToRight);
        label_workStatus_working->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_workStatus_working);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_15);


        verticalLayout_7->addLayout(horizontalLayout_8);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_12);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_16);

        label_workStatus_waiting = new QLabel(layoutWidget2);
        label_workStatus_waiting->setObjectName(QString::fromUtf8("label_workStatus_waiting"));
        label_workStatus_waiting->setMinimumSize(QSize(36, 36));
        label_workStatus_waiting->setMaximumSize(QSize(36, 36));

        horizontalLayout_9->addWidget(label_workStatus_waiting);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_17);


        verticalLayout_7->addLayout(horizontalLayout_9);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_13);


        gridLayout->addLayout(verticalLayout_7, 0, 2, 1, 1);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(-1, -1, -1, 12);
        label_room = new QLabel(layoutWidget2);
        label_room->setObjectName(QString::fromUtf8("label_room"));
        label_room->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_room);

        verticalSpacer_15 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_15);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_20);

        label_off = new QLabel(layoutWidget2);
        label_off->setObjectName(QString::fromUtf8("label_off"));
        label_off->setMinimumSize(QSize(36, 36));
        label_off->setMaximumSize(QSize(36, 36));
        label_off->setLayoutDirection(Qt::LeftToRight);
        label_off->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_off);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_21);


        verticalLayout_8->addLayout(horizontalLayout_11);

        verticalSpacer_16 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_16);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_22);

        label_on = new QLabel(layoutWidget2);
        label_on->setObjectName(QString::fromUtf8("label_on"));
        label_on->setMinimumSize(QSize(36, 36));
        label_on->setMaximumSize(QSize(36, 36));

        horizontalLayout_12->addWidget(label_on);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_23);


        verticalLayout_8->addLayout(horizontalLayout_12);

        verticalSpacer_17 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_17);


        gridLayout->addLayout(verticalLayout_8, 0, 3, 1, 1);

        label_currTemp = new QLabel(widget_back);
        label_currTemp->setObjectName(QString::fromUtf8("label_currTemp"));
        label_currTemp->setGeometry(QRect(90, 23, 64, 16));
        label_currTemp->setAlignment(Qt::AlignCenter);
        label_currTempData = new QLabel(widget_back);
        label_currTempData->setObjectName(QString::fromUtf8("label_currTempData"));
        label_currTempData->setGeometry(QRect(23, 50, 190, 129));
        label_currTempData->setAlignment(Qt::AlignCenter);
        label_desTempData = new QLabel(widget_back);
        label_desTempData->setObjectName(QString::fromUtf8("label_desTempData"));
        label_desTempData->setGeometry(QRect(23, 237, 190, 129));
        label_desTempData->setAlignment(Qt::AlignCenter);
        label_desTemp = new QLabel(widget_back);
        label_desTemp->setObjectName(QString::fromUtf8("label_desTemp"));
        label_desTemp->setGeometry(QRect(90, 210, 64, 16));
        label_desTemp->setAlignment(Qt::AlignCenter);
        label_currCostData = new QLabel(widget_back);
        label_currCostData->setObjectName(QString::fromUtf8("label_currCostData"));
        label_currCostData->setGeometry(QRect(252, 237, 161, 129));
        label_currCostData->setAlignment(Qt::AlignCenter);
        label_currCost = new QLabel(widget_back);
        label_currCost->setObjectName(QString::fromUtf8("label_currCost"));
        label_currCost->setGeometry(QRect(300, 210, 64, 16));
        label_currCost->setAlignment(Qt::AlignCenter);
        label_allinCostData = new QLabel(widget_back);
        label_allinCostData->setObjectName(QString::fromUtf8("label_allinCostData"));
        label_allinCostData->setGeometry(QRect(432, 237, 161, 129));
        label_allinCostData->setAlignment(Qt::AlignCenter);
        label_allinCost = new QLabel(widget_back);
        label_allinCost->setObjectName(QString::fromUtf8("label_allinCost"));
        label_allinCost->setGeometry(QRect(480, 210, 64, 16));
        label_allinCost->setAlignment(Qt::AlignCenter);
        label_errorTip = new QLabel(centralwidget);
        label_errorTip->setObjectName(QString::fromUtf8("label_errorTip"));
        label_errorTip->setGeometry(QRect(40, 520, 341, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_turnOn->setText(QCoreApplication::translate("MainWindow", "\345\274\200\346\234\272", nullptr));
        pushButton_turnOff->setText(QCoreApplication::translate("MainWindow", "\345\205\263\346\234\272", nullptr));
        pushButton_cold->setText(QCoreApplication::translate("MainWindow", "\345\210\266\345\206\267", nullptr));
        pushButton_hot->setText(QCoreApplication::translate("MainWindow", "\345\210\266\347\203\255", nullptr));
        pushButton_high->setText(QCoreApplication::translate("MainWindow", "\351\253\230\351\243\216", nullptr));
        pushButton_middle->setText(QCoreApplication::translate("MainWindow", "\344\270\255\351\243\216", nullptr));
        pushButton_low->setText(QCoreApplication::translate("MainWindow", "\344\275\216\351\243\216", nullptr));
        lineEdit_temperature->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\347\233\256\346\240\207\346\270\251\345\272\246", nullptr));
        pushButton_ok->setText(QCoreApplication::translate("MainWindow", "\347\241\256\350\256\244", nullptr));
        label_speedText->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\351\243\216\351\200\237", nullptr));
        label_speed1->setText(QString());
        label_speed2->setText(QString());
        label_speed3->setText(QString());
        label_workModeText->setText(QCoreApplication::translate("MainWindow", "\345\267\245\344\275\234\346\250\241\345\274\217", nullptr));
        label_workMode_hot->setText(QString());
        label_workMode_cold->setText(QString());
        label_workStatusText->setText(QCoreApplication::translate("MainWindow", "\345\267\245\344\275\234\347\212\266\346\200\201", nullptr));
        label_workStatus_working->setText(QString());
        label_workStatus_waiting->setText(QString());
        label_room->setText(QCoreApplication::translate("MainWindow", "\346\210\277\351\227\2641", nullptr));
        label_off->setText(QString());
        label_on->setText(QString());
        label_currTemp->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\345\256\244\346\270\251", nullptr));
        label_currTempData->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_desTempData->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_desTemp->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\240\207\346\270\251\345\272\246", nullptr));
        label_currCostData->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_currCost->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\350\264\271\347\224\250", nullptr));
        label_allinCostData->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_allinCost->setText(QCoreApplication::translate("MainWindow", "\346\200\273\350\264\271\347\224\250", nullptr));
        label_errorTip->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\240\207\346\270\251\345\272\246\350\214\203\345\233\264\357\274\23216~32", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
