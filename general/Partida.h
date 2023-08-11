
// Created by EQUIPO on 4/08/2023.
//

#ifndef SPACEBULLET_PARTIDA_H
#define SPACEBULLET_PARTIDA_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include <vector>
#include<memory>
#include <random>
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
#include "../components/Observer.h"
#include "../components/ObsPersonaje.h"
#include <thread>
class Partida{
private:
    sf::Vector2f aceleracionViento;
    const sf::Vector2f gravity = sf::Vector2f(0.f, 9.8f); // Gravedad (puedes ajustarla según tus necesidades)
    const float deltaTime = 10.f / 60.f; // Delta de tiempo para cálculos de movimiento (60 FPS)
    sf::RenderWindow& ventana;
    std::unique_ptr<FondoPartida> fondoPartida;
    std::unique_ptr<MascaraBarraPoder> mascaraBarraPoder;
    std::vector<Plataforma> plataformas;
    std::unique_ptr<CompBarraPoder> barraPoder;
    std::unique_ptr<Personaje> personaje1;
    std::unique_ptr<Personaje> personaje2;
    std::vector<Proyectil> proyectiles;
    std::unique_ptr<TimerTurnos> temporalizador;
    std::unique_ptr<FlechaTurno> flechaTurno;
    bool esTurno1;
    ObservadorPersonaje* obsPersona1;
    ObservadorPersonaje* obsPersona2;
public:
    Partida(sf::RenderWindow& window):
    ventana(window),
    aceleracionViento(sf::Vector2f(0.f, 0.f)){
        //Cargar fondo de mapa
        thread_recursos();

    }
    //carga de recursos en threads por medio de detach para un mejor rendimiento
void thread_recursos(){
        std::thread carga_rec(&Partida::cargar_recursos,this);
        carga_rec.detach();
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

        //Actualizar Flecha de turno
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
        obsPersona1->getGameOver()->Draw(ventana);
        obsPersona2->getGameOver()->Draw(ventana);
    }

    void cargar_recursos(){
        float anchoPantalla = ventana.getSize().x;
        float altoPantalla = ventana.getSize().y;
        fondoPartida = std::make_unique<FondoPartida>(sf::Vector2f(anchoPantalla/2, altoPantalla/2),
                                                      anchoPantalla,altoPantalla,
                                                      "../images/mapa.jpg",1,1);
        mascaraBarraPoder =std::make_unique<MascaraBarraPoder>(sf::Vector2f(anchoPantalla/2, altoPantalla-100.f),
                                                               anchoPantalla,200.f);
        //Crear las plataformas bajo un escenario
        FactoryEscenarios* factoryEscenario = GeneradorEscenarioAleatorio::GenerarEscenario();
        factoryEscenario->CrearEscenarios(plataformas);

        //Crea la barra de poder
        barraPoder =std::make_unique <CompBarraPoder>(sf::Vector2f(580, 1000), sf::Vector2f(955, 40),
                                                      sf::Color::Green, sf::Color::Black);
        //Crear los personajes
        personaje1 = std::make_unique<Personaje>(sf::Vector2f(300.f, 100.f),150,150,
                                                 "../images/cocodrilo.png",4,2);
        personaje2 = std::make_unique<Personaje>(sf::Vector2f(1500.f, 100.f),150,150,
                                                 "../images/gatopsicopata.png",4,2);

        //Crear el temporalizador
        temporalizador = std::make_unique<TimerTurnos>(sf::Vector2f(1800.f,100.f),150.f,150.f);
        esTurno1 = true;
        //Crea el observador para lanzar mensaje gameOver para ser usado cuando acabe
        obsPersona1 = new ObservadorPersonaje(*personaje1,sf::Vector2f (ventana.getSize().x/2.f,ventana.getSize().y/2.f),800,800);
        obsPersona2 = new ObservadorPersonaje(*personaje2,sf::Vector2f (ventana.getSize().x/2.f,ventana.getSize().y/2.f),800,800);
        //Crea la felcha de turno
        flechaTurno =std::make_unique<FlechaTurno>(personaje1->getPosicion(),50,50);
    }
};


#endif //SPACEBULLET_PARTIDA_H
