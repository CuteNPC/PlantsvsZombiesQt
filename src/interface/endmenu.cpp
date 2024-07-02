#include "interface/endmenu.h"
#include "include/constval.h"
#include "include/size.h"
#include <QPainter>
#include <QWidget>

// 结束画面
EndMenu::EndMenu(QStackedWidget *parent) : QWidget(parent)
{
    // 设置名称和尺寸
    setObjectName("Endmenu");
    setFixedSize(MAX_X, MAX_Y);

    backButton = new QPushButton("返回", this); // 构造对象，初始化按钮文本和父窗口
    backButton->setGeometry(150, 450, 800, 50);

    connect(backButton, &QPushButton::clicked, parent,
            [=] { parent->setCurrentIndex(0); }); // 按下按钮，跳转到stack的第1页
}

EndMenu::~EndMenu(){};

void EndMenu::setWinBkg() { x = 1; }

void EndMenu::setLoseBkg() { x = 0; }

void EndMenu::paintEvent(QPaintEvent *)
{
    // 创建画家，指定绘图设备
    QPainter painter(this);
    // 创建QPixmap对象
    QPixmap pix;
    // 加载图片
    pix.load(backG[2 + x]);
    // 绘制背景图
    painter.drawPixmap(0, 0, 1100, 600, pix);
    setStyleSheet("#Endmenu{border-image:url(" + backG[2 + x] + ")}");
}
