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
    Partida partida(window);
    sf::Sound sonido;
    sf::SoundBuffer buffer;
    enum Estado { MENU, PARTIDA };
    Estado estadoActual = MENU;
    buffer.loadFromFile("../images/gbstage3.ogg");
    sonido.setBuffer(buffer);
    while (window.isOpen())
    {
        sf::Event event;

        ///////////////////////
        bool buttonTriangulo = 0; // Por ejemplo, el botón A
        bool buttonRedondo = 0; // Por ejemplo, el botón B
        bool buttonX = false; // Por ejemplo, el botón X
        bool buttonCuadrado = 0; // Por ejemplo, el botón Y
        // Comprobar si hay algún mando conectado
        if (sf::Joystick::isConnected(0)) // 0 representa el índice del mando (puede ser del 0 al 7)
        {
            // Obtener el estado del mando
            float xAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
            float yAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);


            // Imprimir la información del mando
            //std::cout << "Eje X: " << xAxis << ", Eje Y: " << yAxis << ", Botón A: " << buttonA << std::endl;

            // Obtener el estado de los botones
            buttonTriangulo = sf::Joystick::isButtonPressed(0, 0); // Por ejemplo, el botón A
            buttonRedondo = sf::Joystick::isButtonPressed(0, 1); // Por ejemplo, el botón B
            buttonX = sf::Joystick::isButtonPressed(0, 2); // Por ejemplo, el botón X
            buttonCuadrado = sf::Joystick::isButtonPressed(0, 3); // Por ejemplo, el botón Y


        }
        // Imprimir el estado de los botones
        std::cout << "Boton Triangulo: " << buttonTriangulo << ", Boton Redondo: " << buttonRedondo << ", Boton X: " << buttonX << ", Boton Cuadrado: " << buttonCuadrado << std::endl;

        /////////////////////////


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
