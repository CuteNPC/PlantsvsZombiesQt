#ifndef BACKBUTTON_H
#define BACKBUTTON_H

#include "include/size.h"
#include <QLabel>

#include <QLabel>

class GameWidget;

// 返回按钮
class BackButton : public QLabel
{
    // 按钮图像
    QPixmap pixmap;
    // 友元，方便直接操作
    friend class GameWidget;

  public:
    BackButton(GameWidget *parent_);
    void mousePressEvent(QMouseEvent *ev); // 捕获鼠标点击按钮事件
    void enterEvent(QEnterEvent *event);   // 捕获鼠标进入按钮区域事件
    void leaveEvent(QEvent *event);        // 捕获鼠标离开按钮区域事件
};

#endif // BACKBUTTON_H
