#include <iostream>
#include <fstream>
#include "arbolexpansion.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include <vector>
#include "arbolproveedores.h"
#include "arbolclientes.h"
#include "arbolsupermercados.h"

const int PRIMERA_VEZ = -1;
const int OPCION_VENTA = 1;
const int OPCION_PROVEEDOR_MAS_VENTAS = 2;
const int OPCION_CLIENTE_MAS_COMPRO = 3;
const int OPCION_PRODUCTO_MAS_VENDIDO = 4;
const int OPCION_PRODUCTOS_CAMBIARON_STOCK = 5;
const int OPCION_CATEGORIA_MAS_VENDIDA = 6;
const int OPCION_SUPERMERCADO_MAS_VENTAS = 7;
const int OPCION_LUGAR_CON_MAS_SUPERMERCADOS = 8;
const int OPCION_IMPRIMIR_ARBOL_PREORDEN = 9;
const int OPCION_ELIMINAR_PRODUCTO = 10;
const int OPCION_ELIMINAR_CLIENTE = 11;
const int OPCION_FACTURA = 12;
int const TAMANHO_BUFFER = 301;



void leerArchLugares(ListaLugares * _lugares){
    std::string nombreArchivo = "Lugares.txt";
    //std::string nombreArchivo = "LugaresDaniel.txt";


    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string id(std::strtok (lineaValores, ";"));
        std::string nombre(std::strtok (NULL, ";"));

        // ... crear el nodo
        //cout << id << "," << nombre << "," << direccion << "," << telefono << endl;
        int codigoL = atoi(id.c_str());


        if (_lugares->existeLugar(codigoL))
            continue;
        else{
            std::cout << "Codigo Lugares: " << id << std::endl;
            _lugares->insertarLugar(codigoL,nombre);
        }
    }
    archivoEntrada.close();
    std::cout << _lugares->largoLista() << std::endl;
}

void leerArchConexiones(ListaLugares* _listaLugares) {
    std::string nombreArchivo = "Conexiones.txt";
    //std::string nombreArchivo = "ConexionesDaniel.txt";

    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo) {
        char *lineaValores = new char[lineaEnArchivo.length() + 1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string codLugar(std::strtok(lineaValores, ";"));
        std::string codConexion(std::strtok(NULL, ";"));
        std::string peso(std::strtok(NULL, ";"));

        // ... crear el nodo
        std::cout << codLugar << "," << codConexion << "," << peso << std::endl;
        int codigoL = atoi(codLugar.c_str());
        int codConex = atoi(codConexion.c_str());
        int pesoI = atoi(peso.c_str());

        NodoLugar *lugar = _listaLugares->getNodoLugar(codigoL);
        lugar->getConexiones()->agregarConexion(codConex, pesoI);
    }


}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//// PARA PRUEBA A VER SI REGISTRA BIEN UN PRODUCTO
void leerArchProductos(ArbolSupermercados* _supermercados) {

    std::string nombreArchivo = "Productos.txt";

    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string codLugar(std::strtok (lineaValores, ";"));
        std::string codSuper(std::strtok (NULL, ";"));
        std::string codigoCategoria(std::strtok (NULL, ";"));
        std::string codigoProducto(std::strtok (NULL, ";"));
        std::string nombreProducto(std::strtok (NULL, ";"));

        std::string precioPorUnidadSt(std::strtok (NULL, ";"));
        std::string cantidadEnStockSt(std::strtok (NULL, ";"));

        int codLugI = atoi(codLugar.c_str());
        int codProI = atoi(codigoProducto.c_str());
        int codCatI = atoi(codigoCategoria.c_str());
        int codSupI = atoi(codSuper.c_str());

        double precioPorUnidad = atof(precioPorUnidadSt.c_str());
        int cantidadEnStock = atoi(cantidadEnStockSt.c_str());


        ArbolCategorias* arbolCategorias = new ArbolCategorias();
        _supermercados->getArbolCat(codSupI,_supermercados->raiz,arbolCategorias);

        ArbolProductos* productos = new ArbolProductos();
        arbolCategorias->getArbolProd(arbolCategorias->raiz,codCatI,productos);

        // ... crear el nodo
        if (productos != NULL && productos->existeProducto(productos->raiz,codProI)){
            continue;
        }else{

            std::cout <<codigoProducto << "," << codigoCategoria << "," << nombreProducto<< "," << precioPorUnidadSt<< ","
                      << cantidadEnStockSt << std::endl;
            //_categoria->insertarProducto(codigoProducto, codigoCategoria, nombreProducto, precioPorUnidad, cantidadEnStock);
            _supermercados->agregarProducto(_supermercados->raiz,codSupI,codCatI,codProI,nombreProducto, precioPorUnidad,
                                            cantidadEnStock);

        }
    }
    archivoEntrada.close();


}


void leerArchCategorias(ArbolSupermercados* _supermercados) {
    std::string nombreArchivo = "Categorias.txt";
    std::ifstream file;
    std::string lineaEnArchivo;
    int codigo;
    int codigoSup,codigoLugar;
    int cont = 0;
    file.open(nombreArchivo,std::ios::in);
    if (file.fail()) {
        std::cout << "Unable to open file";
    }else{
        while(file>>lineaEnArchivo){
            char *valorEnLinea = new char[lineaEnArchivo.length()+1];
            strcpy(valorEnLinea, lineaEnArchivo.c_str());


            std::string _codigoLugar(std::strtok (valorEnLinea, ";") );
            codigoLugar = atoi(_codigoLugar.c_str());
            std::string _codigoSup(std::strtok (NULL, ";") );
            codigoSup = atoi(_codigoSup.c_str());
            std::string _codigo(std::strtok (NULL, ";") );
            codigo = atoi(_codigo.c_str());
            std::string descripcion(std::strtok (NULL, ";") );
            //nodocategoria *nuevo = new nodocategoria(codigo, descripcion);

            if(cont==0){
                //arbolCategorias->insertarValorNodoRN(codigo, descripcion);
                _supermercados->agregarCategoria(_supermercados->raiz,codigoSup,codigo,descripcion);
                cont++;
                std::cout << "primera vez" << std::endl;

            }else{
                if(!_supermercados->existeCategoria(codigoSup,codigo,_supermercados->raiz)) {
                    _supermercados->agregarCategoria(_supermercados->raiz,codigoSup,codigo,descripcion);
                    std::cout <<"Codigo Categoria: "<< _codigo << "," << descripcion << std::endl;
                    cont++;
                }
            }
        }
        //leerArchProductos("Productos.txt");
    }
    file.close();

}


void leerArchSupermercado(ArbolSupermercados * _supermercado, ListaLugares* _lugares){
    bool Hh = false;
    std::string nombreArchivo = "Supermercados.txt";

    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string codLugar1(std::strtok (lineaValores, ";"));
        std::string codSuper(std::strtok (NULL, ";"));
        std::string codLugar(std::strtok (NULL, ";"));
        std::string nombre(std::strtok (NULL, ";"));

        // ... crear el nodo
        //cout << id << "," << nombre << "," << direccion << "," << telefono << endl;

        int codL1int = atoi(codLugar1.c_str());
        int codSint = atoi(codSuper.c_str());
        int codLint = atoi(codLugar.c_str());
        if (_supermercado->existeSupermercado(codSint,_supermercado->raiz)) {
            std::cout << "Supermercado ya existe, codigo: " << codSuper << std::endl;
            continue;
        }else{
            std::cout << "Codigo Supermercado: " << codSuper << " Nombre: "<< nombre << std::endl;
            //std::cout << "Codigo LUGAR: " << codLugar << std::endl;
            //_supermercado->insertarNodoSupermercado(codSint,codLint,nombre);

            _supermercado->insertarBalanceado(_supermercado->raiz, Hh,codSint,codLint,nombre);
            _lugares->aumentarCantidadDeSupermercados(codLint);
        }
    }
    archivoEntrada.close();


}



void leerArchProveedores(ArbolProveedores * _proveedores){
    std::string nombreArchivo = "Proveedores.txt";

    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string id(std::strtok (lineaValores, ";"));
        std::string nombre(std::strtok (NULL, ";"));
        std::string direccion(std::strtok (NULL, ";"));
        std::string telefono(std::strtok (NULL, ";"));

        // ... crear el nodo
        //cout << id << "," << nombre << "," << direccion << "," << telefono << endl;

        int idProveedor = atoi(id.c_str());
        int intTel = atoi(telefono.c_str());
        //cout << "COMENZANDO A EVALUAR" << endl;
        //_proveedores->InordenI(_proveedores->raiz);
        if (_proveedores->existeProveedor(idProveedor,_proveedores->raiz)) {
            std::cout << "Proveedor ya existe, codigo: " << id << std::endl;
            continue;
        }else{
            std::cout << "Codigo Proveedor: " << id << " Nombre: "<< nombre << std::endl;
            //NodoProveedor* nodoProveedor = new NodoProveedor(idProveedor,nombre,direccion,intTel);
            _proveedores->insertarNodoProveedor(idProveedor,nombre,direccion,intTel);
        }
    }
    archivoEntrada.close();

}


void leerArchClientes(ArbolClientes * _ArbolClientes){
    std::string nombreArchivo = "Clientes.txt";
    std::cout << "entro" << std::endl;

    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo) {
        char *lineaValores = new char[lineaEnArchivo.length() + 1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string id(std::strtok(lineaValores, ";"));
        std::string nombre(std::strtok(NULL, ";"));
        std::string direccion(std::strtok(NULL, ";"));
        std::string telefono(std::strtok(NULL, ";"));

        int idCliente = atoi(id.c_str());

        // ... crear el nodo

        std::cout << "Codigo Cliente: " << id << "," << nombre << "," << direccion << "," << telefono << std::endl;
        int intTelefono = atoi(telefono.c_str());

        _ArbolClientes->IniciarInsercionB(idCliente, idCliente, nombre, direccion, intTelefono);


    }
    archivoEntrada.close();
}




//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////



static ListaLugares* listaLugares = new ListaLugares();
static ArbolExpansionMinimo* arbol = new ArbolExpansionMinimo();

void *task1(void *);
static int newsockfd1;
static int newsockfd2;
static int newsockfd3;
static int newsockProvider;
static int newsockfd;
static int newsockfdc2;
int codigoProveedor;



static char bufferProveedor[TAMANHO_BUFFER];
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void* clientManagement (void *dummyPt) {

    //PRUEBAS

    int nodoInicial = 20;
    //

    std::cout << "Thread No: " << pthread_self() << std::endl;
    char buffer[TAMANHO_BUFFER];
    bzero(buffer, TAMANHO_BUFFER);
    char msg[] = "CONECTADO AL SERVIDOR";
    write(newsockfd,msg,strlen(msg));
    bool loop = false;
    while(!loop) {
        bzero(buffer, TAMANHO_BUFFER);
        read(newsockfd, buffer, TAMANHO_BUFFER-1);

        std::string parteString,parteStr;


        //PRUEBAS
        std::string tester (buffer);

        parteString = tester.substr(0,1);
        if (tester == "PROFUNDIDAD") {
            std::string recorridoArbol = "Recorrido en Profundidad:\n";
            recorridoArbol += listaLugares->profundida(nodoInicial);
            std::cout << recorridoArbol << std::endl;

            std::string msg2Provider = "Puede el cliente consultar la profundidad?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));

            std::string msgMal = "NO fue permitido";

            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            std::string bufProvee (bufferProveedor);

            if (bufProvee == "SI\n")
                write(newsockfd,recorridoArbol.c_str() , strlen(recorridoArbol.c_str()));
            else
                write(newsockfd,msgMal.c_str(),strlen(msgMal.c_str()));




            //char msgCodClientPreorden[] = "REVISAR SERVIDOR";
            //write(newsockfd, msgCodClientPreorden, strlen(msgCodClientPreorden));


        } else if ( parteString == "v") {

            std::cout << "SE ESTA REALIZANDO UNA VENTA" << std::endl;
            char serverMsg[] = "V_REALIZADA";
            write(newsockfd,serverMsg,strlen(serverMsg));

        }else {

            std::string tester (buffer);
            std::cout << tester << std::endl;
            char serverMsg[] = "BIENVENIDO AL SERVIDOR \0";
            write(newsockfd,serverMsg,strlen(serverMsg));
            if(tester == "exit")
                break;
        }



        //write()



        //  if(tester == "exit")
        //    break;
    }

    std::cout << "\nClosing thread and conn" << std::endl;
    close(newsockfd);
}

void* clientManagement2 (void *dummyPt) {

    int nodoInicial = 20;
    std::cout << "Thread No: " << pthread_self() << std::endl;
    char buffer[TAMANHO_BUFFER];
    bzero(buffer, TAMANHO_BUFFER);
    char msg[] = "CONECTADO AL SERVIDOR";
    write(newsockfdc2,msg,strlen(msg));
    bool loop = false;
    while(!loop) {
        bzero(buffer, TAMANHO_BUFFER);
        read(newsockfdc2, buffer, TAMANHO_BUFFER-1);
        std::string parteString,parteStr;
        std::string tester (buffer);

        parteString = tester.substr(0,1);
        if (tester == "PROFUNDIDAD") {
            std::string recorridoArbol = "Recorrido en Profundidad:\n";
            recorridoArbol += listaLugares->profundida(nodoInicial);
            std::cout << recorridoArbol << std::endl;

            std::string msg2Provider = "Puede el cliente consultar la profundidad?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));

            std::string msgMal = "NO fue permitido";

            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            std::string bufProvee (bufferProveedor);

            if (bufProvee == "SI\n")
                write(newsockfdc2,recorridoArbol.c_str() , strlen(recorridoArbol.c_str()));
            else
                write(newsockfdc2,msgMal.c_str(),strlen(msgMal.c_str()));


        } else if ( parteString == "v") {

            std::cout << "SE ESTA REALIZANDO UNA VENTA" << std::endl;
            char serverMsg[] = "V_REALIZADA";
            write(newsockfdc2,serverMsg,strlen(serverMsg));

        }else {

            std::string tester (buffer);
            std::cout << tester << std::endl;
            char serverMsg[] = "BIENVENIDO AL SERVIDOR \0";
            write(newsockfdc2,serverMsg,strlen(serverMsg));
            if(tester == "exit")
                break;
        }
    }
    std::cout << "\nClosing thread and conn" << std::endl;
    close(newsockfdc2);
}

void *provider (void *dummyPt) {

    std::cout << "Thread No: " << pthread_self() << std::endl;
/*    while(true) {
        bzero(bufferProveedor,TAMANHO_BUFFER);
        char msg[] = "PORFAVOR DIGITE SU CODIGO: ";
        write(newsockProvider,msg,strlen(msg));

        read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

        std::string respuestaProveedor (bufferProveedor);

        //if (arbolProveedores->exiteProveedor(respuestaProveedor)) {
        //
        //break
        // }
        break;
    }
*/

    bzero(bufferProveedor, TAMANHO_BUFFER);
    char msg[] = "CONECTADO AL SERVIDOR\nBIENVENIDO PROVEEDOR";
    write(newsockProvider, msg, strlen(msg));
    bool loop = false;
    /*
    while (!loop) {
        bzero(buffer, TAMANHO_BUFFER);
        read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string tester(buffer);
            std::cout << tester << std::endl;
            char serverMsg[] = "BIENVENIDO AL SERVIDOR";
            write(newsockfd, serverMsg, strlen(serverMsg));
            if (tester == "exit")
                break;
        }



        //write()



        //  if(tester == "exit")
        //    break;
    }

    std::cout << "\nClosing thread and conn" << std::endl;
    close(newsockProvider);
     */
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////



int main() {

    leerArchLugares(listaLugares);
    leerArchConexiones(listaLugares);
    //ArbolExpansionMinimo* arbolExpansionMinimo = new ArbolExpansionMinimo(_listaLugares);
    //int min = arbolExpansionMinimo->arbolExpancionPrim(_listaLugares);
    //listaLugares->profundida(20);
    //arbol->prim(_listaLugares,78);
    arbol->prim(listaLugares,20);

    char buffer[TAMANHO_BUFFER];
    int pId, portNo, listenFd;
    socklen_t len; //store size of the address
    bool loop = false;
    struct sockaddr_in svrAdd, clntAdd;

    pthread_t threadA[3];

    portNo = 8889;

    //create socket
    listenFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(listenFd < 0) {
        std::cerr << "Cannot open socket" << std::endl;
        return 0;
    }

    bzero((char*) &svrAdd, sizeof(svrAdd));

    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(portNo);

    //bind socket
    if(bind(listenFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0) {
        std::cerr << "Cannot bind" << std::endl;
        return 0;
    }

    listen(listenFd, 5);



    int noThread = 0;

    while (noThread < 3) {



        len = sizeof(clntAdd);
        std::cout << "Listening" << std::endl;

        //this is where client connects. svr will hang in this mode until client conn
        if (noThread == 0)
            newsockfd1 = accept(listenFd, (struct sockaddr *)&clntAdd, &len);
        else if(noThread == 1)
            newsockfd2 = accept(listenFd, (struct sockaddr *)&clntAdd, &len);
        else if (noThread == 2)
            newsockfd3 = accept(listenFd, (struct sockaddr *)&clntAdd, &len);



        if (newsockfd < 0) {
            std::cerr << "Cannot accept connection" << std::endl;
            return 0;
        }else {
            std::cout << "Connection successful" << std::endl;
        }

        int neverUsedVariable;
        bzero(buffer,TAMANHO_BUFFER);
        if (noThread == 0)
            read(newsockfd1, buffer, TAMANHO_BUFFER-1);
        else if(noThread == 1)
            read(newsockfd2, buffer, TAMANHO_BUFFER-1);
        else if (noThread == 2)
            read(newsockfd3, buffer, TAMANHO_BUFFER-1);

        //read(newsockfd, buffer, TAMANHO_BUFFER-1);

        std::string tester (buffer);
        if (tester == "PROVEEDOR") {
            std::cout << "ENTRO EL PROVEEDOR" << std::endl;
            //llama a la funcion de proveedor
            //funcion diferente a las de task1
            if (noThread == 0)
                newsockProvider = newsockfd1;
            else if(noThread == 1)
                newsockProvider = newsockfd2;
            else if (noThread == 2)
                newsockProvider = newsockfd3;

            pthread_create(&threadA[noThread], NULL, provider, NULL);

        } else if (tester == "CLIENTE_1") {
            std::cout << "ENTRO EL CLLIENTE 1 ACA" << std::endl;
            //hace la funcion del cliente1, asi sabe como comunicarse co este cliente en especifico
            if (noThread == 0)
                newsockfd = newsockfd1;
            else if(noThread == 1)
                newsockfd = newsockfd2;
            else if (noThread == 2)
                newsockfd = newsockfd3;

            pthread_create(&threadA[noThread], NULL, clientManagement, NULL);

        }else if (tester == "CLIENTE_2") {
            std::cout << "ENTRO EL CLLIENTE 2 ACA" << std::endl;
            //hace la funcion del cliente1, asi sabe como comunicarse co este cliente en especifico
            if (noThread == 0)
                newsockfdc2 = newsockfd1;
            else if(noThread == 1)
                newsockfdc2 = newsockfd2;
            else if (noThread == 2)
                newsockfdc2 = newsockfd3;

            pthread_create(&threadA[noThread], NULL, clientManagement2, NULL);

        }

        //pthread_create(&threadA[noThread], NULL, clientManagement, NULL);

        noThread++;
    }

    for(int i = 0; i < 3; i++) {
        pthread_join(threadA[i], NULL);
    }





    return 0;
}
