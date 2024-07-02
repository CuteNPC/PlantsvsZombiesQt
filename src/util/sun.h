#ifndef SUN_H
#define SUN_H

#include<QLabel>
#include<QPushButton>
#include<QMovie>
#include<QPropertyAnimation>
#include<QTimer>
#include<QObject>
#include<QMouseEvent>

class GameWidget;

class Sun:public QLabel{
    Q_OBJECT
public:
    QPropertyAnimation* ani1,*ani2;//生成动画，收集动画
    QMovie* movie;
    QTimer *timer, *renewer;//
    GameWidget* parent;//指向gamewidget
    Sun(GameWidget* p, bool is_nature, int x = 0, int y = 0);
    //构造函数 第一个是父对象，第二个是是否是自然生成，第三四个是坐标
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *ev);

public slots:
    void deleteLater();
    //void to_be_deleted();
};

#endif // SUN_H
