QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/core/playthread.cpp \
    src/core/playwindow.cpp \
    src/include/constval.cpp \
    src/include/globalvar.cpp \
    src/interface/backbutton.cpp \
    src/interface/endmenu.cpp \
    src/interface/gamewidget.cpp \
    src/interface/mainmenu.cpp \
    src/interface/mainstackedwidget.cpp \
    src/interface/mainwidget.cpp \
    src/interface/selectgamemenu.cpp \
    src/main.cpp \
    src/plant/coldpeashooter.cpp \
    src/plant/nut.cpp \
    src/plant/peashooter.cpp \
    src/plant/plant.cpp \
    src/plant/sunflower.cpp \
    src/plant/twopeashooter.cpp \
    src/util/bullet.cpp \
    src/util/car.cpp \
    src/util/card.cpp \
    src/util/cardlist.cpp \
    src/util/piconhand.cpp \
    src/util/plantinhand.cpp \
    src/util/shovel.cpp \
    src/util/sun.cpp \
    src/zombie/zombie.cpp

HEADERS += \
    src/core/playthread.h \
    src/core/playwindow.h \
    src/include/constval.h \
    src/include/enum.h \
    src/include/globalvar.h \
    src/include/size.h \
    src/interface/backbutton.h \
    src/interface/endmenu.h \
    src/interface/gamewidget.h \
    src/interface/mainmenu.h \
    src/interface/mainstackedwidget.h \
    src/interface/mainwidget.h \
    src/interface/selectgamemenu.h \
    src/plant/coldpeashooter.h \
    src/plant/nut.h \
    src/plant/peashooter.h \
    src/plant/plant.h \
    src/plant/sunflower.h \
    src/plant/twopeashooter.h \
    src/util/bullet.h \
    src/util/car.h \
    src/util/card.h \
    src/util/cardlist.h \
    src/util/piconhand.h \
    src/util/plantinhand.h \
    src/util/shovel.h \
    src/util/sun.h \
    src/zombie/zombie.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src\res.qrc
