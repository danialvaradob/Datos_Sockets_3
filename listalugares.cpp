//
// Created by Daniel Alvarado on 5/18/17.
//
#include "listalugares.h"
#include "ListaConexiones.cpp"

ListaLugares::~ListaLugares() {
    NodoLugar* aux;

    while(primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    actual = NULL;
}

void ListaLugares::insertarLugar(int _codigo, std::string _nombre) {

    if (listaVacia()){
        NodoLugar* nuevo = new  NodoLugar( _codigo,  _nombre);

        primero = nuevo;
        nuevo->siguiente = primero;
        nuevo->anterior = primero;
    }else{
        NodoLugar* nuevo = new  NodoLugar( _codigo,  _nombre);
        nuevo->siguiente = primero;
        nuevo->anterior = primero->anterior;
        primero->anterior->siguiente = nuevo;
        primero->anterior = nuevo;

    }
}

int ListaLugares::largoLista() {
    int cont = 1;
    NodoLugar* aux;
    aux = primero;
    if(listaVacia()){
        return cont;
    }else{
        while(aux->siguiente != primero){
            aux=aux->siguiente;
            cont++;
        }
        return cont;
    }
}

bool ListaLugares::existeLugar(int _codigo) {
    NodoLugar* aux = primero;
    if (listaVacia()) return false;

    do{
        if (aux->codigo == _codigo) return true;
        aux = aux->getSiguiente();
    }while(aux!= primero);
    return false;
}

void ListaLugares::aumentarCantidadDeSupermercados(int _codLugar) {
    NodoLugar* aux = primero;
    do {
        if (aux->getCodigo() == _codLugar) aux->aumentarCantidadSuper();

        aux = aux->getSiguiente();
    } while (aux != primero);


}

void ListaLugares::getLugarMasSuper(NodoLugar*&_lugarMasSupermercados) {
    NodoLugar* aux = primero;
    while (aux->siguiente!= primero) {
        if (aux == primero) {
            //primera vez, hace el que tiene mayor cantidad de supermercados al primero
            _lugarMasSupermercados = primero;
        }
        else {
            if (aux->cantidadSupermercados > _lugarMasSupermercados->cantidadSupermercados) {
                _lugarMasSupermercados = aux;
            }
        }
        aux = aux->siguiente;
    }
}

NodoLugar* ListaLugares::getNodoLugar(int _codigo) {
    NodoLugar* aux = primero;
    do {
        if (aux->getCodigo() == _codigo)
            return aux;
        aux = aux->siguiente;
    } while (aux!= primero);

    return NULL;
}


//De un cierto nodo, retorna su nodo menor completo con todas sus respectivas conexiones
NodoLugar* ListaLugares::getMenorConexion(NodoLugar *_nodoIncicial) {
    int codigoMenorConexion;
    codigoMenorConexion = _nodoIncicial->getCodigoMenorConexion(); //Codigo de la menor conexion
    NodoLugar* menorConexion =  getNodoLugar(codigoMenorConexion);
    return menorConexion;

}




void ListaLugares::recorridoProfundidad(NodoLugar *_nodoInicial) {

}

int ListaLugares::getNumVertices() {
    int cont = 0;
    NodoLugar* aux = primero;
    do {
        if (aux->conexiones->getCantidadConexiones() != 0)
            cont ++;
        aux = aux->siguiente;
    } while (aux != primero);
    return cont;
}

int ListaLugares::getCodigo(int _posicion) {
    int cont,codigoLugar;
    cont = 0;
    codigoLugar = 0;
    NodoLugar* aux = primero;
    do {
        if (cont == _posicion){
            codigoLugar = aux->getCodigo();
            break;
        }
        cont ++;
        aux = aux->siguiente;
    } while (aux != primero);

    return codigoLugar;
}




void ListaLugares::visitarTodasConexiones(int _codigoDeConexion) {

    NodoLugar* aux = primero;
    do {
        aux->visitarConexion(_codigoDeConexion);
        aux = aux->siguiente;
    } while (aux != primero);


}

void ListaLugares::desvisitarTODO() {
    NodoLugar* aux = primero;
    do {
        aux->visitado = false;
        aux->desvisitarConexiones();
        aux = aux->siguiente;
    } while (aux != primero);
}

int ListaLugares::getMayorPeso() {
    NodoLugar* lugar = primero;
    if (primero->conexiones->primero == NULL) return -1;
    int mayorPeso = primero->conexiones->primero->peso;
    do {
        if (mayorPeso < lugar->getConexiones()->getMayorPeso()) {
            mayorPeso = lugar->getConexiones()->getMayorPeso();

        }
        lugar = lugar->siguiente;
    } while (lugar != primero);
    return mayorPeso;
}

bool ListaLugares::todosVisitados() {
    NodoLugar* aux = primero;
    do {
        if (!aux->visitado)
            return false;
        aux = aux->siguiente;
    } while (aux != primero);
    return true;
}


std::string ListaLugares::profundida(int _puntoInicial) {
    std::string recorrido_str = "";

    int cantVisitados,codLugar = 0;
    int contador = getNumVertices();
    int cantLugares = getNumVertices();
    Pila* pilaLugares = new Pila();
    NodoLugar* lugar;
    while (contador > 0 && !todosVisitados()) {
        if (contador == cantLugares) {
            pilaLugares->push(_puntoInicial);
            //lugar = getNodoLugar(_puntoInicial);
            //lugar->visitar();
            visitarTodasConexiones(_puntoInicial);
            std::cout << "Lugar: " << std::to_string(_puntoInicial)<< std::endl;
            recorrido_str += "Lugar: " + std::to_string(_puntoInicial) + "\n";
        }
        codLugar = pilaLugares->pop();
        lugar = getNodoLugar(codLugar);
        lugar->visitar();
        NodoConexion* aux = lugar->conexiones->primero;
        if (aux!= NULL) {
            do {
                if (!aux->visitado){
                    pilaLugares->push(aux->codLugar);
                    visitarTodasConexiones(aux->codLugar);
                    std::cout << "Lugar: " << std::to_string(aux->codLugar) << std::endl;
                    recorrido_str += "Lugar: " + std::to_string(aux->codLugar) + "\n";
                }
                aux = aux->siguiente;
            } while (aux != lugar->conexiones->primero);
        }
        cantLugares--;
    }
}

void ListaLugares::insertarLugar(NodoLugar* nuevo) {

    if (listaVacia()){
        //NodoLugar* nuevo = new  NodoLugar( _codigo,  _nombre);

        primero = nuevo;
        nuevo->siguiente = primero;
        nuevo->anterior = primero;
    }else{
        //NodoLugar* nuevo = new  NodoLugar( _codigo,  _nombre);
        nuevo->siguiente = primero;
        nuevo->anterior = primero->anterior;
        primero->anterior->siguiente = nuevo;
        primero->anterior = nuevo;

    }
}
/*
NodoLugar* ListaLugares::getNodoLugar(int _codigo) {
    NodoLugar* aux = primero;
    do {
        if (aux->getCodigo() == _codigo)
            return aux;
        aux = aux->siguiente;
    } while (aux!= primero);

    return NULL;
}

int ListaLugares::getMenorPeso() {  //Para obtener el peso real de cualquier nodo, poner un cero como parametro
    NodoLugar* lugar = primero;
    if (primero->conexiones->primero == NULL) return -1;
    int menorPeso = primero->conexiones->primero->peso;
    do {
        if (menorPeso < lugar->getConexiones()->getMenorPeso()) {
            menorPeso = lugar->getConexiones()->getMenorPeso();

        }
        lugar = lugar->siguiente;
    } while (lugar != primero);
    return menorPeso;
}*/



	
	


void ListaLugares::Dijkstra(int inicio, int final){
	
	NodoLugar* aux = primero;
	int distMinima=0;
	int distTotal=0;
	ListaConexiones* nodosResueltos = new ListaConexiones();
	ListaConexiones* nodosNoResueltos = new ListaConexiones();
	int ultimaConexion;
	ListaConexiones* noResueltos = new ListaConexiones();
	int codMenor = inicio;
	
	
	
	//getNodoLugar(inicio)->getConexiones()->getPeso(inicio);
	//profundida(3);
	nodosResueltos->agregarConexion(inicio, getNodoLugar(inicio)->getConexiones()->getPeso(inicio));
	//nodosResueltos->insertarLugar(getNodoLugar(inicio));
	//ListaLugares
	

	
	//std::cout<<"Nodo resuelto    "<<"Nodo no-resuelto    "<<"Distancia minima    "<<"Distancia total"<<"Ultima conexion"<<std::endl;
	while (!todosVisitados()){
		
		if (nodosNoResueltos->listaVacia()){
			noResueltos = getNodoLugar(inicio)->getConexiones();
			noResueltos->visitar(inicio);
			noResueltos->sumarDistTotal(distTotal, inicio);
			nodosNoResueltos = noResueltos;
			nodosNoResueltos->visitar(inicio);
			nodosResueltos->visitar(inicio);
			
			
		}
		else{
			noResueltos = getNodoLugar(codMenor)->getConexiones();
			//int a = noResueltos->getMayorPeso();
			noResueltos->sumarDistTotal(distMinima, codMenor);
			
			if (noResueltos->primero == NULL){
				return;
			}
			
			//noResueltos->insertarNodosNoResueltos(nodosNoResueltos);
			
			NodoConexion* aux = noResueltos->primero;
			int nodosNuevos = noResueltos->getCantidadConexiones();
			NodoConexion* aux2 = noResueltos->primero;
		
		    for (int i = 0; i<nodosNuevos;i++){
		    	
		    	nodosNoResueltos->agregarConexion(aux->codLugar, aux->peso, codMenor);   	
		    	//aux = aux->siguiente;
		    	aux = aux->siguiente;
		    	//aux = aux2;
			}
		    	
			
			/*
			//NodoLugar* nuevo = new  NodoLugar( _codigo,  _nombre);
	        noResueltos->primero->anterior->siguiente = nodosNoResueltos->primero;
	        noResueltos->primero->anterior = nodosNoResueltos->primero->anterior;
	        nodosNoResueltos->primero->anterior->siguiente = noResueltos->primero;
	        nodosNoResueltos->primero->anterior = noResueltos->primero;

			
			//noResueltos->primero->anterior=NULL;
			//noResueltos->primero->anterior->siguiente = nodosNoResueltos->primero->anterior;
			//nodosNoResueltos->primero->anterior = noResueltos->primero;
			//nodosNoResueltos->primero->anterior=noResueltos->primero;
			
			NodoConexion* temp = nodosNoResueltos->primero;
			NodoConexion* tempAnterior = nodosNoResueltos->primero->anterior;
			nodosNoResueltos->primero = noResueltos->primero;
			nodosNoResueltos->primero->anterior = noResueltos->primero->anterior;
			noResueltos->primero = temp;*/
			//noResueltos->primero- = temp;
			
			//nodosNoResueltos->primero = temp;
		}
		
		int nodosNuevos = nodosResueltos->getCantidadConexiones();
		NodoConexion* aux = nodosResueltos->primero;
		
		for (int j = 0; j<nodosNuevos;j++){
		    	
		    	nodosNoResueltos->visitar(aux->codLugar);
		    	getNodoLugar(codMenor)->visitar();
		    //	nodosNoResueltos->agregarConexion(aux->codLugar, aux->peso, codMenor);   	
		    	//aux = aux->siguiente;
		    	aux = aux->siguiente;
		    	//aux = aux2;
			}
			
		
		nodosNoResueltos->visitar(codMenor);
		codMenor = nodosNoResueltos->getCodMenorConexion();
		
		
		distMinima = nodosNoResueltos->getPeso(codMenor);
		//distTotal = getNodoLugar(codMenor)->getConexiones()->getPeso(codMenor);
		nodosResueltos->agregarConexion(codMenor, distMinima);
		
		std::cout<<"Conexiones: "<<nodosNoResueltos->getConexion(codMenor)->codigoUltimaConexion<<" - "<< codMenor<<std::endl;
		
		nodosNoResueltos->visitar(codMenor);
		getNodoLugar(codMenor)->visitar();
		
		//aux=aux->siguiente;
	}
	
	
	
}
