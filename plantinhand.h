#ifndef PLANTINHAND_H
#define PLANTINHAND_H

#include <QLabel>

class PlantInHand : public QLabel
{
    Q_OBJECT
    int id;
    QPixmap pixmap;

public:
    PlantInHand(QWidget *parent,int id0,QString path);

};

#endif // PLANTINHAND_H
