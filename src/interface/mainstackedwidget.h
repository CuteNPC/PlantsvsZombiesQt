#ifndef MAINSTACKEDWIDGET_H
#define MAINSTACKEDWIDGET_H

#include <QStackedWidget>
#include "enum.h"

class MainMenu;
class SelectGameMenu;
class GameWidget;
class EndMenu;

class MainStackedWidget : public QStackedWidget
{
    Q_OBJECT

    MainMenu* mainMenu;             //主菜单界面
    SelectGameMenu* selectGameMenu; //选关界面
    EndMenu* endMenu;               //结束界面
    GameWidget* game;               //游戏界面

    int mainIndex;
    int selectGameIndex;
    int endIndex;
    int gameIndex;

    friend GameWidget;

public:
    MainStackedWidget(QWidget* parent_ = nullptr);
    void gameStart(int level);                //游戏开始
    void gameEnd(enum GameOverStatus status); //游戏结束 x为-1是手动退出 1是胜利 0是失败
};

#endif // MAINSTACKEDWIDGET_H
