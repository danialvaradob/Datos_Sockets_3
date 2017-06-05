#include "arbolsupermercados.h"
//#include "nodosupermercado.h"
//#include <iostream>
//#include <iostream>
//#include <stdio.h>
#include <sstream>

//ARBOL AVL



/*Variables:
nuevo: Nueva hoja del arbol
recorrer: Es el puntero que esta señalando hacia la raiz del arbol, esta variable recorre el arbol hasta encontrar un espacio null donde guardar el nuevo nodo.
PadreAB: Mantiene un puntero al nodo anterior para referirse a el como el padre del nuevo nodo.
Funciones involucradas:
Recursivamente se llama así mismo hasta encontrar la ubicación donde se guardará el nuevo nodo, envío como parámetros (La dirección del lado del árbol hacía donde entrará, La nueva hoja, Referencia al padre).
*/
void ArbolSupermercados::insertarBalanceado(NodoSupermercado *&ra, bool &Hh, int _codSuper, int _codLugar, std::string _nombre) {
    NodoSupermercado *n1;

    if(ra==NULL){
        ra=new NodoSupermercado( _codSuper, _codLugar,  _nombre );
        Hh = true;
    }else {
        if (_codSuper <= ra->obtenerValor()) {

            insertarBalanceado(ra->Hizq, Hh, _codSuper, _codLugar, _nombre);

            if (Hh) {
                switch (ra->FB) {
                    case 1:
                        (ra->FB = 0);
                        Hh = false;
                        break;
                    case 0:
                        (ra->FB = -1);
                        break;
                    case -1:
                        (n1 = ra->Hizq);
                        if (n1->FB == -1) {
                            rotacionSimpleIzquierda(ra, n1);
                        } else {
                            rotacionDobleIzquierda(ra, n1);
                        }
                        Hh = false;
                        break;
                }
            }
        } else {
            if (_codSuper > ra->obtenerValor()) {
                insertarBalanceado(ra->Hder, Hh, _codSuper, _codLugar, _nombre);

                if (Hh) {
                    switch (ra->FB) {
                        case -1:
                            (ra->FB = 0);
                            Hh = false;
                            break;
                        case 0:
                            (ra->FB = 1);
                            break;
                        case 1:
                            (n1 = ra->Hder);
                            if (n1->FB == 1) {
                                rotacionSimpleDerecha(ra, n1);
                            } else {
                                rotacionDobleDerecha(ra, n1);
                            }
                            Hh = false;
                            break;
                    }
                }
            }
        }
    }
}



void ArbolSupermercados::equilibrar1(NodoSupermercado *&n, bool) {
    NodoSupermercado *n1;
    switch (n->FB){
        case -1: n->FB = 0;
            break;
        case 0: n->FB = 1;
            Hh = false;
            break;
        case 1: n1 = n->Hder;
            if(n1->FB>=0){
                if(n1->FB==0){
                    Hh = false;
                    rotacionSimpleDerecha(n, n1);
                }else{
                    rotacionDobleDerecha(n, n1);
                }
            }
    }
}

void ArbolSupermercados::equilibrar2(NodoSupermercado *&n, bool) {
    NodoSupermercado *n1;
    switch (n->FB){
        case 1: n->FB = 0;
            break;
        case 0: n->FB = 1;
            Hh = false;
            break;
        case -1: n1 = n->Hizq;
            if(n1->FB<=0){
                if(n1->FB==0){
                    Hh = false;
                    rotacionSimpleIzquierda(n, n1);
                }else{
                    rotacionDobleIzquierda(n, n1);
                }
            }
    }
}


void ArbolSupermercados::rotacionDobleIzquierda(NodoSupermercado *&n, NodoSupermercado *&n1) {
    NodoSupermercado *n2;
    n2=n1->Hder;
    n->Hizq = n2->Hder;
    n2->Hder=n;
    n1->Hder=n2->Hizq;
    n2->Hizq=n1;

    if(n2->FB==1){
        n1->FB=-1;
    }else{
        n1->FB=0;
    }
    if(n2->FB==-1){
        n->FB=1;
    }else{
        n->FB=0;
    }
    n2->FB=0;
    n=n2;
}
void ArbolSupermercados::rotacionDobleDerecha(NodoSupermercado *&n, NodoSupermercado *&n1) {
    NodoSupermercado *n2;
    n2=n1->Hizq;
    n->Hder = n2->Hizq;
    n2->Hizq=n;
    n1->Hizq=n2->Hder;
    n2->Hder=n1;

    if(n2->FB==1){
        n->FB=-1;
    }else{
        n->FB=0;
    }
    if(n2->FB==-1){
        n1->FB=1;
    }else{
        n1->FB=0;
    }
    n2->FB=0;
    n=n2;
}
void ArbolSupermercados::rotacionSimpleDerecha(NodoSupermercado *&n, NodoSupermercado *&n1) {
    n->Hder=n1->Hizq;
    n1->Hizq=n;

    if(n1->FB==1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=1;
        n1->FB=-1;
    }
    n=n1;
}

void ArbolSupermercados::rotacionSimpleIzquierda(NodoSupermercado *&n, NodoSupermercado *&n1) {

    n->Hizq = n1->Hder;
    n1->Hder = n;

    if(n1->FB==-1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=-1;
        n1->FB=-1;
    }
    n=n1;
}
void ArbolSupermercados::preordenI(NodoSupermercado *R) {
    if(R==NULL){
        return;
    }else{
        std::cout<<R->obtenerValor()<<std::endl;
        preordenI(R->Hizq);
        preordenI(R->Hder);
    }
}

//retornta true si el codigo de supermercado buscado existe
bool ArbolSupermercados::existeSupermercado(int _codNuevoSuper, NodoSupermercado* _raiz) {

    if (_raiz == NULL) {
        return false;
    } else if (_raiz->getCodSuper() == _codNuevoSuper) {
        return true;
    } else {

        return existeSupermercado(_codNuevoSuper,_raiz->Hizq) || existeSupermercado(_codNuevoSuper,_raiz->Hder);

    }
}

void ArbolSupermercados::agregarCategoria(NodoSupermercado *raiz,int _codSuper,int _codCat, std::string _descCat) {
    if (raiz == NULL) {
        return;
    } else if (raiz->codSuper == _codSuper){
        // primero revisa si esta vacio el arbol
        if (raiz->punteroCategorias == NULL) {
            //crea el arbol y le agrega la categoria
            raiz->punteroCategorias = new ArbolCategorias();
            raiz->punteroCategorias->insertarValorNodoRN(_codCat,_descCat);

        } else {
            raiz->punteroCategorias->insertarValorNodoRN(_codCat,_descCat);
        }
        //si no esta vacio lo agrega

    } else{
        agregarCategoria(raiz->Hizq,_codSuper,_codCat,_descCat);
        agregarCategoria(raiz->Hder,_codSuper,_codCat,_descCat);
    }

}

void ArbolSupermercados::agregarProducto(NodoSupermercado *raiz, int _codSuper,
                                         int _codCat, int _codProducto, std::string _nombreProducto, double _precioPorUnidad,
                                         int _cantidadEnStock) {
    if (raiz == NULL) {
        return;
    } else if (raiz->codSuper == _codSuper){
        // primero revisa si esta vacio el arbol
        raiz->punteroCategorias->agregarProducto(raiz->punteroCategorias->raiz,  _codProducto,
                                                   _codCat,  _nombreProducto,  _precioPorUnidad,
                                                   _cantidadEnStock);

        //si no esta vacio lo agrega

    } else{
        agregarProducto(raiz->Hizq, _codSuper,
             _codCat,  _codProducto,  _nombreProducto,  _precioPorUnidad,
             _cantidadEnStock);
        agregarProducto(raiz->Hder, _codSuper,
                        _codCat,  _codProducto,  _nombreProducto,  _precioPorUnidad,
                        _cantidadEnStock);
        //agregarCategoria(raiz->Hizq,_codSuper,_codCat,_descCat);
        //agregarCategoria(raiz->Hder,_codSuper,_codCat,_descCat);
    }

}



bool ArbolSupermercados::existeCategoria(int _codSuper,int _codCat, NodoSupermercado *_raiz) {
    if (_raiz == NULL) return false;

    else if (_raiz->punteroCategorias != NULL) {
            return _raiz->punteroCategorias->existeCategoria(_codCat,_raiz->punteroCategorias->raiz);
    } else {
        return existeCategoria(_codSuper, _codCat,_raiz->Hizq) || existeCategoria(_codSuper, _codCat,_raiz->Hder);
    }

}



ArbolCategorias* ArbolSupermercados::getArbolCategorias(int _codSuper,NodoSupermercado* _raiz) {
    if (_raiz == NULL) return NULL;

    else if (_raiz->codSuper == _codSuper) {
        return _raiz->punteroCategorias;
    } else {
        if (_raiz->Hder != NULL) {
            return getArbolCategorias( _codSuper,_raiz->Hder);
        }
        if (_raiz->Hizq != NULL) {
            return getArbolCategorias( _codSuper, _raiz->Hizq);
        }
    }
}

void ArbolSupermercados::getArbolCat(int _codSuper, NodoSupermercado *_raiz, ArbolCategorias *&_arbolCat) {
    if (_raiz == NULL) return;

    else if (_raiz->codSuper == _codSuper) {
        _arbolCat = _raiz->punteroCategorias;
    } else {
        getArbolCat( _codSuper,_raiz->Hder,_arbolCat);
        getArbolCat( _codSuper, _raiz->Hizq,_arbolCat);

    }
}

void ArbolSupermercados::getNodoSupermercado(int _codSuper, NodoSupermercado *_raiz, NodoSupermercado *&NuevoNodo) {
    if (_raiz== NULL) return;

    else {
        if (_raiz->getCodSuper() == _codSuper) {
            NuevoNodo = _raiz;

        } else {
            getNodoSupermercado(_codSuper,_raiz->Hder,NuevoNodo);
            getNodoSupermercado(_codSuper,_raiz->Hizq,NuevoNodo);

        }
    }
}

void ArbolSupermercados::getSuperMasVendido(NodoSupermercado *_raiz, NodoSupermercado *&NuevoNodo) {
    if (_raiz== NULL) return;

    else {
        if (_raiz->getCantidadVentas() > NuevoNodo->getCantidadVentas()) {
            NuevoNodo = _raiz;

        } else {
            getSuperMasVendido(_raiz->Hder,NuevoNodo);
            getSuperMasVendido(_raiz->Hizq,NuevoNodo);

        }
    }
}

void ArbolSupermercados::getCatMasVendidaS(NodoSupermercado *_raiz, int _codSuper,nodocategoria *&NuevoNodo) {
    if (_raiz== NULL) return;

    else {
        if (_raiz->getCodSuper() == _codSuper) {
            _raiz->punteroCategorias->getCategoriaMasVendida(_raiz->punteroCategorias->raiz, NuevoNodo);

        } else {
            getCatMasVendidaS(_raiz->Hder,_codSuper, NuevoNodo);
            getCatMasVendidaS(_raiz->Hizq,_codSuper, NuevoNodo);

        }
    }
}

void ArbolSupermercados::PreordenSocket(NodoSupermercado *_raiz, std::string &_string) {
    if(_raiz == NULL)
        return;
    else{
        std::stringstream flujo;
        std::string nombre;
        flujo << _raiz->getCodSuper();
        nombre = flujo.str();
        _string+=nombre+"\n";
        PreordenSocket(_raiz->Hizq, _string);
        PreordenSocket(_raiz->Hder, _string);
    }

}

/*/++++++++++++++++++++ inserciones de archivo+++++++++++++++++++++++++++++
 *
 * MODIFICAR Y CAMBIAR A insertarNodoCat  (RN)
 *                       inserntarNodoPro (AA)
 *
void AVL :: InsertaNodoTransporte(NodoHotel *H,int idHotel, int idTransporte, int tipoT,string origen, string destino,string salida,string horaSalida ,string Llegada,string horaLlegada,string compannia ,int  plazas,int precio,int cantT){
    if (H==NULL){
        return;
    }
    else{
        if (H->obtenerValor()==idHotel){
            if (H->siguiente==NULL){
                H->siguiente=new RNegro();
            }
            H->siguiente->insertarValorNodoRN(idTransporte,tipoT,origen, destino, salida, horaSalida, Llegada, horaLlegada,compannia, plazas, precio,  cantT  );
            return;

        }

        else{
            InsertaNodoTransporte(H->Hizq,idHotel, idTransporte,tipoT,origen, destino, salida, horaSalida, Llegada, horaLlegada,compannia, plazas, precio,  cantT );
            InsertaNodoTransporte(H->Hder,idHotel, idTransporte,tipoT,origen, destino, salida, horaSalida, Llegada, horaLlegada,compannia, plazas, precio,  cantT );
        }
    }
}
void AVL:: InsertaNodoOferta(NodoHotel *H,int idHotel, int  idOferta,int  precioInd,int precioDoble,int cantI,int  cantD){
    if (H==NULL){
        return;
    }
    else{
        if (H->obtenerValor()==idHotel){
            if (H->anterior==NULL){
                H->anterior=new AA();
            }
            H->anterior->lookup( idFBrta,  precioInd,  precioDoble,  cantI,  cantD);
            return;
        }
        else{
            InsertaNodoOferta(H->Hizq, idHotel,  idOferta,  precioInd,  precioDoble,  cantI,  cantD);
            InsertaNodoOferta(H->Hder, idHotel,  idOferta,  precioInd,  precioDoble,  cantI,  cantD);
        }
    }
}

 */

