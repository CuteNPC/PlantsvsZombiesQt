#ifndef ENUM_H
#define ENUM_H

enum GameOverStatus {
    ERROR,
    WIN,
    LOSE,
    MANUAL_EXIT,
};

enum StackWidgetIndex {
    MAIN,
    SELECT,
    EXIT,
    GAME,
};

enum PlantId {
    SUNFLOWER,
    PEASHOOTER,
    NUT,
    CLODPEASHOOTER,
};

enum ZombieId {
    NORMAL_ZOMBIE,
    CONE_ZOMEBIE,
    BUCKET_ZOMEBIE,
};

#endif // ENUM_H
