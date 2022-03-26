/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QPushButton *bt_set;
    QPushButton *bt_set2;
    QLabel *label;
    QDateEdit *dateEdit;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(303, 138);
        bt_set = new QPushButton(Form);
        bt_set->setObjectName(QString::fromUtf8("bt_set"));
        bt_set->setGeometry(QRect(20, 80, 91, 41));
        bt_set2 = new QPushButton(Form);
        bt_set2->setObjectName(QString::fromUtf8("bt_set2"));
        bt_set2->setGeometry(QRect(180, 80, 91, 41));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 20, 81, 41));
        dateEdit = new QDateEdit(Form);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setGeometry(QRect(90, 30, 191, 31));
        dateEdit->setDateTime(QDateTime(QDate(2020, 10, 10), QTime(0, 0, 0)));

        retranslateUi(Form);
        QObject::connect(bt_set2, SIGNAL(clicked()), Form, SLOT(close()));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        bt_set->setText(QApplication::translate("Form", "\347\241\256\345\256\232", nullptr));
        bt_set2->setText(QApplication::translate("Form", "\345\217\226\346\266\210", nullptr));
        label->setText(QApplication::translate("Form", " \351\200\211\346\213\251\346\227\245\346\234\237\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
