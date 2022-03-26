#ifndef SQL_H
#define SQL_H
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include<QDate>
#include<QTime>
#include <QtSql/QSqlQuery>
#include <QString>

typedef struct datatype//QT与mysql之间传递的参数
{
    QString  mDate;//日期
    QString mTime;//时间
    double xindian;//心电图像数据
    float bushu;//步数
    float bucheng;//里程
    float tiwen;//体温
    float xinlu;//心率
} my_sys;



bool initsql()//初始化连接数据库
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("10.68.160.68");
    db.setUserName("root");
    db.setPassword("123456");
    db.setDatabaseName("sportdata");
    if(db.open())
    {
        qDebug()<<"Database connected successfully!";
        return true;
    }
    else
    {
        qDebug()<<"Database connected failed!";
        return false;
    }
}

bool addsportdata(my_sys sportdata)//增加运动数据
{
    QSqlQuery query;
    QString str=QString("insert into data value('%1','%2','%3','%4','%5','%6','%7')")
            .arg(sportdata.mDate).arg(sportdata.mTime)
            .arg(sportdata.xindian).arg(sportdata.bushu)
            .arg(sportdata.bucheng).arg(sportdata.tiwen)
            .arg(sportdata.xinlu);
    bool ret=query.exec(str);
    return ret;
}

QVector<my_sys> readsportdata(QString dt)//读取数据库中的气象数据
{
     QVector<my_sys> all_data;
     QSqlQuery query;
     QString sql = QString("select * from data where mDate ='%1'").arg(dt);
     if(query.exec(sql))
     {
         all_data.clear();
         my_sys sys;
         while(query.next())
         {
             sys.mDate=query.value(0).toString();
             sys.mTime=query.value(1).toString();
             sys.xindian=query.value(2).toDouble();
             sys.bushu=query.value(3).toFloat();
             sys.bucheng=query.value(4).toFloat();
             sys.tiwen=query.value(5).toFloat();
             sys.xinlu=query.value(6).toFloat();
             all_data.append(sys);
         }

     }
     return all_data;
}
#endif // SQL_H
