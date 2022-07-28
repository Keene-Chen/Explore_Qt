#include "smallwidget.h"
#include "ui_smallwidget.h"

SmallWidget::SmallWidget(QWidget *parent) : QWidget(parent),
                                            ui(new Ui::SmallWidget)
{
    ui->setupUi(this);

    // SpinBox 与 右侧滚动条交互
    // 使用函数指针确定重载的是那个函数版本
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(100);
    void (QSpinBox::*spinBoxP)(int) = &QSpinBox::valueChanged;
    connect(ui->spinBox, spinBoxP, ui->horizontalSlider, [=](int value)
            { ui->horizontalSlider->setValue(value); });

    // 右侧滚动条 与 SpinBox交互
    ui->horizontalSlider->setMinimum(1);
    ui->horizontalSlider->setMaximum(100);
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, [=](int value)
            { ui->spinBox->setValue(value); });
}

// 获取值
int SmallWidget::getData()
{
    return ui->horizontalSlider->value();
}
// 设置值
void SmallWidget::setData(int value)
{
    ui->horizontalSlider->setValue(value);
}

SmallWidget::~SmallWidget()
{
    delete ui;
}
