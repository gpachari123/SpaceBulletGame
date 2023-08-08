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
#include "../components/FondoPartida.h"
#include "../components/CompBarraPoder.h"
#include "../components/Plataforma.h"
#include "../components/Personaje.h"
#include "../utils/VectorUtil.h"

class Partida {
private:
    sf::Vector2f aceleracionViento;
    const sf::Vector2f gravity = sf::Vector2f(0.f, 9.8f); // Gravedad (puedes ajustarla según tus necesidades)
    const float deltaTime = 10.f / 60.f; // Delta de tiempo para cálculos de movimiento (60 FPS)
    sf::RenderWindow& ventana;

    FondoPartida *fondoPartida;
    std::vector<Plataforma> plataformas;
    CompBarraPoder *barraPoder;
    Personaje *personaje1;
    Personaje *personaje2;

    std::vector<Proyectil> proyectiles;


public:
    Partida(sf::RenderWindow& window):
    ventana(window),
    aceleracionViento(sf::Vector2f(0.f, 0.f)){
        //Cargar fondo de mapa
        float anchoPantalla = ventana.getSize().x;
        float altoPantalla = ventana.getSize().y;
        fondoPartida = new FondoPartida(sf::Vector2f(anchoPantalla/2, altoPantalla/2),
                                        anchoPantalla,altoPantalla,
                                        "../images/mapa.jpg",1,1);
        //Crear las plataformas
        Plataforma plata1(sf::Vector2f(300.f, 600.f),400,100,
                         "../images/Plt2.png",1,1);
        Plataforma plata2(sf::Vector2f(600.f, 800.f),400,100,
                          "../images/Plt1.png",1,1);
        Plataforma plata3(sf::Vector2f(1200.f, 800.f),400,100,
                          "../images/Plt1.png",1,1);
        Plataforma plata4(sf::Vector2f(900.f, 600.f),300,100,
                          "../images/Plt1.png",1,1);
        Plataforma plata5(sf::Vector2f(1500.f, 600.f),400,100,
                          "../images/Plt2.png",1,1);
        plataformas.push_back(plata1);
        plataformas.push_back(plata2);
        plataformas.push_back(plata3);
        plataformas.push_back(plata4);
        plataformas.push_back(plata5);

        //Crea la barra de poder
        barraPoder = new CompBarraPoder(sf::Vector2f(50, 830), sf::Vector2f(800, 40),
                                        sf::Color::Green, sf::Color::Black);
        //Crear los personajes
        personaje1 = new Personaje(sf::Vector2f(300.f, 100.f),150,150,
                               "../images/cocodrilo.png",4,2);
        personaje2 = new Personaje(sf::Vector2f(1500.f, 100.f),150,150,
                                   "../images/gatopsicopata.png",4,2);

    }

    void HandleInput(sf::Event event){
        personaje1->HandleInput(event,proyectiles,*barraPoder);
        personaje2->HandleInput(event, proyectiles,*barraPoder);
        barraPoder->HandleInput(event);
    }
    void Update(){
        //Aplicar gravedad al personaje y actualizar su posicion
        personaje1->AplicarGravedad(deltaTime,gravity+sf::Vector2f (0.f,10.f),plataformas);
        personaje1->Update();

        personaje2->AplicarGravedad(deltaTime,gravity+sf::Vector2f (0.f,10.f),plataformas);
        personaje2->Update();

        //Actualizar proyectiles
        for (auto& proyectil : proyectiles)
        {
            sf::Vector2f posicionImpacto = proyectil.Update(deltaTime,gravity,aceleracionViento,plataformas);
            if (posicionImpacto!=sf::Vector2f(0.f,0.f)){
                //Evaluar cercania de danio a los personajes
                float distancia1 = VectorUtil::distanceBetweenVector(posicionImpacto,personaje1->getPosicion());
                float distancia2 = VectorUtil::distanceBetweenVector(posicionImpacto,personaje2->getPosicion());
                //Evaluar la cercanica de la epxlosion para definir danio
                if (distancia1<100){
                    float danio = (100.f-distancia1)/3.f;
                    personaje1->DisminuirVida(danio);
                    //Aqui colocar un texto del danio hecho al personaje 1
                }
                if (distancia2<100){
                    float danio = (100.f-distancia2)/3.f;
                    personaje2->DisminuirVida(danio);
                    //Aqui colocar un texto del danio hecho al personaje 2
                }

            }
        }
    }
    void Draw(){
        //Dibujar Fondo de pantalla
        fondoPartida->Draw(ventana);
        //Dibujar Plataformas
        for (auto& plataforma : plataformas) {
            plataforma.Draw(ventana);
        }
        //Dibujar Barra de Poder
        barraPoder->Draw(ventana);
        //Dibujar personajes
        personaje1->Draw(ventana);
        personaje2->Draw(ventana);

        //Dibujar proyectiles
        for (auto& proyectil : proyectiles)
        {
            proyectil.Draw(ventana);
        }
    }


};


#endif //SPACEBULLET_PARTIDA_H
