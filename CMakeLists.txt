cmake_minimum_required(VERSION 3.7)
project(Progra_3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp listaconexiones.cpp listaconexiones.h listalugares.cpp listalugares.h nodolugar.cpp nodolugar.h nodoconexion.cpp nodoconexion.h pila.cpp pila.h arbolexpansion.cpp arbolexpansion.h nodoarbolexpansion.cpp nodoarbolexpansion.h nodo.cpp nodo.h
        arbolproveedores.h arbolproveedores.cpp arbolproductos.h arbolproductos.cpp arbolclientes.h arbolclientes.cpp arbolsupermercados.h arbolsupermercados.cpp
        nodoproducto.h nodoproducto.cpp nodocliente.h nodocliente.cpp nodosupermercado.h nodosupermercado.cpp nodoproveedor.h nodoproveedor.cpp nodocategoria.cpp nodocategoria.h arbolcategorias.h arbolcategorias.cpp)
add_executable(Progra_3 ${SOURCE_FILES})