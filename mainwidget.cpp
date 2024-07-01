#include "mainwidget.h"
#include<QStackedWidget>
#include<QWidget>
#include<QPushButton>
#include"mainmenu.h"
#include"mainstackedwidget.h"
#include"size.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    //设置主窗口大小，标题
    setFixedSize(MAX_X,MAX_Y);
    setWindowTitle("植物大战僵尸Qt版");
    //初始化StackedWidget
    mainStackedWidget = new MainStackedWidget(this);
}


