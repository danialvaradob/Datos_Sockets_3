#include <iostream>
#include "arbolexpansion.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include <vector>
#include <cstring>

#include "arbolproveedores.h"
#include "arbolclientes.h"
#include "listaventas.h"

/*
#include "arbolproveedores.cpp"
#include "arbolclientes.cpp"
#include "arbolsupermercados.cpp"
#include "arbolcategorias.cpp"
#include "listalugares.cpp"
#include "listaconexiones.cpp"
#include "listaconjunto.cpp"
#include "pila.cpp"
*/


int const TAMANHO_BUFFER = 2048;



void leerArchLugares(ListaLugares * _lugares){
    //std::string nombreArchivo = "Lugares.txt";
    std::string nombreArchivo = "Lugares.txt";


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
    //std::string nombreArchivo = "Conexiones.txt";
    std::string nombreArchivo = "Conexiones.txt";

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
void leerArchProductos(ListaLugares *_lugares) {

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

        NodoLugar *temp = _lugares->getNodoLugar(codLugI);
        ArbolSupermercados *aux = temp->getArbolSuper();


        ArbolCategorias* arbolCategorias = new ArbolCategorias();
        aux->getArbolCat(codSupI,aux->raiz,arbolCategorias);

        ArbolProductos* productos = new ArbolProductos();
        arbolCategorias->getArbolProd(arbolCategorias->raiz,codCatI,productos);



        // ... crear el nodo
        if (productos != NULL && productos->existeProducto(productos->raiz,codProI)){
            continue;
        }else{

            std::cout <<codigoProducto << "," << codigoCategoria << "," << nombreProducto<< "," << precioPorUnidadSt<< ","
                      << cantidadEnStockSt << std::endl;
            //_categoria->insertarProducto(codigoProducto, codigoCategoria, nombreProducto, precioPorUnidad, cantidadEnStock);
            aux->agregarProducto(aux->raiz,codSupI,codCatI,codProI,nombreProducto, precioPorUnidad,
                                            cantidadEnStock);

        }
    }
    archivoEntrada.close();


}

void leerArchCategorias(ListaLugares* _lugares) {
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
            NodoLugar *temp = _lugares->getNodoLugar(codigoLugar);
            ArbolSupermercados *aux = temp->getArbolSuper();

            if(cont==0){
                //arbolCategorias->insertarValorNodoRN(codigo, descripcion);
                aux->agregarCategoria(aux->raiz,codigoSup,codigo,descripcion);
                cont++;
                std::cout << "primera vez" << std::endl;

            }else{
                if(!aux->existeCategoria(codigoSup,codigo,aux->raiz)) {
                    aux->agregarCategoria(aux->raiz,codigoSup,codigo,descripcion);
                    std::cout <<"Codigo Categoria: "<< _codigo << "," << descripcion << std::endl;
                    cont++;
                }
            }
        }
        //leerArchProductos("Productos.txt");
    }
    file.close();

}

void leerArchSupermercado(ListaLugares* _lugares){
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

        int codLint = atoi(codLugar1.c_str());
        int codSint = atoi(codSuper.c_str());
        NodoLugar *temp = _lugares->getNodoLugar(codLint);
        ArbolSupermercados *aux = temp->getArbolSuper();
        if (aux->existeSupermercado(codSint,aux->raiz)) {
            std::cout << "Supermercado ya existe, codigo: " << codSuper << std::endl;
            continue;
        }else{
            std::cout << "Codigo Supermercado: " << codSuper << " Nombre: "<< nombre << std::endl;
            //std::cout << "Codigo LUGAR: " << codLugar << std::endl;
            //_supermercado->insertarNodoSupermercado(codSint,codLint,nombre);

            aux->insertarBalanceado(aux->raiz, Hh,codSint,codLint,nombre);
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



ListaLugares* listaLugares = new ListaLugares();
ArbolExpansionMinimo* arbol = new ArbolExpansionMinimo();
ArbolClientes* clientes = new ArbolClientes();
ArbolProveedores* proveedores = new ArbolProveedores();
ArbolSupermercados* supermercados = new ArbolSupermercados();
ArbolCategorias* categorias = new ArbolCategorias();
ArbolProductos* productos = new ArbolProductos();
ListaVentas* listaVentas = new ListaVentas();
ArbolExpansionMinimo* arbolKruskal = new ArbolExpansionMinimo();

void *task1(void *);
static int newsockfd1;
static int newsockfd2;
static int newsockfd3;
static int newsockProvider;
static int newsockfd;
static int newsockfdc2;

int codigoProveedorGlobal;
int codigoClienteGlobal;
bool banderaCLIENTENUEVO;



static char bufferProveedor[TAMANHO_BUFFER];
static char bufferC2[TAMANHO_BUFFER];

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

    int nodoInicial;
    //

    std::cout << "Thread No: " << pthread_self() << std::endl;
    char buffer[TAMANHO_BUFFER];
    bzero(buffer, TAMANHO_BUFFER);
    char msg[] = "CONECTADO AL SERVIDOR";
    write(newsockfd,msg,strlen(msg));
    bool loop = false;


    char clienteError[] = "NO_EXISTE";
    char clienteExistemsg[] = "CLIENTE_EXISTE";

/////////////////////////////////////////
    while(!loop) {
        bzero(buffer, TAMANHO_BUFFER);
        read(newsockfd, buffer, TAMANHO_BUFFER - 1);
        std::string parteString, parteStr;
        std::string tester(buffer);
        parteString = tester.substr(0,1);


        if(tester == "CLIENTE"){

            char msg[] = "Esperando Respuesta";
            write(newsockfd,msg,strlen(msg));

            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);
            std::string codigoCliente (buffer);

            std::string msg2Provider = "Codigo Cliente Recibido," + codigoCliente;
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));

            bzero(bufferProveedor, TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER-1);
            std::string bufProvv (bufferProveedor);


            bool existeCliente = false;
            std::string codCliente (buffer);
            clientes->existeCliente(clientes->raizB,atoi(buffer),existeCliente);
            if (existeCliente) {
                std::cout << "El cliente ingresado es el correcto" << std::endl;
                //le dice la cliente que si existe, no pide datos
                write(newsockfd,clienteExistemsg,strlen(clienteExistemsg));
            } else {
                banderaCLIENTENUEVO = true;
                //le dice al cliente que no existe,
                write(newsockfd,clienteError,strlen(clienteError));
                bzero(buffer, TAMANHO_BUFFER);
                read(newsockfd, buffer, TAMANHO_BUFFER - 1);

                char * lineaValores = buffer;

                std::string codClienteNuevo(std::strtok (lineaValores, ";"));
                std::string nombre(std::strtok (NULL, ";"));
                std::string direccion(std::strtok (NULL, ";"));
                std::string telefono(std::strtok (NULL, ";"));

                int codClienteI = atoi(codClienteNuevo.c_str());
                int telI = atoi(telefono.c_str());

                clientes->IniciarInsercionB(codClienteI,codClienteI,nombre,direccion,telI);

                char clienteCre[] = "CLIENTE_CREADO";

                write(newsockfd,clienteCre,strlen(clienteCre));


            }
            codigoClienteGlobal = atoi(codigoCliente.c_str());

        }else if ( (memcmp( buffer, "PROFUNDIDAD", strlen( "PROFUNDIDAD"))) == 0) {

            char * lineaValores = buffer;
            std::string nombre(std::strtok (lineaValores, ";"));
            std::string nodoInicialStr(std::strtok (NULL, ";"));


            std::string recorridoArbol = "Recorrido en Profundidad:\n";
            recorridoArbol += listaLugares->profundida(atoi(nodoInicialStr.c_str()));
            std::cout << recorridoArbol << std::endl;
            std::string msg2Provider = "Puede el cliente consultar la profundidad?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);


            write(newsockfd,recorridoArbol.c_str() , strlen(recorridoArbol.c_str()));

        } else if ( parteString == "v") {

            std::cout << "SE ESTA REALIZANDO UNA VENTA" << std::endl;

            std::string msg2Provider = "Solicitud de Venta Recibida";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor, TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER-1);
            char * lineaValores = buffer;
            std::string venta(std::strtok (lineaValores, ";"));
            std::string codLugar(std::strtok (NULL, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            std::string codCat(std::strtok (NULL, ";"));
            std::string codProducto(std::strtok (NULL, ";"));
            std::string strCant(std::strtok (NULL, ";"));
            std::string codigoProv(std::strtok (NULL, ";"));



            bool codigosCorrectos = false;
            bool ventaRealizada = false;
            int cL,cS,cC,cP, cantidad, codProveedor;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            cC = atoi(codCat.c_str());
            cP = atoi(codProducto.c_str());
            cantidad = atoi(strCant.c_str());
            codProveedor = atoi(codigoProv.c_str());


            NodoLugar* nodo = new NodoLugar();
            NodoProveedor* _nodoProv = new NodoProveedor();
            NodoCliente* _nodoCliente = new NodoCliente();
            if (listaLugares->existeLugar(cL)) {
                nodo = listaLugares->getNodoLugar(cL);
                ArbolSupermercados* super = new ArbolSupermercados();
                super = nodo->getArbolSuper();

                if (super->existeSupermercado(cS,super->raiz)) {
                    NodoSupermercado* nodoSuper = new NodoSupermercado();
                    ArbolCategorias* cat = new ArbolCategorias();
                    super->getArbolCat(cS,super->raiz,cat);

                    if (cat->existeCategoria(cC,cat->raiz)) {
                        ArbolProductos* pro = new ArbolProductos();
                        cat->getArbolProd(cat->raiz,cC,pro);

                        if (pro->existeProducto(pro->raiz,cP)) {
                            NodoProducto* nodoPro = new NodoProducto();
                            pro->getNodoProducto(cP,pro->raiz,nodoPro);
                            codigosCorrectos = true;

                            proveedores->getNodoProveedor(codProveedor,proveedores->raiz,_nodoProv);
                            clientes->getCliente(clientes->raizB, _nodoCliente, codigoClienteGlobal);
                            _nodoCliente->aumentarVentas();
                            _nodoProv->aumentarVentas();
                            nodoPro->setCantidadEnStock(cantidad);
                            nodocategoria *nodoCat = new nodocategoria();
                            cat->getNodoCat(cat->raiz,cC, nodoCat);
                            nodoCat->incBestScore();
                            super->getNodoSupermercado(cS, super->raiz, nodoSuper);
                            nodoSuper->aumentarVentas();

                            ventaRealizada = true;
                            if (banderaCLIENTENUEVO) {



                                NodoVenta *_nodoVenta = new NodoVenta(_nodoProv->getID(), _nodoProv->getNombre(),
                                                                      _nodoCliente->getID(),
                                                                      _nodoCliente->getNombre(), nodoCat->getCodigo(),
                                                                      nodoCat->getDesc(),
                                                                      nodoPro->getCodigoProducto(),
                                                                      nodoPro->getNombreProducto(),
                                                                      nodoPro->getPrecioPorUnidad(), cantidad,
                                                                      nodoPro->getPrecioPorUnidad() * cantidad);
                                listaVentas->insertar(_nodoVenta);


                            }else {
                                    int x = 0;

                                NodoVenta *_nodoVenta = new NodoVenta(_nodoProv->getID(), _nodoProv->getNombre(),
                                                                      _nodoCliente->getID(),
                                                                      _nodoCliente->getNombre(), nodoCat->getCodigo(),
                                                                      nodoCat->getDesc(),
                                                                      nodoPro->getCodigoProducto(),
                                                                      nodoPro->getNombreProducto(),
                                                                      nodoPro->getPrecioPorUnidad(), cantidad,
                                                                      ((nodoPro->getPrecioPorUnidad() * cantidad)) - (nodoPro->getPrecioPorUnidad() * cantidad * 0.05));
                                listaVentas->insertar(_nodoVenta);

                                 }

                        }else {
                            codigosCorrectos = false;

                        }


                    } else {
                        codigosCorrectos = false;
                    }

                } else {
                    codigosCorrectos = false;
                }

            } else {
                codigosCorrectos = false;
            }


            if (codigosCorrectos) {

                //ACA VA ABOSLUTAMENTE TODO LO QUE HACES DE LA VENTA
                //YA ACA SE VERIFICARON LOS CODIGOS
                char serverMsg[] = "V_REALIZADA";
                if (ventaRealizada)
                    write(newsockfd,serverMsg,strlen(serverMsg));


            } else {
                char serverMsgNO[] = "V_NO_REALIZADA";
                write(newsockfd,serverMsgNO,strlen(serverMsgNO));
            }

            //if alguna no existe no lo deja

            //DECLARACION DE VARIABLES



            //arbolSupermercados->getNodoSupermercado(codSuper, arbolSupermercados->raiz, _nodoSup);


        }else if (tester == "PMV") {//Proveedor con mas ventas
            std::string recorridoArbol = "El proveedor con mas ventas es:\n";
            NodoProveedor* nodo = new NodoProveedor();
            proveedores->getNodoProveedorMasVentas(proveedores->raiz,nodo);

            recorridoArbol += nodo->getNombre();
            std::string msg2Provider = "Puede el cliente consultar el proveedor con mas ventas?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);
            write(newsockfd,recorridoArbol.c_str() , strlen(recorridoArbol.c_str()));


        }else if (tester == "CMC") {//CLIENTE QUE MAS COMPRO
            std::string clienteMasCompras = "El Cliente con mas Compras es:\n";

            NodoCliente* nodo = new NodoCliente();
            clientes->getClienteMasCompras(clientes->raizB,nodo);


            clienteMasCompras += nodo->getNombre();
            std::string msg2Provider = "Puede el cliente consultar el cliente con mas compras?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);
            write(newsockfd,clienteMasCompras.c_str() , strlen(clienteMasCompras.c_str()));


        }else if (tester == "PQMV") {//Producto mas vendido
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente consultar el prducto mas comprado?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            cC = atoi(codCat.c_str());

            bool codigosCorrectos = false;

            NodoLugar* nodo = new NodoLugar();
            if (listaLugares->existeLugar(cL)) {
                nodo = listaLugares->getNodoLugar(cL);
                ArbolSupermercados* super = new ArbolSupermercados();
                super = nodo->getArbolSuper();

                if (super->existeSupermercado(cS,super->raiz)) {
                    NodoSupermercado* nodoSuper = new NodoSupermercado();
                    ArbolCategorias* cat = new ArbolCategorias();
                    super->getArbolCat(cS,super->raiz,cat);

                    if (cat->existeCategoria(cC,cat->raiz)) {
                        ArbolProductos* pro = new ArbolProductos();
                        cat->getArbolProd(cat->raiz,cC,pro);

                        NodoProducto* nodoPro = new NodoProducto();
                        pro->getProductoMasVendido(pro->raiz,nodoPro);

                        mensaje = nodoPro->getNombreProducto();
                    }
                } else {
                    codigosCorrectos = false;
                }

            } else {
                codigosCorrectos = false;
            }

            if (!codigosCorrectos)
                mensaje = "Algun codigo erroneo";

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));


        }else if (tester == "PQRSS") {//productos que rebajaron su stock
            int x = 0;
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente consultar los productos que cambiaron su stock?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            cC = atoi(codCat.c_str());

            bool codigosCorrectos = false;

            NodoLugar* nodo = new NodoLugar();
            if (listaLugares->existeLugar(cL)) {
                nodo = listaLugares->getNodoLugar(cL);
                ArbolSupermercados* super = new ArbolSupermercados();
                super = nodo->getArbolSuper();

                if (super->existeSupermercado(cS,super->raiz)) {
                    NodoSupermercado* nodoSuper = new NodoSupermercado();
                    ArbolCategorias* cat = new ArbolCategorias();
                    super->getArbolCat(cS,super->raiz,cat);

                    if (cat->existeCategoria(cC,cat->raiz)) {
                        ArbolProductos* pro = new ArbolProductos();
                        cat->getArbolProd(cat->raiz,cC,pro);

                        std::string nodoPro;
                        pro->getProductosCambiaronStock(pro->raiz,nodoPro);

                        mensaje = nodoPro;
                    }
                } else {
                    codigosCorrectos = false;
                }

            } else {
                codigosCorrectos = false;
            }

            if (!codigosCorrectos)
                mensaje = "Algun codigo erroneo";

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));
            
            
        }else if (tester == "CMV") {//categoria mas vendida
            int x = 0;
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente consultar la categoria mas vendida?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            //std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            //cC = atoi(codCat.c_str());

            bool codigosCorrectos = false;

            NodoLugar* nodo = new NodoLugar();
            if (listaLugares->existeLugar(cL)) {
                nodo = listaLugares->getNodoLugar(cL);
                ArbolSupermercados* super = new ArbolSupermercados();
                super = nodo->getArbolSuper();

                if (super->existeSupermercado(cS,super->raiz)) {
                    NodoSupermercado* nodoSuper = new NodoSupermercado();
                    ArbolCategorias* cat = new ArbolCategorias();
                    super->getArbolCat(cS,super->raiz,cat);


                    nodocategoria* nodoCat = new nodocategoria();


                    cat->getCategoriaMasVendida(cat->raiz, nodoCat);
                    
                    mensaje = nodoCat->getDesc();
                } else {
                    codigosCorrectos = false;
                }

            } else {
                codigosCorrectos = false;
            }

            if (!codigosCorrectos)
                mensaje = "Algun codigo erroneo";

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));
            
        }else if (tester == "SMV") {//supermercado con mas ventas
            int x = 0;
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente consultar el supermercado que mas vendio?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            //std::string codSuper(std::strtok (NULL, ";"));
            //std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            //cS = atoi(codSuper.c_str());
            //cC = atoi(codCat.c_str());

            bool codigosCorrectos = false;

            NodoLugar* nodo = new NodoLugar();
            if (listaLugares->existeLugar(cL)) {
                nodo = listaLugares->getNodoLugar(cL);
                ArbolSupermercados* super = new ArbolSupermercados();
                super = nodo->getArbolSuper();
                
                NodoSupermercado* nodoSup = new NodoSupermercado();
                super->getSuperMasVendido(super->raiz, nodoSup);
                
                mensaje = nodoSup->getNombre();

            } else {
                codigosCorrectos = false;
            }

            if (!codigosCorrectos)
                mensaje = "Algun codigo erroneo";

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));
            
        }else if (tester == "LQMV") {

            std::string msg2Provider = "Puede el cliente consultar el lugar con mas supermercados?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            //std::string codLugar(std::strtok (lineaValores, ";"));
            //std::string codSuper(std::strtok (NULL, ";"));
            //std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            bool codigosCorrectos = false;

            NodoLugar* nodo = new NodoLugar();
            listaLugares->getLugarMasSuper(nodo);
            mensaje = nodo->getNombre();

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));
        }else if (tester == "IMPRESION") {
            int x = 0;
        }else if (( memcmp( buffer, "ELIMINAR_ARTICULO", strlen( "ELIMINAR_ARTICULO"))) == 0) {

            std::cout << "SE ESTA REALIZANDO UNA VENTA" << std::endl;

            std::string msg2Provider = "Solicitud de Eliminar Producto";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor, TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER-1);
            char * lineaValores = buffer;
            std::string eliminar(std::strtok (lineaValores, ";"));
            std::string codLugar(std::strtok (NULL, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            std::string codCat(std::strtok (NULL, ";"));
            std::string codProducto(std::strtok (NULL, ";"));




            bool codigosCorrectos = false;
            bool eliminRealizada = false;
            int cL,cS,cC,cP, cantidad, codProveedor;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            cC = atoi(codCat.c_str());
            cP = atoi(codProducto.c_str());


            NodoLugar* nodo = new NodoLugar();
            NodoProveedor* _nodoProv = new NodoProveedor();
            NodoCliente* _nodoCliente = new NodoCliente();
            if (listaLugares->existeLugar(cL)) {
                nodo = listaLugares->getNodoLugar(cL);
                ArbolSupermercados* super = new ArbolSupermercados();
                super = nodo->getArbolSuper();

                if (super->existeSupermercado(cS,super->raiz)) {
                    NodoSupermercado* nodoSuper = new NodoSupermercado();
                    ArbolCategorias* cat = new ArbolCategorias();
                    super->getArbolCat(cS,super->raiz,cat);

                    if (cat->existeCategoria(cC,cat->raiz)) {
                        ArbolProductos* pro = new ArbolProductos();
                        cat->getArbolProd(cat->raiz,cC,pro);

                        if (pro->existeProducto(pro->raiz,cP)) {

                            pro->eliminar(pro->raiz,cP);


                        }else {
                            codigosCorrectos = false;

                        }


                    } else {
                        codigosCorrectos = false;
                    }

                } else {
                    codigosCorrectos = false;
                }

            } else {
                codigosCorrectos = false;
            }


            if (codigosCorrectos) {

                //ACA VA ABOSLUTAMENTE TODO LO QUE HACES DE LA VENTA
                //YA ACA SE VERIFICARON LOS CODIGOS
                char serverMsg[] = "REALIZADA";
                if (eliminRealizada)
                    write(newsockfd,serverMsg,strlen(serverMsg));


            } else {
                char serverMsgNO[] = "NO_REALIZADA";
                write(newsockfd,serverMsgNO,strlen(serverMsgNO));
            }

            //if alguna no existe no lo deja

            //DECLARACION DE VARIABLES



            //arbolSupermercados->getNodoSupermercado(codSuper, arbolSupermercados->raiz, _nodoSup);





        }else if (( memcmp( buffer, "ANCHURA", strlen( "ANCHURA"))) == 0) {
            char * lineaValores = buffer;
            std::string nombre(std::strtok (lineaValores, ";"));
            std::string nodoInicialStr(std::strtok (NULL, ";"));


            std::string recorridoArbol = "Recorrido en Anchura:\n";
            recorridoArbol += listaLugares->anchura(atoi(nodoInicialStr.c_str()));

            std::cout << recorridoArbol << std::endl;
            std::string msg2Provider = "Puede el cliente consultar el recorrido en Anchura?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);


            write(newsockfd,recorridoArbol.c_str() , strlen(recorridoArbol.c_str()));

        }else if (( memcmp( buffer, "DIJKSTRA", strlen( "DIJKSTRA"))) == 0) {
            int x = 0;
            char * lineaValores = buffer;
            std::string nombre(std::strtok (lineaValores, ";"));
            std::string nodoInicialStr(std::strtok (NULL, ";"));
            std::string nodoFinalStr(std::strtok (NULL, ";"));

            //esto se hace para simular que el proveedor acepta el pedido
            std::string msg2Provider = "Puede el cliente consultar el Dijkstra?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            std::string mensajeTotal = "";
            
            listaLugares->Dijkstra(atoi(nodoInicialStr.c_str()), atoi(nodoFinalStr.c_str()));

        }else if (( memcmp( buffer, "KRUSKAL", strlen( "KRUSKAL"))) == 0) {

            char * lineaValores = buffer;
            std::string nombre(std::strtok (lineaValores, ";"));
            std::string nodoInicialStr(std::strtok (NULL, ";"));

            std::string msg2Provider = "Puede el cliente consultar Kruskal?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            std::string mensajeTotal = "";

            arbolKruskal->kruskal(listaLugares, atoi(nodoInicialStr.c_str()));
            mensajeTotal = arbolKruskal->imprimirKruskal();

            write(newsockfd,mensajeTotal.c_str() , strlen(mensajeTotal.c_str()));
            
        }else if ((memcmp( buffer, "PRIM", strlen( "PRIM"))) == 0) {

            char * lineaValores = buffer;
            std::string nombre(std::strtok (lineaValores, ";"));
            std::string nodoInicialStr(std::strtok (NULL, ";"));

            //esto se hace para simular que el proveedor acepta el pedido
            std::string msg2Provider = "Puede el cliente consultar el PRIM?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            std::string mensajeTotal = "";

            std::string pesoTotal = arbol->prim(listaLugares,atoi(nodoInicialStr.c_str()));
            std::string mensajeParcial = arbol->getPrim();

            mensajeTotal = "Peso Total:  " + pesoTotal +  " " + mensajeParcial;

            write(newsockfd,mensajeTotal.c_str() , strlen(mensajeTotal.c_str()));





            //write(newsockfd,msg,strlen(msg))



        }else if (tester == "ARTICU") {
            int x = 0;

        }else if (tester == "Proveedores") {           //Este manda el arbol apenas le llega el mensaje con "Proveedores"
            //ACA ENTRA PARA IMPRIMIR LOS ARBOLES
            int x = 0;
            //std::string recibido = "Recibido";
            //write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            //read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente recibir un recorrido del arbol de proveedores?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            std::string arbolP = "";
            proveedores->PreordenSocket(proveedores->raiz, arbolP);
            write(newsockfd,arbolP.c_str() , strlen(arbolP.c_str()));

        }else if (tester == "Categorias") {
            int x = 0;
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente recibir un recorrido del arbol de categorias?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            

            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            //cC = atoi(codCat.c_str());

            ArbolCategorias *arbolCat = NULL;

            bool codigosCorrectos = false;
            std::string arbolC = "";
            if(listaLugares->existeLugar(cL)){
                ArbolSupermercados *arbolS;
                NodoLugar *nodoLug;
                nodoLug = listaLugares->getNodoLugar(cL);
                arbolS = nodoLug->getArbolSuper();
                if(arbolS->existeSupermercado(cS, arbolS->raiz)){
                    arbolS->getArbolCat(cS, arbolS->raiz, arbolCat);
                }
            }
            if(arbolCat != NULL){
                arbolCat->PreordenSocket(arbolCat->raiz, arbolC);
                //Aqui van las funciones para hacer el recorrido del arbol de categorias
                mensaje = arbolC;
            }else{
                mensaje = "Codigo(s) erroneo(s)\n";
            }
            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));

        }
        else if (tester == "Productos") {
            //ACA ENTRA PARA IMPRIMIR LOS ARBOLES
            int x = 0;
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente recibir un recorrido del arbol de productos?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            std::string codCat(std::strtok (NULL, ";"));

            ArbolCategorias *arbolCat = NULL;
            ArbolProductos *arbolProd = NULL;
            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            cC = atoi(codCat.c_str());

            bool codigosCorrectos = false;
            std::string arbolP = "";

            //Aqui va lo del recorrido del arbol de productos
            if(listaLugares->existeLugar(cL)){
                ArbolSupermercados *arbolS;
                NodoLugar *nodoLug;
                nodoLug = listaLugares->getNodoLugar(cL);
                arbolS = nodoLug->getArbolSuper();
                if(arbolS->existeSupermercado(cS, arbolS->raiz)){
                    arbolS->getArbolCat(cS, arbolS->raiz, arbolCat);
                    if(arbolCat != NULL){
                        arbolCat->getArbolProd(arbolCat->raiz, cC, arbolProd);
                    }
                }
            }
            if(arbolCat != NULL && arbolProd != NULL){
                arbolProd->PreordenSocket(arbolProd->raiz, arbolP);
                //Aqui van las funciones para hacer el recorrido del arbol de categorias
                mensaje = arbolP;
            }else{
                mensaje = "Codigo(s) erroneo(s)\n";
            }

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));

        }
        else if (tester == "Clientes") {
            //ACA ENTRA PARA IMPRIMIR LOS ARBOLES
            int x = 0;


            std::string msg2Provider = "Puede el cliente recibir un recorrido del arbol de clientes?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

           // char * lineaValores = buffer;
            //std::string codLugar(std::strtok (lineaValores, ";"));
           // std::string codSuper(std::strtok (NULL, ";"));
           // std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
           // int cL,cS,cC;
            //cL = atoi(codLugar.c_str());
            //cS = atoi(codSuper.c_str());
           // cC = atoi(codCat.c_str());

           // bool codigosCorrectos = false;
           std::string arbolClientes = "";
            clientes->PreordenSocket(clientes->raizB, arbolClientes);
			mensaje = arbolClientes;
			
            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));

        }
        
        else if (tester == "Supermercados") {
            //ACA ENTRA PARA IMPRIMIR LOS ARBOLES
            int x = 0;
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente recibir un recorrido del arbol de supermercados?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            //std::string codSuper(std::strtok (NULL, ";"));
            //std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            //cS = atoi(codSuper.c_str());
            //cC = atoi(codCat.c_str());

            bool codigosCorrectos = false;
            std::string strSuper = "";
            //Aca va lo del recorrido del arbol de supermercados
            //listaLugares->getNodoLugar(cL)->getArbolSuper()->PreordenSocket(listaLugares->getNodoLugar(cL)->getArbolSuper()->raiz, arbolS);
            if(listaLugares->existeLugar(cL)) {
                ArbolSupermercados *arbolS;
                NodoLugar *nodoLug;
                nodoLug = listaLugares->getNodoLugar(cL);
                arbolS = nodoLug->getArbolSuper();
                arbolS->PreordenSocket(arbolS->raiz, strSuper);
            }else{
                mensaje = "Codigos erroneos\n";
            }
			mensaje = strSuper;
			
            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));

        }
        
		else {
            std::string tester (buffer);
            std::cout << tester << std::endl;
            char serverMsg[] = "ERROR NO ENTRO EN NINGUNA OPCION \0";
            write(newsockfd,serverMsg,strlen(serverMsg));
            if(tester == "exit")
                break;
        }

        // /write()
        //  if(tester == "exit")
        //    break;
    }

    std::cout << "\nClosing thread and conn" << std::endl;
    close(newsockfd);
}

//todo gual a clientmanagment pero usa
//bufferC2
//newsockfdc2
void* clientManagement2 (void *dummyPt) {

    //PRUEBAS

    int nodoInicial;
    //

    std::cout << "Thread No: " << pthread_self() << std::endl;
    char buffer[TAMANHO_BUFFER];
    bzero(buffer, TAMANHO_BUFFER);
    char msg[] = "CONECTADO AL SERVIDOR";
    write(newsockfd,msg,strlen(msg));
    bool loop = false;


    char clienteError[] = "NO_EXISTE";
    char clienteExistemsg[] = "CLIENTE_EXISTE";

/////////////////////////////////////////
    while(!loop) {
        bzero(buffer, TAMANHO_BUFFER);
        read(newsockfd, buffer, TAMANHO_BUFFER - 1);
        std::string parteString, parteStr;
        std::string tester(buffer);
        parteString = tester.substr(0,1);


        if(tester == "CLIENTE"){

            char msg[] = "Esperando Respuesta";
            write(newsockfd,msg,strlen(msg));

            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);
            std::string codigoCliente (buffer);

            std::string msg2Provider = "Codigo Cliente Recibido," + codigoCliente;
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));

            bzero(bufferProveedor, TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER-1);
            std::string bufProvv (bufferProveedor);


            bool existeCliente = false;
            std::string codCliente (buffer);
            clientes->existeCliente(clientes->raizB,atoi(buffer),existeCliente);
            if (existeCliente) {
                std::cout << "El cliente ingresado es el correcto" << std::endl;
                //le dice la cliente que si existe, no pide datos
                write(newsockfd,clienteExistemsg,strlen(clienteExistemsg));
            } else {
                banderaCLIENTENUEVO = true;
                //le dice al cliente que no existe,
                write(newsockfd,clienteError,strlen(clienteError));
                bzero(buffer, TAMANHO_BUFFER);
                read(newsockfd, buffer, TAMANHO_BUFFER - 1);

                char * lineaValores = buffer;

                std::string codClienteNuevo(std::strtok (lineaValores, ";"));
                std::string nombre(std::strtok (NULL, ";"));
                std::string direccion(std::strtok (NULL, ";"));
                std::string telefono(std::strtok (NULL, ";"));

                int codClienteI = atoi(codClienteNuevo.c_str());
                int telI = atoi(telefono.c_str());

                clientes->IniciarInsercionB(codClienteI,codClienteI,nombre,direccion,telI);

                char clienteCre[] = "CLIENTE_CREADO";

                write(newsockfd,clienteCre,strlen(clienteCre));


            }
            codigoClienteGlobal = atoi(codigoCliente.c_str());

        }else if ( (memcmp( buffer, "PROFUNDIDAD", strlen( "PROFUNDIDAD"))) == 0) {

            char * lineaValores = buffer;
            std::string nombre(std::strtok (lineaValores, ";"));
            std::string nodoInicialStr(std::strtok (NULL, ";"));


            std::string recorridoArbol = "Recorrido en Profundidad:\n";
            recorridoArbol += listaLugares->profundida(atoi(nodoInicialStr.c_str()));
            std::cout << recorridoArbol << std::endl;
            std::string msg2Provider = "Puede el cliente consultar la profundidad?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);


            write(newsockfd,recorridoArbol.c_str() , strlen(recorridoArbol.c_str()));

        } else if ( parteString == "v") {

            std::cout << "SE ESTA REALIZANDO UNA VENTA" << std::endl;

            std::string msg2Provider = "Solicitud de Venta Recibida";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor, TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER-1);
            char * lineaValores = buffer;
            std::string venta(std::strtok (lineaValores, ";"));
            std::string codLugar(std::strtok (NULL, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            std::string codCat(std::strtok (NULL, ";"));
            std::string codProducto(std::strtok (NULL, ";"));
            std::string strCant(std::strtok (NULL, ";"));
            std::string codigoProv(std::strtok (NULL, ";"));



            bool codigosCorrectos = false;
            bool ventaRealizada = false;
            int cL,cS,cC,cP, cantidad, codProveedor;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            cC = atoi(codCat.c_str());
            cP = atoi(codProducto.c_str());
            cantidad = atoi(strCant.c_str());
            codProveedor = atoi(codigoProv.c_str());


            NodoLugar* nodo = new NodoLugar();
            NodoProveedor* _nodoProv = new NodoProveedor();
            NodoCliente* _nodoCliente = new NodoCliente();
            if (listaLugares->existeLugar(cL)) {
                nodo = listaLugares->getNodoLugar(cL);
                ArbolSupermercados* super = new ArbolSupermercados();
                super = nodo->getArbolSuper();

                if (super->existeSupermercado(cS,super->raiz)) {
                    NodoSupermercado* nodoSuper = new NodoSupermercado();
                    ArbolCategorias* cat = new ArbolCategorias();
                    super->getArbolCat(cS,super->raiz,cat);

                    if (cat->existeCategoria(cC,cat->raiz)) {
                        ArbolProductos* pro = new ArbolProductos();
                        cat->getArbolProd(cat->raiz,cC,pro);

                        if (pro->existeProducto(pro->raiz,cP)) {
                            NodoProducto* nodoPro = new NodoProducto();
                            pro->getNodoProducto(cP,pro->raiz,nodoPro);
                            codigosCorrectos = true;

                            proveedores->getNodoProveedor(codProveedor,proveedores->raiz,_nodoProv);
                            clientes->getCliente(clientes->raizB, _nodoCliente, codigoClienteGlobal);
                            _nodoCliente->aumentarVentas();
                            _nodoProv->aumentarVentas();
                            nodoPro->setCantidadEnStock(cantidad);
                            nodocategoria *nodoCat = new nodocategoria();
                            cat->getNodoCat(cat->raiz,cC, nodoCat);
                            nodoCat->incBestScore();
                            super->getNodoSupermercado(cS, super->raiz, nodoSuper);
                            nodoSuper->aumentarVentas();

                            ventaRealizada = true;
                            if (banderaCLIENTENUEVO) {



                                NodoVenta *_nodoVenta = new NodoVenta(_nodoProv->getID(), _nodoProv->getNombre(),
                                                                      _nodoCliente->getID(),
                                                                      _nodoCliente->getNombre(), nodoCat->getCodigo(),
                                                                      nodoCat->getDesc(),
                                                                      nodoPro->getCodigoProducto(),
                                                                      nodoPro->getNombreProducto(),
                                                                      nodoPro->getPrecioPorUnidad(), cantidad,
                                                                      nodoPro->getPrecioPorUnidad() * cantidad);
                                listaVentas->insertar(_nodoVenta);


                            }else {
                                int x = 0;

                                NodoVenta *_nodoVenta = new NodoVenta(_nodoProv->getID(), _nodoProv->getNombre(),
                                                                      _nodoCliente->getID(),
                                                                      _nodoCliente->getNombre(), nodoCat->getCodigo(),
                                                                      nodoCat->getDesc(),
                                                                      nodoPro->getCodigoProducto(),
                                                                      nodoPro->getNombreProducto(),
                                                                      nodoPro->getPrecioPorUnidad(), cantidad,
                                                                      ((nodoPro->getPrecioPorUnidad() * cantidad)) - (nodoPro->getPrecioPorUnidad() * cantidad * 0.05));
                                listaVentas->insertar(_nodoVenta);

                            }

                        }else {
                            codigosCorrectos = false;

                        }


                    } else {
                        codigosCorrectos = false;
                    }

                } else {
                    codigosCorrectos = false;
                }

            } else {
                codigosCorrectos = false;
            }


            if (codigosCorrectos) {

                //ACA VA ABOSLUTAMENTE TODO LO QUE HACES DE LA VENTA
                //YA ACA SE VERIFICARON LOS CODIGOS
                char serverMsg[] = "V_REALIZADA";
                if (ventaRealizada)
                    write(newsockfd,serverMsg,strlen(serverMsg));


            } else {
                char serverMsgNO[] = "V_NO_REALIZADA";
                write(newsockfd,serverMsgNO,strlen(serverMsgNO));
            }

            //if alguna no existe no lo deja

            //DECLARACION DE VARIABLES



            //arbolSupermercados->getNodoSupermercado(codSuper, arbolSupermercados->raiz, _nodoSup);


        }else if (tester == "PMV") {//Proveedor con mas ventas
            std::string recorridoArbol = "El proveedor con mas ventas es:\n";
            NodoProveedor* nodo = new NodoProveedor();
            proveedores->getNodoProveedorMasVentas(proveedores->raiz,nodo);

            recorridoArbol += nodo->getNombre();
            std::string msg2Provider = "Puede el cliente consultar el proveedor con mas ventas?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);
            write(newsockfd,recorridoArbol.c_str() , strlen(recorridoArbol.c_str()));


        }else if (tester == "CMC") {//CLIENTE QUE MAS COMPRO
            std::string clienteMasCompras = "El Cliente con mas Compras es:\n";

            NodoCliente* nodo = new NodoCliente();
            clientes->getClienteMasCompras(clientes->raizB,nodo);


            clienteMasCompras += nodo->getNombre();
            std::string msg2Provider = "Puede el cliente consultar el cliente con mas compras?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);
            write(newsockfd,clienteMasCompras.c_str() , strlen(clienteMasCompras.c_str()));


        }else if (tester == "PQMV") {//Producto mas vendido
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente consultar el prducto mas comprado?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            cC = atoi(codCat.c_str());

            bool codigosCorrectos = false;

            NodoLugar* nodo = new NodoLugar();
            if (listaLugares->existeLugar(cL)) {
                nodo = listaLugares->getNodoLugar(cL);
                ArbolSupermercados* super = new ArbolSupermercados();
                super = nodo->getArbolSuper();

                if (super->existeSupermercado(cS,super->raiz)) {
                    NodoSupermercado* nodoSuper = new NodoSupermercado();
                    ArbolCategorias* cat = new ArbolCategorias();
                    super->getArbolCat(cS,super->raiz,cat);

                    if (cat->existeCategoria(cC,cat->raiz)) {
                        ArbolProductos* pro = new ArbolProductos();
                        cat->getArbolProd(cat->raiz,cC,pro);

                        NodoProducto* nodoPro = new NodoProducto();
                        pro->getProductoMasVendido(pro->raiz,nodoPro);

                        mensaje = nodoPro->getNombreProducto();
                    }
                } else {
                    codigosCorrectos = false;
                }

            } else {
                codigosCorrectos = false;
            }

            if (!codigosCorrectos)
                mensaje = "Algun codigo erroneo";

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));


        }else if (tester == "PQRSS") {//productos que rebajaron su stock
            int x = 0;
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente consultar los productos que cambiaron su stock?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            cC = atoi(codCat.c_str());

            bool codigosCorrectos = false;

            NodoLugar* nodo = new NodoLugar();
            if (listaLugares->existeLugar(cL)) {
                nodo = listaLugares->getNodoLugar(cL);
                ArbolSupermercados* super = new ArbolSupermercados();
                super = nodo->getArbolSuper();

                if (super->existeSupermercado(cS,super->raiz)) {
                    NodoSupermercado* nodoSuper = new NodoSupermercado();
                    ArbolCategorias* cat = new ArbolCategorias();
                    super->getArbolCat(cS,super->raiz,cat);

                    if (cat->existeCategoria(cC,cat->raiz)) {
                        ArbolProductos* pro = new ArbolProductos();
                        cat->getArbolProd(cat->raiz,cC,pro);

                        std::string nodoPro;
                        pro->getProductosCambiaronStock(pro->raiz,nodoPro);

                        mensaje = nodoPro;
                    }
                } else {
                    codigosCorrectos = false;
                }

            } else {
                codigosCorrectos = false;
            }

            if (!codigosCorrectos)
                mensaje = "Algun codigo erroneo";

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));


        }else if (tester == "CMV") {//categoria mas vendida
            int x = 0;
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente consultar la categoria mas vendida?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            //std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            //cC = atoi(codCat.c_str());

            bool codigosCorrectos = false;

            NodoLugar* nodo = new NodoLugar();
            if (listaLugares->existeLugar(cL)) {
                nodo = listaLugares->getNodoLugar(cL);
                ArbolSupermercados* super = new ArbolSupermercados();
                super = nodo->getArbolSuper();

                if (super->existeSupermercado(cS,super->raiz)) {
                    NodoSupermercado* nodoSuper = new NodoSupermercado();
                    ArbolCategorias* cat = new ArbolCategorias();
                    super->getArbolCat(cS,super->raiz,cat);


                    nodocategoria* nodoCat = new nodocategoria();


                    cat->getCategoriaMasVendida(cat->raiz, nodoCat);

                    mensaje = nodoCat->getDesc();
                } else {
                    codigosCorrectos = false;
                }

            } else {
                codigosCorrectos = false;
            }

            if (!codigosCorrectos)
                mensaje = "Algun codigo erroneo";

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));

        }else if (tester == "SMV") {//supermercado con mas ventas
            int x = 0;
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente consultar el supermercado que mas vendio?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            //std::string codSuper(std::strtok (NULL, ";"));
            //std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            //cS = atoi(codSuper.c_str());
            //cC = atoi(codCat.c_str());

            bool codigosCorrectos = false;

            NodoLugar* nodo = new NodoLugar();
            if (listaLugares->existeLugar(cL)) {
                nodo = listaLugares->getNodoLugar(cL);
                ArbolSupermercados* super = new ArbolSupermercados();
                super = nodo->getArbolSuper();

                NodoSupermercado* nodoSup = new NodoSupermercado();
                super->getSuperMasVendido(super->raiz, nodoSup);

                mensaje = nodoSup->getNombre();

            } else {
                codigosCorrectos = false;
            }

            if (!codigosCorrectos)
                mensaje = "Algun codigo erroneo";

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));

        }else if (tester == "LQMV") {

            std::string msg2Provider = "Puede el cliente consultar el lugar con mas supermercados?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            //std::string codLugar(std::strtok (lineaValores, ";"));
            //std::string codSuper(std::strtok (NULL, ";"));
            //std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            bool codigosCorrectos = false;

            NodoLugar* nodo = new NodoLugar();
            listaLugares->getLugarMasSuper(nodo);
            mensaje = nodo->getNombre();

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));
        }else if (tester == "IMPRESION") {
            int x = 0;
        }else if (( memcmp( buffer, "ELIMINAR_ARTICULO", strlen( "ELIMINAR_ARTICULO"))) == 0) {

            std::cout << "SE ESTA REALIZANDO UNA VENTA" << std::endl;

            std::string msg2Provider = "Solicitud de Eliminar Producto";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor, TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER-1);
            char * lineaValores = buffer;
            std::string eliminar(std::strtok (lineaValores, ";"));
            std::string codLugar(std::strtok (NULL, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            std::string codCat(std::strtok (NULL, ";"));
            std::string codProducto(std::strtok (NULL, ";"));




            bool codigosCorrectos = false;
            bool eliminRealizada = false;
            int cL,cS,cC,cP, cantidad, codProveedor;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            cC = atoi(codCat.c_str());
            cP = atoi(codProducto.c_str());


            NodoLugar* nodo = new NodoLugar();
            NodoProveedor* _nodoProv = new NodoProveedor();
            NodoCliente* _nodoCliente = new NodoCliente();
            if (listaLugares->existeLugar(cL)) {
                nodo = listaLugares->getNodoLugar(cL);
                ArbolSupermercados* super = new ArbolSupermercados();
                super = nodo->getArbolSuper();

                if (super->existeSupermercado(cS,super->raiz)) {
                    NodoSupermercado* nodoSuper = new NodoSupermercado();
                    ArbolCategorias* cat = new ArbolCategorias();
                    super->getArbolCat(cS,super->raiz,cat);

                    if (cat->existeCategoria(cC,cat->raiz)) {
                        ArbolProductos* pro = new ArbolProductos();
                        cat->getArbolProd(cat->raiz,cC,pro);

                        if (pro->existeProducto(pro->raiz,cP)) {

                            pro->eliminar(pro->raiz,cP);


                        }else {
                            codigosCorrectos = false;

                        }


                    } else {
                        codigosCorrectos = false;
                    }

                } else {
                    codigosCorrectos = false;
                }

            } else {
                codigosCorrectos = false;
            }


            if (codigosCorrectos) {

                //ACA VA ABOSLUTAMENTE TODO LO QUE HACES DE LA VENTA
                //YA ACA SE VERIFICARON LOS CODIGOS
                char serverMsg[] = "REALIZADA";
                if (eliminRealizada)
                    write(newsockfd,serverMsg,strlen(serverMsg));


            } else {
                char serverMsgNO[] = "NO_REALIZADA";
                write(newsockfd,serverMsgNO,strlen(serverMsgNO));
            }

            //if alguna no existe no lo deja

            //DECLARACION DE VARIABLES



            //arbolSupermercados->getNodoSupermercado(codSuper, arbolSupermercados->raiz, _nodoSup);





        }else if (( memcmp( buffer, "ANCHURA", strlen( "ANCHURA"))) == 0) {
            char * lineaValores = buffer;
            std::string nombre(std::strtok (lineaValores, ";"));
            std::string nodoInicialStr(std::strtok (NULL, ";"));


            std::string recorridoArbol = "Recorrido en Anchura:\n";
            recorridoArbol += listaLugares->anchura(atoi(nodoInicialStr.c_str()));

            std::cout << recorridoArbol << std::endl;
            std::string msg2Provider = "Puede el cliente consultar el recorrido en Anchura?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);


            write(newsockfd,recorridoArbol.c_str() , strlen(recorridoArbol.c_str()));

        }else if (( memcmp( buffer, "DIJKSTRA", strlen( "DIJKSTRA"))) == 0) {
            int x = 0;
            char * lineaValores = buffer;
            std::string nombre(std::strtok (lineaValores, ";"));
            std::string nodoInicialStr(std::strtok (NULL, ";"));
            std::string nodoFinalStr(std::strtok (NULL, ";"));

            //esto se hace para simular que el proveedor acepta el pedido
            std::string msg2Provider = "Puede el cliente consultar el Dijkstra?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            std::string mensajeTotal = "";

            listaLugares->Dijkstra(atoi(nodoInicialStr.c_str()), atoi(nodoFinalStr.c_str()));

        }else if (( memcmp( buffer, "KRUSKAL", strlen( "KRUSKAL"))) == 0) {

            int x = 0;

        }else if ((memcmp( buffer, "PRIM", strlen( "PRIM"))) == 0) {

            char * lineaValores = buffer;
            std::string nombre(std::strtok (lineaValores, ";"));
            std::string nodoInicialStr(std::strtok (NULL, ";"));

            //esto se hace para simular que el proveedor acepta el pedido
            std::string msg2Provider = "Puede el cliente consultar el PRIM?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            std::string mensajeTotal = "";

            std::string pesoTotal = arbol->prim(listaLugares,atoi(nodoInicialStr.c_str()));
            std::string mensajeParcial = arbol->getPrim();

            mensajeTotal = "Peso Total:  " + pesoTotal +  " " + mensajeParcial;

            write(newsockfd,mensajeTotal.c_str() , strlen(mensajeTotal.c_str()));





            //write(newsockfd,msg,strlen(msg))



        }else if (tester == "ARTICU") {
            int x = 0;

        }else if (tester == "Proveedores") {           //Este manda el arbol apenas le llega el mensaje con "Proveedores"
            //ACA ENTRA PARA IMPRIMIR LOS ARBOLES
            int x = 0;
            //std::string recibido = "Recibido";
            //write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            //read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente recibir un recorrido del arbol de proveedores?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            std::string arbolP = "";
            proveedores->PreordenSocket(proveedores->raiz, arbolP);
            write(newsockfd,arbolP.c_str() , strlen(arbolP.c_str()));

        }else if (tester == "Categorias") {
            int x = 0;
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente recibir un recorrido del arbol de categorias?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            std::string codSuper(std::strtok (NULL, ";"));


            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            //cC = atoi(codCat.c_str());

            ArbolCategorias *arbolCat = NULL;

            bool codigosCorrectos = false;
            std::string arbolC = "";
            if(listaLugares->existeLugar(cL)){
                ArbolSupermercados *arbolS;
                NodoLugar *nodoLug;
                nodoLug = listaLugares->getNodoLugar(cL);
                arbolS = nodoLug->getArbolSuper();
                if(arbolS->existeSupermercado(cS, arbolS->raiz)){
                    arbolS->getArbolCat(cS, arbolS->raiz, arbolCat);
                }
            }
            if(arbolCat != NULL){
                arbolCat->PreordenSocket(arbolCat->raiz, arbolC);
                //Aqui van las funciones para hacer el recorrido del arbol de categorias
                mensaje = arbolC;
            }else{
                mensaje = "Codigo(s) erroneo(s)\n";
            }
            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));

        }
        else if (tester == "Productos") {
            //ACA ENTRA PARA IMPRIMIR LOS ARBOLES
            int x = 0;
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente recibir un recorrido del arbol de productos?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            std::string codSuper(std::strtok (NULL, ";"));
            std::string codCat(std::strtok (NULL, ";"));

            ArbolCategorias *arbolCat = NULL;
            ArbolProductos *arbolProd = NULL;
            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            cS = atoi(codSuper.c_str());
            cC = atoi(codCat.c_str());

            bool codigosCorrectos = false;
            std::string arbolP = "";

            //Aqui va lo del recorrido del arbol de productos
            if(listaLugares->existeLugar(cL)){
                ArbolSupermercados *arbolS;
                NodoLugar *nodoLug;
                nodoLug = listaLugares->getNodoLugar(cL);
                arbolS = nodoLug->getArbolSuper();
                if(arbolS->existeSupermercado(cS, arbolS->raiz)){
                    arbolS->getArbolCat(cS, arbolS->raiz, arbolCat);
                    if(arbolCat != NULL){
                        arbolCat->getArbolProd(arbolCat->raiz, cC, arbolProd);
                    }
                }
            }
            if(arbolCat != NULL && arbolProd != NULL){
                arbolProd->PreordenSocket(arbolProd->raiz, arbolP);
                //Aqui van las funciones para hacer el recorrido del arbol de categorias
                mensaje = arbolP;
            }else{
                mensaje = "Codigo(s) erroneo(s)\n";
            }

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));

        }
        else if (tester == "Clientes") {
            //ACA ENTRA PARA IMPRIMIR LOS ARBOLES
            int x = 0;


            std::string msg2Provider = "Puede el cliente recibir un recorrido del arbol de clientes?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            // char * lineaValores = buffer;
            //std::string codLugar(std::strtok (lineaValores, ";"));
            // std::string codSuper(std::strtok (NULL, ";"));
            // std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            // int cL,cS,cC;
            //cL = atoi(codLugar.c_str());
            //cS = atoi(codSuper.c_str());
            // cC = atoi(codCat.c_str());

            // bool codigosCorrectos = false;
            std::string arbolClientes = "";
            clientes->PreordenSocket(clientes->raizB, arbolClientes);
            mensaje = arbolClientes;

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));

        }

        else if (tester == "Supermercados") {
            //ACA ENTRA PARA IMPRIMIR LOS ARBOLES
            int x = 0;
            std::string recibido = "Recibido";
            write(newsockfd,recibido.c_str() , strlen(recibido.c_str()));
            bzero(buffer, TAMANHO_BUFFER);
            read(newsockfd, buffer, TAMANHO_BUFFER - 1);

            std::string msg2Provider = "Puede el cliente recibir un recorrido del arbol de supermercados?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));
            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            char * lineaValores = buffer;
            std::string codLugar(std::strtok (lineaValores, ";"));
            //std::string codSuper(std::strtok (NULL, ";"));
            //std::string codCat(std::strtok (NULL, ";"));

            std::string mensaje = "";
            int cL,cS,cC;
            cL = atoi(codLugar.c_str());
            //cS = atoi(codSuper.c_str());
            //cC = atoi(codCat.c_str());

            bool codigosCorrectos = false;
            std::string strSuper = "";
            //Aca va lo del recorrido del arbol de supermercados
            //listaLugares->getNodoLugar(cL)->getArbolSuper()->PreordenSocket(listaLugares->getNodoLugar(cL)->getArbolSuper()->raiz, arbolS);
            if(listaLugares->existeLugar(cL)) {
                ArbolSupermercados *arbolS;
                NodoLugar *nodoLug;
                nodoLug = listaLugares->getNodoLugar(cL);
                arbolS = nodoLug->getArbolSuper();
                arbolS->PreordenSocket(arbolS->raiz, strSuper);
            }else{
                mensaje = "Codigos erroneos\n";
            }
            mensaje = strSuper;

            write(newsockfd,mensaje.c_str() , strlen(mensaje.c_str()));

        }

        else {
            std::string tester (buffer);
            std::cout << tester << std::endl;
            char serverMsg[] = "ERROR NO ENTRO EN NINGUNA OPCION \0";
            write(newsockfd,serverMsg,strlen(serverMsg));
            if(tester == "exit")
                break;
        }

        // /write()
        //  if(tester == "exit")
        //    break;
    }

    std::cout << "\nClosing thread and conn" << std::endl;
    close(newsockfd);
}

/*
    int nodoInicial = 20;
    std::cout << "Thread No: " << pthread_self() << std::endl;
    char bufferC2[TAMANHO_BUFFER];
    bzero(bufferC2, TAMANHO_BUFFER);
    char msg[] = "CONECTADO AL SERVIDOR";
    write(newsockfdc2,msg,strlen(msg));
    bool loop = false;
    while(!loop) {
        bzero(bufferC2, TAMANHO_BUFFER);
        read(newsockfdc2, bufferC2, TAMANHO_BUFFER-1);
        std::string parteString,parteStr;
        std::string tester (bufferC2);

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

        } else if ( tester == "V_COD_CLIENTE") {

            std::string msgC = "CLIENTE EXISTE";
            std::string msgC2 = "CLIENTE NO EXISTE\nINGRESE SUS DATOS";

            std::string msg2Provider = "Puede el cliente consultar la profundidad?";
            write(newsockProvider,msg2Provider.c_str(),strlen(msg2Provider.c_str()));

            std::string msgMal = "NO fue permitido";

            bzero(bufferProveedor,TAMANHO_BUFFER);
            read(newsockProvider,bufferProveedor,TAMANHO_BUFFER - 1);

            std::string bufProvee (bufferProveedor);

            if (bufProvee == "SI\n")
                write(newsockfdc2,msgC.c_str() , strlen(msgC.c_str()));
            else
                write(newsockfdc2,msgC2.c_str(),strlen(msgC2.c_str()));

        }else {

            std::string tester (bufferC2);
            std::cout << tester << std::endl;
            char serverMsg[] = "BIENVENIDO AL SERVIDOR \0";
            write(newsockfdc2,serverMsg,strlen(serverMsg));
            if(tester == "exit")
                break;
        }
    }
    std::cout << "\nClosing thread and conn" << std::endl;
    close(newsockfdc2);
    */




void *provider (void *dummyPt) {
    std::cout << "Thread No: " << pthread_self() << std::endl;
    bzero(bufferProveedor, TAMANHO_BUFFER);
    //write(newsockProvider, msg, strlen(msg));
    bool loop = false;
   while(true) {
       bzero(bufferProveedor, TAMANHO_BUFFER);
       char msg2[] = "PORFAVOR DIGITE SU CODIGO: ";
       write(newsockProvider, msg2, strlen(msg2));
       read(newsockProvider, bufferProveedor, TAMANHO_BUFFER - 1);
       std::string respuestaProveedor(bufferProveedor);
       if (proveedores->existeProveedor(atoi(bufferProveedor), proveedores->raiz)) {
           codigoProveedorGlobal = atoi(bufferProveedor);
           break;
       }
   }
       bzero(bufferProveedor, TAMANHO_BUFFER);
       char msg[] = "CONECTADO";
       write(newsockProvider, msg, strlen(msg));
       /*
       while (!loop) {
           bzero(bufferProveedor, TAMANHO_BUFFER);
           read(newsockProvider, bufferProveedor, TAMANHO_BUFFER - 1);

           std::string tester(bufferProveedor);

           //Proveedor espera una venta
           if (tester == "1") {
               sleep(10000);

           }

           std::cout << tester << std::endl;
           char serverMsg[] = "BIENVENIDO AL SERVIDOR";
           write(newsockProvider, serverMsg, strlen(serverMsg));

           if (tester == "exit")
               break;
           }

       std::cout << "\nClosing thread and conn" << std::endl;
       close(newsockProvider);

       }*/
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
    leerArchSupermercado(listaLugares);
    leerArchCategorias(listaLugares);
    leerArchProductos(listaLugares);
    leerArchClientes(clientes);
    leerArchProveedores(proveedores);
    //leerArchClientes();
    //ArbolExpansionMinimo* arbolExpansionMinimo = new ArbolExpansionMinimo(_listaLugares);
    //int min = arbolExpansionMinimo->arbolExpancionPrim(_listaLugares);

   // listaLugares->profundida(1);
    //listaLugares->puntosDeArticulacion(1);
   // listaLugares->desvisitarTODO();
    //listaLugares->puntosDeArticulacion(1);

   // std::cout<<"Pf: "<<std::endl;
   // listaLugares->profundida(20);
    //listaLugares->desvisitarTODO();
   // arbol->prim(listaLugares,78);
    //arbol->prim(listaLugares,20);

    //listaLugares->Dijkstra(31, 8);
    
    
    

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
