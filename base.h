#ifndef COMMON_H
#define COMMON_H

#define WIDTH 80
#define HEIGHT 80

extern int mind;
extern int maxd;

enum StateRace {
    START,
    FINISH,
};
enum CollisionType {
    COLLISION_VERTICAL,
    COLLISION_HORIZONTAL,
    NO_COLLISION,
    OUT_OF_BOUNDS,
};



#endif