#include "mainscene.h"
#include <QApplication>
#include <QSoundEffect>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainScene w;
    w.show();
    QSoundEffect effect;
    effect.setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    effect.setVolume(0.25f);
    effect.play();
    return a.exec();
}
