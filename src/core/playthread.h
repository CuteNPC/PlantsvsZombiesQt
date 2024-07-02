#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include "plant.h"
#include "sun.h"
#include "zombie.h"
#include <QThread>
#include <QTimer>

class GameWidget;

class Mainthread : public QThread
{
    Q_OBJECT
  public:
    GameWidget *parent;
    Mainthread(GameWidget *ptr);
    void run();
};

class Zombiethread : public QTimer
{
    Q_OBJECT

    GameWidget *parent;

  public:
    Zombiethread(GameWidget *ptr);
    QVector<int> zombieid, showtime; // 存储僵尸的种类。以及出现的时间

  signals:
    void generate(int id);

  private slots:
    void prepare_for_next();
};

#endif // PLAYTHREAD_H
