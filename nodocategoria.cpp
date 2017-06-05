//
// Created by Daniel Alvarado on 5/8/17.
//

#include "nodocategoria.h"
#include <sstream>

std::string nodocategoria::toString() {
    std::stringstream flujo;
    std::stringstream flujo2;
    std::string _cod;
    std::string _bestScore;

    flujo << codigo;
    _cod = flujo.str();
    flujo2 << bestScore;
    _bestScore = flujo2.str();

    return "Codigo de categoria: "+_cod+"\nDescripcion del producto: "+descripcion;
}
