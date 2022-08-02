#ifndef KCBUTTON_H
#define KCBUTTON_H

#include <QPushButton>

class KCButton : public QPushButton {
    Q_OBJECT
public:
    QString normalImgPath;
    QString pressImgPath;

public:
    KCButton(QString normalImg, QString pressImg = "");

public:
    // 开始按钮特效
    void zoom1();
    void zoom2();
    // 重写鼠标事件
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

signals:
};

#endif // KCBUTTON_H
