//
// Created by EQUIPO on 9/08/2023.
//

#ifndef SPACEBULLET_GAME_H
#define SPACEBULLET_GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Partida.h"
#include <SFML/Audio.hpp>

class Game{
private:
    static Game *instance;
    Game(int ancho, int largo, const std::string& titulo){
        sf::RenderWindow window(sf::VideoMode(ancho, largo), titulo);
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

    }
public:
    static Game* getInstance(int ancho, int largo, const std::string& titulo){
        if (instance == nullptr){
            instance = new Game(ancho, largo, titulo);
        }
        return instance;
    }
};
Game* Game::instance = nullptr;


#endif //SPACEBULLET_GAME_H
