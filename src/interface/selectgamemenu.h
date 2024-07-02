#ifndef SELECTGAMEMENU_H
#define SELECTGAMEMENU_H

#include "interface/mainstackedwidget.h"
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>

class SelectGameMenu : public QWidget
{
    Q_OBJECT

    // 选关 返回按钮
    QPushButton startButton[3];
    QPushButton *backButton;

  public:
    explicit SelectGameMenu(MainStackedWidget *parent = nullptr);
    ~SelectGameMenu() noexcept;
    void paintEvent(QPaintEvent *);
  signals:
};

#endif // SELECTGAMEMENU_H
