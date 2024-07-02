#include "interface/mainstackedwidget.h"
#include "include/enum.h"
#include "include/size.h"
#include "interface/endmenu.h"
#include "interface/gamewidget.h"
#include "interface/mainmenu.h"
#include "interface/selectgamemenu.h"
#include <QStackedWidget>

MainStackedWidget::MainStackedWidget(QWidget *parent) : QStackedWidget(parent)
{
    // 设置大小
    setFixedSize(MAX_X, MAX_Y);

    // 创建窗口
    mainMenu = new MainMenu(this);
    mainIndex = addWidget(mainMenu);

    selectGameMenu = new SelectGameMenu(this);
    selectGameIndex = addWidget(selectGameMenu);

    game = nullptr;

    endMenu = new EndMenu(this);
    endIndex = addWidget(endMenu);

    setCurrentIndex(mainIndex);
}

MainStackedWidget::~MainStackedWidget() {};

// 游戏开始
void MainStackedWidget::gameStart(int level)
{
    game = new GameWidget(this, level);
    gameIndex = addWidget(game);

    setCurrentIndex(gameIndex);
}

// 游戏结束 x为2是手动退出 1是胜利 0是失败
void MainStackedWidget::gameEnd(enum GameStatus status)
{
    removeWidget(game);
    switch (status)
    {
    case GameStatus::WIN:
        endMenu->setWinBkg();
        setCurrentIndex(endIndex);
        break;
    case GameStatus::LOSE:
        endMenu->setLoseBkg();
        setCurrentIndex(endIndex);
        break;
    case GameStatus::MANUAL_EXIT:
        setCurrentIndex(0);
        break;
    default:
        exit(-1);
        break;
    }
}
