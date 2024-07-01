#ifndef ENDMENU_H
#define ENDMENU_H

#include <QWidget>
#include<QPushButton>
#include<QStackedWidget>

//结束画面
class EndMenu : public QWidget
{
    Q_OBJECT
    QPushButton* backButton;//返回按钮
    int x=0;//状态 0是失败 1是胜利

public:
    explicit EndMenu(QStackedWidget *parent = nullptr);//结束菜单
    void paintEvent(QPaintEvent *);//绘制背景
    void setBkg(int x);//设置背景
signals:

};

#endif // ENDMENU_H
