#include "student.h"
#include <QDebug>

Student::Student(QObject *parent)
    : QObject{parent}
{
}

void Student::class_is_over()
{
    static int count = 1;
    qDebug() << "学生放学了" << count++;
}

void Student::class_is_over(QString name)
{
    // QString转char *  通过.toUtf8转为QByteArray类型  通过.data()转为char *
    qDebug() << name.toUtf8().data() << "放学了";
}
