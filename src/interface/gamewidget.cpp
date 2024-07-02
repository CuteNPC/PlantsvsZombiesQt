#include "interface/gamewidget.h"
#include "core/playthread.h"
#include "include/constval.h"
#include "include/size.h"
#include "interface/backbutton.h"
#include "interface/mainstackedwidget.h"
#include "plant/coldpeashooter.h"
#include "plant/nut.h"
#include "plant/peashooter.h"
#include "plant/plant.h"
#include "plant/sunflower.h"
#include "plant/twopeashooter.h"
#include "util/card.h"
#include "util/cardlist.h"
#include "util/piconhand.h"
#include "util/shovel.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

GameWidget::GameWidget(QWidget *parent, int stage_)
    : QWidget(parent), zom_mutex(new QMutex()), zomthread(new Zombiethread(this)),
      sun_mutex(new QMutex()), /*, refresh_timer(new QTimer())*/
      Suntimer(new QTimer()), mainthread(new Mainthread(this))
{
    // 把返回按钮与结束游戏的功能连接起来
    connect(mainthread, &Mainthread::finished,
            [=]() { ((MainStackedWidget *)(parentWidget()))->gameEnd(result); });
    // 初始化
    stage = stage_;
    sunshine = 150;
    plantInHand = 0;
    ShoveInHand = 0;
    picOnHand = NULL;
    shovel = new Shovel(this);
    backButton = new BackButton(this);
    srand(clock());
    for (int i = 0; i < 5; i++)
    {
        bul_mutex[i] = new QMutex;
        cars[i] = new Car(this, i * 100 + 80);
    }
    // 设置样式
    setObjectName("gamewidget");
    setStyleSheet("#gamewidget{border-image:url(:/resources/images/background.png)}");
    setFixedSize(MAX_X, MAX_Y);
    // 运行阳光计时器，playthread
    Suntimer->setInterval(15000);
    connect(Suntimer, SIGNAL(timeout()), this, SLOT(newSun()));
    mainthread->start();
    zomthread->start();
    Suntimer->start();

    //    refresh_timer->setInterval(10);
    //    connect(refresh_timer, SIGNAL(timeout()), this, SLOT(refresh()));
    //    refresh_timer->start();
    // 设置卡槽组
    cradlist = new CardList(this, LEN_CRAD);
    // 设置阳光标签
    sunLabel = new QLabel(this);
    sunLabel->setAlignment(Qt::AlignCenter);
    sunLabel->setGeometry(0, SUN_SY, CARD_SX, SUN_Y);
    sunLabel->setText(QString::number(sunshine));
    sunLabel->show();
    // show();
}

void GameWidget::mousePressEvent(QMouseEvent *ev) // 鼠标点击事件
{
    if (ev->button() == Qt::LeftButton)
    {
        // 左键
        int x = ev->position().x();
        int y = ev->position().y();
        if (x <= PLANT_SX + COLUMN * PLANT_X && x >= PLANT_SX && y >= PLANT_SY &&
            y <= PLANT_SY + PLANT_Y * ROW && (plantInHand || ShoveInHand))
        {
            int px = (x - PLANT_SX) / PLANT_X;
            int py = (y - PLANT_SY) / PLANT_Y;                 // 获取位置
            if (plants[py][px] == nullptr && plantInHand != 0) // 判断是不是要种植物
            {
                cradlist->cardptr(plantInHand)->setColdTime(0);
                putCard(plantInHand, px, py);
            }
            else if (plants[py][px] != nullptr && ShoveInHand != 0) // 判断是不是要铲植物
            {
                putShovel(px, py);
            }
        }
    }
    else if (ev->button() == Qt::RightButton) // 右键，取消
    {
        cancelCard();
        cancelShovel();
    }
}

bool GameWidget::emptyHand() // 判断是否空手
{
    return plantInHand == 0 && ShoveInHand == 0;
}

void GameWidget::getCard(int id_, int x, int y) // 获取卡片
{
    if (plantInHand == 0 && ShoveInHand == 0)
    {
        plantInHand = id_;
        picOnHand = new PicOnHand(this, cImgPath[id_][0]); // 设置手上的图片
        picOnHand->move(x + CARD_SX + CARD_X * (id_ - 1), y);
        setMouseTracking(1); // 开始追踪鼠标
        cradlist->setAttribute(Qt::WA_TransparentForMouseEvents, 1);
    }
}

void GameWidget::putCard(int id, int x, int y) // 放置卡片
{
    if (plants[y][x] == nullptr && plantInHand != 0)
    {
        createPlant(x, y, id);
        remSun(plantCost[id]);
        cancelCard();
    }
}

void GameWidget::cancelCard() // 取消卡片
{
    delete picOnHand;
    picOnHand = NULL;
    plantInHand = 0;
    setMouseTracking(0);
    cradlist->setAttribute(Qt::WA_TransparentForMouseEvents, 0);
}

void GameWidget::getShovel(int x, int y) // 获取铲子
{
    if (plantInHand == 0 && ShoveInHand == 0)
    {
        ShoveInHand = 1;
        picOnHand = new PicOnHand(this, shovelImg[0]);
        picOnHand->move(x + SH_X, y);
        setMouseTracking(1);
        cradlist->setAttribute(Qt::WA_TransparentForMouseEvents, 1);
    }
}

void GameWidget::putShovel(int x, int y) // 使用铲子
{
    if (plants[y][x] != nullptr && ShoveInHand != 0)
    {
        plants[y][x]->deleteLater();
        plants[y][x] = nullptr;
        cancelShovel();
    }
}

void GameWidget::cancelShovel() // 取消铲子
{
    delete picOnHand;
    picOnHand = NULL;
    ShoveInHand = 0;
    setMouseTracking(0);
    cradlist->setAttribute(Qt::WA_TransparentForMouseEvents, 0);
}

void GameWidget::mouseMoveEvent(QMouseEvent *ev) // 鼠标移动追踪
{
    tryMove(ev->position().x(), ev->position().y());
}

void GameWidget::tryMove(int x, int y) // 手上的图片移动到鼠标的位置
{
    if (plantInHand || ShoveInHand)
    {
        picOnHand->move(x, y);
        //        num++;
    }
}

void GameWidget::addSun(int x) // 阳光增加
{
    sunshine += x;
    sunLabel->setText(QString::number(sunshine));
}

void GameWidget::remSun(int x) // 阳光减少
{
    addSun(-x);
}

bool GameWidget::enough(int x) // 阳光是否足够
{
    return sunshine >= x;
}

void GameWidget::new_zombie(int id) // 生成新僵尸
{
    zom_mutex->lock();
    int loc = rand() % 5;

    switch (id)
    {
    case 0:
        zombies[loc] << new ordinary(loc, this);
        break;
    case 1:
        zombies[loc] << new barricade(loc, this);
        break;
    case 2:
        zombies[loc] << new drums(loc, this);
        break;
    default:
        break;
    }
    zom_mutex->unlock();
}

void GameWidget::newSun() // 新生成阳光
{
    sun_mutex->lock();
    suns << new Sun(this, 1);
    sun_mutex->unlock();
}

// void GameWidget::refresh()
//{
//     //setStyleSheet("#playwindow{border-image:url(:/resources/images/background.png)}");
// }

// void GameWidget::exit()
//{

//}

// void GameWidget::pause()
//{

//}

void GameWidget::delete_car(int I) // 删除小车
{
    cars[I] = nullptr;
}

void GameWidget::createPlant(int x_, int y_, int id_) // 根据id创造植物
{
    switch (id_)
    {
    case 1:
        plants[y_][x_] = new PeaShooter(this, y_, x_);
        break;
    case 2:
        plants[y_][x_] = new SunFlower(this, y_, x_);
        break;
    case 3:
        plants[y_][x_] = new Nut(this, y_, x_);
        break;
    case 4:
        plants[y_][x_] = new ColdPeaShooter(this, y_, x_);
        break;
    case 5:
        plants[y_][x_] = new TwoPeaShooter(this, y_, x_);
        break;
    }
}

void GameWidget::paintEvent(QPaintEvent *) // 刷新屏幕，避免出现白线
{
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":/resources/images/background.png"), QRect());
    setStyleSheet("#playwindow{border-image:url(:/resources/images/background.png)}");
}

bool GameWidget::hasZombie(int x) // 判断一行有没有僵尸
{
    return !zombies[x].empty();
}

GameWidget::~GameWidget()
{
    mainthread->quit();
    _sleep(1000);
}
