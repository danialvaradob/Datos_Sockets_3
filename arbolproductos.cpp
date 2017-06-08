#include "arbolproductos.h"
//#include "nodoproducto.cpp"
//#include <string>
//#include <iostream>
#include <sstream>
//ARBOL ArbolProductos


void ArbolProductos::buscar(int _codigoProducto, int _codigoCategoria, std::string _nombreProducto, double _precioPorUnidad, int _cantidadEnStock)
{
    NodoProducto *temp = new NodoProducto( _codigoProducto,  _codigoCategoria,  _nombreProducto,  _precioPorUnidad,  _cantidadEnStock);
    temp->nivel = 1;
    temp->cont = 0;
    temp->izq = NULL;
    temp->der = NULL;
    temp->padre = NULL;
    temp=insertarNodo(raiz, temp);
}

void ArbolProductos::girar(NodoProducto  *temp)
{
    NodoProducto *ptr = temp->izq;
    if (temp->padre->izq == temp)
        temp->padre->izq = ptr;
    else
        temp->padre->der = ptr;
    ptr->padre = temp->padre;
    temp->padre = ptr;
    temp->izq = ptr->der;
    if (temp->izq != NULL)
        temp->izq->padre = temp;
    ptr->der = temp;
    temp->nivel = (temp->izq ? temp->izq->nivel + 1 : 1);
}




bool ArbolProductos::dividir(NodoProducto  *temp)
{
    NodoProducto * ptr = temp->der;
    if (ptr && ptr->der && (ptr->der->nivel == temp->nivel))
    {
        if (temp->padre->izq == temp)
            temp->padre->izq = ptr;
        else
            temp->padre->der = ptr;
        ptr->padre = temp->padre;
        temp->padre = ptr;
        temp->der = ptr->izq;
        if (temp->der != NULL)
            temp->der->padre = temp;
        ptr->izq = temp;
        ptr->nivel = temp->nivel + 1;
        return true;
    }
    return false;
}

void ArbolProductos::balancear(NodoProducto * temp)
{
    temp->izq = NULL;
    temp->der = NULL;
    temp->nivel = 1;
    for (temp = temp->padre; temp != raiz; temp = temp->padre)
    {
        if (temp->nivel != (temp->izq ? temp->izq->nivel + 1 : 1 ))
        {
            girar(temp);
            if (temp->der == NULL)
                temp = temp->padre;
            else if (temp->nivel != temp->der->nivel)
                temp = temp->padre;
        }
        if (temp->padre != raiz)
        {
            if (!dividir(temp->padre))
                break;
        }
    }
}

NodoProducto* ArbolProductos::insertarNodo(NodoProducto * temp, NodoProducto * ins)
{
    if (raiz == NULL)
    {
        ins->cont = 1;
        ins->padre = NULL;
        ins->izq = NULL;
        ins->der = NULL;
        raiz = ins;
        return temp;
    }
    if (ins->getCodigoProducto() < temp->getCodigoProducto())
    {
        if (temp->izq)
            return insertarNodo(temp->izq, ins);
        temp->izq = ins;
        ins->padre = temp;
        ins->cont = 1;
        balancear(ins);
        return ins;
    }
    if (ins->getCodigoProducto() > temp->getCodigoProducto())
    {
        if (temp->der)
            return insertarNodo(temp->der, ins);
        temp->der = ins;
        ins->padre = temp;
        ins->cont = 1;
        balancear(ins);
        return ins;
    }
    temp->cont++;
    delete ins;
    return temp;
}



bool ArbolProductos::existeProducto(NodoProducto *_raiz, int _codProducto) {
    if(_raiz==NULL){
        //cout << "Final de un nodo" << endl;
        return false;
    }else if (_raiz->getCodigoProducto() == _codProducto) {
        std::cout << "PRODUCTO ENCONTRADO" << std::endl;
        return true;
    }else{
        //cout << "buscando" << endl;
        return  existeProducto(_raiz->izq,_codProducto) || existeProducto(_raiz->der,_codProducto);


    }
}

NodoProducto *ArbolProductos::eliminar(NodoProducto *_raiz, int _codigoProducto) {
    //_raiz = T
    // L = L
    //_codigoProducto = X

    NodoProducto *L;
    if( _codigoProducto > _raiz->getCodigoProducto()) {
        _raiz->der = eliminar(_raiz->der, _codigoProducto);
    } else if(_codigoProducto < _raiz->getCodigoProducto()) {

        _raiz->izq = eliminar(_raiz->izq, _codigoProducto);

    } else {
        if (_raiz->izq == NULL && _raiz->der == NULL) {
            return NULL;
        }else {
            if(_raiz->izq == NULL){
                L = _raiz->der;
                _raiz->der = eliminar(_raiz->der, L->getCodigoProducto());
                _raiz = L;
            } else{
                L = _raiz->padre;
                _raiz->izq = eliminar(_raiz->izq, L->getCodigoProducto());
                _raiz = L;
            }
        }
    }
    raiz = decrementarNivel(raiz);
    if (raiz->izq) girar(raiz);
    if (raiz->der) girar(raiz->der);
    if (raiz->der->der) girar(raiz->der->der);
    dividir(raiz);
    if (raiz->der) dividir(raiz->der);
    return raiz;

}




/*
void ArbolProductos::PreordenI(NodoProducto *R){
    if(R==NULL){
        return;
    }else{

        cout << "Nombre del producto: " << R->getNombreProducto() << endl;
        cout << "Codigo del producto: " << R->getCodigoProducto() << endl;
        cout << "Pertenece a la categoria: " << R->getCodigoCategoria() << endl;
        PreordenI(R->izq);
        PreordenI(R->der);
    }
}
*/
void ArbolProductos::cambiarStock(NodoProducto *&_raiz,int _codProducto, int _cantidad) {
    if (_raiz == NULL) return;
/*
    else {
        if (_raiz->getCodigoProducto() == _codProducto) {
            _raiz->getCantidadEnStock()

        }

    }*/
}


void ArbolProductos::getNodoProducto(int _codProducto, NodoProducto* _raiz, NodoProducto *&_nuevoNodo) {
    if (_raiz == NULL) return;

    else if (_codProducto == _raiz->getCodigoProducto()) {
            _nuevoNodo = _raiz;
        }
    else {
        getNodoProducto(_codProducto, _raiz->izq,_nuevoNodo);
        getNodoProducto(_codProducto, _raiz->der,_nuevoNodo);

    }
}

void ArbolProductos::getProductoMasVendido(NodoProducto *_raiz, NodoProducto *&_nuevoNodo) {
    if (_raiz == NULL) return;
    else if (_raiz->getBestScore() > _nuevoNodo->getBestScore()) {

        _nuevoNodo = _raiz;
    } else {
        getProductoMasVendido(_raiz->izq,_nuevoNodo);
        getProductoMasVendido(_raiz->der,_nuevoNodo);

    }
}

void ArbolProductos::getProductosCambiaronStock(NodoProducto *_raiz, std::string &_string) {
    if (_raiz==NULL)return;
    else {
        if (_raiz->getCantidadEnStock() != _raiz->getCantidadAlInicio()) {
            std::stringstream flujo;
            std::string _codP;
            flujo << _raiz->getCodigoProducto();
            _codP = flujo.str();
            _string+="\nNombre: "+_raiz->getNombreProducto()+"\nCodigo: "+_codP+"\n";
        }
        getProductosCambiaronStock(_raiz->der, _string);
        getProductosCambiaronStock(_raiz->izq, _string);

    }
}

void ArbolProductos::PreordenSocket(NodoProducto *_raiz, std::string &_string) {
    if (_raiz==NULL)return;
    else {
        std::stringstream flujo;
        std::string nombre;
        flujo << _raiz->getCodigoProducto();
        nombre = flujo.str();
        _string+=nombre+"\n";
        PreordenSocket(_raiz->izq, _string);
        PreordenSocket(_raiz->der, _string);
    }
}

/*
 *
 *
 *
 *
 *


void ArbolProductos::PreordenI(NodoProducto *R){
    if(R==NULL){
        return;
    }else{
        cout<<"El id de la oferta es : "<<R->getCodigoProducto()<<endl;
        cout<<"Los precios de la oferta individual es :"<<R->obtenerI()<<" Y quedan :"<<R->obtenerCI()<<endl;
        cout<<"Los precios de la oferta Doble es :"<<R->obtenerD()<<" Y quedan :"<<R->obtenerCD()<<endl;
        PreordenI(R->izq);
        PreordenI(R->der);
    }
}



 void ArbolProductos::print(NodoProducto* temp)
{
    if (!temp)
        return;
    print(temp->izq);
    cout <<"Value: "<<temp->getCodigoProducto() << "  cont:" << temp->obtenerCI();
    cout<<"  nivel: "<<temp->obtenerCD()<<endl;
    print(temp->der);
}

void ArbolProductos::PreordenI(NodoProducto *R){
    if(R==NULL){
        return;
    }else{
        cout<<"El id de la oferta es : "<<R->getCodigoProducto()<<endl;
        cout<<"Los precios de la oferta individual es :"<<R->obtenerI()<<" Y quedan :"<<R->obtenerCI()<<endl;
        cout<<"Los precios de la oferta Doble es :"<<R->obtenerD()<<" Y quedan :"<<R->obtenerCD()<<endl;
        PreordenI(R->izq);
        PreordenI(R->der);
    }
}

int ArbolProductos::obtenerPrecioOferta(NodoProducto *O,int r,int ci,int cd){
    if(O==NULL){
        cout<<" El numero que usted ingreso no es de las ofertas"<<endl;
        return 0;
    }
    else if(O->getCodigoProducto()==r){
        if(O->obtenerCI()<ci){
            cout<<"No se tienen suficientes habitaciones simples."<<endl;
            return 0;
        }
        else if(O->obtenerCD()<cd){
            cout<<"No se tienen suficientes habitaciones dobles."<<endl;
            return 0;
        }
        else{
            return O->obtenerI()*ci + O->obtenerD()*cd;
        }
    }
    else{
        obtenerPrecioOferta(O->izq, r, ci, cd);
        obtenerPrecioOferta(O->der, r, ci, cd);
    }

}

 */


NodoProducto* ArbolProductos::torsion(NodoProducto *T) {
    if (!T)
        return NULL;
    else if(T->izq && T->izq->nivel == T->nivel) {
        NodoProducto* L = T->izq;
        T->izq = L->der;
        L->der = T;
        return  L;
    } else  {
        return T;
    }

}

NodoProducto* ArbolProductos::division(NodoProducto *T) {
    if (!T) {
        return NULL;
    }else if (T->der && T->der->der &&  T->nivel == T->der->der->nivel) {
        NodoProducto* R = T->der;
        T->der = R->izq;
        R->izq = T;
        R->nivel++;
        return R;
    }else {
        return T;
    }
}


NodoProducto* ArbolProductos::insertar(NodoProducto *T, int _codigoProducto, int _codigoCategoria,
                                       std::string _nombreProducto, double _precioPorUnidad, int _cantidadEnStock) {

    if (!T) {
        NodoProducto* X = new NodoProducto( _codigoProducto,  _codigoCategoria,  _nombreProducto,  _precioPorUnidad,  _cantidadEnStock);
        return X;
    }else if (_codigoProducto < T->getCodigoProducto()) {
        T->izq = insertar(T->izq, _codigoProducto,_codigoCategoria
                ,_nombreProducto,_precioPorUnidad,_cantidadEnStock);
    } else if (_codigoProducto > T->getCodigoProducto()) {
        T->der = insertar(T->der, _codigoProducto,_codigoCategoria
                ,_nombreProducto,_precioPorUnidad,_cantidadEnStock);
    }
    T = torsion(T);
    T = division(T);
    return T;

}


NodoProducto *ArbolProductos::decrementarNivel(NodoProducto *_raiz) {
    int debe_ser;
    if (_raiz->izq != NULL && _raiz->der != NULL) {
        //debe_ser = std::min(_raiz->izq->nivel,_raiz->der->nivel + 1);
        if (_raiz->izq->nivel < _raiz->der->nivel + 1) {
            debe_ser = _raiz->izq->nivel;
        } else {
            debe_ser = _raiz->der->nivel + 1;
        }
    }
    else if (_raiz->izq) {
        debe_ser = _raiz->izq->nivel;
    }else if (_raiz->der){
        debe_ser = _raiz->der->nivel;
    }

    if (debe_ser < _raiz->nivel) {
        _raiz->nivel = debe_ser;
        if (_raiz->der !=NULL && debe_ser < _raiz->der->nivel) {
            _raiz->der->nivel = debe_ser;
        }
    }
    return _raiz;
}

NodoProducto* ArbolProductos::borrar(NodoProducto *T, int _codPro) {
    //NodoProducto* L = new NodoProducto();
    int L;
    if (T && _codPro > T->getCodigoProducto()) {
        T->der = borrar(T->der,_codPro);
    } else if (T && _codPro < T->getCodigoProducto()) {
        T->izq = borrar(T->izq,_codPro);
    } else {
        if (T->izq == NULL && T->der==NULL) {
            return NULL;
        } else if (T->izq == NULL) {
            L = T->der->getCodigoProducto();
            T->der = borrar(T->der,L);
            T->setCodigo(L);
        } else {
            L = T->izq->getCodigoProducto();
            T->izq = borrar(T->izq,L);
            T->setCodigo(L);
        }

    }
    T = decrementarNivel(T);
    T = torsion(T);
    if (T) T->der = torsion(T->der);
    if (T && T->der)T->der->der = torsion(T->der->der);
    T = division(T);
    if(T->der) T->der = torsion(T->der);
    return T;

}

