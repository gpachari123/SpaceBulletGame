
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
#include "../components/FlechaTurno.h"
#include "../components/GameOver.h"
#include "../components/FondoPartida.h"
#include "../components/MascaraBarraPoder.h"
#include "../components/TimerTurnos.h"
#include "../components/CompBarraPoder.h"
#include "../components/Plataforma.h"
#include "../components/Personaje.h"
#include "../utils/VectorUtil.h"
#include "../components/factoryEscenarios.h"
class Partida {
private:
    sf::Vector2f aceleracionViento;
    const sf::Vector2f gravity = sf::Vector2f(0.f, 9.8f); // Gravedad (puedes ajustarla según tus necesidades)
    const float deltaTime = 10.f / 60.f; // Delta de tiempo para cálculos de movimiento (60 FPS)
    sf::RenderWindow& ventana;
    FactoryEscenarios *factory;
    FondoPartida *fondoPartida;
    MascaraBarraPoder *mascaraBarraPoder;
    std::vector<Plataforma> plataformas;
    CompBarraPoder *barraPoder;
    std::unique_ptr<Personaje> personaje1;
    std::unique_ptr<Personaje> personaje2;
    std::vector<Proyectil> proyectiles;
    TimerTurnos *temporalizador;
    FlechaTurno *flechaTurno;
    bool esTurno1;
    GameOver *estadoGameOver;



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
        mascaraBarraPoder = new MascaraBarraPoder(sf::Vector2f(anchoPantalla/2, altoPantalla-100.f),
                                                  anchoPantalla,200.f);
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
        barraPoder = new CompBarraPoder(sf::Vector2f(580, 1000), sf::Vector2f(955, 40),
                                        sf::Color::Green, sf::Color::Black);
        //Crear los personajes
        personaje1 = std::make_unique<Personaje>(sf::Vector2f(300.f, 100.f),150,150,
                               "../images/cocodrilo.png",4,2);
        personaje2 = std::make_unique<Personaje>(sf::Vector2f(1500.f, 100.f),150,150,
                                   "../images/gatopsicopata.png",4,2);

        //Crear el temporalizador
        temporalizador = new TimerTurnos(sf::Vector2f(1800.f,100.f),150.f,150.f);
        esTurno1 = true;

        //Crea el mensajeGameOver para ser usado cuando acabe
        estadoGameOver = new GameOver(sf::Vector2f (ventana.getSize().x/2.f,ventana.getSize().y/2.f),800,800);

        //Crea la felcha de turno
        flechaTurno = new FlechaTurno(personaje1->getPosicion(),50,50);
    }


    void HandleInput(sf::Event event){
        if (esTurno1){
            if (!personaje1->HandleInput(event,proyectiles,*barraPoder)){
                esTurno1= false;
                temporalizador->PararContabilizador();
                temporalizador->ReinicarContador();
            }
            if (!temporalizador->EstaCorriendo()){
                esTurno1= false;
                temporalizador->PararContabilizador();
                temporalizador->ReinicarContador();
            }
        }
        else{
            if (!personaje2->HandleInput(event,proyectiles,*barraPoder)){
                esTurno1= true;
                temporalizador->PararContabilizador();
                temporalizador->ReinicarContador();
            }
            if (!temporalizador->EstaCorriendo()){
                esTurno1= true;
                temporalizador->PararContabilizador();
                temporalizador->ReinicarContador();
            }
        }
        barraPoder->HandleInput(event);
        temporalizador->HandleInput(event);
    }
    bool Update(){
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
        //Verificar estado de vida de los personajes
        if (personaje1->getVida()<=0 || personaje2->getVida()<=0){
            estadoGameOver->IniciarGameOver();
        }
        //Actualizar temporalizador
        if (estadoGameOver->YaSeUsoGameOver()){
            //std::cout<<"Ya llamar al menu"<<std::endl;
            return false;
        }

        //Actualizar Flecha
        if (esTurno1)
            flechaTurno->Update(personaje1->getPosicion());
        else
            flechaTurno->Update(personaje2->getPosicion());
        return true;
    }
    void Draw(){
        //Dibujar Fondo de pantalla
        fondoPartida->Draw(ventana);
        //Dibujar Plataformas
        for (auto& plataforma : plataformas) {
            plataforma.Draw(ventana);
        }

        //Dibujar personajes
        personaje1->Draw(ventana);
        personaje2->Draw(ventana);

        //Dibujar proyectiles
        for (auto& proyectil : proyectiles)
        {
            proyectil.Draw(ventana);
        }

        //Dibujar Barra de Poder
        barraPoder->Draw(ventana);
        //Dibujar Mascara
        mascaraBarraPoder->Draw(ventana);

        //Dibujar temporalizador
        temporalizador->Draw(ventana);

        //DibujarFlecha de turno
        flechaTurno->Draw(ventana);

        //Dibujar GameOver
        estadoGameOver->Draw(ventana);
    }


};


#endif //SPACEBULLET_PARTIDA_H
