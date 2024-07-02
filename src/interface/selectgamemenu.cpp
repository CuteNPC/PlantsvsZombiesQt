#include "interface/selectgamemenu.h"
#include "include/size.h"
#include "interface/mainstackedwidget.h"
#include <QPainter>

SelectGameMenu::SelectGameMenu(MainStackedWidget *parent) : QWidget{parent}
{
    // 设置背景
    setObjectName("selectgamemenu");
    setStyleSheet("#selectgamemenu{border-image:url(:/resources/images/bkg2.png)}");

    // 设置窗口大小
    setFixedSize(MAX_X, MAX_Y);

    // 设置三个关卡
    for (int j = 0; j <= 2; j++)
    {
        startButton[j].setParent(this);
        startButton[j].setText(QString::number(j + 1));
        startButton[j].setGeometry(150 + j * 300, 100, 200, 300);

        connect(&startButton[j], &QPushButton::clicked, [=]() { parent->gameStart(j + 1); });
    }

    // 返回按钮
    backButton = new QPushButton("返回", this);
    backButton->setGeometry(150, 450, 800, 50);
    connect(backButton, &QPushButton::clicked, parent, [=] { parent->setCurrentIndex(0); });
}

SelectGameMenu::~SelectGameMenu(){};

void SelectGameMenu::paintEvent(QPaintEvent *)
{
    // 创建画家，指定绘图设备
    QPainter painter(this);
    // 创建QPixmap对象
    QPixmap pix;
    // 加载图片
    pix.load(":/resources/images/bkg2.png");
    // 绘制背景图
    painter.drawPixmap(0, 0, 1100, 600, pix);
}
