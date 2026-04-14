#ifndef HORSE_H
#define HORSE_H

#include <ncurses.h>
#include "base.h"


class Horse {
    public:
        Horse(char h) {
            this->x=0;
            this->h = h;
            this->x = 0;
            this->y = 8;
        }
        void move(int dx, int dy, char map[HEIGHT][WIDTH]);
        void display() const; 
        int x;
        int y;
        char h;
};

#endif