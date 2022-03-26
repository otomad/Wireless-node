#include "form.h"
#include "ui_form.h"
#include"QDebug"

Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}
void Form::on_bt_set_clicked()
{
    m_date =  ui->dateEdit->date();//获取时间
//    s = ui->spinBox->value();
    isOK = true;
    qDebug()<<m_date;
    this->close();
}
