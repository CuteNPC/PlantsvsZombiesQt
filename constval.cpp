#include<QWidget>
#include<QImage>
#include"size.h"

//常量

int plantCd[MAX_CARD+2]={0,1000,10000,0,1000,250};

//最大冷却时间
int maxColdTime[MAX_CARD+2]={0,7000,3500,5000,10000,12000};

//植物的花费
int plantCost[MAX_CARD+2]={0,100,50,50,175,200};

//植物的血量
int plantHP[MAX_CARD+2]={0,100,100,1000,100,200};

//卡槽贴图地址
QString cGifPath[MAX_CARD+2]={
    "",
    ":/images/peashooter.gif",
    ":/images/sunflower.gif",
    ":/images/nut.gif",
    ":/images/coldshooter.gif",
    ":/images/twoshooter.gif"
};

//动图地址
QString cImgPath[MAX_CARD+2][2]={
    {},
    {":/images/peacard.png",":/images/peacard2.png"},
    {":/images/sunflowercard.png",":/images/sunflowercard2.png"},
    {":/images/nutcard.png",":/images/nutcard2.png"},
    {":/images/coldshootercard.png",":/images/coldshootercard2.png"},
    {":/images/twoshootercard.png",":/images/twoshootercard2.png"}
};

//僵尸贴图
QString* ordinary_formal = new QString[2]{":/images/zwalk.gif",
        ":/images/zhurt.gif"};

QString* ordinary_mid = new QString[2]{":/images/zhurt.gif",
        ":/images/zdie.gif"};

QString* ordinary_eat = new QString[2]{":/images/zeat.gif",
        ":/images/zeat.gif"};

QString* drums_formal = new QString[3]{":/images/bzwalk.gif",
        ":/images/zwalk.gif",
        ":/images/zhurt.gif"};

QString* drums_mid = new QString[3]{":/images/zwalk.gif",
        ":/images/zhurt.gif",
        ":/images/zdie.gif"};

QString* drums_eat = new QString[3]{":/images/bzeat.gif",
        ":/images/zeat.gif",
        ":/images/zeat.gif"};

QString* barricade_formal = new QString[3]{":/images/hzwalk.gif",
        ":/images/zwalk.gif",
        ":/images/zhurt.gif"};

QString* barricade_mid = new QString[3]{":/images/zwalk.gif",
        ":/images/zhurt.gif",
        ":/images/zdie.gif"};

QString* barricade_eat = new QString[3]{":/images/hzeat.gif",
        ":/images/zeat.gif",
        ":/images/zeat.gif"};

QString* pole_formal = new QString[2]{":/images/zwalk.gif", ":/images/zhurt.gif"};

QString* pole_mid = new QString[2]{":/images/zhurt.gif", ":/images/zdie.gif"};

QString* pole_eat = new QString[2]{":/images/zeat.gif", ":/images/zeat.gif"};

QImage Zarm(":/images/zarm.png");

//铲子图片
QString* shovelImg = new QString[2]{":/images/shovel.png", ":/images/shovel2.png"};

//子弹图片
QString* bulletImg = new QString[3]{":/images/pea.png",":/images/coldpea.png",":/images/crash.gif"};

//子弹图片
QImage* bulletQImg = new QImage[2]{QImage(":/images/pea.png"),QImage(":/images/coldpea.png")};

//小推车
QString* trolley = new QString[1]{":/images/trolley.gif"};

//背景图
QString* backG =  new QString[4]{":/images/bkg1.png",":/images/bkg2.png",":/images/bkg3.png",":/images/bkg4.png"};

//关卡
QString* stageFile =  new QString[4]{":/zombielist.txt",":/zombielist1.txt",":/zombielist2.txt",":/zombielist3.txt"};
