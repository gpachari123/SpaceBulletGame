#include <iostream>
#include <SFML/Graphics.hpp>
#include "general/Menu.h"
#include "general/Partida.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Mi Juego");
    window.setFramerateLimit(60);
    Menu menu(window, false);
    Partida partida(window);

    enum Estado { MENU, PARTIDA };
    Estado estadoActual = MENU;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            else{
                if (estadoActual == MENU) {
                    if (!menu.HandleInput(event)) //Esperando a que devuelva false cuando se presione enter
                        estadoActual = PARTIDA;
                } else if (estadoActual == PARTIDA) {
                    partida.HandleInput(event);
                }
            }
        }
        // Clear screen
        window.clear();

        // -------------------DRAW----------------------------------->

        if (estadoActual == MENU) {
            menu.Draw();
        } else if (estadoActual == PARTIDA) {
            partida.Update();
            partida.Draw();
        }
        // Update the window
        window.display();
    }
    return 0;
}
