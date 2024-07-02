#ifndef ENDMENU_H
#define ENDMENU_H

#include "include/enum.h"
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>

// 结束画面
class EndMenu : public QWidget
{
    Q_OBJECT
    QPushButton *backButton; // 返回按钮
    int x = 0;               // 状态 0是失败 1是胜利

  public:
    explicit EndMenu(QStackedWidget *parent = nullptr); // 结束菜单
    ~EndMenu() noexcept; // 结束菜单
    void paintEvent(QPaintEvent *);                     // 绘制背景
    void setWinBkg();                                 // 设置背景
    void setLoseBkg();                                 // 设置背景
  signals:
};

#endif // ENDMENU_H
