#include "interface/backbutton.h"
#include "include/enum.h"
#include "include/size.h"
#include "interface/gamewidget.h"
#include "interface/mainstackedwidget.h"
#include <QLabel>
#include <QPixmap>

BackButton::BackButton(GameWidget *parent_) : QLabel(parent_)
{
    // 设置尺寸
    setGeometry(MENU_SX, 0, MENU_X, MENU_Y);
    // 设置图片
    pixmap = QPixmap(":/resources/images/SelectorScreen_Quit1.png");
    setPixmap(pixmap);
    // 填充显示
    setScaledContents(true);
    // 显示
    show();
}

BackButton::~BackButton() {};

// 鼠标点击事件
void BackButton::mousePressEvent(QMouseEvent *ev)
{
    // 如果空手左键点击
    if (ev->button() == Qt::LeftButton && ((GameWidget *)parentWidget())->emptyHand())
    {
        // 游戏结束，2代表手动返回的结束代码
        ((MainStackedWidget *)(parentWidget()->parentWidget()))
            ->gameEnd(GameStatus::MANUAL_EXIT);
    }
    // 如果右键
    else if (ev->button() == Qt::RightButton)
    {
        // 清空手中的卡片或者铲子的
        ((GameWidget *)parentWidget())->cancelCard();
        ((GameWidget *)parentWidget())->cancelShovel();
    }
}

// 鼠标进入事件
void BackButton::enterEvent(QEnterEvent *)
{
    // 更改贴图
    pixmap = QPixmap(":/resources/images/SelectorScreen_Quit2.png");
    setPixmap(pixmap);
}

// 鼠标离开事件
void BackButton::leaveEvent(QEvent *)
{
    // 更改贴图
    pixmap = QPixmap(":/resources/images/SelectorScreen_Quit1.png");
    setPixmap(pixmap);
}
