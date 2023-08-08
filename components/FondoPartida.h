//
// Created by EQUIPO on 7/08/2023.
//

#ifndef SPACEBULLET_FONDOPARTIDA_H
#define SPACEBULLET_FONDOPARTIDA_H

#include "Componente.h"

class FondoPartida: public Componente{
public:
    ///Constructor Clase Plataforma
    FondoPartida(sf::Vector2f posInicial, float ancho, float alto,
               const std::string& rutaTextura, int divX, int divY)
            : Componente(posInicial,ancho,alto,rutaTextura,divX, divY){
        //Implementar constructor Plataforma
    }
    ///Override funcion Draw
    void Draw(sf::RenderWindow& window) override{
        //Dibujo del Sprite de la plataforma
        window.draw(*this->sprite);
    };
};

#endif //SPACEBULLET_FONDOPARTIDA_H
