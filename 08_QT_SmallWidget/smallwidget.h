#ifndef SMALLWIDGET_H
#define SMALLWIDGET_H

#include <QWidget>

namespace Ui
{
    class SmallWidget;
}

class SmallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SmallWidget(QWidget *parent = nullptr);
    ~SmallWidget();

public:
    // 对外提供设置值
    int getData();
    // 获取值
    void setData(int value);

private:
    Ui::SmallWidget *ui;
};

#endif // SMALLWIDGET_H
