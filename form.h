#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include <QDate>
namespace Ui {
class Form;
}




class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    QDate m_date;
//    QString s;
    bool isOK = false;

private slots:
    void on_bt_set_clicked();
private:
      Ui::Form *ui;



};

#endif // FORM_H
