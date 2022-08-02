#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include "playscene.h"
#include <QMainWindow>

class ChooseLevelScene : public QMainWindow {
    Q_OBJECT
public:
    PlayScene* playScene = nullptr;

public:
    explicit ChooseLevelScene(QWidget* parent = nullptr);

public:
    void paintEvent(QPaintEvent* ev);

signals:
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
