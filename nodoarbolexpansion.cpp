//
// Created by Daniel Alvarado on 5/29/17.
//

#include "nodoarbolexpansion.h"
#include <sstream>

std::string NodoArbolExpansion::toString() {
    std::stringstream flujo1;
    std::stringstream flujo2;
    std::stringstream flujo3;
    std::string f1;
    std::string f2;
    std::string f3;
    flujo1 << codLugar1;
    f1 = flujo1.str();
    flujo2 << codLugar2;
    f2 = flujo2.str();
    flujo3 << peso;
    f3 = flujo3.str();

    return "Lugar1: " + f1 + "| Lugar2: " + f2 + "| Peso: " + f3 + ";\n";
}
