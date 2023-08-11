//
// Created by Fernando on 08/08/2023.
//

#ifndef SPACEBULLET_FACTORYESCENARIOS_H
#define SPACEBULLET_FACTORYESCENARIOS_H

#include <random>
#include "Plataforma.h"
#include "FondoPartida.h"

class FactoryEscenarios{
public:
    virtual void CrearEscenarios(std::vector<Plataforma>& plataforma)=0;
};


class Escenario1:public FactoryEscenarios{
public:
    Escenario1()   {}
 void CrearEscenarios(std::vector<Plataforma>& plataformas) override{

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
public:
    Escenario2()   {}
    void CrearEscenarios(std::vector<Plataforma>& plataformas) override{

        Plataforma plata1(sf::Vector2f(300.f, 800.f),400,100,
                          "../images/Plt2.png",1,1);
        Plataforma plata2(sf::Vector2f(600.f, 800.f),400,100,
                          "../images/Plt1.png",1,1);
        Plataforma plata3(sf::Vector2f(1200.f, 800.f),400,100,
                          "../images/Plt1.png",1,1);
        Plataforma plata4(sf::Vector2f(900.f, 800.f),300,100,
                          "../images/Plt1.png",1,1);
        Plataforma plata5(sf::Vector2f(1500.f, 800.f),400,100,
                          "../images/Plt2.png",1,1);
        plataformas.push_back(plata1);
        plataformas.push_back(plata2);
        plataformas.push_back(plata3);
        plataformas.push_back(plata4);
        plataformas.push_back(plata5);
    }
};

class Escenario3:public FactoryEscenarios{
public:
    Escenario3()   {}
    void CrearEscenarios(std::vector<Plataforma>& plataformas) override{

        Plataforma plata1(sf::Vector2f(300.f, 900.f),400,100,
                          "../images/Plt2.png",1,1);
        Plataforma plata2(sf::Vector2f(600.f, 750.f),400,100,
                          "../images/Plt1.png",1,1);
        Plataforma plata4(sf::Vector2f(900.f, 600.f),300,100,
                          "../images/Plt1.png",1,1);
        Plataforma plata3(sf::Vector2f(1200.f, 400.f),400,100,
                          "../images/Plt1.png",1,1);
        Plataforma plata5(sf::Vector2f(1500.f, 200.f),400,100,
                          "../images/Plt2.png",1,1);
        plataformas.push_back(plata1);
        plataformas.push_back(plata2);
        plataformas.push_back(plata3);
        plataformas.push_back(plata4);
        plataformas.push_back(plata5);
    }
};

class Escenario4:public FactoryEscenarios{
public:
    Escenario4()   {}
    void CrearEscenarios(std::vector<Plataforma>& plataformas) override{

        Plataforma plata1(sf::Vector2f(300.f, 800.f),400,100,
                          "../images/Plt2.png",1,1);
        Plataforma plata2(sf::Vector2f(600.f, 600.f),400,100,
                          "../images/Plt1.png",1,1);
        Plataforma plata4(sf::Vector2f(900.f, 400.f),300,100,
                          "../images/Plt1.png",1,1);
        Plataforma plata3(sf::Vector2f(1200.f, 600.f),400,100,
                          "../images/Plt1.png",1,1);
        Plataforma plata5(sf::Vector2f(1500.f, 800.f),400,100,
                          "../images/Plt2.png",1,1);
        plataformas.push_back(plata1);
        plataformas.push_back(plata2);
        plataformas.push_back(plata3);
        plataformas.push_back(plata4);
        plataformas.push_back(plata5);
    }
};

class GeneradorEscenarioAleatorio{
private:
public:
    static FactoryEscenarios* GenerarEscenario(){
        std::random_device rd;  // Dispositivo de generación de números aleatorios
        std::mt19937 gen(rd()); // Motor Mersenne Twister
        std::uniform_int_distribution<int> distribution(1, 5); // Rango de 1 a 5

        // Generar un número aleatorio entre 1 y 5
        int randomNumber = distribution(gen);

        if (randomNumber==1)
            return new Escenario1();
        else if (randomNumber==2)
            return new Escenario2();
        else if (randomNumber==3)
            return new Escenario3();
        else if (randomNumber==4)
            return new Escenario4();
        else if (randomNumber==5)
            return new Escenario1();
        else
            return new Escenario1();
    }
};
#endif //SPACEBULLET_FACTORYESCENARIOS_H
