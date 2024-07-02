#ifndef BULLET_H
#define BULLET_H
#include<QLabel>
#include<QPropertyAnimation>
#include<QMutex>

class GameWidget;
class once_movie;

//子弹类
class Bullet:public QLabel
{
    Q_OBJECT
public:
    int attack;                     //攻击力
    bool is_debuff, is_dead = 0;        //是否减速，是否已经被僵尸碰到
    QMutex* mutex;
    QPropertyAnimation* ani;
    QTimer* timer;
    Bullet(int x, int y, QWidget* ptr, int a = 1, bool b = 0);

public slots:
    void deleteLater();
    void to_be_deleted();
    void crash();

signals:
    void shut_down();
};

#endif // BULLET_H
