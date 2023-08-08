//
// Created by EQUIPO on 7/08/2023.
//

#ifndef SPACEBULLET_ANGULODISPARO_H
#define SPACEBULLET_ANGULODISPARO_H


#include "Componente.h"

class AnguloDisparo: public Componente{

private:
    float anguloDisparo;
public:
    ///Constructor Clase Plataforma
    AnguloDisparo(sf::Vector2f posInicial, float ancho, float alto,
                  const std::string& rutaTextura, int divX, int divY)
            : Componente(posInicial,ancho,alto,rutaTextura,divX, divY){
        //Implementar constructor Plataforma
        sprite->setOrigin(0.0,altoMostrado/2);
    }

    ///Override funcion Draw
    void Draw(sf::RenderWindow& window) override{
        //Dibujo del Sprite de la plataforma
        window.draw(*this->sprite);
    };

    void Update(sf::Vector2f posicionN, float angulo){
        //Vector para desfasar la ubicacion de la barra de vida------------------------------->
        sf::Vector2f desfase = sf::Vector2f (0.f,-15.f);
        sprite->setPosition(posicionN+desfase);
        sprite->setRotation(angulo);
    }


    ///Funcion para obtener el angulo de disparo
    double getAnguloDisparo(){
        return anguloDisparo;
    }

    ///Funcion para setear el angulo de disparo
    void setAnguloDisparo(float valor){
        this->anguloDisparo = valor;
    }
};


#endif //SPACEBULLET_ANGULODISPARO_H
