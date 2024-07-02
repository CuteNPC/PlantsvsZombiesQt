#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include "core/playthread.h"
#include "include/size.h"
#include "plant/plant.h"
#include "util/bullet.h"
#include "util/car.h"
#include "util/sun.h"
#include "zombie/zombie.h"
#include <QLabel>
#include <QMainWindow>
#include <QMutex>
#include <QQueue>
#include <QTimer>
#include <QVector>
#include <QWidget>

class Bullet;
class Sun;
class Car;
class Zombie;
class PicOnHand;
class Plant;
class CardList;
class Card;
class Shovel;
class BackButton;
class MainStackedWidget;

// 游戏窗体类
class GameWidget : public QWidget
{
    Q_OBJECT

    friend MainStackedWidget;

  public:
    QMutex *bul_mutex[ROW];
    QMutex *zom_mutex;
    QMutex *sun_mutex;

  private:
    int stage;              // 第几关
    CardList *cradlist;     // 卡片列
    int plantInHand;        // 手上的卡片
    bool ShoveInHand;       // 手上是否有铲子
    PicOnHand *picOnHand;   // 手上的植物
    QLabel *sunLabel;       // 显示阳光的标签
    Shovel *shovel;         // 铲子
    QTimer *Suntimer;       // 自然阳光生成计时
    /*, *refresh_timer*/    //
    int sunshine;           // 阳光数量
    BackButton *backButton; // 返回按钮

  public:
    int result = -1;                          // 游戏结局
    Plant *plants[ROW][COLUMN] = {{nullptr}}; // 植物指针数组，管理植物
    QVector<Bullet *> bullets[ROW];           // 管理子弹
    QVector<Zombie *> zombies[ROW];           // 管理僵尸
    QVector<Sun *> suns;                      // 管理阳光
    Car *cars[ROW];                           // 管理小车

    Mainthread *mainthread; // 用来不断刷新的线程
    Zombiethread *zomthread;

  public:
    explicit GameWidget(QWidget *parent = nullptr, int stage_ = 1);
    ~GameWidget();
    void mousePressEvent(QMouseEvent *ev);
    bool emptyHand();
    bool hasZombie(int x);
    void getCard(int id_, int x, int y);
    void putCard(int id_, int x, int y);
    void cancelCard();

    void getShovel(int x_, int y_);
    void putShovel(int x_, int y_);
    void cancelShovel();

    void tryMove(int x, int y);

    void remSun(int x);
    virtual void mouseMoveEvent(QMouseEvent *ev);
    bool enough(int x);
    void createPlant(int x_, int y_, int id_);
    void paintEvent(QPaintEvent *ev);

  public slots:
    // void pause();
    // void exit();
    void new_zombie(int id);
    void newSun();
    void addSun(int x);
    //    void refresh();
    void delete_car(int I);
};

#endif // GAMEWIDGET_H
