cmake_minimum_required(VERSION 3.25)
project(SpaceBullet)

set(CMAKE_CXX_STANDARD 20)

add_executable(SpaceBullet
        main.cpp
        components/Componente.h
        utils/VectorUtil.h
        components/Plataforma.h general/Partida.h general/Menu.h
        components/Personaje.h)

find_package(SFML 2.5.1 REQUIRED COMPONENTS graphics audio window network system)

target_link_libraries(SpaceBullet
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-network
        sfml-system
        )