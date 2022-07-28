#ifndef KCWIDGET_H
#define KCWIDGET_H

#include <QWidget>

class KCWidget : public QWidget
{
    Q_OBJECT

public:
    KCWidget(QWidget *parent = nullptr);
    ~KCWidget();
};
#endif // KCWIDGET_H
