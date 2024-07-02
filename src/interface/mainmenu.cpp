#include "interface/mainmenu.h"
#include "include/size.h"
#include "interface/mainstackedwidget.h"
#include <QDebug>
#include <QPainter>
#include <QStackedWidget>

MainMenu::MainMenu(QStackedWidget *parent) : QWidget{parent}
{
    // 设置大小
    setObjectName("mainmenu");
    setStyleSheet("#mainmenu{border-image:url(:/resources/images/bkg1.png)}");

    setFixedSize(MAX_X, MAX_Y);
    // 五个按钮
    startGameButton = new QPushButton(this);          // 初始化按钮文本和父窗口
    startGameButton->setGeometry(624, 128, 292, 260); // 设置大小
    startGameButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);"); // 设置尺寸
    connect(startGameButton, &QPushButton::clicked, parent,
            [=] { parent->setCurrentIndex(1); }); // 按下按钮，跳转到stack的第1页

    exitButton = new QPushButton(this);        // 初始化按钮文本和父窗口
    exitButton->setGeometry(989, 516, 70, 29); // 设置大小
    exitButton->setStyleSheet("background-color: rgba(255, 255, 255, 0);"); // 设置尺寸
    connect(exitButton, &QPushButton::clicked, parent->parentWidget(),
            &QWidget::close); // 按下按钮，关闭mainmenu；从而关闭整个程序
}

MainMenu::~MainMenu() {};

void MainMenu::paintEvent(QPaintEvent *)
{
    // 创建画家，指定绘图设备
    QPainter painter(this);
    // 创建QPixmap对象
    QPixmap pix;
    // 加载图片
    pix.load(":/resources/images/bkg1.png");
    // 绘制背景图
    painter.drawPixmap(0, 0, 1100, 600, pix);
}
