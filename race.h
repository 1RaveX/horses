#include <ncurses.h>
#include <ctime>
#include <chrono>
#include <thread>

#include "base.h"
#include "horse.h"




void buildRaceCourse();
void drawRaceCourse();
ColisionType detectColision(int x, int y);
bool isDetectColition(int x, int y);
bool isPath(int x, int y);

void runRace();
void runRaceRender();
void horseSimulation(Horse &horse);