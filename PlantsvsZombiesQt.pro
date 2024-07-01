QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backbutton.cpp \
    endmenu.cpp \
    main.cpp \
    mainwidget.cpp \
    mainmenu.cpp \
    mainstackedwidget.cpp \
    selectgamemenu.cpp \
    gamewidget.cpp \
    plant.cpp \
    cardlist.cpp \
    card.cpp \
    globalvar.cpp \
    constval.cpp \
    car.cpp \
    zombie.cpp \
    playthread.cpp \
    bullet.cpp \
    sun.cpp \
    piconhand.cpp \
    shovel.cpp \
    sunflower.cpp \
    peashooter.cpp \
    nut.cpp \
    coldpeashooter.cpp \
    twopeashooter.cpp
HEADERS += \
    backbutton.h \
    endmenu.h \
    size.h \
    nut.h \
    twopeashooter.h \
    coldpeashooter.h \
    mainwidget.h \
    mainmenu.h \
    peashooter.h \
    sunflower.h \
    shovel.h \
    sun.h \
    bullet.h \
    playthread.h \
    zombie.h \
    constval.h \
    car.h \
    globalvar.h \
    card.h \
    cardlist.h \
    selectgamemenu.h \
    gamewidget.h \
    piconhand.h \
    mainstackedwidget.h \
    plant.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
