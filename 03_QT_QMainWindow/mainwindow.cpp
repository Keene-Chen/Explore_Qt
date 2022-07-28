#include "mainwindow.h"
#include <QPushButton>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 窗口配置
    setWindowTitle("03_QMainWindow");
    setFixedSize(1280, 720);

    // 1.添加菜单栏，只能有一个
    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    QMenu *fileMenu = bar->addMenu("文件");
    QMenu *editMenu = bar->addMenu("编辑");

    // 创建菜单项
    QAction *newAction = fileMenu->addAction("新建文件");
    QAction *saveAction = fileMenu->addAction("保存文件");
    // 添加分割线
    fileMenu->addSeparator();
    QAction *closeAction = fileMenu->addAction("关闭文件");
    QAction *cutAction = editMenu->addAction("剪切");
    QAction *copyAction = editMenu->addAction("复制");
    QAction *pasteAction = editMenu->addAction("粘贴");

    // 2.添加工具栏，可以有多个
    QToolBar *toolBar = new QToolBar(this);
    addToolBar(Qt::TopToolBarArea, toolBar);
    // 设置只允许左右停靠
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);
    // 设置是否允许浮动
    toolBar->setFloatable(false);
    // 设置是否允许移动(总开关)
    toolBar->setMovable(false);
    // 添加工具栏中的部件
    toolBar->addAction(newAction);
    toolBar->addSeparator();
    toolBar->addAction(closeAction);

    // 3.添加状态栏，只能有一个
    QStatusBar *stBar = statusBar();
    setStatusBar(stBar);
    QLabel *label1 = new QLabel("左侧提示", this);
    stBar->addWidget(label1);
    QLabel *label2 = new QLabel("右侧提示", this);
    stBar->addPermanentWidget(label2);

    // 4.添加铆接部件(浮动窗口)，可以有多个
    QDockWidget *dock = new QDockWidget("信息", this);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // 5.添加核心部件，只能有一个
    QTextEdit *edit = new QTextEdit(this);
    setCentralWidget(edit);
}

MainWindow::~MainWindow()
{
}
