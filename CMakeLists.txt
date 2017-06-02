cmake_minimum_required(VERSION 3.7)
project(Progra_3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp listaconexiones.cpp listaconexiones.h listalugares.cpp listalugares.h nodolugar.cpp nodolugar.h nodoconexion.cpp nodoconexion.h pila.cpp pila.h arbolexpansion.cpp arbolexpansion.h nodoarbolexpansion.cpp nodoarbolexpansion.h)
add_executable(Progra_3 ${SOURCE_FILES})