#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->action_new->setIcon(QIcon(":/resource/doc.png"));
    ui->action_close->setIcon(QIcon(":/resource/interface.png"));
    ui->action_copy->setIcon(QIcon(":/resource/copy.png"));
    ui->action_paste->setIcon(QIcon(":/resource/paste.png"));
    ui->action_cut->setIcon(QIcon(":/resource/cut.png"));
    setWindowIcon(QIcon(":/resource/integrity.png"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

