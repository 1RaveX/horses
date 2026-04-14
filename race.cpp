#include "race.h"

char mapC[HEIGHT][WIDTH];
std::vector<Horse> horses;
std::vector<std::thread> threads;
bool raceFinished = false;
char tipeHorse[5] = {'A','B','C','D','E'};

void buildRaceCourse() {
    for(int i=0;i<HEIGHT;i++) {
        for(int j=0;j<WIDTH;j++) {
            mapC[i][j] = ' ';
        }
    }
    for (int i = 1; i < 80; i++) {
        mapC[5][i] = '-';
        mapC[15][i] = '-';
    }

    /*
    for (int j = 6; j < 29; j++) {
        mapC[j][70] = '|';
    }

    for (int j = 11; j < 29; j++) {
        mapC[j][50] = '|';
    }
    */
}
void drawRaceCourse() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            mvaddch(y, x, mapC[y][x]);
        }
    }
    mvprintw(28, 60, "Meta");
}

ColisionType detectColision(int x, int y) {
    if(mapC[y][x] == '-') return COLISSION_COL;
    if(mapC[y][x] == '|') return COLISSION_ROW;

    if(y > 15 || y < 5) {
        return OUT;
    } 
    return NOT_COLISSION;
}
bool isDetectColition(int x, int y) {
    if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return true;

    return mapC[y][x] == '-' || mapC[y][x] == '|';
}


bool isPath(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 ||  y >= HEIGHT) return false;
    
    if (mapC[y][x] == '-' || mapC[y][x] == '|') {
        return false;
    }
    if (y >= 15 || y <= 5) {
        return false;
    }

    return true;
}
/*
void runRace() {
    std::srand(time(nullptr));

    StateRace state = START;
    Horse horse = Horse('A');
    while (state != FINISH) {
        mvaddch(horse.y, horse.x, ' ');

        int dice = std::rand() % 10;
        int rx = (dice < 7) ? 1 : (dice < 9 ? 0 : -1);
        int ry = (std::rand() % 3) - 1;

        // detectar colission:
        if(!isDetectColition(horse.x + rx,horse.y + ry)) {
            horse.move(rx,ry,mapC);
        } 
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        horse.display();
        refresh();

        if(horse.x >= 70) {
            state = FINISH;
            mvprintw(30, 60, "FINISH!");
        }

    }
}
*/


void runRace() {
    std::srand(time(nullptr));
    for(int i=0; i< 5; i++){
        char h = tipeHorse[i];
        Horse horse = Horse(h);
        horses.push_back(horse);
    }

    for(int i=0;i < 5; i++) {
        threads.emplace_back(horseSimulation, std::ref(horses[i]));
    }
    runRaceRender();
    for(auto&t : threads) {
        t.join();
    }
}

void runRaceRender() {
    while(!raceFinished) {
        clear();
        drawRaceCourse();
        for(auto &h : horses) {
            h.display();
        }
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    mvprintw(30, 60, "FINISH!");
    refresh();
}


void horseSimulation(Horse &horse) {
    StateRace state = START;
    while (!raceFinished) {
        int dice = std::rand() % 10;
        int rx = (dice < 7) ? 1 : (dice < 9 ? 0 : -1);
        int ry = (std::rand() % 3) - 1;

        // detectar colission:
        if(!isDetectColition(horse.x + rx,horse.y + ry)) {
            horse.move(rx,ry,mapC);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        /*
        if(isHorseWin(horse)) {
            state = FINISH;
        } 
        */  
    }
}