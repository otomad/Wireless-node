#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qcustomplot.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>
#include <QDebug>
#include<QTcpServer>//监听套接字
#include<QTcpSocket>//通信套接字

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void windows_init();
    void serialport_init();
    void read_serialport();     //读串口数据
    void find_serialport();     //查找串口
    void insert_table(QString date, QString t);
    bool flag = false;

    void Wind_show(int sun);


private slots:
    void onMouseMove(QMouseEvent* event);
    void customsplot_init(double theTime, double xindian,double tiwen,double bucheng);
    void on_open_serialport_clicked();
    void on_close_serialport_clicked();
    void checkbox_change();
    void on_bt_set_clicked();




    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_buttonClose_clicked();

    void on_buttonSent_clicked();

private:
    Ui::Widget *ui;
    QTimer dataTimer;           //时间
    QSerialPort *serialport;    //串口类


    QCPItemText *textItem;
    QTcpServer *tcpServe;//监听套接字
    QTcpSocket *tcpSocket;//通信套接字

    // 定时器
    QTimer *_pTimerUpdate;
    QElapsedTimer _elapsedTimer;        //之间计时
    int _fps;
    int _interval;
    double _lastPointKey;
    bool _SqlConFlag;
    bool _pause;
    int num = 0;
    int num2 = 0;
    QString ba[156];
    int data[25];



};


#endif // WIDGET_H
