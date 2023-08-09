#include <iostream>
#include <SFML/Graphics.hpp>
#include "general/Menu.h"
#include "general/Partida.h"
#include <SFML/Audio.hpp>
int X=1920;
int Y=1080;
int main() {
    sf::RenderWindow window(sf::VideoMode(X, Y), "Mi Juego");
    window.setFramerateLimit(60);
    Menu menu(window, false);
    Partida *partida = new Partida(window);
    sf::Sound sonido;
    sf::SoundBuffer buffer;

    enum Estado { MENU, PARTIDA };
    Estado estadoActual = MENU;
    buffer.loadFromFile("../images/gbstage3.ogg");
    sonido.setBuffer(buffer);
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed){
                window.close();
            }
            else{
                if (estadoActual == MENU) {
                    sonido.play();
                    if (!menu.HandleInput(event)) //Esperando a que devuelva false cuando se presione enter
                        estadoActual = PARTIDA;
                } else if (estadoActual == PARTIDA) {
                    partida->HandleInput(event);
                }
            }
        }

        // Clear screen
        window.clear();

        // -------------------DRAW----------------------------------->

        if (estadoActual == MENU) {
            menu.Draw();
        } else if (estadoActual == PARTIDA) {
            if (!partida->Update()){
                estadoActual = MENU;
                partida = new Partida(window);
            }
            partida->Draw();
        }
        // Update the window
        window.display();
    }
    return 0;
}
