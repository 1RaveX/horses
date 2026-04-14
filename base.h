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
enum ColisionType {
    COLISSION_COL,
    COLISSION_ROW,
    NOT_COLISSION,
    OUT,
};



#endif