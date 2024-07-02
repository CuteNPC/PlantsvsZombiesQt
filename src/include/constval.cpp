#include "include/size.h"
#include <QImage>
#include <QWidget>

// 常量

int plantCd[MAX_CARD + 2] = {0, 1000, 10000, 0, 1000, 250};

// 最大冷却时间
int maxColdTime[MAX_CARD + 2] = {0, 7000, 3500, 5000, 10000, 12000};

// 植物的花费
int plantCost[MAX_CARD + 2] = {0, 100, 50, 50, 175, 200};

// 植物的血量
int plantHP[MAX_CARD + 2] = {0, 100, 100, 1000, 100, 200};

// 卡槽贴图地址
QString cGifPath[MAX_CARD + 2] = {"",
                                  ":/resources/images/peashooter.gif",
                                  ":/resources/images/sunflower.gif",
                                  ":/resources/images/nut.gif",
                                  ":/resources/images/coldshooter.gif",
                                  ":/resources/images/twoshooter.gif"};

// 动图地址
QString cImgPath[MAX_CARD + 2][2] = {
    {},
    {":/resources/images/peacard.png", ":/resources/images/peacard2.png"},
    {":/resources/images/sunflowercard.png", ":/resources/images/sunflowercard2.png"},
    {":/resources/images/nutcard.png", ":/resources/images/nutcard2.png"},
    {":/resources/images/coldshootercard.png", ":/resources/images/coldshootercard2.png"},
    {":/resources/images/twoshootercard.png", ":/resources/images/twoshootercard2.png"}};

// 僵尸贴图
QString *ordinary_formal =
    new QString[2]{":/resources/images/zwalk.gif", ":/resources/images/zhurt.gif"};

QString *ordinary_mid =
    new QString[2]{":/resources/images/zhurt.gif", ":/resources/images/zdie.gif"};

QString *ordinary_eat =
    new QString[2]{":/resources/images/zeat.gif", ":/resources/images/zeat.gif"};

QString *drums_formal =
    new QString[3]{":/resources/images/bzwalk.gif", ":/resources/images/zwalk.gif",
                   ":/resources/images/zhurt.gif"};

QString *drums_mid = new QString[3]{":/resources/images/zwalk.gif", ":/resources/images/zhurt.gif",
                                    ":/resources/images/zdie.gif"};

QString *drums_eat = new QString[3]{":/resources/images/bzeat.gif", ":/resources/images/zeat.gif",
                                    ":/resources/images/zeat.gif"};

QString *barricade_formal =
    new QString[3]{":/resources/images/hzwalk.gif", ":/resources/images/zwalk.gif",
                   ":/resources/images/zhurt.gif"};

QString *barricade_mid = new QString[3]{
    ":/resources/images/zwalk.gif", ":/resources/images/zhurt.gif", ":/resources/images/zdie.gif"};

QString *barricade_eat = new QString[3]{
    ":/resources/images/hzeat.gif", ":/resources/images/zeat.gif", ":/resources/images/zeat.gif"};

QString *pole_formal =
    new QString[2]{":/resources/images/zwalk.gif", ":/resources/images/zhurt.gif"};

QString *pole_mid = new QString[2]{":/resources/images/zhurt.gif", ":/resources/images/zdie.gif"};

QString *pole_eat = new QString[2]{":/resources/images/zeat.gif", ":/resources/images/zeat.gif"};

QImage Zarm(":/resources/images/zarm.png");

// 铲子图片
QString *shovelImg =
    new QString[2]{":/resources/images/shovel.png", ":/resources/images/shovel2.png"};

// 子弹图片
QString *bulletImg = new QString[3]{":/resources/images/pea.png", ":/resources/images/coldpea.png",
                                    ":/resources/images/crash.gif"};

// 子弹图片
QImage *bulletQImg =
    new QImage[2]{QImage(":/resources/images/pea.png"), QImage(":/resources/images/coldpea.png")};

// 小推车
QString *trolley = new QString[1]{":/resources/images/trolley.gif"};

// 背景图
QString *backG = new QString[4]{":/resources/images/bkg1.png", ":/resources/images/bkg2.png",
                                ":/resources/images/bkg3.png", ":/resources/images/bkg4.png"};

// 关卡
QString *stageFile =
    new QString[4]{":/resources/info/zombielist.txt", ":/resources/info/zombielist1.txt",
                   ":/resources/info/zombielist2.txt", ":/resources/info/zombielist3.txt"};
