//
// Created by EQUIPO on 7/08/2023.
//

#ifndef SPACEBULLET_COMPBARRAVIDA_H
#define SPACEBULLET_COMPBARRAVIDA_H

#include "Componente.h"

class CompBarraVida{
private:
    sf::RectangleShape rectBarraVida;
    sf::RectangleShape rectBorde;
    sf::Vector2f posicion;
    float vida; //Va de 0 a 100
    bool seLleno;
public:
///Constructor de BarraProgreso
    CompBarraVida(sf::Vector2f position, sf::Vector2f size)
            : posicion(position),vida(100.0f), seLleno(false)
    {
        rectBarraVida.setPosition(position);
        rectBarraVida.setSize(size);
        rectBarraVida.setFillColor(sf::Color::Red);

        rectBorde.setPosition(position);
        rectBorde.setSize(size);
        rectBorde.setFillColor(sf::Color::Transparent);
        rectBorde.setOutlineColor(sf::Color::Black);
        rectBorde.setOutlineThickness(2.0f);
    }
///Funcion para actualizar Posicion
    void setPosicion(sf::Vector2f posicion){
        this->posicion=posicion;
    }

///Funcion geter para obtener el vida
    float getVida(){
        return this->vida;
    }

    ///Funcion geter para obtener el vida
    void disminuirVida(float danio){
        float nuevaVida = this->vida-danio;
        this->vida = nuevaVida>0?nuevaVida:0.0f;
    }

///Función para dibujar la barra de vida
    void Draw(sf::RenderWindow& window){
        //Vector para desfasar la ubicacion de la barra de vida------------------------------->
        sf::Vector2f desfase = sf::Vector2f (-39.f,20.f);
        rectBorde.setPosition(posicion+desfase);
        if (vida > 0)
        {
            sf::RectangleShape progressRect(rectBarraVida);
            //Obtener relacion
            float relacion = vida / 100.0f;
            progressRect.setSize(sf::Vector2f(rectBarraVida.getSize().x * relacion, rectBarraVida.getSize().y));
            progressRect.setPosition(posicion + desfase);
            window.draw(progressRect);
        }
        window.draw(rectBorde);
    }

///Función para responder a eventos
    void ResponderEvento(sf::Event event){
        if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::O) )
        {
            if (seLleno) //Si detecta que ya se lleno previamente. reinica el vida
            {
                this->vida = 0.0f;
            }
            this->vida+=1.0; //Condifurar incremento, es la Velocidad del progressBar
            if (vida >= 100.f)
                this->vida = 100.0f;
            seLleno = false; //Mientras se este apretando la barra espaciadora selleno es falso
        }
        else if (event.type == sf::Event::KeyReleased && (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::O))
        {
            seLleno = true; //Una vez se suelta la barra espaciadora "selleno" es true
        }
    }
};


#endif //SPACEBULLET_COMPBARRAVIDA_H
