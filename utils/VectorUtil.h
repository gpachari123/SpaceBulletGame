//
// Created by EQUIPO on 4/08/2023.
//

#ifndef SPACEBULLET_VECTORUTIL_H
#define SPACEBULLET_VECTORUTIL_H

#include <SFML/System/Vector2.hpp>
#include <cmath>

class VectorUtil {
public:
    ///Funcion para obtener el vector proyeccion sobre otro vector
    static sf::Vector2f proyectarVectorSobreOtro(const sf::Vector2f& a, const sf::Vector2f& b) {
        float dot = (a.x * b.x) + (a.y * b.y);
        float lengthSquared = (b.x * b.x) + (b.y * b.y);

        return sf::Vector2f((dot / lengthSquared) * b.x, (dot / lengthSquared) * b.y);
    }

    ///Funcion para aplicar mirror a un vector
    static sf::Vector2f reflejarVector(const sf::Vector2f& original, const sf::Vector2f& mirror) {
        sf::Vector2f projection = proyectarVectorSobreOtro(original, mirror);
        return sf::Vector2f(2.0f * projection.x - original.x, 2.0f * projection.y - original.y);
    }

    ///Funcion para normalizar un vector ( vector unitario)
    static sf::Vector2f normalizarVector(const sf::Vector2f& vector){
        float x = vector.x;
        float  y = vector.y;
        float length = std::sqrt(x * x + y * y);
        if (length != 0.0f) {
            x /= length;
            y /= length;
        }
        return sf::Vector2f(x,y);
    }

    ///Funcion para obtener el angulo que forma un vector con el vector "X" positivo, en grados sexagesimales
    static float getAngleWithXAxis(const sf::Vector2f& vector){
        float x = vector.x;
        float y = vector.y;
        return std::atan2(y, x)* 180.0f / M_PI;
    }

    ///Funcion para incrementar un angulo dado a la direccion de un vector
    static void incrementarAnguloAVector(sf::Vector2f& vector, float incrementoDegrees){
        float x = vector.x;
        float y = vector.y;
        float currentAngleRadians = std::atan2(y, x);
        float incrementRadians = incrementoDegrees * M_PI / 180.0f; // Convertir 1 grado a radianes

        float newAngleRadians = currentAngleRadians + incrementRadians;

        // Calcular las nuevas coordenadas con el ángulo incrementado
        float length = std::sqrt(x * x + y * y);
        x = length * std::cos(newAngleRadians);
        y = length * std::sin(newAngleRadians);

        vector.x = x;
        vector.y = y;
    }

    //Funcion para obtener la distancia entre dos vectores ( cabeza de vectores)
    static float distanceBetweenVector(const sf::Vector2f& v1,const sf::Vector2f& v2){
        float deltaX = v2.x - v1.x;
        float deltaY = v2.y - v1.y;

        return std::sqrt(deltaX * deltaX + deltaY * deltaY);;
    }
};



#endif //SPACEBULLET_VECTORUTIL_H
