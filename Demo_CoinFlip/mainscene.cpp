#include "mainscene.h"
#include "./ui_mainscene.h"
#include "chooselevelscene.h"
#include "kcbutton.h"
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>

MainScene::MainScene(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    // 加载ui界面文件
    ui->setupUi(this);

    // 配置主场景
    this->setWindowTitle("翻金币主场景");
    this->setFixedSize(320, 588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));

    // 退出游戏
    connect(ui->actionQuit, &QAction::triggered, [=]() {
        this->close();
    });

    // 开始按钮
    KCButton* startBtn = new KCButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    // 加载关卡选择场景
    ChooseLevelScene* chooseScene = new ChooseLevelScene();
    connect(startBtn, &QPushButton::clicked, [=]() {
        // 开始按钮特效
        startBtn->zoom1();
        startBtn->zoom2();
        QTimer::singleShot(500, [=]() {
            this->hide();
            // 设置窗口中心位置
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });
    });

    //监听选择场景的返回按钮
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, [=]() {
        this->setGeometry(chooseScene->geometry());
        this->show();
    });
}

MainScene::~MainScene()
{
    delete ui;
}

// 重写绘图事件设置背景图片
void MainScene::paintEvent(QPaintEvent* ev)
{
    // 主场景背景图
    QPainter painter(this);
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
    // 主场景标题图
    pix.load(":/res/Title.png");
    // 缩放图片
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix);
}
