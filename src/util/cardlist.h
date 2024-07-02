#ifndef CARDLIST_H
#define CARDLIST_H

#include "include/size.h"
#include <QWidget>

class Card;
class GameWidget;

// 卡槽窗口类 声明
class CardList : public QWidget
{
    Q_OBJECT
    int len;                     // 卡槽长度
    Card *cardPointer[MAX_CARD]; // 卡槽指针数组

  public:
    explicit CardList(QWidget *parent = nullptr, int len_ = 0); // 构造函数
    ~CardList() noexcept;                                       // 构造函数
    Card *cardptr(int x);                                       // 返回一个卡槽指针

  signals:
};

#endif // CARDLIST_H
