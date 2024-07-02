#ifndef CAR_H
#define CAR_H
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>

class GameWidget;

class Car : public QLabel
{
    Q_OBJECT
  public:
    QPropertyAnimation *ani;
    QTimer *timer;
    bool is_active = 0; // 是否已经被激活
    Car(GameWidget *ptr, int y);
    ~Car() noexcept;

  private slots:
    void deleteLater();
    void try_to_set_null();
    void try_to_kill();
    void activate();

  signals:
    void set_null(int);
    void kill(int);
};

#endif // CAR_H
