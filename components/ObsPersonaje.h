//
// Created by EQUIPO on 11/08/2023.
//

#ifndef SPACEBULLET_OBSPERSONAJE_H
#define SPACEBULLET_OBSPERSONAJE_H
#include "Observer.h"
#include "Personaje.h"
#include "GameOver.h"


class ObservadorPersonaje : public Observer {
public:
    ObservadorPersonaje(Personaje& pers,sf::Vector2f posInicial, float ancho, float alto) : personaje(pers) {
        personaje.addObserver(this);
        estadoGameOver = new GameOver(posInicial, ancho, alto);
    }

    void onNotify() override {
        estadoGameOver->IniciarGameOver();
        std::cout << "Se ha hecho acabado la vida del personaje: " << std::endl;
    }

    GameOver *getGameOver(){
        return estadoGameOver;
    }

private:
    Personaje& personaje;
    GameOver *estadoGameOver;
};


#endif //SPACEBULLET_OBSPERSONAJE_H
