//
// Created by EQUIPO on 7/08/2023.
//

#ifndef SPACEBULLET_COMPBARRAPODER_H
#define SPACEBULLET_COMPBARRAPODER_H

#include <SFML/Graphics.hpp>

class CompBarraPoder{
private:
    sf::RectangleShape rectBarraVida;
    sf::RectangleShape rectBorde;
    float vida; //Va de 0 a 100
    bool seLleno;
public:
    ///Constructor de BarraProgreso
    CompBarraPoder(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Color borderColor)
            : vida(0.0f), seLleno(false)
    {
        rectBarraVida.setPosition(position);
        rectBarraVida.setSize(size);
        rectBarraVida.setFillColor(fillColor);

        rectBorde.setPosition(position);
        rectBorde.setSize(size);
        rectBorde.setFillColor(sf::Color::Transparent);
        rectBorde.setOutlineColor(borderColor);
        rectBorde.setOutlineThickness(2.0f);
    }

    ///Funcion geter para obtener el vida
    float getProgreso(){
        return this->vida;
    }
    ///Función para dibujar la barra de vida
    void Draw(sf::RenderWindow& window){
        if (vida > 0)
        {
            sf::RectangleShape progressRect(rectBarraVida);
            //Obtener relacion
            float relacion = vida / 100.0f;
            progressRect.setSize(sf::Vector2f(rectBarraVida.getSize().x * relacion, rectBarraVida.getSize().y));
            window.draw(progressRect);
        }
        window.draw(rectBorde);
    }

    ///Función para responder a eventos
    void HandleInput(sf::Event event){
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

#endif //SPACEBULLET_COMPBARRAPODER_H
