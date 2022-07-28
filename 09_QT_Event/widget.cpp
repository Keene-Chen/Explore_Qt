#include "widget.h"
#include "./ui_widget.h"
#include <QMouseEvent>
#include <QTimer>

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    setWindowTitle("09_QT_Event");
    setFixedSize(350, 200);
    ui->setupUi(this);
    // 开启定时器
    timer1 = startTimer(1000);
    timer2 = startTimer(2000);

    // 定时器对象
    QTimer* timer3 = new QTimer(this);
    timer3->start(500);
    // 每隔0.5s抛出信号
    connect(timer3, &QTimer::timeout, [=]() {
        static int count3 = 0;
        ui->label_4->setText(QString::number(count3++));
    });
    // 点击按钮停止定时器
    connect(ui->pushButton, &QPushButton::clicked, [=]() {
        timer3->stop();
    });

    // 安装事件过滤器
    ui->label->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent* te)
{
    if (te->timerId() == timer1) {
        static int count1 = 0;
        ui->label_2->setText(QString::number(count1++));
    }
    if (te->timerId() == timer2) {
        static int count2 = 0;
        ui->label_3->setText(QString::number(count2++));
    }
}

// 事件过滤器
bool Widget::eventFilter(QObject* obj, QEvent* e)
{
    if (obj == ui->label) {
        if (e->type() == QEvent::MouseButtonPress) {
            // 父类转换为子类
            QMouseEvent* ev = static_cast<QMouseEvent*>(e);
            qDebug() << QString("事件过滤器 x %1,y %2").arg(ev->position().x()).arg(ev->position().y());
            return true;
        }
    }

    // 让父类处理其他事件
    return QWidget::eventFilter(obj, e);
}
