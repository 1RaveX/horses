#include "horse.h"

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

