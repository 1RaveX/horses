#include "horse.h"

void Horse::move(int dx, int dy, char mapC[HEIGHT][WIDTH]) {
    int nX = x + dx;
    int nY = y + dy;

    // si choca con una pared que se devuelva
    if (nY <= 5 || nY >= 15 || mapC[nY][x] == '-') {
        nY = y - dy; 
    }
    // choca con camino vertical
    if (nX <= 0 || nX >= 79 || mapC[y][nX] == '|') {
        nX = x - dx;
    }
    //cambia la posicion
    if (nY > 5 && nY < 15 && nX > 0 && nX < 80) {
        x = nX;
        y = nY;
    }

}
void Horse::display() const {
    mvaddch(y, x, h);
}

