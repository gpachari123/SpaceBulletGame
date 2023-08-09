//
// Created by EQUIPO on 8/08/2023.
//

#ifndef SPACEBULLET_EXPLOSIONPROYECTIL_H
#define SPACEBULLET_EXPLOSIONPROYECTIL_H

#include "Componente.h"
#include "Plataforma.h"
#include "../utils/VectorUtil.h"
#include <SFML/Audio.hpp>
class ExplosionProyectil: public Componente{

private:
    sf::Clock clock;
    float frameTime = 0.1f; // Tiempo entre cada frame de la animación (ajústalo según tu necesidad)
    bool realcontacto;
    sf::Sound sonido;
    sf::SoundBuffer buffer;
public:
    ///Constructor Clase Plataforma
    ExplosionProyectil(sf::Vector2f posInicial, float ancho, float alto)
            : Componente(posInicial,ancho,alto,"../images/Explosion2.png",4, 4){
            realcontacto = true;
            if(!buffer.loadFromFile("../images/explosion.ogg")){
                std::cout<<"no se puede cargar archivo";
            }
            sonido.setBuffer(buffer);
    }

    ///Override funcion Draw
    void Draw(sf::RenderWindow& window) override{
        if (realcontacto) {
            sonido.stop();
            if (clock.getElapsedTime().asSeconds() >= frameTime) {
                // Actualizar frame
                sf::IntRect rectangulo(frame_actual.x * (sprite->getTexture()->getSize().x / divisionsprite.x),
                                       frame_actual.y * (sprite->getTexture()->getSize().y / divisionsprite.y),
                                       sprite->getTexture()->getSize().x / divisionsprite.x,
                                       sprite->getTexture()->getSize().y / divisionsprite.y);
                sprite->setTextureRect(rectangulo);
                // Avanzar al siguiente frame de la explosión
                if (frame_actual.x < divisionsprite.x - 1) {
                    frame_actual.x++;
                } else {
                    frame_actual.y++;
                    frame_actual.x = 0;
                }
                if (frame_actual.x >= divisionsprite.x) {
                    // Si se llegó al último frame, se detiene la animación

                    realcontacto = false;
                    sonido.play();
                    sonido.setVolume(100);
                }
                clock.restart();
            }
            window.draw(*sprite);
        }
    };

    void setPosicion(sf::Vector2f nuevaPosicion)
    {
        posicion=nuevaPosicion;
    }
    void Update(){
        sprite->setPosition(posicion);

    }
};


#endif //SPACEBULLET_EXPLOSIONPROYECTIL_H
