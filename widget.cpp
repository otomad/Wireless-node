#include "widget.h"
#include "ui_widget.h"
#include <QTabWidget>
#include <QFileDialog>
#include<QString>
#include <QFile>
#include<QDebug>
#include <form.h>
#include<QVector>
#include <thesql.h>
#include<QTextEdit>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    _lastPointKey(0)
{
    _SqlConFlag  =false;
    ui->setupUi(this); 

    //防止在没有传输数据的过程误点击sent 按钮
        tcpServe = NULL;
        tcpSocket = NULL;

    //监听套接字,指定父对象，让其自动回收空间
        tcpServe= new QTcpServer(this);
        tcpServe->listen(QHostAddress::Any,8888);//监听8888端口的所有ip

    setFixedSize( this->width(),this->height());    //窗口定大小
    setWindowTitle(QString::fromLocal8Bit("运动数据监测服务器"));

    serialport = new QSerialPort;
    windows_init();

    // 显示坐标
    textItem = new QCPItemText(ui->widget);
    connect(ui->widget, &QCustomPlot::mouseMove, this, &Widget::onMouseMove);

    textItem = new QCPItemText(ui->widget_2);
    connect(ui->widget_2, &QCustomPlot::mouseMove, this, &Widget::onMouseMove);

    //轴缩放槽函数
    int i = 0;
    connect(ui->checkBox_X, SIGNAL(stateChanged(int)), this, SLOT(checkbox_change()));
    connect(ui->checkBox_Y, SIGNAL(stateChanged(int)), this, SLOT(checkbox_change()));
    connect(ui->checkBox_XY, SIGNAL(stateChanged(int)), this, SLOT(checkbox_change()));


    //判断数据库是否连接
    if(initsql()){
        _SqlConFlag = true;
        qDebug()<<"*************SQL success";
    }else{
        _SqlConFlag = false;
        QMessageBox::warning(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("连接数据库失败"), QMessageBox::Yes, QMessageBox::Yes);
        //qDebug()<<"*************SQL failed";
    }

    connect(tcpServe,&QTcpServer::newConnection,
                [=]()
                    {
                       //取出建立好连接的套接字
                        tcpSocket =tcpServe->nextPendingConnection();
                       //获取对方的ip和端口
                        QString ip = tcpSocket->peerAddress().toString();
                        qint16 port= tcpSocket->peerPort();
                        QString temp = QString (QString::fromLocal8Bit("[%1:%2]：成功连接")).arg(ip).arg(port);//字符串拼接,连接信息打印
                        ui->textEditWrite_2->setText(temp);
                       connect(tcpSocket,&QTcpSocket::readyRead,
                               [=]()
                               {
                                   //从通信套接字中取出内容
                                  QByteArray buf = tcpSocket->readAll();
                                  qDebug()<<"buf"<<buf<<"****"<<buf.size();
                                  ui->textEditWrite_2->append(buf);
                                 QString fff = buf.toHex(); //QString fff = buf;
//                                  int i = 2;
//                                  int j = 0;
//                                  for(i=2,j=0; i <52;i++){
//                                      data[j++]=fff.mid(i,1).toInt()*16+fff.mid(i+1,1).toInt();
//                                      i++;
//                                  }
//                                   qDebug()<<fff<<"**********";
//                                   for(int ii = 0; ii < 25;ii++)
//                                   {
//                                       qDebug()<<"**********"<<data[ii];
//                                   }
                                 if(fff.left(2)=="01")//判断帧头、长度和帧尾
                                 {
                                     qDebug()<<"yes";
                                     int i = 2;
                                     int j = 0;
                                     for(i=2,j=0; i <52;i++)
                                     {
                                         data[j++]=fff.mid(i,1).toInt()*16+fff.mid(i+1,1).toInt();
                                         i++;
                                         /*if(j == 51)
                                         {
                                             for(int i=0; i<25;i++)
                                             {
                                                 data[i] = 0;
                                             }

                                         }*/
                                     }
                                      qDebug()<<fff<<"**********";
                                      for(int ii = 0; ii < 25;ii++)
                                      {
                                          qDebug()<<"**********"<<data[ii];
                                      }
                              //步数
                                     int i1=fff.mid(52,2).toInt(NULL,16);
                                     qDebug()<<fff.mid(52,2);
                                     if(fff.mid(52,2)=="FE"){
                                         i1=0;
                                     }
                             //步程整数
                                     int jj;
                                     if(fff.mid(54,2)=="FE"){
                                         jj=0;
                                     }
                                     else
                                        jj=fff.mid(54,2).toInt(NULL,16);
                                     qDebug()<<fff.mid(54,2);

                             //步程小数
                                     int k;
                                     if(fff.mid(56,2)=="FE"){
                                         k=0;
                                     }
                                     else
                                        k=fff.mid(56,2).toInt(NULL,16);
                                     qDebug()<<fff.mid(56,2);

                             //体温整数
                                     int l=fff.mid(58,2).toInt(NULL,16);
                                     qDebug()<<fff.mid(58,2);
                             //体温小数
                                     int m=fff.mid(60,2).toInt(NULL,16);
                                     qDebug()<<fff.mid(60,2);
                             //心率
                                     int n=fff.mid(62,2).toInt(NULL,16);
                                     qDebug()<<fff.mid(62,2);

                                     datatype ttt;

                                         ttt.bushu = i1;
                                         ttt.bucheng = jj+k*0.1;
                                         ttt.tiwen = l+m*0.1;
                                         ttt.xinlu = n;
                                         QTime time(QTime::currentTime());
                                         ttt.mTime = time.toString("hh:mm:ss");
                                         QDate date(QDate::currentDate());
                                         ttt.mDate = date.toString("yyyy-MM-dd");

                                         QDateTime dateTime = QDateTime::currentDateTime();//获取当前时间
                                         double  now = dateTime.toTime_t();//当前时间转化为秒
                                         customsplot_init(now,ttt.xindian,ttt.tiwen,ttt.bucheng);
                                         ui->lcdNumber->display(ttt.xinlu);
                                         ui->lcdNumber_2->display(ttt.tiwen);
                                         ui->lcdNumber_3->display(ttt.bucheng);
                                         ui->lcdNumber_4->display(ttt.bushu);
                                         //将数据存入数据库中
                                         if((time.minute()*60+time.second())%1 == 0)//1秒添加一个
                                         addsportdata(ttt);
                                 }
                                 buf.clear();
                               }
                       );
                    }
        );
}

Widget::~Widget()
{
    delete ui,serialport;
}



/********************************* 回放模式* *************************************/
void Widget::on_bt_set_clicked()
{
    Form set(this);//该语句有点不懂

    set.exec();//模态对话框
    qDebug()<<"*************"<<set.m_date;
//    qDebug()<<"*************"<<set.s;
//    int u =(set.s.mid(4,2)).toInt();
//    qDebug()<<(set.s).mid(1,1);
    if(set.isOK) {
      qDebug()<<"*************"<<set.m_date;
      QVector<my_sys> myData = readsportdata(set.m_date.toString("yyyy-MM-dd"));//获取时间

//      QVector<my_sys> myId= readsportdata(set.m_date.toString());//读取结点

      QVector<double> mTime,xindian,bushu,bucheng,tiwen,xinlu;


      QString aaa;
      QVector<my_sys>::iterator iter;
          for (iter= myData.begin();iter!=myData.end();iter++)
          {

//     QVector<my_sys>::iterator iter;
              xindian.append(iter->xindian);
              tiwen.append(iter->tiwen);
              bucheng.append(iter->bucheng);
              aaa = iter->mDate+ " " + iter->mTime;
              mTime.append( QDateTime::fromString(aaa,"yyyy-MM-dd hh:mm:ss").toTime_t());
          }


       QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//显示时间（默认了时间）
       QDateTime dateTime = QDateTime::fromString(aaa,"yyyy-MM-dd hh:mm:ss");//获取当前时间
       double  now = dateTime.toTime_t() - dateTime.time().hour()*3600 - dateTime.time().minute()*60 - dateTime.time().second();//当前时间转化为秒
       ui->widget_2->xAxis->setRange(now, now+3600*24);//设置X轴的范围
       dateTicker->setDateTimeFormat("hh:mm:ss");//设置显示格式
       ui->widget_2->xAxis->setTicker(dateTicker);//显示的是默认的时间：“1-1-8:00”
       ui->widget_2->axisRect()->setupFullAxesBox();    //坐标为矩

       ui->widget_2->graph(0)->addData(mTime,xindian);
       ui->widget_2->graph(1)->addData(mTime,tiwen);
       ui->widget_2->graph(2)->addData(mTime,bucheng);
       ui->widget_2->replot();

    }
}



//该函数需要仔细看
void Widget::onMouseMove(QMouseEvent *event)
{

        QCustomPlot* customPlot = qobject_cast<QCustomPlot*>(sender());

        //添加了事件
        double x = customPlot->xAxis->pixelToCoord(event->pos().x());
        double y = customPlot->yAxis->pixelToCoord(event->pos().y());

        textItem->setText(QString("(%1, %2)").arg(x).arg(y));
        textItem->position->setCoords(QPointF(x, y));
        textItem->setFont(QFont(font().family(), 10));
        customPlot->replot();//动态画图


}

// 前端显示界面初始化
void Widget::windows_init()
{
//控件初始化
    ui->close_serialport->setEnabled(false);

// 单选框
    QButtonGroup* pButtonGroup = new QButtonGroup(this);
    pButtonGroup->addButton(ui->checkBox_X,1);
    pButtonGroup->addButton(ui->checkBox_Y,2);
    pButtonGroup->addButton(ui->checkBox_XY,3);

// lcd 初始化
    /************************ 显示当前心率 ****************************/
    ui->lcdNumber->setDigitCount(5);    //显示位数
    ui->lcdNumber->setMode(QLCDNumber::Dec);    //十进制
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Outline);       //显示方式
    ui->lcdNumber->setPalette(Qt::red);
    /**********************  显示当前体温 *****************************/
    ui->lcdNumber_2->setDigitCount(5);    //显示位数
    ui->lcdNumber_2->setMode(QLCDNumber::Dec);    //十进制
    ui->lcdNumber_2->setSegmentStyle(QLCDNumber::Outline);       //显示方式
    ui->lcdNumber_2->setPalette(Qt::blue);
    /**********************  显示当前里程*****************************/
    ui->lcdNumber_3->setDigitCount(5);    //显示位数
    ui->lcdNumber_3->setMode(QLCDNumber::Dec);    //十进制
    ui->lcdNumber_3->setSegmentStyle(QLCDNumber::Outline);       //显示方式
    ui->lcdNumber_3->setPalette(Qt::green);

    /**********************  显示当前步数*****************************/
    ui->lcdNumber_4->setDigitCount(5);    //显示位数
    ui->lcdNumber_4->setMode(QLCDNumber::Dec);    //十进制
    ui->lcdNumber_4->setSegmentStyle(QLCDNumber::Outline);       //显示方式
    ui->lcdNumber_4->setPalette(Qt::yellow);



    /*********************添加曲线（addGraph ,graph），设置坐标******************************/
//绘图初始化
    /******************************* widget_1  ***************************************/
    /******************** 添加曲线1（心电曲线）**************************************/
     ui->widget->addGraph();
     ui->widget->graph(0)->setPen(QPen(Qt::red,3));       // 设置笔的颜色
     ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);   // 画线条
     ui->widget->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);     // 设置点的形状
     ui->widget->graph(0)->setName(QString::fromLocal8Bit("心电曲线"));
     ui->widget->legend->setVisible(true);
    /******************** 添加曲线2（体温曲线）**************************************/
    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::green));       // 设置笔的颜色
    ui->widget->graph(1)->setLineStyle(QCPGraph::lsLine);   //画线条
    ui->widget->legend->setVisible(true);
    ui->widget->graph(1)->setName(QString::fromLocal8Bit("体温曲线"));
    ui->widget->graph(1)->setScatterStyle(QCPScatterStyle::ssStar); //设置为星型
    /******************** 添加曲线3（里程曲线）**************************************/
    ui->widget->addGraph();
    ui->widget->graph(2)->setPen(QPen(Qt::black));       // 设置笔的颜色
    ui->widget->legend->setVisible(true);
    ui->widget->graph(2)->setLineStyle(QCPGraph::lsLine );   // 画线条
    ui->widget->graph(2)->setName(QString::fromLocal8Bit("里程曲线"));
    ui->widget->graph(2)->setScatterStyle(QCPScatterStyle::ssDiamond ); //设置为星型


/******************************* widget_2  ***************************************/
/******************** 添加曲线1（心电）**************************************/
    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->setPen(QPen(Qt::red,3));       // 设置笔的颜色
    ui->widget_2->graph(0)->setLineStyle(QCPGraph::lsLine);   // 画线条
    ui->widget_2->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);     // 设置点的形状
    ui->widget_2->graph(0)->setName(QString::fromLocal8Bit("心电"));
    ui->widget_2->legend->setVisible(true);
   /******************** 添加曲线2（体温）**************************************/
   ui->widget_2->addGraph();
   ui->widget_2->graph(1)->setPen(QPen(Qt::green));       // 设置笔的颜色
   ui->widget_2->graph(1)->setLineStyle(QCPGraph::lsLine);   //画线条
   ui->widget_2->legend->setVisible(true);
   ui->widget_2->graph(1)->setName(QString::fromLocal8Bit("体温"));
   ui->widget_2->graph(1)->setScatterStyle(QCPScatterStyle::ssStar); //设置为星型
   /******************** 添加曲线3（里程）**************************************/
   ui->widget_2->addGraph();
   ui->widget_2->graph(2)->setPen(QPen(Qt::black));       // 设置笔的颜色
   ui->widget_2->legend->setVisible(true);
   ui->widget_2->graph(2)->setLineStyle(QCPGraph::lsLine );   // 画线条
   ui->widget_2->graph(2)->setName(QString::fromLocal8Bit("里程"));
   ui->widget_2->graph(2)->setScatterStyle(QCPScatterStyle::ssDiamond ); //设置为星型






       QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//显示时间（默认了时间）
       QDateTime dateTime = QDateTime::currentDateTime();//获取当前时间
       double  now = dateTime.toTime_t() - dateTime.time().hour()*3600 - dateTime.time().minute()*60 - dateTime.time().second();//当前时间转化为秒
       ui->widget->xAxis->setRange(0, 300);//设置X轴的范围
       ui->widget->yAxis->setRange(0,250);
       ui->widget_2->xAxis->setRange(now, now+3600*24);//设置X轴的范围
       dateTicker->setDateTimeFormat("hh:mm:ss");//设置显示格式
//       ui->widget->xAxis->setTicker(dateTicker);//显示的是默认的时间：“1-1-8:00”
//       ui->widget->axisRect()->setupFullAxesBox();    //坐标为矩
       ui->widget_2->xAxis->setTicker(dateTicker);//显示的是默认的时间：“1-1-8:00”
       ui->widget_2->axisRect()->setupFullAxesBox();    //坐标为矩


    // x轴设置
    ui->widget->xAxis->setLabel(QString::fromLocal8Bit("（按数据接收先后数据）"));  //设置横轴标签
    //ui->widget->yAxis->setRange(0,100);       //设置数值范围
    ui->widget->yAxis->setLabel(QString::fromLocal8Bit("数据"));


    /**************************  widget_2  ***********************************/
    ui->widget_2->xAxis->setLabel(QString::fromLocal8Bit("时间(单位s)"));  //设置横轴标签
    ui->widget_2->yAxis->setRange(0,100);       //设置温度范围

    ui->widget_2->yAxis->setLabel(QString::fromLocal8Bit("数据"));



    /***********************坐标背景色**************************/
        QLinearGradient axisRectGradient;
        axisRectGradient.setStart(0, 0);
        axisRectGradient.setFinalStop(0,350 );
        axisRectGradient.setColorAt(0, QColor(236, 238, 241));
        axisRectGradient.setColorAt(1, QColor(236, 238, 241));
        ui->widget ->axisRect()->setBackground(axisRectGradient);


        QLinearGradient axisRectGradient1;
        axisRectGradient1.setStart(0, 0);
        axisRectGradient1.setFinalStop(0,350 );
        axisRectGradient1.setColorAt(0, QColor(236, 238, 241));
        axisRectGradient1.setColorAt(1, QColor(236, 238, 241));
        ui->widget_2 ->axisRect()->setBackground(axisRectGradient1);



       ui->widget->xAxis->setBasePen(QPen(Qt::blue, 1));
       ui->widget->yAxis->setBasePen(QPen(Qt::blue, 1));
       ui->widget->xAxis->setTickLabelColor(Qt::red);
       ui->widget->yAxis->setTickLabelColor(Qt::red);



    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);    //允许可缩放，移动
    ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    QList < QCPAxis *>  xis;
    xis.append(ui->widget->xAxis);
    xis.append(ui->widget_2->xAxis);

    ui->widget->axisRect()->setRangeZoomAxes(xis);
    ui->widget_2->axisRect()->setRangeZoomAxes(xis);

    //轴随动
    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->widget_2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_2->yAxis2, SLOT(setRange(QCPRange)));


  // 实时更新槽函数
   _pTimerUpdate = new QTimer(this);
  connect(_pTimerUpdate, SIGNAL(timeout()), this, SLOT(LCD_update()));

}


/****************************** 曲线数据绑定  ****************************************/

void Widget::customsplot_init(double theTime, double xindian,double tiwen,double bucheng)
{
    if(num  >= 299)
    {
        num = 1;
        //ui->widget->clearGraphs();

        ui->widget->graph(0)->clearLine();

    }
    if(num2  >= 299)
    {
        num2 = 1;
        //ui->widget->clearGraphs();

        ui->widget->graph(1)->clearLine();
        ui->widget->graph(2)->clearLine();

    }
    num2++;
    qDebug()<<"*********************tiwen******"<<tiwen;
    qDebug()<<"*********************bucheng******"<<bucheng;
    const double aa = 36;
    ui->widget->graph(1)->addData(num2,tiwen);
    ui->widget->graph(2)->addData(num2,bucheng);
     for(int ii = 0; ii < 15;ii++)
     {
         int aaaa = num ++;
         ui->widget->graph(0)->addData(aaaa,data[ii]);
         qDebug()<<"*********************xindian******"<<data[ii];
         if(num  >= 299)
             break;
     }
     ui->widget->replot();
     qDebug()<<"*********************num"<<num;




//     ui->widget->graph(1)->addData(theTime*1000,tiwen);
//     ui->widget->graph(2)->addData(theTime*1000,bucheng);
     /*ui->widget->replot();  */     //画图

    // 缩放轴
     QList < QCPAxis *>  axis_x,axis_y,axis_xy;
     axis_x.append(ui->widget->xAxis);
     axis_y.append(ui->widget->yAxis);
     axis_xy.append(ui->widget->xAxis);
     axis_xy.append(ui->widget->yAxis);

     axis_x.append(ui->widget_2->xAxis);
     axis_y.append(ui->widget_2->yAxis);
     axis_xy.append(ui->widget_2->xAxis);
     axis_xy.append(ui->widget_2->yAxis);


     if(ui->checkBox_X->checkState())
     {
        ui->widget->axisRect()->setRangeZoomAxes(axis_x);
        ui->widget_2->axisRect()->setRangeZoomAxes(axis_x);
     }
     if(ui->checkBox_Y->checkState())
     {
        ui->widget->axisRect()->setRangeZoomAxes(axis_y);
        ui->widget_2->axisRect()->setRangeZoomAxes(axis_y);
     }
     if(ui->checkBox_XY->checkState())
     {
        ui->widget->axisRect()->setRangeZoomAxes(axis_xy);
        ui->widget_2->axisRect()->setRangeZoomAxes(axis_xy);
     }
}

// 打开串口
void Widget::on_open_serialport_clicked()
{
    find_serialport();

    if(ui->com->count() != 0)   //不为空时
        //初始化串口
            serialport->setPortName(ui->com->currentText());        //设置串口名
            if(serialport->open(QIODevice::ReadWrite))              //打开串口成功
            {
               serialport->setBaudRate(115200);       //设置波特率
               serialport->setDataBits(QSerialPort::Data8);
               serialport->setParity(QSerialPort::NoParity);
               serialport->setStopBits(QSerialPort::OneStop);
               serialport->setStopBits(QSerialPort::TwoStop);
               serialport->setFlowControl(QSerialPort::NoFlowControl);     //设置流控制



               /******************************该处添加了信号与槽，抛出了一个信号读取数据*******************************/
               QObject::connect(serialport, &QSerialPort::readyRead, this, &Widget::read_serialport);    //读数据


               //控件可见设置
               ui->close_serialport->setEnabled(true);
               ui->open_serialport->setEnabled(false);
               ui->label_state->setText(QString::fromLocal8Bit("串口打开成功"));
               ui->widget->replot();       //画图


            }
            else    //打开失败提示
            {
                QMessageBox::information(this,QString::fromLocal8Bit("Erro"),QString::fromLocal8Bit("Open the failure"),QMessageBox::Ok);
                ui->label_state->setText(QString::fromLocal8Bit("串口未打开"));
            }
}


//关闭串口
void Widget::on_close_serialport_clicked()
{
    //关闭串口
    serialport->clear();        //清空缓存区
    serialport->close();        //关闭串口


    //控件设置
    ui->open_serialport->setEnabled(true);
    ui->close_serialport->setEnabled(false);
    ui->label_state->setText(QString::fromLocal8Bit("串口 关闭"));

    // lcd 显示 0

    ui->lcdNumber_2->display( 0 );
    ui->lcdNumber_3->display(0);
    ui->lcdNumber->display(0);    //lcd显示数据
    ui->lcdNumber_4->display(0);

}



/*****************************进行数据处理*************************************/
// 读串口数据
void Widget::read_serialport()
{
    QString end ="";
    QByteArray buf;
    buf = serialport->readAll();
    QByteArray block;//定义TCP传送变量
   //将串口的数据通过TCP/IP协议发送
//   block = serialport->readAll();
//给对方发送数据，使用套接字是tcpSocket
//   tcpSocket->write(block);

    QString fff =buf.toHex();//QString fff = buf;
    qDebug()<<"fff"<<fff;
    if(fff.mid(20,2)=="01")//判断帧头
    {
        qDebug()<<"yes";
        int i = 18;
        int j = 0;
        for(i=22,j=0; i <52;i++)//心电数据
        {
            data[j++]=fff.mid(i,1).toInt()*16+fff.mid(i+1,1).toInt();
            i++;

        }
         qDebug()<<fff<<"**********";
         for(int ii = 0; ii < 15;ii++)
         {
             qDebug()<<"**********"<<data[ii];

         }
//步数
        int i1=fff.mid(52,2).toInt(NULL,16);
        qDebug()<<fff.mid(52,2);
        if(fff.mid(52,2)=="fe"){
            i1=0;
        }
//步程整数
        int jj=fff.mid(54,2).toInt(NULL,16);
        qDebug()<<fff.mid(54,2);
        if(fff.mid(54,2)=="fe"){
            jj=0;
        }
//步程小数
        int k=fff.mid(56,2).toInt(NULL,16);
        qDebug()<<fff.mid(56,2);
        if(fff.mid(56,2)=="fe"){
            k=0;
        }
//体温整数
        int l=fff.mid(58,2).toInt(NULL,16);
        qDebug()<<fff.mid(58,2);
//体温小数
        int m=fff.mid(60,2).toInt(NULL,16);
        qDebug()<<fff.mid(60,2);
//心率
        int n=fff.mid(62,2).toInt(NULL,16);
        qDebug()<<fff.mid(62,2);

        datatype ttt;



            ttt.bushu = i1;
            ttt.bucheng = jj+k*0.1;
            ttt.tiwen = l+m*0.1;
            ttt.xinlu = n;
            QTime time(QTime::currentTime());
            ttt.mTime = time.toString("hh:mm:ss");
            QDate date(QDate::currentDate());
            ttt.mDate = date.toString("yyyy-MM-dd");

            QDateTime dateTime = QDateTime::currentDateTime();//获取当前时间
            double  now = dateTime.toTime_t();//当前时间转化为秒
            customsplot_init(now,ttt.xindian,ttt.tiwen,ttt.bucheng);
            ui->lcdNumber->display(ttt.xinlu);
            ui->lcdNumber_2->display(ttt.tiwen);
            ui->lcdNumber_3->display(ttt.bucheng);
            ui->lcdNumber_4->display(ttt.bushu);
            //将数据存入数据库中
            if((time.minute()*60+time.second())%1 == 0)//3秒添加一个
            addsportdata(ttt);




}

     buf.clear();    //清空缓存区
////     block.clear();//清空缓冲区

    }



//查找串口
void Widget::find_serialport()
{
    //查找可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);   //设置串口
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->com->addItem(serial.portName());        //显示串口name
            serial.close();
        }
    }
}



// 缩放轴选择
void Widget::checkbox_change()
{
    // 缩放轴
     QList < QCPAxis *>  axis_x,axis_y,axis_xy;
     axis_x.append(ui->widget->xAxis);
     axis_y.append(ui->widget->yAxis);
     axis_xy.append(ui->widget->xAxis);
     axis_xy.append(ui->widget->yAxis);

     axis_x.append(ui->widget_2->xAxis);
     axis_y.append(ui->widget_2->yAxis);
     axis_xy.append(ui->widget_2->xAxis);
     axis_xy.append(ui->widget_2->yAxis);

     if(ui->checkBox_X->checkState())
     {
        ui->widget->axisRect()->setRangeZoomAxes(axis_x);
        ui->widget_2->axisRect()->setRangeZoomAxes(axis_x);
     }
     if(ui->checkBox_Y->checkState())
     {
        ui->widget->axisRect()->setRangeZoomAxes(axis_y);
        ui->widget_2->axisRect()->setRangeZoomAxes(axis_y);
     }
     if(ui->checkBox_XY->checkState())
     {
        ui->widget->axisRect()->setRangeZoomAxes(axis_xy);
        ui->widget_2->axisRect()->setRangeZoomAxes(axis_xy);
     }

}



//按键控制只显示心电曲线
void Widget::on_pushButton_clicked()
{
        //心电显示
        ui->widget->graph(0)->setVisible(true);
        ui->widget->graph(1)->setVisible(flag);//体温隐藏
        ui->widget->graph(2)->setVisible(flag);//里程隐藏

}

//按键控制只显示体温曲线
void Widget::on_pushButton_2_clicked()
{
    //体温显示
    ui->widget->graph(1)->setVisible(true);
    ui->widget->graph(0)->setVisible(flag);//心电隐藏
    ui->widget->graph(2)->setVisible(flag);//里程隐藏

}

//按键控制只显示里程曲线
void Widget::on_pushButton_3_clicked()
{
    //里程显示
    ui->widget->graph(2)->setVisible(true);
    ui->widget->graph(0)->setVisible(flag);//心电隐藏
    ui->widget->graph(1)->setVisible(flag);//体温隐藏

}

void Widget::on_buttonClose_clicked()
{
    //当没有数据传输时不进行返回
   if(NULL == tcpSocket)
   {
       return;
   }
   //主动和客户端断开连接
   tcpSocket->disconnectFromHost();
   tcpSocket->close();
   tcpSocket = NULL;//tcpSocket重载数据
}

void Widget::on_buttonSent_clicked()
{
    //当没有数据传输时不进行返回
    if(NULL == tcpSocket)
    {
        return;
    }

    //获取编辑区得内容
  // QString str =ui->textEditWrite->toPlainText();





}
