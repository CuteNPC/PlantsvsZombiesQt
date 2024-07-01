#ifndef CONSTVAL_H
#define CONSTVAL_H
#include<QWidget>
#include<QImage>

//常量

extern int plantCd[];//植物运行周期

extern int maxColdTime[];//最大冷却时间

extern int plantCost[];//植物的花费

extern int plantHP[];//植物的血量

extern QString cGifPath[];//动图地址

extern QString cImgPath[][2];//卡槽贴图地址

//以下是僵尸贴图

extern QString* ordinary_formal;

extern QString* ordinary_mid;

extern QString* ordinary_eat;

extern QString* drums_formal;

extern QString* drums_mid;

extern QString* drums_eat;

extern QString* barricade_formal;

extern QString* barricade_mid;

extern QString* barricade_eat;

extern QString* pole_formal;

extern QString* pole_mid;

extern QString* pole_eat;

//以上是僵尸贴图

extern QString* shovelImg;//铲子图片

extern QString* bulletImg;//子弹图片

extern QImage* bulletQImg;//子弹图片

extern QImage Zarm;//僵尸掉手

extern QString* trolley;//小推车

extern QString* backG;//背景图片

extern QString* stageFile;//关卡

#endif // CONSTVAL_H
