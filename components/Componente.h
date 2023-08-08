//
// Created by EQUIPO on 4/08/2023.
//

#ifndef SPACEBULLET_COMPONENTE_H
#define SPACEBULLET_COMPONENTE_H
#include <SFML/Graphics.hpp>
#include "../utils/VectorUtil.h"
#include <cmath>
#include <iostream>

class Componente {
protected:
    sf::Vector2f posicion; //Posicion del sprite
    float anchoMostrado; //Ancho del componente
    float altoMostrado; //Alto del componente
    float anchoFrame;
    float altoFrame;
    float velocidadMovimiento; //Velocidad de movimiento del componente
    sf::Texture *textura; //Textura para el componente
    sf::Sprite *sprite; //Sprite del personaje
    sf::Vector2i divisionsprite; //Division de texturas para sprite
    sf::Vector2i frame_actual;
public:
    ///Constructor Clase Abstracta Componente
    Componente(sf::Vector2f posInicial, float ancho, float alto,
               const std::string& rutaTextura, int divX, int divY)
            : posicion(posInicial), anchoMostrado(ancho), altoMostrado(alto)
    {
        //Establecer texturas y sprites del Componente
        textura = new sf::Texture;
        textura->loadFromFile(rutaTextura);
        //Division de la imagen
        divisionsprite = sf::Vector2i (divX,divY);
        frame_actual = sf::Vector2i (0,0);
        //Creacion del sprite
        sprite = new sf::Sprite;
        sprite->setTexture(*textura);
        //Calcular ancho y alto de un frame
        anchoFrame = textura->getSize().x / divisionsprite.x;
        altoFrame = textura->getSize().y / divisionsprite.y;

        //Redefinir centro de coordenads del componente (al centro)
        sprite->setOrigin(anchoFrame/2,altoFrame/2);
        //Scalar sprite para ajustar al ancho y alto establecidos
        sprite->scale(ancho/anchoFrame,alto/altoFrame);

        //Colocar sprite en posicion inicial
        sprite->setPosition(posInicial);

        //Actualizar el frame del sprite
        RefreshAnimacion();
    }

    ///Destructor Clase Componente
    virtual ~Componente()=default; //Destructor

    ///Funcion virtual pura (sebe ser implementada por clases derivadas)
    ///para dibujar lo que s etenga que dibujar
    virtual void Draw(sf::RenderWindow& window) = 0;

    ///Funcion virtual (puede ser sobreescrito en clases derivadas)
    ///para Manejar los eventos
    /*virtual void HandleInput(sf::Event event){
        //Por defecto no responde a eventos
    }*/

    ///Funcion virtual (puede ser sobreescrito en clases derivadas)
    ///para Actualizar propieades del componente
    virtual void Update(){

    }

    ///Funcion No Virtual (no es candidato de sobreescritura en clases derivadas)
    ///para obtener el rectangulo de contorno del componente
    sf::FloatRect GetBound(){
        return sprite->getGlobalBounds();
    }

    //Funcion No virtual para actualizar
    void RefreshAnimacion()
    {
        sf::IntRect rectangulo(frame_actual.x * (sprite->getTexture()->getSize().x / divisionsprite.x),
                               frame_actual.y * (sprite->getTexture()->getSize().y / divisionsprite.y),
                               sprite->getTexture()->getSize().x / divisionsprite.x,
                               sprite->getTexture()->getSize().y / divisionsprite.y);
        sprite->setTextureRect(rectangulo);
    }
};

#endif //SPACEBULLET_COMPONENTE_H
