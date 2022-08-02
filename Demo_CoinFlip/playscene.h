#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "kccoin.h"
#include <QMainWindow>

class PlayScene : public QMainWindow {
    Q_OBJECT
public:
    int levalIndex;
    int gameArray[4][4]; // 游戏关卡数组
    KCCoin* coinBtn[4][4]; //金币按钮数组
    bool isWin; //是否胜利

public:
    PlayScene(int levalIndex);

public:
    void paintEvent(QPaintEvent* ev);
signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H