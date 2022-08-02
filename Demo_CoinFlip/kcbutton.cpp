#include "kcbutton.h"
#include <QMouseEvent>
#include <QPixmap>
#include <QPropertyAnimation>

KCButton::KCButton(QString normalImg, QString pressImg)
{
    // 初始化图片路径
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;
    // QPixmap加载图片
    QPixmap pix;
    if (!pix.load(normalImg)) {
        QString str = QString("图片加载失败 %1").arg(normalImgPath);
        qDebug() << str;
        return;
    }
    // 设置图片大小
    this->setFixedSize(pix.width(), pix.height());
    // 设置不规则形状
    this->setStyleSheet("QPushButton{border:0px;}");
    // 设置图标
    this->setIcon(pix);
    // 设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));
}

// 启动按钮特效
void KCButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    //设置时间间隔，单位毫秒
    animation->setDuration(200);
    //创建起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //创建结束位置
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    // animation->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation->start();
}

void KCButton::zoom2()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

// 重写鼠标事件
void KCButton::mousePressEvent(QMouseEvent* e)
{
    if (pressImgPath != "") //选中路径不为空，显示选中图片
    {
        QPixmap pixmap;
        bool ret = pixmap.load(pressImgPath);
        if (!ret) {
            qDebug() << pressImgPath << "加载图片失败!";
        }

        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    //交给父类执行按下事件
    return QPushButton::mousePressEvent(e);
}
void KCButton::mouseReleaseEvent(QMouseEvent* e)
{
    if (normalImgPath != "") //选中路径不为空，显示选中图片
    {
        QPixmap pixmap;
        bool ret = pixmap.load(normalImgPath);
        if (!ret) {
            qDebug() << normalImgPath << "加载图片失败!";
        }
        this->setFixedSize(pixmap.width(), pixmap.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(), pixmap.height()));
    }
    //交给父类执行 释放事件
    return QPushButton::mouseReleaseEvent(e);
}