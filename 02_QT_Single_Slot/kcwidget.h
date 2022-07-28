#ifndef KCWIDGET_H
#define KCWIDGET_H

#include "teacher.h"
#include "student.h"
#include <QWidget>

class KCWidget : public QWidget
{
    Q_OBJECT

public:
    KCWidget(QWidget *parent = nullptr);
    ~KCWidget();

public:
    // 声明老师和学生对象
    Teacher *teacher;
    Student *student;
    // 到点打铃
    void jow();
};
#endif // KCWIDGET_H
