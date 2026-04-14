#include <iostream>
#include <ncurses.h>
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>
#include <string>


#define WIDTH 80
#define HEIGHT 80


// hipodromo
char mapC[HEIGHT][WIDTH];
int mind = 5;
int maxd = 10;

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
    // 1. Validar límites físicos de la matriz para evitar errores de memoria
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return false;

    // 2. Si el mapa tiene algo que no sea aire/piso, hay colisión
    // Asumimos que ' ' es por donde el caballo PUEDE caminar.
    if (mapC[y][x] == '-' || mapC[y][x] == '|') {
        return false;
    }

    // 3. Validar rango vertical (tu restricción de 5 a 15)
    if (y >= 15 || y <= 5) {
        return false;
    }

    return true;
}


// horses:
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
void Horse::move(int dx, int dy, char map[HEIGHT][WIDTH]) {
    int nextX = x + dx;
    int nextY = y + dy;

    if (nextY <= 5 || nextY >= 15 || map[nextY][x] == '-') {
        // REBOTE: Invertimos la dirección vertical
        nextY = y - dy; 
    }

    // Detectar colisión en el eje X (Paredes '|')
    if (nextX <= 0 || nextX >= 79 || map[y][nextX] == '|') {
        // REBOTE: Invertimos la dirección horizontal
        nextX = x - dx;
    }

    // Finalmente, si la posición tras el rebote es segura, nos movemos
    // (Añadimos una validación extra por seguridad)
    if (nextY > 5 && nextY < 15 && nextX > 0 && nextX < 80) {
        x = nextX;
        y = nextY;
    }

}
void Horse::display() const {
    mvaddch(y, x, h);
}

int randomNumber() {
    return std::rand() % (maxd - mind + 1) + mind;
}


// race:
std::vector<Horse> horses;

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

// win horses:




// menu:

int main() {

    
    initscr();

    
    buildRaceCourse();
    drawRaceCourse();
    runRace();

    getch();
    endwin();
    
    
    return 0;
}