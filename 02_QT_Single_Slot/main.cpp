#include "kcwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KCWidget w;
    w.show();
    return a.exec();
}
