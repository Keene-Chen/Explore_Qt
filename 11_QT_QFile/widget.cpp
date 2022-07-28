#include "widget.h"
#include "./ui_widget.h"
#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <QMessageBox>
#include <QPushButton>

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("11_QT_QFile");

    // 点击打开文件
    connect(ui->pushButton, &QPushButton::clicked, [=]() {
        QString filepath = QFileDialog::getOpenFileName(this, "打开文件", "E:\\zm", "Text files (*.txt)");
        if (filepath.isEmpty()) {
            QMessageBox::warning(this, "警告", "文件路径不能为空");
        } else {
            ui->lineEdit->setText(filepath);
            // 读取文件内容
            QFile file(filepath);
            file.open(QIODevice::ReadOnly);
            QByteArray array = file.readAll();
            ui->textEdit->setText(array);
            // 读取一行
            // while (!file.atEnd()) {
            //     file.readLine();
            // }
            file.close();
            // 写文件
            file.open(QFile::Append);
            file.write("写完啦");
            file.close();
        }
    });
}

Widget::~Widget()
{
    delete ui;
}
