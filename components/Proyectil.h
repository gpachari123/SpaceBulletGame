//
// Created by EQUIPO on 7/08/2023.
//

#ifndef SPACEBULLET_PROYECTIL_H
#define SPACEBULLET_PROYECTIL_H

#include "Componente.h"
#include "Plataforma.h"
#include "ExplosionProyectil.h"
#include "../utils/VectorUtil.h"

class Proyectil: public Componente{

private:
    sf::Vector2f velocidad;
    bool estaExplotado; //
    ExplosionProyectil *explosionProyectil; //Siempre habra una explosion
public:
    ///Constructor Clase Plataforma
    Proyectil(sf::Vector2f posInicial,sf::Vector2f velocidadInicial, float ancho, float alto,
                  const std::string& rutaTextura, int divX, int divY)
            : Componente(posInicial,ancho,alto,rutaTextura,divX, divY){
        //Implementar constructor Plataforma
        velocidad = velocidadInicial;
        estaExplotado = false;
        explosionProyectil = new ExplosionProyectil(posInicial,50.f,50.f);
    }

    ///Override funcion Draw
    void Draw(sf::RenderWindow& window) override{
        //Dibujo del Sprite de la plataforma
        if (!estaExplotado){
            window.draw(*this->sprite);
        }
        else{
            explosionProyectil->Draw(window);
        }
    };

    void Update(float deltaTime, sf::Vector2f gravedad, sf::Vector2f viento,
                std::vector<Plataforma> plataformas){

        // Calcula el ángulo de la velocidad
        float angle = VectorUtil::getAngleWithXAxis(velocidad);
        //Vector para desfasar la ubicacion de la barra de vida------------------------------->
        sf::Vector2f desfase = sf::Vector2f (0.f,-15.f);
        sprite->setPosition(posicion+desfase);
        sprite->setRotation(angle);
        explosionProyectil->setPosicion(posicion+desfase);
        explosionProyectil->Update();
        //Verifica si hay colision con alguna plataforma
        if (!estaExplotado){//Ejecutar solo si no esta explotado
            // Actualizar posiciones y velocidad de los proyectiles
            velocidad += (gravedad+viento) * deltaTime;
            posicion += velocidad * deltaTime;
            //Verirficar si la posicion del sprite esta dentro de alguna plataforma
            for (auto& plataforma : plataformas) {
                if (plataforma.GetBound().contains(posicion)) {
                    estaExplotado = true;
                    //Generar daño
                    std::cout<<"Se genera danio"<<std::endl;

                    break;
                }
            }
        }
    }

};


#endif //SPACEBULLET_PROYECTIL_H
