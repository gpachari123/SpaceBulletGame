//
// Created by EQUIPO on 9/08/2023.
//

#ifndef SPACEBULLET_TIMERTURNOS_H
#define SPACEBULLET_TIMERTURNOS_H

#include "Componente.h"
#include "Plataforma.h"
#include "../utils/VectorUtil.h"
#include <SFML/Audio.hpp>
class TimerTurnos: public Componente {

private:
    sf::Clock clock;
    float frameTime = 1.f; // Tiempo entre cada frame de la animación (ajústalo según tu necesidad)
    bool estaCorriendo;
public:
    ///Constructor Clase Plataforma
    TimerTurnos(sf::Vector2f posInicial, float ancho, float alto)
            : Componente(posInicial,ancho,alto,"../images/turn_timer.png",1, 20){
        estaCorriendo = true;
        frame_actual.x = 0;
        frame_actual.y = 19;
    }
    ///Override funcion Draw
    void Draw(sf::RenderWindow& window) override{
        if (estaCorriendo){
            if (clock.getElapsedTime().asSeconds() >= frameTime) {
                // Actualizar frame
                sf::IntRect rectangulo(frame_actual.x * (sprite->getTexture()->getSize().x / divisionsprite.x),
                                       frame_actual.y * (sprite->getTexture()->getSize().y / divisionsprite.y),
                                       sprite->getTexture()->getSize().x / divisionsprite.x,
                                       sprite->getTexture()->getSize().y / divisionsprite.y);
                sprite->setTextureRect(rectangulo);
                // Avanzar al siguiente frame de la explosión
                if (frame_actual.y > 0) {
                    frame_actual.y--;
                }
                clock.restart();
            }
            if (frame_actual.y != 0){
                window.draw(*sprite);
            }
            else{
                estaCorriendo= false;
            }

        }
    };

    void ReinicarContador(){
        estaCorriendo = true;
        frame_actual.y = 19;
    }

    void PararContabilizador(){
        estaCorriendo = false;
    }

    void Update(){
        sprite->setPosition(posicion);
    }

    void HandleInput(sf::Event event){
        if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::P)
                ReinicarContador();
        }
    }

    bool EstaCorriendo(){
        return estaCorriendo;
    }

};


#endif //SPACEBULLET_TIMERTURNOS_H
