#ifndef KCLABEL_H
#define KCLABEL_H

#include <QLabel>

class KCLabel : public QLabel {
    Q_OBJECT
public:
    explicit KCLabel(QWidget* parent = nullptr);
    ~KCLabel();

public:
    // 鼠标进入事件
    void enterEvent(QEnterEvent*);
    // 鼠标离开事件
    void leaveEvent(QEvent*);
    // 鼠标移动
    void mouseMoveEvent(QMouseEvent*);
    // 鼠标按下
    void mousePressEvent(QMouseEvent*);
    // 鼠标释放
    void mouseReleaseEvent(QMouseEvent*);
    // 事件分发器
    bool event(QEvent*);

signals:
};

#endif // KCLABEL_H
