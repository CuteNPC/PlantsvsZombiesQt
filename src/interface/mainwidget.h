#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>

class MainStackedWidget;

class MainWidget : public QWidget
{
    Q_OBJECT
    MainStackedWidget *mainStackedWidget;

  public:
    MainWidget(QWidget *parent = nullptr);
};

#endif // MAINWIDGET_H
