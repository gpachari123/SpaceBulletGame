//
// Created by EQUIPO on 4/08/2023.
//

#ifndef SPACEBULLET_PLATAFORMA_H
#define SPACEBULLET_PLATAFORMA_H

#include "Componente.h"

class Plataforma: public Componente{
public:
    ///Constructor Clase Plataforma
    Plataforma(sf::Vector2f posInicial, float ancho, float alto,
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

#endif //SPACEBULLET_PLATAFORMA_H
