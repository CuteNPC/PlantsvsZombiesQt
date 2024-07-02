#ifndef ENUM_H
#define ENUM_H

enum GameStatus
{
    WAITING,
    RUNNING,
    WIN,
    LOSE,
    MANUAL_EXIT,
    ERROR,
};

enum StackWidgetIndex
{
    MAIN,
    SELECT,
    EXIT,
    GAME,
};

enum PlantId
{
    SUNFLOWER,
    PEASHOOTER,
    NUT,
    CLODPEASHOOTER,
};

enum ZombieId
{
    NORMAL_ZOMBIE,
    CONE_ZOMEBIE,
    BUCKET_ZOMEBIE,
};

#endif // ENUM_H
