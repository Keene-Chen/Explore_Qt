#include "kcwidget.h"
#include "kcbutton.h"
#include <QPushButton>
#include <QDebug>

KCWidget::KCWidget(QWidget *parent)
    : QWidget(parent)
{
    // 按钮1
    QPushButton *btn1 = new QPushButton;
    btn1->setParent(this);
    btn1->setText("这是按钮");
    btn1->resize(80, 30);

    // 按钮2,使用构造函数创建按钮
    QPushButton *btn2 = new QPushButton("按钮2", this);
    btn2->move(75, 0);
    btn2->resize(80, 30);

    // 重置窗口大小
    // setMaximumSize(1280, 720);
    // setMinimumSize(256, 144);
    // resize(800, 600);
    // 设置窗口固定大小
    setFixedSize(1280, 720);
    // 窗口标题
    setWindowTitle("01_hello_QT");

    // 调用自定义按钮
    KCButton *kcbtn = new KCButton(this);
    kcbtn->setText("自定义按钮");
    kcbtn->move(150, 0);
    kcbtn->resize(80, 30);

    // 信号和槽函数
    connect(btn1, &QPushButton::clicked, this, &QPushButton::close);
    connect(kcbtn, &QPushButton::clicked, this, [=]()
            { kcbtn->setText("我被修改了"); });
}

KCWidget::~KCWidget()
{
    qDebug() << "窗口析构";
}
