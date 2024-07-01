#include "mainstackedwidget.h"
#include"gamewidget.h"
#include"selectgamemenu.h"
#include"mainmenu.h"
#include<QStackedWidget>
#include"size.h"
#include"endmenu.h"

MainStackedWidget::MainStackedWidget(QWidget* parent)
    :QStackedWidget(parent)
{
    //设置大小
    setFixedSize(MAX_X,MAX_Y);

    //创建窗口
    mainMenu=new MainMenu(this);
    selectGameMenu=new SelectGameMenu(this);
    endMenu=new EndMenu(this);

    //将窗口加入到栈窗口中
    addWidget(mainMenu);
    addWidget(selectGameMenu);
    addWidget(endMenu);

    setCurrentIndex(0);
}

//游戏开始
void MainStackedWidget::gameStart(int x)
{
    game=new GameWidget(this,x);
    addWidget(game);
    setCurrentIndex(3);
}

//游戏结束 x为2是手动退出 1是胜利 0是失败
void MainStackedWidget::gameEnd(int x)
{
    removeWidget(game);
    setCurrentIndex(2);
    if(x==2)
    {
        setCurrentIndex(0);
    }
    else
    {
    endMenu->setBkg(x);
    }
    //delete game;
}
