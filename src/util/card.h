#ifndef CARD_H
#define CARD_H

#include "include/size.h"
#include <QLabel>
#include <QTimer>
#include <QWidget>

class CardList;
class GameWidget;

// 卡槽类
class Card : public QLabel
{
    Q_OBJECT
    QLabel mask;             // 遮住卡牌的阴影
    int id;                  // 卡牌id
    QString *imgPath;        // 贴图路径
    QPixmap pixmap;          // 贴图
    QTimer *timer;           // 计时器，用于让冷却时间增加
    int coldTime;            // 冷却时间
    GameWidget *grandParent; // 找游戏窗口的指针，方便使用

    friend class GameWidget;

  public:
    Card(QWidget *parent, int id_);        // 构造函数
    void mousePressEvent(QMouseEvent *ev); // 捕获鼠标点击卡牌事件
    void enterEvent(QEnterEvent *event);   // 捕获鼠标进入卡牌区域事件
    void leaveEvent(QEvent *event);        // 捕获鼠标离开卡牌区域事件
    void setColdTime(int x);               // 设置冷却时间（用于放置后时间归零）

  signals:
};

#endif // CARD_H
