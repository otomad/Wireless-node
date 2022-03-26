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

    //��ֹ��û�д������ݵĹ�������sent ��ť
        tcpServe = NULL;
        tcpSocket = NULL;

    //�����׽���,ָ�������������Զ����տռ�
        tcpServe= new QTcpServer(this);
        tcpServe->listen(QHostAddress::Any,8888);//����8888�˿ڵ�����ip

    setFixedSize( this->width(),this->height());    //���ڶ���С
    setWindowTitle(QString::fromLocal8Bit("�˶����ݼ�������"));

    serialport = new QSerialPort;
    windows_init();

    // ��ʾ����
    textItem = new QCPItemText(ui->widget);
    connect(ui->widget, &QCustomPlot::mouseMove, this, &Widget::onMouseMove);

    textItem = new QCPItemText(ui->widget_2);
    connect(ui->widget_2, &QCustomPlot::mouseMove, this, &Widget::onMouseMove);

    //�����Ųۺ���
    int i = 0;
    connect(ui->checkBox_X, SIGNAL(stateChanged(int)), this, SLOT(checkbox_change()));
    connect(ui->checkBox_Y, SIGNAL(stateChanged(int)), this, SLOT(checkbox_change()));
    connect(ui->checkBox_XY, SIGNAL(stateChanged(int)), this, SLOT(checkbox_change()));


    //�ж����ݿ��Ƿ�����
    if(initsql()){
        _SqlConFlag = true;
        qDebug()<<"*************SQL success";
    }else{
        _SqlConFlag = false;
        QMessageBox::warning(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�������ݿ�ʧ��"), QMessageBox::Yes, QMessageBox::Yes);
        //qDebug()<<"*************SQL failed";
    }

    connect(tcpServe,&QTcpServer::newConnection,
                [=]()
                    {
                       //ȡ�����������ӵ��׽���
                        tcpSocket =tcpServe->nextPendingConnection();
                       //��ȡ�Է���ip�Ͷ˿�
                        QString ip = tcpSocket->peerAddress().toString();
                        qint16 port= tcpSocket->peerPort();
                        QString temp = QString (QString::fromLocal8Bit("[%1:%2]���ɹ�����")).arg(ip).arg(port);//�ַ���ƴ��,������Ϣ��ӡ
                        ui->textEditWrite_2->setText(temp);
                       connect(tcpSocket,&QTcpSocket::readyRead,
                               [=]()
                               {
                                   //��ͨ���׽�����ȡ������
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
                                 if(fff.left(2)=="01")//�ж�֡ͷ�����Ⱥ�֡β
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
                              //����
                                     int i1=fff.mid(52,2).toInt(NULL,16);
                                     qDebug()<<fff.mid(52,2);
                                     if(fff.mid(52,2)=="FE"){
                                         i1=0;
                                     }
                             //��������
                                     int jj;
                                     if(fff.mid(54,2)=="FE"){
                                         jj=0;
                                     }
                                     else
                                        jj=fff.mid(54,2).toInt(NULL,16);
                                     qDebug()<<fff.mid(54,2);

                             //����С��
                                     int k;
                                     if(fff.mid(56,2)=="FE"){
                                         k=0;
                                     }
                                     else
                                        k=fff.mid(56,2).toInt(NULL,16);
                                     qDebug()<<fff.mid(56,2);

                             //��������
                                     int l=fff.mid(58,2).toInt(NULL,16);
                                     qDebug()<<fff.mid(58,2);
                             //����С��
                                     int m=fff.mid(60,2).toInt(NULL,16);
                                     qDebug()<<fff.mid(60,2);
                             //����
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

                                         QDateTime dateTime = QDateTime::currentDateTime();//��ȡ��ǰʱ��
                                         double  now = dateTime.toTime_t();//��ǰʱ��ת��Ϊ��
                                         customsplot_init(now,ttt.xindian,ttt.tiwen,ttt.bucheng);
                                         ui->lcdNumber->display(ttt.xinlu);
                                         ui->lcdNumber_2->display(ttt.tiwen);
                                         ui->lcdNumber_3->display(ttt.bucheng);
                                         ui->lcdNumber_4->display(ttt.bushu);
                                         //�����ݴ������ݿ���
                                         if((time.minute()*60+time.second())%1 == 0)//1�����һ��
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



/********************************* �ط�ģʽ* *************************************/
void Widget::on_bt_set_clicked()
{
    Form set(this);//������е㲻��

    set.exec();//ģ̬�Ի���
    qDebug()<<"*************"<<set.m_date;
//    qDebug()<<"*************"<<set.s;
//    int u =(set.s.mid(4,2)).toInt();
//    qDebug()<<(set.s).mid(1,1);
    if(set.isOK) {
      qDebug()<<"*************"<<set.m_date;
      QVector<my_sys> myData = readsportdata(set.m_date.toString("yyyy-MM-dd"));//��ȡʱ��

//      QVector<my_sys> myId= readsportdata(set.m_date.toString());//��ȡ���

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


       QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//��ʾʱ�䣨Ĭ����ʱ�䣩
       QDateTime dateTime = QDateTime::fromString(aaa,"yyyy-MM-dd hh:mm:ss");//��ȡ��ǰʱ��
       double  now = dateTime.toTime_t() - dateTime.time().hour()*3600 - dateTime.time().minute()*60 - dateTime.time().second();//��ǰʱ��ת��Ϊ��
       ui->widget_2->xAxis->setRange(now, now+3600*24);//����X��ķ�Χ
       dateTicker->setDateTimeFormat("hh:mm:ss");//������ʾ��ʽ
       ui->widget_2->xAxis->setTicker(dateTicker);//��ʾ����Ĭ�ϵ�ʱ�䣺��1-1-8:00��
       ui->widget_2->axisRect()->setupFullAxesBox();    //����Ϊ��

       ui->widget_2->graph(0)->addData(mTime,xindian);
       ui->widget_2->graph(1)->addData(mTime,tiwen);
       ui->widget_2->graph(2)->addData(mTime,bucheng);
       ui->widget_2->replot();

    }
}



//�ú�����Ҫ��ϸ��
void Widget::onMouseMove(QMouseEvent *event)
{

        QCustomPlot* customPlot = qobject_cast<QCustomPlot*>(sender());

        //������¼�
        double x = customPlot->xAxis->pixelToCoord(event->pos().x());
        double y = customPlot->yAxis->pixelToCoord(event->pos().y());

        textItem->setText(QString("(%1, %2)").arg(x).arg(y));
        textItem->position->setCoords(QPointF(x, y));
        textItem->setFont(QFont(font().family(), 10));
        customPlot->replot();//��̬��ͼ


}

// ǰ����ʾ�����ʼ��
void Widget::windows_init()
{
//�ؼ���ʼ��
    ui->close_serialport->setEnabled(false);

// ��ѡ��
    QButtonGroup* pButtonGroup = new QButtonGroup(this);
    pButtonGroup->addButton(ui->checkBox_X,1);
    pButtonGroup->addButton(ui->checkBox_Y,2);
    pButtonGroup->addButton(ui->checkBox_XY,3);

// lcd ��ʼ��
    /************************ ��ʾ��ǰ���� ****************************/
    ui->lcdNumber->setDigitCount(5);    //��ʾλ��
    ui->lcdNumber->setMode(QLCDNumber::Dec);    //ʮ����
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Outline);       //��ʾ��ʽ
    ui->lcdNumber->setPalette(Qt::red);
    /**********************  ��ʾ��ǰ���� *****************************/
    ui->lcdNumber_2->setDigitCount(5);    //��ʾλ��
    ui->lcdNumber_2->setMode(QLCDNumber::Dec);    //ʮ����
    ui->lcdNumber_2->setSegmentStyle(QLCDNumber::Outline);       //��ʾ��ʽ
    ui->lcdNumber_2->setPalette(Qt::blue);
    /**********************  ��ʾ��ǰ���*****************************/
    ui->lcdNumber_3->setDigitCount(5);    //��ʾλ��
    ui->lcdNumber_3->setMode(QLCDNumber::Dec);    //ʮ����
    ui->lcdNumber_3->setSegmentStyle(QLCDNumber::Outline);       //��ʾ��ʽ
    ui->lcdNumber_3->setPalette(Qt::green);

    /**********************  ��ʾ��ǰ����*****************************/
    ui->lcdNumber_4->setDigitCount(5);    //��ʾλ��
    ui->lcdNumber_4->setMode(QLCDNumber::Dec);    //ʮ����
    ui->lcdNumber_4->setSegmentStyle(QLCDNumber::Outline);       //��ʾ��ʽ
    ui->lcdNumber_4->setPalette(Qt::yellow);



    /*********************������ߣ�addGraph ,graph������������******************************/
//��ͼ��ʼ��
    /******************************* widget_1  ***************************************/
    /******************** �������1���ĵ����ߣ�**************************************/
     ui->widget->addGraph();
     ui->widget->graph(0)->setPen(QPen(Qt::red,3));       // ���ñʵ���ɫ
     ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);   // ������
     ui->widget->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);     // ���õ����״
     ui->widget->graph(0)->setName(QString::fromLocal8Bit("�ĵ�����"));
     ui->widget->legend->setVisible(true);
    /******************** �������2���������ߣ�**************************************/
    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::green));       // ���ñʵ���ɫ
    ui->widget->graph(1)->setLineStyle(QCPGraph::lsLine);   //������
    ui->widget->legend->setVisible(true);
    ui->widget->graph(1)->setName(QString::fromLocal8Bit("��������"));
    ui->widget->graph(1)->setScatterStyle(QCPScatterStyle::ssStar); //����Ϊ����
    /******************** �������3��������ߣ�**************************************/
    ui->widget->addGraph();
    ui->widget->graph(2)->setPen(QPen(Qt::black));       // ���ñʵ���ɫ
    ui->widget->legend->setVisible(true);
    ui->widget->graph(2)->setLineStyle(QCPGraph::lsLine );   // ������
    ui->widget->graph(2)->setName(QString::fromLocal8Bit("�������"));
    ui->widget->graph(2)->setScatterStyle(QCPScatterStyle::ssDiamond ); //����Ϊ����


/******************************* widget_2  ***************************************/
/******************** �������1���ĵ磩**************************************/
    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->setPen(QPen(Qt::red,3));       // ���ñʵ���ɫ
    ui->widget_2->graph(0)->setLineStyle(QCPGraph::lsLine);   // ������
    ui->widget_2->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);     // ���õ����״
    ui->widget_2->graph(0)->setName(QString::fromLocal8Bit("�ĵ�"));
    ui->widget_2->legend->setVisible(true);
   /******************** �������2�����£�**************************************/
   ui->widget_2->addGraph();
   ui->widget_2->graph(1)->setPen(QPen(Qt::green));       // ���ñʵ���ɫ
   ui->widget_2->graph(1)->setLineStyle(QCPGraph::lsLine);   //������
   ui->widget_2->legend->setVisible(true);
   ui->widget_2->graph(1)->setName(QString::fromLocal8Bit("����"));
   ui->widget_2->graph(1)->setScatterStyle(QCPScatterStyle::ssStar); //����Ϊ����
   /******************** �������3����̣�**************************************/
   ui->widget_2->addGraph();
   ui->widget_2->graph(2)->setPen(QPen(Qt::black));       // ���ñʵ���ɫ
   ui->widget_2->legend->setVisible(true);
   ui->widget_2->graph(2)->setLineStyle(QCPGraph::lsLine );   // ������
   ui->widget_2->graph(2)->setName(QString::fromLocal8Bit("���"));
   ui->widget_2->graph(2)->setScatterStyle(QCPScatterStyle::ssDiamond ); //����Ϊ����






       QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//��ʾʱ�䣨Ĭ����ʱ�䣩
       QDateTime dateTime = QDateTime::currentDateTime();//��ȡ��ǰʱ��
       double  now = dateTime.toTime_t() - dateTime.time().hour()*3600 - dateTime.time().minute()*60 - dateTime.time().second();//��ǰʱ��ת��Ϊ��
       ui->widget->xAxis->setRange(0, 300);//����X��ķ�Χ
       ui->widget->yAxis->setRange(0,250);
       ui->widget_2->xAxis->setRange(now, now+3600*24);//����X��ķ�Χ
       dateTicker->setDateTimeFormat("hh:mm:ss");//������ʾ��ʽ
//       ui->widget->xAxis->setTicker(dateTicker);//��ʾ����Ĭ�ϵ�ʱ�䣺��1-1-8:00��
//       ui->widget->axisRect()->setupFullAxesBox();    //����Ϊ��
       ui->widget_2->xAxis->setTicker(dateTicker);//��ʾ����Ĭ�ϵ�ʱ�䣺��1-1-8:00��
       ui->widget_2->axisRect()->setupFullAxesBox();    //����Ϊ��


    // x������
    ui->widget->xAxis->setLabel(QString::fromLocal8Bit("�������ݽ����Ⱥ����ݣ�"));  //���ú����ǩ
    //ui->widget->yAxis->setRange(0,100);       //������ֵ��Χ
    ui->widget->yAxis->setLabel(QString::fromLocal8Bit("����"));


    /**************************  widget_2  ***********************************/
    ui->widget_2->xAxis->setLabel(QString::fromLocal8Bit("ʱ��(��λs)"));  //���ú����ǩ
    ui->widget_2->yAxis->setRange(0,100);       //�����¶ȷ�Χ

    ui->widget_2->yAxis->setLabel(QString::fromLocal8Bit("����"));



    /***********************���걳��ɫ**************************/
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



    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);    //��������ţ��ƶ�
    ui->widget_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    QList < QCPAxis *>  xis;
    xis.append(ui->widget->xAxis);
    xis.append(ui->widget_2->xAxis);

    ui->widget->axisRect()->setRangeZoomAxes(xis);
    ui->widget_2->axisRect()->setRangeZoomAxes(xis);

    //���涯
    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->yAxis2, SLOT(setRange(QCPRange)));

    connect(ui->widget_2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget_2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget_2->yAxis2, SLOT(setRange(QCPRange)));


  // ʵʱ���²ۺ���
   _pTimerUpdate = new QTimer(this);
  connect(_pTimerUpdate, SIGNAL(timeout()), this, SLOT(LCD_update()));

}


/****************************** �������ݰ�  ****************************************/

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
     /*ui->widget->replot();  */     //��ͼ

    // ������
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

// �򿪴���
void Widget::on_open_serialport_clicked()
{
    find_serialport();

    if(ui->com->count() != 0)   //��Ϊ��ʱ
        //��ʼ������
            serialport->setPortName(ui->com->currentText());        //���ô�����
            if(serialport->open(QIODevice::ReadWrite))              //�򿪴��ڳɹ�
            {
               serialport->setBaudRate(115200);       //���ò�����
               serialport->setDataBits(QSerialPort::Data8);
               serialport->setParity(QSerialPort::NoParity);
               serialport->setStopBits(QSerialPort::OneStop);
               serialport->setStopBits(QSerialPort::TwoStop);
               serialport->setFlowControl(QSerialPort::NoFlowControl);     //����������



               /******************************�ô�������ź���ۣ��׳���һ���źŶ�ȡ����*******************************/
               QObject::connect(serialport, &QSerialPort::readyRead, this, &Widget::read_serialport);    //������


               //�ؼ��ɼ�����
               ui->close_serialport->setEnabled(true);
               ui->open_serialport->setEnabled(false);
               ui->label_state->setText(QString::fromLocal8Bit("���ڴ򿪳ɹ�"));
               ui->widget->replot();       //��ͼ


            }
            else    //��ʧ����ʾ
            {
                QMessageBox::information(this,QString::fromLocal8Bit("Erro"),QString::fromLocal8Bit("Open the failure"),QMessageBox::Ok);
                ui->label_state->setText(QString::fromLocal8Bit("����δ��"));
            }
}


//�رմ���
void Widget::on_close_serialport_clicked()
{
    //�رմ���
    serialport->clear();        //��ջ�����
    serialport->close();        //�رմ���


    //�ؼ�����
    ui->open_serialport->setEnabled(true);
    ui->close_serialport->setEnabled(false);
    ui->label_state->setText(QString::fromLocal8Bit("���� �ر�"));

    // lcd ��ʾ 0

    ui->lcdNumber_2->display( 0 );
    ui->lcdNumber_3->display(0);
    ui->lcdNumber->display(0);    //lcd��ʾ����
    ui->lcdNumber_4->display(0);

}



/*****************************�������ݴ���*************************************/
// ����������
void Widget::read_serialport()
{
    QString end ="";
    QByteArray buf;
    buf = serialport->readAll();
    QByteArray block;//����TCP���ͱ���
   //�����ڵ�����ͨ��TCP/IPЭ�鷢��
//   block = serialport->readAll();
//���Է��������ݣ�ʹ���׽�����tcpSocket
//   tcpSocket->write(block);

    QString fff =buf.toHex();//QString fff = buf;
    qDebug()<<"fff"<<fff;
    if(fff.mid(20,2)=="01")//�ж�֡ͷ
    {
        qDebug()<<"yes";
        int i = 18;
        int j = 0;
        for(i=22,j=0; i <52;i++)//�ĵ�����
        {
            data[j++]=fff.mid(i,1).toInt()*16+fff.mid(i+1,1).toInt();
            i++;

        }
         qDebug()<<fff<<"**********";
         for(int ii = 0; ii < 15;ii++)
         {
             qDebug()<<"**********"<<data[ii];

         }
//����
        int i1=fff.mid(52,2).toInt(NULL,16);
        qDebug()<<fff.mid(52,2);
        if(fff.mid(52,2)=="fe"){
            i1=0;
        }
//��������
        int jj=fff.mid(54,2).toInt(NULL,16);
        qDebug()<<fff.mid(54,2);
        if(fff.mid(54,2)=="fe"){
            jj=0;
        }
//����С��
        int k=fff.mid(56,2).toInt(NULL,16);
        qDebug()<<fff.mid(56,2);
        if(fff.mid(56,2)=="fe"){
            k=0;
        }
//��������
        int l=fff.mid(58,2).toInt(NULL,16);
        qDebug()<<fff.mid(58,2);
//����С��
        int m=fff.mid(60,2).toInt(NULL,16);
        qDebug()<<fff.mid(60,2);
//����
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

            QDateTime dateTime = QDateTime::currentDateTime();//��ȡ��ǰʱ��
            double  now = dateTime.toTime_t();//��ǰʱ��ת��Ϊ��
            customsplot_init(now,ttt.xindian,ttt.tiwen,ttt.bucheng);
            ui->lcdNumber->display(ttt.xinlu);
            ui->lcdNumber_2->display(ttt.tiwen);
            ui->lcdNumber_3->display(ttt.bucheng);
            ui->lcdNumber_4->display(ttt.bushu);
            //�����ݴ������ݿ���
            if((time.minute()*60+time.second())%1 == 0)//3�����һ��
            addsportdata(ttt);




}

     buf.clear();    //��ջ�����
////     block.clear();//��ջ�����

    }



//���Ҵ���
void Widget::find_serialport()
{
    //���ҿ��õĴ���
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);   //���ô���
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->com->addItem(serial.portName());        //��ʾ����name
            serial.close();
        }
    }
}



// ������ѡ��
void Widget::checkbox_change()
{
    // ������
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



//��������ֻ��ʾ�ĵ�����
void Widget::on_pushButton_clicked()
{
        //�ĵ���ʾ
        ui->widget->graph(0)->setVisible(true);
        ui->widget->graph(1)->setVisible(flag);//��������
        ui->widget->graph(2)->setVisible(flag);//�������

}

//��������ֻ��ʾ��������
void Widget::on_pushButton_2_clicked()
{
    //������ʾ
    ui->widget->graph(1)->setVisible(true);
    ui->widget->graph(0)->setVisible(flag);//�ĵ�����
    ui->widget->graph(2)->setVisible(flag);//�������

}

//��������ֻ��ʾ�������
void Widget::on_pushButton_3_clicked()
{
    //�����ʾ
    ui->widget->graph(2)->setVisible(true);
    ui->widget->graph(0)->setVisible(flag);//�ĵ�����
    ui->widget->graph(1)->setVisible(flag);//��������

}

void Widget::on_buttonClose_clicked()
{
    //��û�����ݴ���ʱ�����з���
   if(NULL == tcpSocket)
   {
       return;
   }
   //�����Ϳͻ��˶Ͽ�����
   tcpSocket->disconnectFromHost();
   tcpSocket->close();
   tcpSocket = NULL;//tcpSocket��������
}

void Widget::on_buttonSent_clicked()
{
    //��û�����ݴ���ʱ�����з���
    if(NULL == tcpSocket)
    {
        return;
    }

    //��ȡ�༭��������
  // QString str =ui->textEditWrite->toPlainText();





}
