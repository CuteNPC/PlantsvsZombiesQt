#ifndef SELECTGAMEMENU_H
#define SELECTGAMEMENU_H

#include <QWidget>
#include<QPushButton>
#include<QStackedWidget>
#include"mainstackedwidget.h"

class SelectGameMenu : public QWidget
{
    Q_OBJECT

    //选关 返回按钮
    QPushButton startButton[3];
    QPushButton *backButton;

public:
    explicit SelectGameMenu(MainStackedWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:

};

#endif // SELECTGAMEMENU_H
