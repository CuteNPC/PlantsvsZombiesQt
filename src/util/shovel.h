#ifndef SHOVEL_H
#define SHOVEL_H

#include "include/size.h"
#include <QLabel>
class GameWidget;

// 铲子类

class Shovel : public QLabel
{
    QPixmap pixmap;
    // 铲子图像;
    friend class GameWidget;

  public:
    Shovel(GameWidget *parent_);
    void mousePressEvent(QMouseEvent *ev); // 捕获鼠标点击铲子事件
    void enterEvent(QEnterEvent *event);   // 捕获鼠标进入铲子区域事件
    void leaveEvent(QEvent *event);        // 捕获鼠标离开铲子区域事件
};

#endif // SHOVEL_H
