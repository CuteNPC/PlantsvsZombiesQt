#include "plant/plant.h"
#include "include/constval.h"
#include "include/size.h"
#include "util/bullet.h"
#include <QTimer>
#include <QTimerEvent>

Plant::Plant(QWidget *parent_, int y_, int x_, int id_) : QLabel(parent_)
{
    setAlignment(Qt::AlignCenter);
    placeX = x_;                 // x坐标（横向）
    placeY = y_;                 // y坐标（纵向）
    id = id_;                    // id
    HP = plantHP[id];            // 血量
    gifPath = cGifPath[id];      // 贴图路径
    movie = new QMovie(gifPath); // 初始化动画
    setGeometry(PLANT_SX + PLANT_X * placeX, PLANT_SY + PLANT_Y * placeY, PLANT_X,
                PLANT_Y);                                 // 设置形状，大小
    setMovie(movie);                                      // 设置动画
    movie->start();                                       // 播放动画
    show();                                               // 展示
    setAttribute(Qt::WA_TransparentForMouseEvents, true); // 不要让植物挡到鼠标
}

Plant::~Plant() {};

void Plant::hurt()
{
    HP--;
    // if(HP==0)
    // die();
}

// void Plant::die()
//{
// 待补充
// }

bool Plant::is_dead() { return HP <= 0; }
