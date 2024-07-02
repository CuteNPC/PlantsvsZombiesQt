#include "core/playthread.h"
#include "interface/gamewidget.h"
#include "interface/mainstackedwidget.h"
#include "plant/plant.h"
#include <QFile>
#include <qrandom.h>

Mainthread::Mainthread(GameWidget *ptr) : parent(ptr) // 主要线程构造
{
}

Zombiethread::Zombiethread(GameWidget *ptr) : parent(ptr)
{ // 僵尸生成的控制器，实质上是QTimer
    connect(this, SIGNAL(generate(int)), ptr, SLOT(new_zombie(int)));
    connect(this, SIGNAL(timeout()), this, SLOT(prepare_for_next()));
    zombieid << 0; // 从资源文件读入僵尸生成时序表
    showtime << 0;
    QFile file(":/zombielist.txt");
    file.open(QIODevice::ReadOnly);
    char *str = new char[100];
    for (int i = 0;; i++)
    {
        int byte = file.readLine(str, 100);
        if (byte == 0 || byte == -1)
            break;
        if (i % 2 == 0)
            zombieid << std::stoi(str);
        else
            showtime << std::stoi(str);
    }
    setInterval(showtime[1]); // 设置第一个僵尸生成的时间
    setSingleShot(1);
}

void Zombiethread::prepare_for_next()
{ // timeout时生成一个僵尸，同时根据时序表改变自身interval，再次启动
    if (zombieid.count() <= 1)
        return;
    int interval = showtime[1] - showtime[0];
    zombieid.remove(0);
    showtime.remove(0);
    emit generate(zombieid[0]);
    setInterval(interval);
    start();
}

void Mainthread::run()
{ // 主要线程的执行
    while (parent->result == -1)
    { // 游戏尚未结束时进入循环
        msleep(10);

        bool flag = 0;
        parent->zom_mutex->lock(); // 遍历所有存活的僵尸，执行其run函数；死亡僵尸被移除队列
        for (int j = 0; j < 5; j++)
        {
            if (!parent->zombies[j].empty())
                flag = 1;
            for (int i = 0; i < parent->zombies[j].count();)
            {
                if (parent->zombies[j][i]->if_dead)
                {
                    parent->zombies[j][i]->deleteLater();
                    parent->zombies[j].remove(i);
                    continue;
                }
                if (parent->zombies[j][i]->x() == 0) // 有僵尸已经到达目的地，游戏失败
                    parent->result = 0;
                parent->zombies[j][i]->run();
                i++;
            }
        }
        parent->zom_mutex->unlock();

        if (!flag && parent->zomthread->showtime.count() ==
                         1) // 所有僵尸生成完毕，且当前场上没有僵尸，游戏胜利
            parent->result = 1;

        for (int j = 0; j < 5; j++) // 遍历所有豌豆子弹，已经飞出场外的或击中僵尸的移除队列
        {
            parent->bul_mutex[j]->lock();
            for (int i = 0; i < parent->bullets[j].count();)
            {
                if (parent->bullets[j][i]->is_dead)
                {
                    emit parent->bullets[j][i]->shut_down();
                    parent->bullets[j].remove(i);
                }
                else
                    i++;
            }
            parent->bul_mutex[j]->unlock();
        }

        for (int i = 0; i < 9; i++) // 遍历种植位置，已经死去的植物被移除
            for (int j = 0; j < 5; j++)
                if (parent->plants[j][i] && parent->plants[j][i]->is_dead())
                {
                    parent->plants[j][i]->deleteLater();
                    parent->plants[j][i] = nullptr;
                }
    }
}
