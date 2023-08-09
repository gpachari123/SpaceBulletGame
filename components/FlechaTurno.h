//
// Created by EQUIPO on 9/08/2023.
//

#ifndef SPACEBULLET_FLECHATURNO_H
#define SPACEBULLET_FLECHATURNO_H


#include "Componente.h"
#include <SFML/Audio.hpp>
class FlechaTurno: public Componente{

private:
    sf::Clock clock;
    sf::Time waitTime = sf::seconds(0.2f);

public:
    ///Constructor Clase Plataforma
    FlechaTurno(sf::Vector2f posInicial, float ancho, float alto)
            : Componente(posInicial,ancho,alto,"../images/flechaSprite.png",4, 1){

    }

    ///Override funcion Draw
    void Draw(sf::RenderWindow& window) override{
        if (clock.getElapsedTime() >= waitTime) {
            // Actualizar frame
            sf::IntRect rectangulo(frame_actual.x * (sprite->getTexture()->getSize().x / divisionsprite.x),
                                   frame_actual.y * (sprite->getTexture()->getSize().y / divisionsprite.y),
                                   sprite->getTexture()->getSize().x / divisionsprite.x,
                                   sprite->getTexture()->getSize().y / divisionsprite.y);
            sprite->setTextureRect(rectangulo);
            // Avanzar al siguiente frame de la flecha
            if (frame_actual.x <divisionsprite.x){
                frame_actual.x++;
            }
            if (frame_actual.x==divisionsprite.x)
                frame_actual.x=0;
            clock.restart();
        }
        window.draw(*sprite);
    };

    void Update(sf::Vector2f posicionN){
        posicion = posicionN;
        sprite->setPosition(posicion + sf::Vector2f(0.f,-120.f));
    }



};

#endif //SPACEBULLET_FLECHATURNO_H
