/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_9;
    QCustomPlot *widget;
    QWidget *tab_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *bt_set;
    QCustomPlot *widget_2;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox_X;
    QCheckBox *checkBox_Y;
    QCheckBox *checkBox_XY;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLCDNumber *lcdNumber;
    QLabel *label_8;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_4;
    QLCDNumber *lcdNumber_3;
    QLabel *label_7;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_2;
    QLCDNumber *lcdNumber_2;
    QLabel *label_9;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLCDNumber *lcdNumber_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label_state;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *open_serialport;
    QPushButton *close_serialport;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *com;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_11;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *buttonSent;
    QPushButton *buttonClose;
    QLabel *label_12;
    QTextEdit *textEditWrite;
    QTextEdit *textEditWrite_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1291, 734);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setStyleSheet(QString::fromUtf8(""));
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 781, 561));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_9 = new QHBoxLayout(tab);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        widget = new QCustomPlot(tab);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout_9->addWidget(widget);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayoutWidget = new QWidget(tab_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 111, 31));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        bt_set = new QPushButton(verticalLayoutWidget);
        bt_set->setObjectName(QString::fromUtf8("bt_set"));

        verticalLayout_2->addWidget(bt_set);

        widget_2 = new QCustomPlot(tab_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(10, 50, 751, 461));
        tabWidget->addTab(tab_2, QString());
        groupBox_3 = new QGroupBox(Widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(790, 570, 171, 121));
        layoutWidget = new QWidget(groupBox_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 91, 91));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox_X = new QCheckBox(layoutWidget);
        checkBox_X->setObjectName(QString::fromUtf8("checkBox_X"));
        checkBox_X->setChecked(true);

        verticalLayout->addWidget(checkBox_X);

        checkBox_Y = new QCheckBox(layoutWidget);
        checkBox_Y->setObjectName(QString::fromUtf8("checkBox_Y"));

        verticalLayout->addWidget(checkBox_Y);

        checkBox_XY = new QCheckBox(layoutWidget);
        checkBox_XY->setObjectName(QString::fromUtf8("checkBox_XY"));

        verticalLayout->addWidget(checkBox_XY);

        layoutWidget1 = new QWidget(Widget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(60, 570, 148, 41));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        lcdNumber = new QLCDNumber(layoutWidget1);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));

        horizontalLayout_5->addWidget(lcdNumber);

        label_8 = new QLabel(Widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(220, 570, 41, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font.setPointSize(12);
        label_8->setFont(font);
        layoutWidget2 = new QWidget(Widget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(370, 640, 148, 41));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_11->addWidget(label_4);

        lcdNumber_3 = new QLCDNumber(layoutWidget2);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));

        horizontalLayout_11->addWidget(lcdNumber_3);

        label_7 = new QLabel(Widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(520, 640, 24, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font1.setPointSize(18);
        label_7->setFont(font1);
        layoutWidget3 = new QWidget(Widget);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(370, 570, 151, 41));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_12->addWidget(label_2);

        lcdNumber_2 = new QLCDNumber(layoutWidget3);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));

        horizontalLayout_12->addWidget(lcdNumber_2);

        label_9 = new QLabel(Widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(530, 570, 81, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223"));
        font2.setPointSize(16);
        label_9->setFont(font2);
        layoutWidget4 = new QWidget(Widget);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(60, 640, 164, 41));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_7->addWidget(label_6);

        lcdNumber_4 = new QLCDNumber(layoutWidget4);
        lcdNumber_4->setObjectName(QString::fromUtf8("lcdNumber_4"));

        horizontalLayout_7->addWidget(lcdNumber_4);

        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(790, 20, 181, 211));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 43, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_state = new QLabel(groupBox);
        label_state->setObjectName(QString::fromUtf8("label_state"));

        horizontalLayout_3->addWidget(label_state);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        open_serialport = new QPushButton(groupBox);
        open_serialport->setObjectName(QString::fromUtf8("open_serialport"));

        horizontalLayout_2->addWidget(open_serialport);

        close_serialport = new QPushButton(groupBox);
        close_serialport->setObjectName(QString::fromUtf8("close_serialport"));

        horizontalLayout_2->addWidget(close_serialport);


        gridLayout->addLayout(horizontalLayout_2, 4, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        com = new QComboBox(groupBox);
        com->setObjectName(QString::fromUtf8("com"));

        horizontalLayout->addWidget(com);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);

        label_11 = new QLabel(Widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(820, 250, 121, 31));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(810, 300, 141, 51));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(810, 390, 141, 51));
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(810, 480, 141, 51));
        buttonSent = new QPushButton(Widget);
        buttonSent->setObjectName(QString::fromUtf8("buttonSent"));
        buttonSent->setGeometry(QRect(970, 490, 93, 28));
        buttonClose = new QPushButton(Widget);
        buttonClose->setObjectName(QString::fromUtf8("buttonClose"));
        buttonClose->setGeometry(QRect(1120, 490, 93, 28));
        label_12 = new QLabel(Widget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(990, 30, 256, 15));
        textEditWrite = new QTextEdit(Widget);
        textEditWrite->setObjectName(QString::fromUtf8("textEditWrite"));
        textEditWrite->setGeometry(QRect(980, 260, 256, 201));
        textEditWrite_2 = new QTextEdit(Widget);
        textEditWrite_2->setObjectName(QString::fromUtf8("textEditWrite_2"));
        textEditWrite_2->setGeometry(QRect(980, 50, 256, 201));

        retranslateUi(Widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Widget", "\345\275\223\345\211\215\346\225\260\346\215\256", nullptr));
        bt_set->setText(QApplication::translate("Widget", "\350\256\276\347\275\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Widget", "\344\273\245\345\276\200\346\225\260\346\215\256", nullptr));
        groupBox_3->setTitle(QApplication::translate("Widget", "\350\275\264\347\274\251\346\224\276", nullptr));
        checkBox_X->setText(QApplication::translate("Widget", "X", nullptr));
        checkBox_Y->setText(QApplication::translate("Widget", "Y", nullptr));
        checkBox_XY->setText(QApplication::translate("Widget", "XY", nullptr));
        label_3->setText(QApplication::translate("Widget", " \345\275\223\345\211\215\345\277\203\347\216\207\357\274\232", nullptr));
        label_8->setText(QApplication::translate("Widget", "bpm", nullptr));
        label_4->setText(QApplication::translate("Widget", " \345\275\223\345\211\215\351\207\214\347\250\213\357\274\232", nullptr));
        label_7->setText(QApplication::translate("Widget", "\347\261\263", nullptr));
        label_2->setText(QApplication::translate("Widget", " \345\275\223\345\211\215\344\275\223\346\270\251\357\274\232", nullptr));
        label_9->setText(QApplication::translate("Widget", "\346\221\204\346\260\217\345\272\246", nullptr));
        label_6->setText(QApplication::translate("Widget", "  \345\275\223\345\211\215\346\255\245\346\225\260\357\274\232", nullptr));
        groupBox->setTitle(QApplication::translate("Widget", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        label_state->setText(QApplication::translate("Widget", "\344\270\262\345\217\243\346\234\252\346\211\223\345\274\200", nullptr));
        open_serialport->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        close_serialport->setText(QApplication::translate("Widget", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        label->setText(QApplication::translate("Widget", "\344\270\262\345\217\243\345\217\267:", nullptr));
        label_11->setText(QApplication::translate("Widget", "     \351\200\211\346\213\251\346\233\262\347\272\277\357\274\232", nullptr));
        pushButton->setText(QApplication::translate("Widget", "\345\277\203\347\224\265\346\233\262\347\272\277", nullptr));
        pushButton_2->setText(QApplication::translate("Widget", "\344\275\223\346\270\251\346\233\262\347\272\277", nullptr));
        pushButton_3->setText(QApplication::translate("Widget", "\351\207\214\347\250\213\346\233\262\347\272\277", nullptr));
        buttonSent->setText(QApplication::translate("Widget", "sent", nullptr));
        buttonClose->setText(QApplication::translate("Widget", "close", nullptr));
        label_12->setText(QApplication::translate("Widget", "\346\234\215\345\212\241\345\231\250\357\274\2328888", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
