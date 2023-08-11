#include <iostream>
#include "general/Game.h"

int X=1920;
int Y=1080;
int main() {
    Game* partida = Game::getInstance(X, Y, "Prueba");
    return 0;
}
