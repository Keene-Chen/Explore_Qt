#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT
public:
    int timer1;
    int timer2;

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

public:
    // 定时器事件
    void timerEvent(QTimerEvent*);
    // 事件过滤器
    bool eventFilter(QObject*, QEvent*);

private:
    Ui::Widget* ui;
};
#endif // WIDGET_H
