#include "chooselevelscene.h"
#include "kcbutton.h"
#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QSoundEffect>
#include <QString>
#include <QTimer>

ChooseLevelScene::ChooseLevelScene(QWidget* parent)
    : QMainWindow { parent }
{
    //设置窗口固定大小
    this->setFixedSize(320, 588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar* bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu* startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction* quitAction = startMenu->addAction("退出");
    //点击退出 退出游戏
    connect(quitAction, &QAction::triggered, [=]() { this->close(); });

    // 选择关卡音效
    QSoundEffect* chooseSound = new QSoundEffect(this);
    chooseSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    // 返回音效
    QSoundEffect* backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));

    //返回按钮
    KCButton* closeBtn = new KCButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width() - closeBtn->width(), this->height() - closeBtn->height());
    //返回按钮功能实现
    connect(closeBtn, &KCButton::clicked, [=]() {
        // 播放返回音效
        backSound->play();
        QTimer::singleShot(500, this, [=]() {
            this->hide();
            //触发自定义信号，关闭自身，该信号写到 signals下做声明
            emit this->chooseSceneBack();
        });
    });

    // 创建20个关卡
    for (int i = 0; i < 20; i++) {
        KCButton* menuBtn = new KCButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        // i%4 控制列 i/4 控制行
        menuBtn->move(25 + (i % 4) * 70, 130 + (i / 4) * 70);
        // 显示图标上的文字
        QLabel* label = new QLabel(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        //设置居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->move(23 + (i % 4) * 70, 128 + (i / 4) * 70);
        //鼠标事件穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents, true);

        //监听选择关卡按钮的信号槽
        connect(menuBtn, &KCButton::clicked, [=]() {
            //游戏场景最好不用复用，直接移除掉创建新的场景
            if (playScene == NULL) {
                this->hide();
                //将选择的关卡号 传入给PlayerScene
                playScene = new PlayScene(i + 1);
                // 设置窗口中心位置
                playScene->setGeometry(this->geometry());
                playScene->show();

                connect(playScene, &PlayScene::chooseSceneBack, [=]() {
                    // 播放选择关卡音效
                    chooseSound->play();
                    this->show();
                    this->setGeometry(playScene->geometry());
                    delete playScene;
                    playScene = NULL;
                });
            }
        });
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}