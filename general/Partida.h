//
// Created by EQUIPO on 4/08/2023.
//

#ifndef SPACEBULLET_PARTIDA_H
#define SPACEBULLET_PARTIDA_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include <vector>
#include<memory>
#include "Menu.h"
#include "../components/Plataforma.h"
#include "../components/Personaje.h"

class Partida {
private:
    sf::Vector2f aceleracionViento;
    const sf::Vector2f gravity = sf::Vector2f(0.f, 9.8f); // Gravedad (puedes ajustarla según tus necesidades)
    const float deltaTime = 10.f / 60.f; // Delta de tiempo para cálculos de movimiento (60 FPS)
    sf::RenderWindow& ventana;

    std::vector<Plataforma> plataformas;
    Personaje *personaje1;
    Personaje *personaje2;

public:
    Partida(sf::RenderWindow& window):
    ventana(window),
    aceleracionViento(sf::Vector2f(0.f, 0.f)){
        //Cargar fondo de mapa
        //Crear las plataformas
        Plataforma plata1(sf::Vector2f(300.f, 300.f),400,100,
                         "../images/plataformaAzul.png",1,1);
        Plataforma plata2(sf::Vector2f(600.f, 500.f),400,100,
                          "../images/plataformaAzul.png",1,1);
        Plataforma plata3(sf::Vector2f(1200.f, 500.f),400,100,
                          "../images/plataformaAzul.png",1,1);
        Plataforma plata4(sf::Vector2f(900.f, 300.f),300,100,
                          "../images/plataformaAzul.png",1,1);
        plataformas.push_back(plata1);
        plataformas.push_back(plata2);
        plataformas.push_back(plata3);
        plataformas.push_back(plata4);

        //Crear los personajes
        personaje1 = new Personaje(sf::Vector2f(300.f, 100.f),150,150,
                               "../images/cocodrilo.png",4,2);
        personaje2 = new Personaje(sf::Vector2f(1000.f, 100.f),150,150,
                                   "../images/gatopsicopata.png",4,2);

    }

    void HandleInput(sf::Event event){
        personaje1->HandleInput(event);
        personaje2->HandleInput(event);
    }
    void Update(){
        //Aplicar gravedad al personaje y actualizar su posicion
        personaje1->AplicarGravedad(deltaTime,gravity,plataformas);
        personaje1->Update();

        personaje2->AplicarGravedad(deltaTime,gravity,plataformas);
        personaje2->Update();
    }
    void Draw(){
        //Dibujar Plataformas
        for (auto& plataforma : plataformas) {
            plataforma.Draw(ventana);
        }
        //Dibujar personajes
        personaje1->Draw(ventana);
        personaje2->Draw(ventana);
    }


};


#endif //SPACEBULLET_PARTIDA_H
