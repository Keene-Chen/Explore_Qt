#ifndef KCBUTTON_H
#define KCBUTTON_H

#include <QPushButton>

class KCButton : public QPushButton
{
    Q_OBJECT
public:
    explicit KCButton(QWidget *parent = nullptr);
    ~KCButton();

signals:
};

#endif // KCBUTTON_H
