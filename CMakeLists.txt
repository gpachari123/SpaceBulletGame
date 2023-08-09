cmake_minimum_required(VERSION 3.23.2)
project(SpaceBullet)

set(CMAKE_CXX_STANDARD 20)

add_executable(SpaceBullet
        main.cpp
        components/Componente.h
        utils/VectorUtil.h
        components/Plataforma.h general/Partida.h general/Menu.h
        components/Personaje.h components/CompBarraPoder.h components/CompBarraVida.h components/AnguloDisparo.h components/FondoPartida.h components/Proyectil.h components/ExplosionProyectil.h components/factoryEscenarios.h components/TimerTurnos.h components/MascaraBarraPoder.h components/GameOver.h components/FlechaTurno.h)

find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics audio window network system)

target_link_libraries(SpaceBullet
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-network
        sfml-system
        )