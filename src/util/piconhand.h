#ifndef PICONHAND_H
#define PICONHAND_H

#include <QLabel>
#include <QWidget>

class PicOnHand : public QLabel
{
    Q_OBJECT
    QPixmap pixmap;

  public:
    PicOnHand(QWidget *parent, QString path);
    ~PicOnHand() noexcept;
};

#endif // PICONHAND_H
