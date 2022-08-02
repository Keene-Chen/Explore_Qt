#include "playscene.h"
#include "dataconfig.h"
#include "kcbutton.h"
#include "kccoin.h"
#include <QDebug>
#include <QFont>
#include <QLabel>
#include <QMenuBar>
#include <QPainter>
#include <QPropertyAnimation>
#include <QSoundEffect>
#include <QTimer>

PlayScene::PlayScene(int levalIndex)
{
    // 记录选择的关卡号
    this->levalIndex = levalIndex;
    qDebug() << "选择的关卡: " << this->levalIndex;
    // 配置游戏场景窗口信息
    this->setFixedSize(320, 588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币");
    QMenuBar* bar = this->menuBar();
    this->setMenuBar(bar);
    QMenu* startMenu = bar->addMenu("开始");
    QAction* quitAction = startMenu->addAction("退出");
    connect(quitAction, &QAction::triggered, [=]() { this->close(); });
    // 显示当前关卡信息
    QLabel* label = new QLabel(this);
    QFont font;
    font.setFamily("华文琥珀");
    font.setPointSize(18);
    label->setFont(font);
    label->setText(QString("Leavel: %1").arg(this->levalIndex));
    label->setGeometry(QRect(30, this->height() - 50, 120, 50));

    // 返回音效
    QSoundEffect* backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    //翻金币音效
    QSoundEffect* flipSound = new QSoundEffect(this);
    flipSound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
    //胜利按钮音效
    QSoundEffect* winSound = new QSoundEffect(this);
    winSound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));

    //返回按钮
    KCButton* closeBtn = new KCButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    closeBtn->setParent(this);
    closeBtn->move(this->width() - closeBtn->width(), this->height() - closeBtn->height());

    //返回按钮功能实现
    connect(closeBtn, &KCButton::clicked, [=]() {
        backSound->play();
        QTimer::singleShot(500, this, [=]() {
            this->hide();
            //触发自定义信号，关闭自身，该信号写到 signals下做声明
            emit this->chooseSceneBack();
        });
    });

    // 初始化关卡数据
    DataConfig config;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->gameArray[i][j] = config.mData[this->levalIndex][i][j];
        }
    }

    // 胜利图片
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width()) * 0.5, -tmpPix.height());

    //创建金币的背景图片
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            //绘制背景图片
            QLabel* label = new QLabel;
            label->setGeometry(0, 0, 50, 50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57 + i * 50, 200 + j * 50);

            QString img;
            if (this->gameArray[i][j] == 1) {
                img = ":/res/Coin0001.png";
            } else {
                img = ":/res/Coin0008.png";
            }

            // 创建金币对象
            KCCoin* coin = new KCCoin(img);
            coin->setParent(this);
            coin->move(59 + i * 50, 204 + j * 50);
            coin->posX = i; //记录x坐标
            coin->posY = j; //记录y坐标
            coin->flag = this->gameArray[i][j]; //记录正反标志

            // 将金币数据放入二维数组
            coinBtn[i][j] = coin;

            connect(coin, &KCCoin::clicked, [=]() {
                flipSound->play();
                // 锁定金币状态,防止翻转动画未执行完点击其他金币
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        coinBtn[i][j]->isWin = true;
                    }
                }

                // 改变金币状态，翻转金币
                coin->changeFlag();
                // 同步金币状态
                this->gameArray[i][j] = this->gameArray[i][j] == 1 ? 0 : 1; //数组内部记录的标志同步修改

                // 延时翻转周边金币
                QTimer::singleShot(300, this, [=]() {
                    // 检查右侧金币状态并同步
                    if (coin->posX + 1 <= 3) {
                        coinBtn[coin->posX + 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX + 1][coin->posY] = this->gameArray[coin->posX + 1][coin->posY] == 1 ? 0 : 1;
                    }
                    // 检查左侧金币状态并同步
                    if (coin->posX - 1 >= 0) {
                        coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX - 1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
                    }
                    // 检查上侧金币状态并同步
                    if (coin->posY + 1 <= 3) {
                        coinBtn[coin->posX][coin->posY + 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY + 1] = this->gameArray[coin->posX][coin->posY + 1] == 0 ? 1 : 0;
                    }
                    // 检查下侧金币状态并同步
                    if (coin->posY - 1 >= 0) {
                        coinBtn[coin->posX][coin->posY - 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY - 1] = this->gameArray[coin->posX][coin->posY - 1] == 0 ? 1 : 0;
                    }

                    // 取消锁定金币
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            coinBtn[i][j]->isWin = false;
                        }
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (coinBtn[i][j]->flag == false) {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if (this->isWin) {
                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                                // 胜利音效
                                winSound->play();
                                // 胜利动画
                                QPropertyAnimation* animation1 = new QPropertyAnimation(winLabel, "geometry");
                                animation1->setDuration(1000);
                                animation1->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                                animation1->setEndValue(QRect(winLabel->x(), winLabel->y() + 170, winLabel->width(), winLabel->height()));
                                animation1->setEasingCurve(QEasingCurve::OutBounce);
                                animation1->start();

                                // 每个金币是否胜利
                                coinBtn[i][j]->isWin = true;
                            }
                        }
                    }
                });
            });
        }
    }
}

// 重写绘图事件设置背景图片
void PlayScene::paintEvent(QPaintEvent* ev)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width() * 0.5, pix.height() * 0.5);
    painter.drawPixmap(10, 30, pix.width(), pix.height(), pix);
}
