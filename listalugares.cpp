//
// Created by Daniel Alvarado on 5/18/17.
//
#include "listalugares.h"
#include <iomanip>
//#include "ListaConexiones.cpp"
//#include "pila.cpp"



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

    int cantVisitados = 0;
    int codLugar = 0;
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
    desvisitarTODO();
    return recorrido_str;
}

std::string ListaLugares::anchura(int _puntoInicial) {
    std::string recorrido_str = "";

    int cantVisitados = 0;
    int codLugar = 0;
    int contador = getNumVertices();
    int cantLugares = getNumVertices();
    ListaLugares* pilaLugares = new ListaLugares();
    NodoLugar* lugar;
    while (contador > 0 && !todosVisitados()) {
        if (contador == cantLugares) {
            pilaLugares->InsertarInicio(_puntoInicial);
            //lugar = getNodoLugar(_puntoInicial);
            //lugar->visitar();
            visitarTodasConexiones(_puntoInicial);
            std::cout << "Lugar: " << std::to_string(_puntoInicial)<< std::endl;
            recorrido_str += "Lugar: " + std::to_string(_puntoInicial) + "\n";
        }
        codLugar = pilaLugares->SacarFinal();
        lugar = getNodoLugar(codLugar);
        lugar->visitar();
        NodoConexion* aux = lugar->conexiones->primero;
        if (aux!= NULL) {
            do {
                if (!aux->visitado){
                    pilaLugares->InsertarInicio(aux->codLugar);
                    visitarTodasConexiones(aux->codLugar);
                    std::cout << "Lugar: " << std::to_string(aux->codLugar) << std::endl;
                    recorrido_str += "Lugar: " + std::to_string(aux->codLugar) + "\n";
                }
                aux = aux->siguiente;
            } while (aux != lugar->conexiones->primero);
        }
        cantLugares--;
    }
    desvisitarTODO();
    return recorrido_str;
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

void ListaLugares::InsertarInicio(int v)
{
  
   if (listaVacia())
   {
     primero = new NodoLugar(v, "");
     primero->anterior=primero;
     primero->siguiente=primero;
   }  
   else
   {
     NodoLugar* nuevo = new NodoLugar(v, "");
     nuevo->siguiente=primero;
     nuevo->anterior= primero->anterior;
     primero->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primero= nuevo;
   }
}

int ListaLugares::SacarFinal(){
	NodoLugar* temp = primero;
	primero = primero->siguiente;
	
	return temp->getCodigo();
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



	
	


std::string ListaLugares::Dijkstra(int inicio, int final){
	
	NodoLugar* aux = primero;
	int distMinima=0;
	int distTotal=0;
	ListaConexiones* nodosResueltos = new ListaConexiones();
	ListaConexiones* nodosNoResueltos = new ListaConexiones();
	int ultimaConexion;
	ListaConexiones* noResueltos = new ListaConexiones();
	int codMenor = inicio;
	std::string tablaDijkstra;
	std::string resueltos;
	std::string noresueltos;
	std::string distminima;
	std::string disttotal;
	std::string ultimaconexion;
	
	
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
				break;
			}
			
			//noResueltos->insertarNodosNoResueltos(nodosNoResueltos);
			
			NodoConexion* aux = noResueltos->primero;
			int nodosNuevos = noResueltos->getCantidadConexiones();
			//NodoConexion* aux2 = noResueltos->primero;
		
		    for (int i = 0; i<nodosNuevos;i++){
		    	
		    	nodosNoResueltos->agregarConexion(aux->codLugar, aux->peso, codMenor);   	
		    	//aux = aux->siguiente;
		    	aux = aux->siguiente;
		    	//aux = aux2;
			}
		   
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
		resueltos = resueltos;	
		int tempNodos = nodosResueltos->getCantidadConexiones();
		NodoConexion* aux2 = nodosResueltos->primero; 
		for (int k = 0; k<tempNodos;k++){
			
			
			if (nodosNoResueltos->getCantidadConexionesSinVisitar(aux2->codLugar) != 0){
				std::cout<<aux2->codLugar<<std::endl;
				resueltos = resueltos + std::to_string(aux2->codLugar) + ",";
				
			}
			aux2 = aux2->siguiente;
		}
		resueltos = resueltos + ";";
		
		
		noresueltos = noresueltos ;
		tempNodos = nodosNoResueltos->getCantidadConexiones();
		aux2 = nodosNoResueltos->primero; 
		for (int k = 0; k<tempNodos;k++){
			std::cout<<"No resueltos: "<<std::endl;
			if (!nodosNoResueltos->getEstado(aux2->codLugar)){
				std::cout<<aux2->codLugar<<std::endl;
				noresueltos = noresueltos + std::to_string(aux2->codLugar) + "_" + std::to_string(aux2->peso) + ",";
				
			}
			aux2 = aux2->siguiente;
		}
		noresueltos = noresueltos + ";";
		nodosNoResueltos->visitar(codMenor);
		codMenor = nodosNoResueltos->getCodMenorConexion();
		
		
		distMinima = nodosNoResueltos->getPeso(codMenor);
		distminima = distminima + std::to_string(distMinima) + ";";
		disttotal = disttotal + std::to_string(distMinima) + ";";
		
		//distTotal = getNodoLugar(codMenor)->getConexiones()->getPeso(codMenor);
		nodosResueltos->agregarConexion(codMenor, distMinima);
		
		std::cout<<"Conexiones: "<<nodosNoResueltos->getConexion(codMenor)->codigoUltimaConexion<<" - "<< codMenor<<std::endl;
		ultimaconexion = ultimaconexion + std::to_string(nodosNoResueltos->getConexion(codMenor)->codigoUltimaConexion) + "-" + std::to_string(codMenor) + ";";
		
		nodosNoResueltos->visitar(codMenor);
		getNodoLugar(codMenor)->visitar();
		
		//aux=aux->siguiente;
	}
	
	
	std::string ruta =  getRutaDijkstra(ultimaconexion, inicio, final);
	
	
	tablaDijkstra = resueltos + "$" +" " + noresueltos + "$" + " " + distminima + "$" +" " + disttotal + "$" + " " + ultimaconexion + "$" + " " + ruta;
	std::cout<<tablaDijkstra<<std::endl;
	generarTablaDijkstra(tablaDijkstra);
	return tablaDijkstra;
	//std::cout<<resueltos<<std::endl<<noresueltos<<std::endl<<distminima<<std::endl<<disttotal<<std::endl<<ultimaconexion<<std::endl;
	
	
}

std::string ListaLugares::getRutaDijkstra(std::string& ultimaconexion, int inicio, int final){
	//ultimaconexion = std::string ( ultimaconexion.rbegin(), ultimaconexion.rend() );
	//std::string _codigoLugar(std::strtok (valorEnLinea, ";") );
	
	
	/*while (true){
	    std::istringstream iss(ultimaconexion);
	    std::string token;
	    while (std::getline(iss, token, '-'))
	    {
	        std::cout << token << std::endl;
	        while (std::getline(iss, token, ';'))
	   		{
	        std::cout << token << std::endl;
	        break;
	    	}
	    }
    }*/
    
    std::string str = "";
    std::string primeraComponente = "";
    std::string segundaComponente = "";
    std::string lastcon = "";
    std::string strinicio = std::to_string(inicio);
    std::string strfinal = std::to_string(final);
    bool guardar = false;
	for(char& c : ultimaconexion) {
	    //std::cout<<c<<std::endl;
	    if (c == ';'){
	    	if (segundaComponente == strfinal){
	    		lastcon+=segundaComponente;
	    		lastcon+="-";
	    		lastcon+=primeraComponente;
	    		segundaComponente = "";
	    		segundaComponente = primeraComponente;
	    		primeraComponente = "";
	    		guardar=false;
	    		
			}
			else{
				segundaComponente = "";
	    		//segundaComponente = primeraComponente;
	    		primeraComponente = "";
	    		guardar=false;
			}
		}
	    else if (c == '-'){
	    	guardar = true;
		}
		else if (guardar){
			segundaComponente+=c;
		}
		else{
			primeraComponente+=c;
		}
		
	    
	    
	}
	lastcon+="-";
	lastcon+=strinicio;
	std::cout<<"Last connection: "<<lastcon<<std::endl;
	return lastcon;
	
}

void ListaLugares::generarTablaDijkstra(std::string tablaDijkstra){
		//std::string tablaDijkstra;
		std::string resueltos;
		std::string noresueltos;
		std::string distminima;
		std::string disttotal;
		std::string ultimaconexion;
		std::string ruta;
		
		
	    std::istringstream iss(tablaDijkstra);
	    std::string token;
	    std::getline(iss, token, ' ');
	    resueltos = token;
	    
	    std::getline(iss, token, ' ');
	    noresueltos = token;
	    
	    std::getline(iss, token, ' ');
	    distminima = token;
	    
	    std::getline(iss, token, ' ');
	    disttotal = token;
	    
	    std::getline(iss, token, ' ');
	    ultimaconexion = token;
	    
	    std::getline(iss, token, ' ');
	    ruta = token;
	    
	        
	    //std::cout<<"LALALA "<<ruta<<std::endl;
	    
	    std::ofstream myfile;
		myfile.open ("Dijkstra.txt");
		myfile << "---------------------------------------------------------------\n";
		myfile << "---------------------------------------------------------------\n";
		myfile<<"Nodo resuelto"<<std::setw(100)<<"Nodo no-resuelto"<<std::setw(100)<<"Distancia minima"<<std::setw(100)<<"Distancia total"<<std::setw(100)<<"Ultima conexion"<<std::endl;
	    
	    
	    std::istringstream iss0(resueltos);
	    std::istringstream iss1(noresueltos);
	    std::istringstream iss2(distminima);
	    std::istringstream iss3(disttotal);
	    std::istringstream iss4(ultimaconexion);
	    while (true){
	    	
		
	    std::getline(iss0, token, ';');
	    myfile << std::left<<std::setw(50) <<token << std::setw(50) << "      ";
	    std::cout << token << std::endl;
	    
	    
	    std::getline(iss1, token, ';');
	    myfile << std::setw(50) << token << std::setw(50) << "      ";
	    std::cout << token << std::endl;
		
		
	    std::getline(iss2, token, ';');
	    myfile << std::left<< std::setw(50) << token << std::setw(50) << "      ";
	    std::cout << token << std::endl;
		
		
		
	    std::getline(iss3, token, ';');
	    myfile<< std::left << std::setw(50) << token << std::setw(50) << "      ";
	    std::cout << token << std::endl;
		
		
	    std::getline(iss4, token, ';');
	    myfile << std::left<< std::setw(50) << token << "      "<<std::endl;
	    myfile <<std::endl<<std::endl;;
	    std::cout << token << std::endl;
		
		if (token == "$"){
	
			myfile << "La ruta es: " <<ruta;
		   break;
	   	}
	    }
	
}

std::string ListaLugares::puntosDeArticulacion(int _puntoInicial) {
    std::string recorrido_str = "";

    int cantVisitados,codLugar = 0;
    int contador = getNumVertices();
    int cantLugares = getNumVertices();
    Pila* pilaLugares = new Pila();
    ListaLugares* arbolM = new ListaLugares();
    ListaConexiones* arbolm_ario = new ListaConexiones();
    NodoLugar* lugar;
    while (contador > 0 && !todosVisitados()) {
        if (contador == cantLugares) {
            pilaLugares->push(_puntoInicial);
            //lugar = getNodoLugar(_puntoInicial);
            //lugar->visitar();
            visitarTodasConexiones(_puntoInicial);
            arbolM->insertarLugar(_puntoInicial, "");
            //arbolm_ario->agregarConexion(_puntoInicial, 0);
           // std::cout << "Lugar: " << std::to_string(_puntoInicial)<< std::endl;
            recorrido_str += "Lugar: " + std::to_string(_puntoInicial) + "\n";
        }
        codLugar = pilaLugares->pop();
        lugar = getNodoLugar(codLugar);
        lugar->visitar();
        
        NodoConexion* aux = lugar->conexiones->primero;
        if (aux!= NULL) {
            do {
                if (!aux->visitado){
                	NodoLugar* temp = arbolM->primero->anterior;
                	int largo = arbolM->largoLista();
                	for (int i = 0; i<largo;i++){
                		if(getNodoLugar(temp->getCodigo())->existeConexion(codLugar)){
                			int a = getNodoLugar(temp->getCodigo())->getCodigo();
                			if (!arbolM->existeLugar(codLugar))
                				{
								arbolM->insertarLugar(codLugar, "");
								arbolM->getNodoLugar(temp->getCodigo())->getConexiones()->agregarConexion(codLugar, 1);
								}
                			
                			break;
						}
                		else{
                			temp = temp->anterior;
						}
                		//NodoLugar->
					}
                	
                    pilaLugares->push(aux->codLugar);
                    visitarTodasConexiones(aux->codLugar);
                    
                    //arbolM->insertarLugar(codLugar, "");
					//arbolm_ario->agregarConexion(codLugar, 0);
					
				//	NodoLugar *lugar = _listaLugares->getNodoLugar(codigoL);
        		//	lugar->getConexiones()->agregarConexion(codConex, pesoI);
                    
                   // std::cout << "Lugar: " << std::to_string(aux->codLugar) << std::endl;
                    recorrido_str += "Lugar: " + std::to_string(aux->codLugar) + "\n";
                    
                    
                }
                aux = aux->siguiente;
            } while (aux != lugar->conexiones->primero);
        }
        
        cantLugares--;
    }
    arbolm_ario->largoLista();
   // std::cout<<"BARRA SEPARADORA"<<std::endl;
   //arbolM->desvisitarTODO();
   // arbolM->profundida(_puntoInicial);

    return recorrido_str;
}

