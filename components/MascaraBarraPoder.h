//
// Created by EQUIPO on 9/08/2023.
//

#ifndef SPACEBULLET_MASCARABARRAPODER_H
#define SPACEBULLET_MASCARABARRAPODER_H

#include "Componente.h"

class MascaraBarraPoder: public Componente{
public:
    ///Constructor Clase Plataforma
    MascaraBarraPoder(sf::Vector2f posInicial, float ancho, float alto)
            : Componente(posInicial,ancho,alto,"../images/barraPoder.png",1, 1){
        //Implementar constructor Plataforma
    }
    ///Override funcion Draw
    void Draw(sf::RenderWindow& window) override{
        //Dibujo del Sprite de la plataforma
        window.draw(*this->sprite);
    };
};
#endif //SPACEBULLET_MASCARABARRAPODER_H
