#include "cardlist.h"
#include "card.h"
#include "gamewidget.h"

//卡槽窗口类 实现
CardList::CardList(QWidget *parent, int len_)
    : QWidget{parent}
{
    len = len_;                                               //卡槽列长度
    setGeometry(CARD_SX, CARD_SY, MAX_CARD * CARD_X, CARD_Y); //位置形状
    for (int i = 1; i <= len; i++) {
        cardPointer[i] = new Card(this, i); //构造这些卡槽
    }
}

//返回一个卡槽指针，供游戏窗体使用
Card *CardList::cardptr(int x)
{
    return cardPointer[x];
}
