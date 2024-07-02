#ifndef MAINMENU_H
#define MAINMENU_H

#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include "QPainter"

class MainMenu : public QWidget
{
    Q_OBJECT
    QPushButton *startGameButton; //开始游戏按钮
    QPushButton *exitButton;      //退出按钮

public:
    explicit MainMenu(QStackedWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:
};

#endif // MAINMENU_H
