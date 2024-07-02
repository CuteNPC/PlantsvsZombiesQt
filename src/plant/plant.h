#ifndef PLANT_H
#define PLANT_H

#include <QLabel>
#include <QMovie>
#include <QObject>
#include <QTimer>
#include <QTimerEvent>

// 植物类
class Plant : public QLabel
{
    Q_OBJECT

  protected:
    QString gifPath; // 贴图地址
    int id;          // 植物类别
    QMovie *movie;   // 动画
    double HP;       // 生命值
    int placeX;      // x坐标，从左向右为0-8
    int placeY;      // y坐标，从上到下为0-4

  public:
    Plant(QWidget *parent, int y, int x, int id); // 根据xy坐标和id初始化
    ~Plant() noexcept;
    bool is_dead();                               // 检测是不是死了
    void die();                                   // 去死吧
    void hurt();                                  // 受伤
};
#endif // PLANTS_H
