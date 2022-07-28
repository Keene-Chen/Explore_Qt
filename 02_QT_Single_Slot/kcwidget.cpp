/**
 * Author:   KeeneChen
 * DateTime: 2022.07.21-13:10:02
 * Description: 打铃时，老师下课，学生放学
 */
#include "kcwidget.h"
#include <QPushButton>
#include <QDebug>

KCWidget::KCWidget(QWidget *parent)
    : QWidget(parent)
{
    // 窗口配置信息
    setWindowTitle("02_Single_Slot");
    setFixedSize(1280, 720);

    QPushButton *btn = new QPushButton("KeeneChen", this);
    btn->setFixedSize(80, 30);
    // 系统自带信号和槽函数
    /**
     * connect(sender, signal, receiver, slot);
     * sender 信号发送者 对象的指针
     * signal 发送的信号 函数地址
     * receiver 信号接收者 对象的指针
     * slot 槽函数，接收信号后的处理动作 函数地址
     */
    connect(btn, &QPushButton::clicked, this, &QPushButton::close);

    // 实例化老师和学生，并挂载到对象树上
    this->teacher = new Teacher(this);
    this->student = new Student(this);
    // 调用自定义信号和槽函数
    // connect(teacher, &Teacher::off_work, student, &Student::class_is_over);

    // 调用重载的信号和槽函数,当有重载函数时就必须用函数指针指定具体那个重载函数
    /* void (Teacher::*TeacherSingle)(QString) = &Teacher::off_work; // 使用函数指针获取要调用的具体函数
    void (Student::*StudentSlot)(QString) = &Student::class_is_over;
    connect(teacher, TeacherSingle, student, StudentSlot);
    调用打铃触发老师下课
    jow(); */

    // 通过按钮触发打铃
    QPushButton *btn1 = new QPushButton("打铃", this);
    btn1->setFixedSize(80, 30);
    btn1->move(80, 0);

    void (Teacher::*TeacherSingle)() = &Teacher::off_work;
    void (Student::*StudentSlot)() = &Student::class_is_over;
    // 连接无参槽函数
    connect(teacher, TeacherSingle, student, StudentSlot);
    // 通过信号和信号两两连接实现按钮触发打铃信号
    connect(btn1, &QPushButton::clicked, teacher, TeacherSingle);

    // Lambda 应用
    QPushButton *btn2 = new QPushButton("0",this);
    btn2->setFixedSize(80, 30);
    btn2->move(160, 0);
    static int count = 0;
    connect(btn2, &QPushButton::clicked, this, [=]()
            { count++; btn2->setText(QString::number(count, 10)); });
}

KCWidget::~KCWidget()
{
    qDebug() << "窗口析构~";
}

// 打铃
void KCWidget::jow()
{
    // 使用emit宏触发自定义信号
    emit this->teacher->off_work();
    // emit this->teacher->off_work("张三");
}
