#include "card.h"
#include <QLabel>
#include <QMouseEvent>
#include <QTimer>
#include <QTimerEvent>
#include "cardlist.h"
#include "constval.h"
#include "gamewidget.h"
#include "size.h"

//卡槽类 实现
Card::Card(QWidget *parent, int id_)
    : QLabel(parent)
    , mask(parent)
{
    coldTime = maxColdTime[id_] - 100; //冷却时间初始化为已经冷却完毕
    grandParent = (GameWidget *) (parentWidget()->parentWidget()); //找游戏窗口的指针，方便使用
    id = id_;                                                      //id初始化

    setGeometry(CARD_X * (id - 1), CARD_SY, CARD_X, CARD_Y); //设置坐标和大小

    mask.setGeometry(CARD_X * (id - 1), CARD_SY, CARD_X, CARD_Y); //设置坐标和大小
    mask.setStyleSheet("background-color: rgba(0, 0, 0, 128);");
    mask.show();

    imgPath = cImgPath[id];       //取路径字符串数组的指针
    pixmap = QPixmap(imgPath[0]); //取图片（有两张，0是暗的，1是亮的）
    setPixmap(pixmap);            //设置图片
    setScaledContents(true);      //填充显示

    timer = new QTimer(this); //设置计时器
    timer->start(TICKTIME);   //开始计时

    //设置计时策略，每50ms让coldTime加50，直到达到最大冷却时间
    connect(timer, &QTimer::timeout, [=]() {
        if (coldTime < maxColdTime[id]) {
            //coldTime=maxColdTime[id];
            coldTime += TICKTIME;
            mask.setGeometry(CARD_X * (id - 1),
                             CARD_Y * coldTime / maxColdTime[id],
                             CARD_X,
                             CARD_Y - CARD_Y * coldTime / maxColdTime[id]);
        }
    });
}

//鼠标点击事件
void Card::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        //激活条件：鼠标上没有卡牌，阳光足够，冷却时间已到
        if (grandParent->emptyHand() && grandParent->enough(plantCost[id])
            && coldTime >= maxColdTime[id])
            grandParent->getCard(id, ev->x(), ev->y());
    } else if (ev->button() == Qt::RightButton) {
        //取消卡牌和铲子
        grandParent->cancelCard();
        grandParent->cancelShovel();
    }
}

//鼠标进入事件
void Card::enterEvent(QEnterEvent *event)
{
    //更改贴图
    if (coldTime >= maxColdTime[id] && grandParent->enough(plantCost[id])) {
        pixmap = QPixmap(imgPath[1]);
        setPixmap(pixmap);
    }
}

//鼠标离开事件
void Card::leaveEvent(QEvent *event)
{
    //更改贴图
    pixmap = QPixmap(imgPath[0]);
    setPixmap(pixmap);
}

//设置冷却时间，用于清零
void Card::setColdTime(int x)
{
    coldTime = x;
}
