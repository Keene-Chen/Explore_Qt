#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->btn_set,&QPushButton::clicked,[=](){
        ui->widget->setData(50);
    });

    connect(ui->btn_get,&QPushButton::clicked,[=](){
       qDebug() << ui->widget->getData();
    });
}

Widget::~Widget()
{
    delete ui;
}

