#include "widget.h"
#include "./ui_widget.h"
#include <QLineEdit>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->log_out, &QPushButton::clicked, this, &QPushButton::close);
    connect(ui->log_in, &QPushButton::clicked, this, [=]()
            {
        if(ui->account->text()=="keenechen"&&ui->password->text()=="2555"){
            qDebug()<<"登录成功";
            QMessageBox::information(this," ", "登录成功");
        }else{
            qDebug()<<"登录失败";
           QMessageBox::information(this," ", "登录失败");
            qDebug()<<ui->account->text();
            qDebug()<<ui->password->text();
        } });
}

Widget::~Widget()
{
    delete ui;
}
