//
// Created by Daniel Alvarado on 5/20/17.
//

#include "arbolexpansion.h"
#include "pila.h"

/*
ArbolExpansionMinimo::ArbolExpansionMinimo(ListaLugares* _grafo) {
    n = _grafo->getNumVertices();
    INFINITO = 0xFFFF;
    longMin = 0;
    typedef int* pint;
    T = new pint [n];
    for (int i = 0;i < n;i++) {
        T[i] = new int [n];
        for (int j = 0; j < n;j ++) {
            T[i][j] = INFINITO;
        }
    }
}

int ArbolExpansionMinimo::arbolExpancionPrim(ListaLugares *_grafo) {
    int menor;
    int *coste = new int [n];
    int i,j,z;
    int *masCerca = new int[n];
    bool *W = new bool [n];
    for (i = 0; i < n; i++)
        W[i] = false;           //Conjunto Vacio
    W[0] = true;                //se parte del vertice 0
                                //inicialmente, coste[i] es la arista (0,i)
    for (i=1; i < n;i++) {
        coste[i] = _grafo->Ovalor(0,i);
        masCerca[i] = 0;
    }

    coste[0] = INFINITO;
    for (i = 1; i < n;i++) {
        //busca vertice x de V-W mas cercano,
        //de menor longitud de arista, a algun vertice de w
        menor = coste[i];
        z = 1;
        for (j = 2;j < n;j++) {
            if (coste[j] < menor) {
                menor = coste[j];
                z = j;
            }
        }
        longMin += menor;
        //se escribe el arco incorporado al arbol de expansion
        std::cout << "V" << masCerca[z] << "-> V" << z;
        W[z] = true;            //vertice z se anade al conjunto de W
        T[masCerca[z]][z] = T[z][masCerca[z]] = coste[z];
        coste[z] = INFINITO;
                        //debido a la incorporacion de z,
                        //se ajusta el coste[] para el resto de vertices
        for (j = 1;j < n; j++){
            if ((_grafo->Ovalor(i,z) < coste[j])&& !W[j]) {
                coste[j] = _grafo->Ovalor(i,z);
                masCerca[j] = z;
            }
        }
    }
    return longMin;

}
*/

int ArbolExpansionMinimo::largoArbol() {
    int cont = 1;
    NodoArbolExpansion* aux;
    aux = primero;
    if(arbolVacio()){
        return cont;
    }else{
        while(aux->siguiente != primero){
            aux=aux->siguiente;
            cont++;
        }
        return cont;
    }
}



std::string ArbolExpansionMinimo::prim(ListaLugares *_grafo, int _primerNodo) {
    int cantidadNodos = _grafo->getNumVertices();
    int cantNodosVisitados = 0;
    int codMenor,pesoMenor;
    bool crearNodoArbolExp = false;


    NodoLugar* nodo = _grafo->getNodoLugar(_primerNodo);
    NodoLugar* nodo2;

    //lista donde va a recorrer todos
    while (cantidadNodos > 0) {

        if (arbolVacio()) {

            int codigo1 = nodo->getCodigo();
            codMenor = nodo->getCodigoMenorConexion();
            NodoLugar* nodoMenor = _grafo->getNodoLugar(codMenor);
            //se cambia a visitado tanto el nodo del usuario como el otro vertice
            nodo->visitar();
            nodo->visitarConexion(codMenor);
            nodoMenor->visitar();
            nodoMenor->visitarConexion(codigo1);
            //funcion que visita todos los nodos de conexiones a traves de una lista de lugares
            _grafo->visitarTodasConexiones(codMenor);
            _grafo->visitarTodasConexiones(codigo1);
            cantNodosVisitados += 2;
            pesoMenor = nodo->getPesoMenorConexion(codMenor);
            insertarNodo(codigo1,codMenor,pesoMenor);

        }else {

            int i = largoArbol();
            int codigoNodo1,codigoNodo2;
            //VARIABLES QUE GUARDAN LOS DOS CODIGOS DE LOS LUGARES QUE ESTAN CONECTADOS
            //SI EL PESO ENTRE ESTOS DOS CODIGOS ES EL MENOR ENTONCES SE CREA UN NODOEXPANSION
            int codVertice1,codVertice2;
            NodoArbolExpansion* nodoExpansionAux = primero;
            crearNodoArbolExp = false;
            do {
                //nodo = _grafo->getNodoLugar(nodoExpansionAux->codLugar1);
                //nodo2 = _grafo->getNodoLugar(nodoExpansionAux->codLugar2);
                //CAMBIAR ESTA FUNCION PARA DESPUES PODER COMPARAR CON ESTE
                if (nodoExpansionAux == primero){
                    pesoMenor = _grafo->getMayorPeso();
                }
                //primer codigo
                codigoNodo1 = nodoExpansionAux->codLugar1;
                nodo = _grafo->getNodoLugar(codigoNodo1);

                int codigoAcomparar = nodo->getCodigoMenorConexion();
                //if (!nodoVisitado(nodo->getCodigoMenorConexion())) {
                if (!nodoVisitado(codigoAcomparar) && _grafo->existeLugar(codigoAcomparar) && nodo->existeConexion(codigoAcomparar)) {
                    //si entra aca quiere decir que retorno un codigo que no esta visitado
                    if (pesoMenor >= nodo->getPesoMenorConexion(nodo->getCodigoMenorConexion())) {
                        pesoMenor = nodo->getPesoMenorConexion(nodo->getCodigoMenorConexion());
                        codVertice1 = nodo->getCodigo();
                        codVertice2 = nodo->getCodigoMenorConexion();
                        crearNodoArbolExp = true;
                    }
                }
                //segundo codigo
                codigoNodo2 = nodoExpansionAux->codLugar2;
                nodo2 = _grafo->getNodoLugar(codigoNodo2);
                int codigoAcomparar2 = nodo2->getCodigoMenorConexion();
                //if (!nodoVisitado(nodo2->getCodigoMenorConexion())) {
                if (!nodoVisitado(codigoAcomparar2) && _grafo->existeLugar(codigoAcomparar2) && nodo2->existeConexion(codigoAcomparar2)) {
                    //si entra aca quiere decir que retorno un codigo que no esta visitado
                    if (pesoMenor >= nodo2->getPesoMenorConexion(nodo2->getCodigoMenorConexion())) {
                        pesoMenor = nodo2->getPesoMenorConexion(nodo2->getCodigoMenorConexion());
                        codVertice1 = nodo2->getCodigo();
                        codVertice2 = nodo2->getCodigoMenorConexion();
                        crearNodoArbolExp = true;
                    }
                }
                nodoExpansionAux = nodoExpansionAux->siguiente;
            }while(nodoExpansionAux != primero);
            if (crearNodoArbolExp) {
                //ACA A LOS CODIGOS QUE HAYAN EN CODIGO VERTICE
                //LUGAR1
                nodo = _grafo->getNodoLugar(codVertice1);
                nodo2->visitar();
                //LUGAR2 --> LO VISITA
                nodo2 = _grafo->getNodoLugar(codVertice2);
                nodo2->visitar();
                //visita todas las conexiones
                _grafo->visitarTodasConexiones(codVertice1);
                _grafo->visitarTodasConexiones(codVertice2);
                //INSERTA EL NODO AL ARBOL
                insertarNodo(codVertice1, codVertice2, pesoMenor);
                //pesoTotal += pesoMenor;
            }
        }
        cantidadNodos--;
    }

    _grafo->desvisitarTODO();
    std::cout << "El peso total es: "<< pesoTotal << std::endl;
    return std::to_string(pesoTotal);
}

std::string ArbolExpansionMinimo::getPrim() {

}

void ArbolExpansionMinimo::kruskal(ListaLugares *_grafo, int _primerNodo) {
    int codNodo2, peso;


    NodoLugar *nodo = _grafo->getNodoLugar(_primerNodo);
    do
    {
        if (arbolVacio()) {
            int codigo1 = nodo->getCodigo();
            NodoConexion *nodoConexion = nodo->getConexiones()->primero;
            codNodo2 = nodoConexion->codLugar;
            peso = nodoConexion->peso;
            insertarNodo(codigo1, codNodo2, peso);
            nodoConexion = nodoConexion->siguiente;

            while (nodoConexion != nodo->getConexiones()->primero) {
                codigo1 = nodo->getCodigo();
                codNodo2 = nodoConexion->codLugar;
                peso = nodoConexion->peso;
                insertarNodo(codigo1, codNodo2, peso);
                nodoConexion = nodoConexion->siguiente;
            }
        } else {
            int codigo1 = nodo->getCodigo();
            NodoConexion *nodoConexion = nodo->getConexiones()->primero;
            codNodo2 = nodoConexion->codLugar;
            if (!existeConexion(codigo1,codNodo2)) {
                peso = nodoConexion->peso;
                insertarNodo(codigo1, codNodo2, peso);
            }
            nodoConexion = nodoConexion->siguiente;
            while (nodoConexion != nodo->getConexiones()->primero) {
                codigo1 = nodo->getCodigo();
                codNodo2 = nodoConexion->codLugar;
                if(!existeConexion(codigo1,codNodo2)){
                    peso = nodoConexion->peso;
                    insertarNodo(codigo1, codNodo2, peso);
                    nodoConexion = nodoConexion->siguiente;
                }else{
                    nodoConexion = nodoConexion->siguiente;
                    continue;
                }
            }
        }
        nodo = nodo->siguiente;
    } while (nodo != _grafo->primero);

    ordenarKruskal();
    ListaConjunto *kruskal = new ListaConjunto();
    seleccionarAristas(kruskal);
    imprimirKruskal();
    _grafo->desvisitarTODO();
}

void ArbolExpansionMinimo::ordenarKruskal() {
    NodoArbolExpansion *aux;

    int i = 1;
    while(i <= largoArbol()-1)
    {
        aux = obetenerNodoEnPosicion(i);
        if (i==1 || aux->anterior->peso <= aux->peso)
        {
            i++;
            continue;
        }else if (aux->peso < primero->peso && !aux->ordenado)
        {
            aux->anterior->siguiente = aux->siguiente;
            aux->siguiente->anterior = aux->anterior;
            primero->anterior->siguiente = aux;
            aux->anterior = primero->anterior;
            aux->siguiente = primero;
            primero->anterior = aux;
            primero = aux;
            primero->ordenado = true;
        }else{
            aux->anterior->anterior->siguiente = aux;
            aux->siguiente->anterior = aux->anterior;
            aux->anterior->siguiente = aux->siguiente;
            aux->siguiente = aux->anterior;
            aux->anterior = aux->siguiente->anterior;
            aux->siguiente->anterior = aux;
        }
        i--;
        if (i==0)
        {
            i=1;
        }
    }
}

void ArbolExpansionMinimo::seleccionarAristas(ListaConjunto *conjunto) {
    NodoArbolExpansion *aux = primero;
    do{
        if(conjunto->listaVacia()){
            conjunto->insertarConjunto(aux->codLugar1);
            conjunto->insertarNodoEnConjunto(aux->codLugar2, 1);
            aux->kruskalElegido = true;
        }
        else {
            if(!conjunto->existeEnLista(aux->codLugar1) && !conjunto->existeEnLista(aux->codLugar2)){
                conjunto->insertarConjunto(aux->codLugar1);
                conjunto->insertarNodoEnConjunto(aux->codLugar2, conjunto->largoLista());
                aux->kruskalElegido = true;
            } else {
                if (conjunto->getIndicedelNodo(aux->codLugar1) == 0) {
                    int indice = conjunto->getIndicedelNodo(aux->codLugar2);
                    conjunto->insertarNodoEnConjunto(aux->codLugar1, indice);
                    aux->kruskalElegido = true;
                }
                if (conjunto->getIndicedelNodo(aux->codLugar2) == 0) {
                    int indice = conjunto->getIndicedelNodo(aux->codLugar1);
                    conjunto->insertarNodoEnConjunto(aux->codLugar2, indice);
                    aux->kruskalElegido = true;
                } else {
                    if(!conjunto->existeNodoEnConjunto(aux->codLugar2, conjunto->getIndicedelNodo(aux->codLugar1)) || !conjunto->existeNodoEnConjunto(aux->codLugar1, conjunto->getIndicedelNodo(aux->codLugar2))){
                        conjunto->unirConjuntos(conjunto->getIndicedelNodo(aux->codLugar1),conjunto->getIndicedelNodo(aux->codLugar2));
                        aux->kruskalElegido = true;
                    }
                }
            }
        }
        aux = aux->siguiente;
    }while(aux != primero);
}

void ArbolExpansionMinimo::imprimirKruskal() {
    NodoArbolExpansion *aux = primero;
    pesoTotal = 0;
    do{
        if(aux->kruskalElegido){
            std::cout << "cod1: " << aux->codLugar1 << "| cod2: " << aux->codLugar2 << "| peso: " << aux->peso << std::endl;
            pesoTotal += aux->peso;
        }
        aux = aux->siguiente;
    }while(aux!=primero);
    std::cout << "Peso Total: " << pesoTotal << std::endl;
}

NodoArbolExpansion *ArbolExpansionMinimo::obetenerNodoEnPosicion(int pos) {
    int cont = 0;
    NodoArbolExpansion *aux = primero;
    while(cont<pos){
        aux = aux->siguiente;
        cont++;
    }
    return aux;
}

void ArbolExpansionMinimo::insertarNodo(int _codigo1, int _codigo2, int _peso) {

    if (arbolVacio()){
        NodoArbolExpansion* nuevo = new  NodoArbolExpansion( _codigo1,  _codigo2,  _peso);
        primero = nuevo;
        nuevo->siguiente = primero;
        nuevo->anterior = primero;
        pesoTotal = _peso;
    }else{
        NodoArbolExpansion* nuevo = new  NodoArbolExpansion( _codigo1,  _codigo2,  _peso);
        nuevo->siguiente = primero;
        nuevo->anterior = primero->anterior;
        primero->anterior->siguiente = nuevo;
        primero->anterior = nuevo;
        pesoTotal += _peso;

    }
}

bool ArbolExpansionMinimo::existeConexion(int _codigo1, int _codigo2) {
    if (arbolVacio()) {
        return false;
    }else {
        NodoArbolExpansion* aux = primero;
        do {
            if ((aux->codLugar1 == _codigo1 && aux->codLugar2 == _codigo2) || (aux->codLugar1 == _codigo2 && aux->codLugar2 == _codigo1))
                return true;
            aux = aux->siguiente;

        } while (aux != primero);

        return false;

    }
}

bool ArbolExpansionMinimo::nodoVisitado(int _codigo) {
    if (arbolVacio()) {
        return false;
    }else {
        NodoArbolExpansion* aux = primero;
        do {
            if (aux->codLugar1 == _codigo || aux->codLugar2 == _codigo)
                return true;
            aux = aux->siguiente;

        } while (aux != primero);

        return false;

    }

}



/*
void ArbolExpansionMinimo::profundida(ListaLugares *_grafo, int _puntoInicial) {
    int cantVisitados = 0;
    int cantLugares,contador = _grafo->getNumVertices();
    Pila* pilaLugares = new Pila();
    NodoLugar* lugar;


    while (contador > 0) {
        if (contador == cantLugares) {
            pilaLugares->push(_puntoInicial);
            lugar = _grafo->getNodoLugar(_puntoInicial);
        }





        cantLugares--;
    }


}
*/



