#include "shovel.h"
#include<QPixmap>
#include<QLabel>
#include"gamewidget.h"
#include"constval.h"
#include"size.h"
#include"mainstackedwidget.h"

Shovel::Shovel(GameWidget *parent_):QLabel(parent_)
{
    //设置尺寸，图像，填充显示
    setGeometry(SH_X,SH_Y,CARD_Y,CARD_Y);
    pixmap=QPixmap(shovelImg[0]);
    setPixmap(pixmap);
    setScaledContents(true);
    show();
}

//鼠标点击事件
void Shovel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        //如果左键，尝试拾取铲子
        ((GameWidget*)parentWidget())->getShovel(ev->x(),ev->y());
    }
    else if(ev->button()==Qt::RightButton)
    {
        //右键取消铲子
        ((GameWidget*)parentWidget())->cancelCard();
        ((GameWidget*)parentWidget())->cancelShovel();
    }
}

//鼠标进入事件
void Shovel::enterEvent(QEnterEvent *)
{
    //更改贴图
    pixmap=QPixmap(shovelImg[1]);
    setPixmap(pixmap);
}

//鼠标离开事件
void Shovel::leaveEvent(QEvent *)
{
    //更改贴图
    pixmap=QPixmap(shovelImg[0]);
    setPixmap(pixmap);
}
