//
// Created by Fernando on 08/08/2023.
//

#ifndef SPACEBULLET_FACTORYESCENARIOS_H
#define SPACEBULLET_FACTORYESCENARIOS_H
#include "Plataforma.h"
#include "FondoPartida.h"
class FactoryEscenarios{
public:
    virtual void CrearEscenarios(std::vector<Plataforma>& plataforma)=0;
};
class Escenario1:public FactoryEscenarios{
private:
    float anchoPantalla;
    float altoPantalla;
public:
    Escenario1(float ancho, float alto) : anchoPantalla(ancho), altoPantalla(alto) {}
 void CrearEscenarios(std::vector<Plataforma>& plataformas) override{
    FondoPartida fondo(sf::Vector2f(anchoPantalla/2, altoPantalla/2),
             anchoPantalla,altoPantalla,
             "../images/mapa.jpg",1,1);
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
 }

};
class Escenario2:public FactoryEscenarios{
    void CrearEscenarios(std::vector<Plataforma>& plataformas) override{
    }

};
class Escenario3:public FactoryEscenarios{
    void CrearEscenarios(std::vector<Plataforma>& plataformas) override{

    }
};

#endif //SPACEBULLET_FACTORYESCENARIOS_H
