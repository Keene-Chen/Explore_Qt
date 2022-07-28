#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->action_new->setIcon(QIcon(":/resource/save.png"));
    ui->action_close->setIcon(QIcon(":/resource/chart.png"));

    // 点击新建，创建对话框
    /**
     * 对话框分为：模态对话框和非模态对话框
     * 模态对话框：不可以对其他窗口进行操作
     * 非模态对话框：可以对其他窗口进行操作
     */
    void (MainWindow::*createSlot)() = &MainWindow::create;
    connect(ui->action_new, &QAction::triggered, this, createSlot);
}

void MainWindow::create()
{
    // 模态对话框
    // QDialog dlg(this);
    // dlg.exec();

    // 模态对话框
    // QDialog *dlg2= new QDialog(this);
    // dlg2->show();
    // dlg2->setAttribute(Qt::WA_DeleteOnClose);

    /* // 错误提示对话框
    QMessageBox::critical(this, "错误", "critical");
    // 信息提示对话框
    QMessageBox::information(this, "信息", "information");
    // 警告提示对话框
    QMessageBox::warning(this, "警告", "warning");
    // 询问提示对话框
    if (QMessageBox::Save == QMessageBox::question(this, "询问", "question", QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Save))
    {
        qDebug() << "点击的是保存按钮";
    }
    else
    {
        qDebug() << "点击的是取消按钮";
    } */

    // 颜色对话框
    // QColor color = QColorDialog::getColor();
    // qDebug() << color.redF() << color.greenF() << color.blueF();

    // 文件选择对话框
    // QString filepath = QFileDialog::getOpenFileName(this, "打开文件","E:/","Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)");
    // qDebug() << filepath.toUtf8().data();

    // 字体选择对话框
    bool *flag = nullptr;
    QFont font = QFontDialog::getFont(flag, this);
    qDebug() << font.toString();
}

MainWindow::~MainWindow()
{
    qDebug() << "窗口析构~";
    delete ui;
}
