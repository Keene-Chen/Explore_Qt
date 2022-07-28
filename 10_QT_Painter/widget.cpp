#include "widget.h"
#include "./ui_widget.h"
#include <QBrush>
#include <QColor>
#include <QIcon>
#include <QPainter.h>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <qnamespace.h>
#include <qpoint.h>

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("10_QT_Painter");
}

Widget::~Widget()
{
    delete ui;
}

// 绘图事件
void Widget::paintEvent(QPaintEvent*)
{
    // 创建一个画家
    QPainter painter(this);

    // 设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置画笔
    QPen pen(QColor(255, 0, 0));
    // 设置线的宽度
    pen.setWidth(2);
    // 设置线的风格
    //    pen.setStyle(Qt::DashLine);
    painter.setPen(pen);

    // 设置画刷
    QBrush brush(Qt::cyan);
    painter.setBrush(brush);

    // 画线
    painter.drawLine(0, 0, 100, 100);
    // 画圆
    painter.drawEllipse(QPoint(100, 100), 50, 50);
    // 画矩形
    painter.drawRect(150, 0, 100, 50);
    // 写字
    painter.drawText(QRect(0, 250, 200, 100), "这是一行文字");
}
