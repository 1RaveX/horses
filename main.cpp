#include <iostream>
#include <ncurses.h>
#include <vector>

#include <string>
#include "race.h"

int main() {    
    initscr();

    buildRaceCourse();
    runRace();

    getch();
    endwin();
    
    return 0;
}