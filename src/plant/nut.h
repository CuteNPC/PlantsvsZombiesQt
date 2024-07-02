#ifndef NUT_H
#define NUT_H

#include "plant.h"
#include <QWidget>

//坚果类
class Nut : public Plant
{
public:
    Nut(QWidget* parent,int y_,int x_);
};

#endif // NUT_H
