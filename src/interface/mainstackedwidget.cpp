#include "mainstackedwidget.h"
#include <QStackedWidget>
#include "endmenu.h"
#include "enum.h"
#include "gamewidget.h"
#include "mainmenu.h"
#include "selectgamemenu.h"
#include "size.h"

MainStackedWidget::MainStackedWidget(QWidget* parent)
    : QStackedWidget(parent)
{
    //设置大小
    setFixedSize(MAX_X, MAX_Y);

    //创建窗口
    mainMenu = new MainMenu(this);
    mainIndex = addWidget(mainMenu);

    selectGameMenu = new SelectGameMenu(this);
    selectGameIndex = addWidget(selectGameMenu);

    game = nullptr;

    endMenu = new EndMenu(this);
    endIndex = addWidget(endMenu);

    setCurrentIndex(mainIndex);
}

//游戏开始
void MainStackedWidget::gameStart(int level)
{
    game = new GameWidget(this, level);
    gameIndex = addWidget(game);

    setCurrentIndex(gameIndex);
}

//游戏结束 x为2是手动退出 1是胜利 0是失败
void MainStackedWidget::gameEnd(enum GameOverStatus status)
{
    removeWidget(game);
    switch (status) {
    case GameOverStatus::WIN:
        endMenu->setWinBkg();
        setCurrentIndex(endIndex);
        break;
    case GameOverStatus::LOSE:
        endMenu->setLoseBkg();
        setCurrentIndex(endIndex);
        break;
    case GameOverStatus::MANUAL_EXIT:
        setCurrentIndex(0);
        break;
    case GameOverStatus::ERROR:
    default:
        exit(-1);
        break;
    }
}
