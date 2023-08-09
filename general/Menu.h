//
// Created by EQUIPO on 4/08/2023.
//

#ifndef SPACEBULLET_MENU_H
#define SPACEBULLET_MENU_H

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Partida.h"
class Menu {
private:
    sf::RenderWindow& ventana;
    sf::Font fuente;
    sf::Texture texturaFondo;
    sf::Sprite spriteFondo;
    std::unique_ptr<sf::Sound> sonido;
    std::unique_ptr<sf::SoundBuffer> buffer;
    ///Propiedades del menu
    std::vector<std::string> opciones;
    int opcionSeleccionada;
    bool sigueEnMenu;
public:
    /// Contructor del menu
    Menu(sf::RenderWindow& window, bool estaEnPartida): ventana(window), opcionSeleccionada(0) , sigueEnMenu(true){
        // Carga una fuente para el texto del menú
        if (!fuente.loadFromFile("../images/04B_31__.ttf")) {
            // Manejo de error si la fuente no se pudo cargar
        }
        // Carga el fondo del menu
        if (!texturaFondo.loadFromFile("../images/Space bullet.png")) {
            // Manejo de error si la imagen no se pudo cargar

        }
        spriteFondo.setTexture(texturaFondo);

        // Define las opciones del menú
        if (!estaEnPartida){
            opciones.push_back("Jugar");
            opciones.push_back("Configuracion");
            opciones.push_back("Salir");
        }
        else{
            opciones.push_back("Resume");
            opciones.push_back("Nueva Partida");
            opciones.push_back("Configuracion");
            opciones.push_back("Salir");
        }

    }

    ///Funcion para manejar los eventos del menu
    bool HandleInput(sf::Event event){
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            opcionSeleccionada = (opcionSeleccionada + opciones.size() - 1) % opciones.size();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            opcionSeleccionada = (opcionSeleccionada + 1) % opciones.size();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter){
            // Procesar selección de opción
            if (opcionSeleccionada == 0) {
                //estadoJuego=EstadoJuego::RealGame;
                //estadoJuego = EstadoJuego::RealGame;
                // Opción "Jugar"
                // Aquí puedes iniciar el juego o cambiar el estado del juego
                sigueEnMenu = false;
            } else if (opcionSeleccionada == 1) {
                // Opción "Configuración"
                // Implementa la configuración del juego si lo deseas
            } else if (opcionSeleccionada == 2) {
                // Opción "Salir"
                ventana.close();
            }
        }
        return sigueEnMenu;
    }

    void Update(){};

    ///Funcion para dibujar los componentes del menu
    void Draw(){
        ventana.draw(spriteFondo);
        spriteFondo.setScale(ventana.getSize().x/spriteFondo.getTexture()->getSize().x,
                             ventana.getSize().y/spriteFondo.getTexture()->getSize().y);
        // Configura el tamaño y color del texto
        int tamTexto = 30;
        sf::Color colorTextoNormal = sf::Color::White;
        sf::Color colorTextoSeleccionado = sf::Color::Red;
        for (size_t i = 0; i < opciones.size(); i++) {
            sf::Text texto(opciones[i], fuente, tamTexto);
            texto.setPosition(ventana.getSize().x / 2 - texto.getGlobalBounds().width / 2, 500.f + i * 100.f);

            // Cambia el color del texto si está seleccionado
            if (i == opcionSeleccionada) {
                texto.setFillColor(colorTextoSeleccionado);
            } else {
                texto.setFillColor(colorTextoNormal);
            }

            ventana.draw(texto);
        }
    }

    int getOpcionSeleccionada(){
        return opcionSeleccionada;
    }

};

#endif //SPACEBULLET_MENU_H
