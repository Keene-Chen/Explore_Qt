#include "kclabel.h"

#include <QDebug>
#include <QMouseEvent>

KCLabel::KCLabel(QWidget* parent)
    : QLabel { parent }
{
    // 设置鼠标追踪
    setMouseTracking(false);
}

KCLabel::~KCLabel() { }

// 鼠标进入事件
void KCLabel::enterEvent(QEnterEvent*) { qDebug() << "鼠标进入"; }

// 鼠标离开事件
void KCLabel::leaveEvent(QEvent*) { qDebug() << "鼠标离开"; }

// 鼠标移动事件
void KCLabel::mouseMoveEvent(QMouseEvent* ev)
{
    // 获取鼠标坐标
    QString str2 = QString("x %1,y %2").arg(ev->position().x()).arg(ev->position().y());
    // 是否为鼠标左键
    if (ev->buttons() & Qt::LeftButton) {
        qDebug() << str2;
    } else {
        qDebug() << str2;
    }
}

// 鼠标按下事件
void KCLabel::mousePressEvent(QMouseEvent* ev)
{
    if (ev->button() == Qt::LeftButton) {
        qDebug() << QString("x %1,y %2").arg(ev->position().x()).arg(ev->position().y());
    }
}

// 鼠标释放事件
void KCLabel::mouseReleaseEvent(QMouseEvent* ev)
{
    if (ev->button() == Qt::LeftButton) {
        qDebug() << QString("x %1,y %2").arg(ev->position().x()).arg(ev->position().y());
    }
}

// 事件分发器
bool KCLabel::event(QEvent* e)
{
    // 拦截事件分发器，不往下分发事件
    if (e->type() == QEvent::MouseButtonPress) {
        // 父类转换为子类
        QMouseEvent* ev = static_cast<QMouseEvent*>(e);
        qDebug() << QString("事件分发器 x %1,y %2").arg(ev->position().x()).arg(ev->position().y());
        return true;
    }
    // 让父类处理其他事件
    return QLabel::event(e);
}
