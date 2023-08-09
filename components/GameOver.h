//
// Created by EQUIPO on 9/08/2023.
//

#ifndef SPACEBULLET_GAMEOVER_H
#define SPACEBULLET_GAMEOVER_H

#include "Componente.h"
#include "Plataforma.h"
#include "../utils/VectorUtil.h"
#include <SFML/Audio.hpp>
class GameOver: public Componente{

private:
    sf::Clock clock;
    sf::Time waitTime = sf::seconds(5.0f);
    bool estaCorriendo;
    bool yaSeLlamo;
public:
    ///Constructor Clase Plataforma
    GameOver(sf::Vector2f posInicial, float ancho, float alto)
            : Componente(posInicial,ancho,alto,"../images/GameOver.png",1, 1){
        estaCorriendo = false;
        yaSeLlamo = false;
    }

    ///Override funcion Draw
    void Draw(sf::RenderWindow& window) override{
        if (estaCorriendo){
            if (clock.getElapsedTime() <= waitTime) {
                // Actualizar frame
                window.draw(*sprite);
            } else{
                estaCorriendo= false;
            }
        }
    };

    void IniciarGameOver(){
        if (!yaSeLlamo){
            clock.restart();
            estaCorriendo = true;
            yaSeLlamo = true;
        }
    }

    void Update(){
        sprite->setPosition(posicion);
    }

    bool YaSeUsoGameOver(){
        return yaSeLlamo && !estaCorriendo;
    }


};


#endif //SPACEBULLET_GAMEOVER_H
