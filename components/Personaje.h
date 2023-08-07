//
// Created by GERALD on 6/08/2023.
//

#ifndef SPACEBULLET_PERSONAJE_H
#define SPACEBULLET_PERSONAJE_H

#include "Componente.h"
#include "../utils/VectorUtil.h"
#include "Plataforma.h"

class Personaje: public Componente{
private:
    float movementSpeed; //Velocidad de movimiento del personaje
    bool estaSobrePlataforma;
    float anguloDisparo;
    sf::Vector2f vectorDireccionDisparo;
    bool estaEnCaidaLibre;
public:
    ///Constructor Clase Personaje
    Personaje(sf::Vector2f posInicial, float ancho, float alto,
               const std::string& rutaTextura, int divX, int divY)
            : Componente(posInicial,ancho,alto,rutaTextura,divX, divY){
        //Reestablecer origen del personaje
        sprite->setOrigin(anchoFrame/2,4*altoFrame/5);
        //Establecer direccion disparo inicial
        vectorDireccionDisparo = sf::Vector2f(1.0,-1.0);
        anguloDisparo = VectorUtil::getAngleWithXAxis(vectorDireccionDisparo);
        movementSpeed = 5.f;
        estaEnCaidaLibre = true;
    }

    ///Override funcion Draw
    void Draw(sf::RenderWindow& window) override{
        //Dibujo del Sprite del personaje
        window.draw(*this->sprite);
    };

    ///Override del manejador de eventos
    void HandleInput(sf::Event event) override{
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            this->moveUp();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            this->moveDown();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            this->moveLeft();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            this->moveRight();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {

        }
        else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
        {
            //Definir Fuerza de lanzamiento
            /*float fuerzaLanzamiento = barra.getProgreso(); //Esta es la fuerza de disparo, falta definir un valor maximo y una barra
            sf::Vector2f v0 = fuerzaLanzamiento*vectorDireccionDisparo; // Velocidad inicial del proyectil ( se supone que el vector direccion debe estar normalizado)
            this->Disparar(proyectiles2, v0);*/
        }
    }

    void moveUp() {
        float incremento = -1;
        if(frame_actual.y == 1)
            incremento *=-1;
        //Incrementar 1 grado la direccion de disparo
        VectorUtil::incrementarAnguloAVector(vectorDireccionDisparo,incremento);
        Update();
    }

    void moveDown() {
        float incremento = 1;
        if(frame_actual.y == 1)
            incremento *=-1;
        VectorUtil::incrementarAnguloAVector(vectorDireccionDisparo,incremento);
        Update();
    }

    void moveLeft() {
        if (frame_actual.y != 1){
            frame_actual.y = 1;
            vectorDireccionDisparo = VectorUtil::reflejarVector(vectorDireccionDisparo,sf::Vector2f(0,1));
        }
        else{
            if (!estaEnCaidaLibre){
                frame_actual.x++;
                if (frame_actual.x == divisionsprite.x){
                    frame_actual.x =0;
                }
                posicion.x -= movementSpeed;
            }
        }
        Update();
        RefreshAnimacion();
    }

    void moveRight() {
        if (frame_actual.y != 0){
            frame_actual.y = 0;
            vectorDireccionDisparo = VectorUtil::reflejarVector(vectorDireccionDisparo,sf::Vector2f(0,1));
        }
        else{
            if (!estaEnCaidaLibre){
                frame_actual.x++;
                if (frame_actual.x == divisionsprite.x){
                    frame_actual.x =0;
                }
                posicion.x += movementSpeed;
            }
        }
        Update();
        RefreshAnimacion();
    }

    float getPosicionY(){
        return posicion.y;
    }

    void Update() override{

        //barraVida->setPosicion(position);
        sprite->setPosition(posicion);
        //spriteFlecha->setPosition(position);
        anguloDisparo = VectorUtil::getAngleWithXAxis(vectorDireccionDisparo);
        //spriteFlecha->setRotation(anguloDisparo);*/
    }

    void AplicarGravedad(float deltaTime, sf::Vector2f gravedad,
                                    std::vector<Plataforma> plataformas) {
        //Verificar sisigue intersecando con plataforma
        for (auto& plataforma : plataformas) {
            if (plataforma.GetBound().contains(posicion)) {
                estaEnCaidaLibre = false;
                break;
            }
            estaEnCaidaLibre=true; //Si no encuentra colision, cambia a caida libre
        }
        if (estaEnCaidaLibre){//Ejecutar solo si esta en caida libre
            // Aplicar la gravedad a la velocidad actual del personaje
            sf::Vector2f velocidad = gravedad * deltaTime;
            // Actualizar la posición del personaje con la nueva velocidad
            posicion += velocidad;
            //Verirficar si la posicion del sprite esta dentro de alguna plataforma
            for (auto& plataforma : plataformas) {
                if (plataforma.GetBound().contains(posicion)) {
                    estaEnCaidaLibre = false;
                    break;
                }
            }
        }
    }

};

#endif //SPACEBULLET_PERSONAJE_H
