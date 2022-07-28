#include "kcbutton.h"
#include <QDebug>

KCButton::KCButton(QWidget *parent)
    : QPushButton{parent}
{
}

KCButton::~KCButton()
{
    qDebug() << "按钮析构";
}
