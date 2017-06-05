#include <sstream>
#include "arbolclientes.h"
//#include <iostream>
//#include <string>
//ARBOL B

void ArregloClaves::InsertarClave(pNodoCliente Clave, int Numero){
    arregloClaves[Numero] = Clave;
}

int ArregloClaves::ObtenerClave(int Numero)
{
    pNodoCliente Clave;
    Clave = arregloClaves[Numero];
    int numero = Clave->numero;
    return numero;
}

pNodoCliente ArregloClaves::ObtenerApuntadorClave(int Numero)
{
    pNodoCliente Clave;
    Clave = arregloClaves[Numero];
    return Clave;
}

void ArregloRamas::InsertarRama(ApuntadorPagina Rama, int Numero)
{
    arregloRamas[Numero] = Rama;
}

ApuntadorPagina ArregloRamas::ObtenerRama(int Numero)
{
    ApuntadorPagina AP;
    AP = arregloRamas[Numero];
    return AP;
}


void ArbolClientes::EstablecerRaizB(ApuntadorPagina Raiz)
{
    raizB = Raiz;
}

void ArbolClientes::IniciarInsercionB(int Numero, int _id, std::string _nombre, std::string _direccion, int _telefono)
{
    ApuntadorPagina Raiz = raizB;
    raizB = InsertarB(Raiz,Numero,  _id,  _nombre,  _direccion,  _telefono);
}

ApuntadorPagina ArbolClientes::InsertarB(ApuntadorPagina Raiz, int Numero, int _id, std::string _nombre, std::string _direccion, int _telefono)
{
    ApuntadorPagina P = NULL;

    Raiz = EmpujarB(Raiz,Numero,  _id,  _nombre,  _direccion,  _telefono);
    if (Raiz->Esta) {
        Raiz->Esta = false;
        return Raiz;
    }
    if(Raiz->EmpujarArriba){
        P = new Pagina();
        P->cuenta = 1;
        pNodoCliente Auxiliar = new NodoCliente(Raiz->X,  _id,  _nombre,  _direccion, _telefono);
        P->Claves->InsertarClave(Auxiliar,1);
        P->Ramas->InsertarRama(Raiz->Xr,1);
        if(Raiz->llamadas == 1){
            P->Ramas->InsertarRama(NULL,0);
        }
        else{
            P->Ramas->InsertarRama(Raiz,0);
        }

        Raiz = P;
    }
    return Raiz;


}

ApuntadorPagina ArbolClientes::EmpujarB(ApuntadorPagina Raiz, int Numero, int _id, std::string _nombre, std::string _direccion, int _telefono)
{
    if(Raiz == NULL){
        Raiz = new Pagina();
        Raiz->EmpujarArriba = true;
        Raiz->X = Numero;
        Raiz->Xr = NULL;
        Raiz->llamadas++;
        return Raiz;
    }

    else{
        Raiz = BuscarNodoB(Raiz,Numero);
        if(Raiz->Esta){
            std::cout << "Elemento Repetido" << std::endl;
            return Raiz;

        }
        if(Raiz->K == 0){

        }
        ApuntadorPagina Aux;
        Aux = EmpujarB(Raiz->Ramas->ObtenerRama(Raiz->K),Numero,  _id,  _nombre,  _direccion,  _telefono);
        Raiz->EmpujarArriba = Aux->EmpujarArriba;
        Raiz->X = Aux -> X;
        Raiz->Xr = Aux->Xr;
        if(Raiz->EmpujarArriba){
            if(Raiz->cuenta < 4){
                Raiz->EmpujarArriba = false;
                Raiz = MeterHojaB(Raiz,  _id,  _nombre,  _direccion,  _telefono);
            }
        }
        else{
            Raiz->EmpujarArriba = true;
            Raiz = DividirNodoB(Raiz,  _id,  _nombre,  _direccion,  _telefono);

        }
        return Raiz;

    }
}

ApuntadorPagina ArbolClientes::BuscarNodoB(ApuntadorPagina Raiz, int Numero)
{
    int PClave1 = Raiz->Claves->ObtenerClave(1);
    if(Numero < PClave1){
        Raiz->Esta = false;
        Raiz->K = 0;
    }
    else{
        Raiz->K = Raiz->cuenta;
        while(Numero < Raiz->Claves->ObtenerClave(Raiz->K) && Raiz->K > 1){
            Raiz->K--;
        }
        if(Numero == Raiz->Claves->ObtenerClave(Raiz->K)){
            Raiz->Esta = true;
        }
    }
    Raiz->llamadas++;
    return Raiz;
}

ApuntadorPagina ArbolClientes::MeterHojaB(ApuntadorPagina Raiz, int _id, std::string _nombre, std::string _direccion, int _telefono)
{
    int I;
    I = Raiz->cuenta;
    while(I >= Raiz->K + 1){
        Raiz->Claves->InsertarClave(Raiz->Claves->ObtenerApuntadorClave(I),I+1);
        Raiz->Ramas->InsertarRama(Raiz->Ramas->ObtenerRama(I),I+1);
        I--;
    }
    pNodoCliente X = new NodoCliente(Raiz->X, _id,  _nombre,  _direccion,  _telefono);
    Raiz->Claves->InsertarClave( X,Raiz->K + 1);
    Raiz->Ramas->InsertarRama(Raiz->Xr ,Raiz->K + 1);
    Raiz->cuenta++;


    return Raiz;


}

ApuntadorPagina ArbolClientes::DividirNodoB(ApuntadorPagina Raiz, int _id, std::string _nombre, std::string _direccion, int _telefono)
{
    int I;
    int Posmda;
    ApuntadorPagina Mder;
    int Mda;

    if(Raiz->K <= 2){
        Posmda = 2;
    }
    else{
        Posmda = 3;
    }

    Mder = new Pagina();
    I = Posmda + 1;
    while(I <= 4){
        Mder->Claves->InsertarClave(Raiz->Claves->ObtenerApuntadorClave(I) ,I - Posmda);
        Mder->Ramas->InsertarRama(Raiz->Ramas->ObtenerRama(I) ,I - Posmda);
        I++;
    }
    Mder->cuenta = 4 - Posmda;
    Raiz->cuenta = Posmda;

    if(Raiz->K <= 2){
        Raiz = MeterHojaB(Raiz,   _id,  _nombre,  _direccion,  _telefono);
    }
    else{
        Mder->X = Raiz->X;
        Mder->Xr = Raiz->Xr;
        Mder->K = Raiz->K - Posmda;
        Mder = MeterHojaB(Mder,  _id,  _nombre,  _direccion,  _telefono);
    }
    Mda = Raiz->Claves->ObtenerClave(Raiz->cuenta);
    Raiz->X = Mda;
    Mder->Ramas->InsertarRama(Raiz->Ramas->ObtenerRama(Raiz->cuenta),0);
    Raiz->cuenta--;
    Raiz->Xr = Mder;
    return Raiz;
}

void ArbolClientes::IniciarRecorridoB()
{
    ApuntadorPagina Raiz = raizB;
    RecorridoInordenB(Raiz);
}

void ArbolClientes::RecorridoInordenB(ApuntadorPagina Raiz){
    if(Raiz == NULL){
        return;
    }
    else{
        int I = 1;
        while(I <= Raiz->cuenta){

            pNodoCliente Recorrido = Raiz->Claves->ObtenerApuntadorClave(I);

            std::cout << "Nombre: " << Recorrido->getNombre()<< std::endl;
            std::cout<< "Identificacion: "<< Recorrido->getID() << std::endl;
            std::cout << "Cantidad de Compras: " << Recorrido->getCantidadCompras()<< std::endl;
            std::cout << "Ciudad: " << Recorrido->getDireccion()<< std::endl;
            std::cout << "Telefono: " << Recorrido->getTelefono() << std::endl;
            std::cout << "\n" << std::endl;

            RecorridoInordenB(Raiz->Ramas->ObtenerRama(I-1));

            I++;
        }
    }
}

void ArbolClientes::existeCliente(ApuntadorPagina Raiz, int _Numero, bool& _existe) {
    if(Raiz == NULL){
        return;
    }
    else{
        int I = 1;
        while(I <= Raiz->cuenta){

            pNodoCliente Recorrido = Raiz->Claves->ObtenerApuntadorClave(I);

            if (Recorrido->getID() == _Numero)
                _existe = true;

            existeCliente(Raiz->Ramas->ObtenerRama(I-1), _Numero, _existe);

            I++;
        }
    }

}


void ArbolClientes::agregarCompra(ApuntadorPagina Raiz, int _codCliente) {
    if(Raiz == NULL){
        return;
    }
    else{
        int I = 1;
        while(I <= Raiz->cuenta){

            pNodoCliente Recorrido = Raiz->Claves->ObtenerApuntadorClave(I);

            if (Recorrido->getID() == _codCliente){
                Recorrido->aumentarVentas();
            }

            agregarCompra(Raiz->Ramas->ObtenerRama(I-1),_codCliente);

            I++;
        }
    }

}


void ArbolClientes::getClienteMasCompras(ApuntadorPagina Raiz, NodoCliente *&_clienteMasCompras) {
    if(Raiz == NULL){
        return;
    }
    else{
        int I = 1;
        while(I <= Raiz->cuenta){

            pNodoCliente Recorrido = Raiz->Claves->ObtenerApuntadorClave(I);

            if (Recorrido->cantidadDeCompras > _clienteMasCompras->cantidadDeCompras) _clienteMasCompras = Recorrido;
            getClienteMasCompras(Raiz->Ramas->ObtenerRama(I-1),_clienteMasCompras);

            I++;
        }
    }

}

void ArbolClientes::getCliente(ApuntadorPagina Raiz, NodoCliente *&_cliente, int _id) {
    if(Raiz == NULL){
        return;
    }
    else{
        int I = 1;
        while(I <= Raiz->cuenta){

            pNodoCliente Recorrido = Raiz->Claves->ObtenerApuntadorClave(I);

            if (Recorrido->getID() == _id) _cliente = Recorrido;
            getCliente(Raiz->Ramas->ObtenerRama(I-1), _cliente, _id);

            I++;
        }
    }
}

void ArbolClientes::PreordenSocket(ApuntadorPagina _raiz, std::string &_string) {
    if(_raiz == NULL){
        return;
    }
    else{
        int I = 1;
        while(I <= _raiz->cuenta){

            pNodoCliente Recorrido = _raiz->Claves->ObtenerApuntadorClave(I);
            std::stringstream flujo;
            flujo << Recorrido->getID();
            std::string nombre = flujo.str();
            _string += nombre + "\n";
            PreordenSocket(_raiz->Ramas->ObtenerRama(I-1), _string);
            I++;
        }
    }

}

void ArbolClientes::BuscarNodo(int Clave, ApuntadorPagina P, bool & Encontrado, int & K)
{
// Este método examina la pagina referenciada por P. De no //encontrarse el valor nuevo, K será el índice de la rama por //donde bajar

    {
        int C =  P->Claves->ObtenerApuntadorClave(1)->getID();
        if (Clave < C)   // recuerde que los arreglos aquí inician en 1
        {
            //P->K = 0;
            //P->Esta = 0;
            Encontrado=false;
            K=0; //rama por donde descender
        }
        else
        {
            //Examina claves de la pagina
            K=P->cuenta; // Numero de claves de la Pagina
            while(Clave<P->Claves->ObtenerApuntadorClave(K)->getID() and (K>1))
            {
                K=K-1;
            }

            if (Clave==P->Claves->ObtenerApuntadorClave(K)->getID()){
                Encontrado=true;
            }

        }
    }
}


//Tiene como funcion devolver la nueva raiz si la raiz inicial se ha quedado sin claves
void ArbolClientes::Eliminar (int C1, ApuntadorPagina Raiz){

    bool Encontrado;
    ApuntadorPagina P;
    {
        EliminarRegistro(C1,Raiz,Encontrado);
        if (!Encontrado){
            std::cout<< "El elemento no se encuentra en el árbol"<<std::endl;
        }

        else{

            if (Raiz->cuenta == 0) // la raíz ha quedado vacia
            {
                P= Raiz;
                Raiz= Raiz->Ramas->ObtenerRama(0);
                delete(P);
            }
        }
    }
}



//Este metodo controla el proceso de borrado de una clave
//Primero busca en el nodo donde se encuentra la clave a eliminar
//Si es una hoja, llama a elimina
// Si no es hoja, se busca el sucesor inmediato, se coloca en el elemento a eliminar
//Luego se suprime el sucesor  en la hoja
void ArbolClientes::EliminarRegistro(int C1, ApuntadorPagina Raiz, bool & Encontrado)
{
    int K;

    if (BVacio())
        Encontrado= false; // se ha llegado debajo de una hoja, la clave no esta en el arbol
    else
    {
        //with Raiz
        {
            BuscarNodo(C1,Raiz,Encontrado,K);
            if (Encontrado)
            {
                if (Raiz->Ramas->ObtenerRama(K-1)==NULL)//Las ramas estan indexadas desde 0 a Max, por lo que este nodo es hoja
                {
                    Quitar(Raiz,K);
                    std::cout<<"Despues de Quitar: " << Raiz->Claves->ObtenerApuntadorClave(1)->getID()<<std::endl;

                }
                else //No es hoja
                {
                    Sucesor(Raiz,K); //reemplaza  Claves[K] por su sucesor
                    EliminarRegistro(Raiz->Claves->ObtenerApuntadorClave(K)->getID(), Raiz->Ramas->ObtenerRama(K),Encontrado);  //Elimina la clave sucesora en su nodo
                    if (!Encontrado) //inconsistencia debe esta en el nodo
                    {std::cout << "Error en el proceso"<<std::endl;}
                }
            }
            else // No ha sido localizada la clave
            {
                EliminarRegistro (C1,Raiz->Ramas->arregloRamas[K],Encontrado);
                // Las llamadas recursivas retornan el control a este punto,
                // se comprueba que el nodo hijo mantenga un numero
                // claves igual o mayor que el minimo necesario
                if (Raiz->Ramas->ObtenerRama(K) !=NULL){

                    if (Raiz->Ramas->ObtenerRama(K)->cuenta<5){

                        Restablecer(Raiz,K);
                    }
                }
            }
        }
    }
}



//recibe la direccion del nodo y la posicion de la clave a eliminar.
//Elimina la clave junto con la rama que le corresponde
void ArbolClientes::Quitar(ApuntadorPagina & P, int& K)
{
    int J; //entero
    //With P

    {
        for (J= K+1;J <= P->cuenta; J++)
        {
            //	P->Claves->ObtenerApuntadorClave(J) = P->Claves->ObtenerApuntadorClave(J-1);

            //P->Claves[J-1] = P->Claves[J];
            //P->Claves[J-1].ObtenerClave(0);
            //	P->Ramas[J-1] =  P->Ramas[J];

//	cout<<	"DAAAAAAAAAAAAAAAAH: "<<P->Claves->ObtenerApuntadorClave(J)->valorCl->getCedula()<<endl;


            //	nodo* temp = P->Claves->ObtenerApuntadorClave(J);
            P->Claves->arregloClaves[J-1] = P->Claves->ObtenerApuntadorClave(J);
            //	nodo* temp2 = P->Claves->ObtenerApuntadorClave(J-1);
            //   temp2 = temp;   //Desplaza una posicion a la izquierda, con ello elimina la clave}

            //    cout<<temp2->valorCl->getCedula()<<endl;
            //delete (temp);

            P->Ramas->arregloRamas[J-1] = P->Ramas->ObtenerRama(J);
            //   ApuntadorPagina temp3 = P->Ramas->ObtenerRama(J);
            //     ApuntadorPagina temp4 = P->Ramas->ObtenerRama(J-1);
            //   temp4 = temp3;

        }
        P->cuenta=(P->cuenta)-1;
    }

}


//Busca la clave inmediatamente sucesor de la clave k y reemplaza la clave K
void ArbolClientes::Sucesor(ApuntadorPagina P, int& K)
{
    ApuntadorPagina Q;

    Q = P->Ramas->ObtenerRama(K);

    while (Q->Ramas->ObtenerRama(0) != NULL){
        Q = Q->Ramas->ObtenerRama(0);
    }

    P->Claves[K] = Q->Claves[1];
}



//Este realiza las acciones mas complejas del proceso. Restaura el nodo P.Ramas[K]
//el cual ha quedado con un numero menor de claves, menos que el minimo
void ArbolClientes::Restablecer (ApuntadorPagina P, int& K)
{
    if (K>0)   //Tiene hermano izquierdo
    {
        if (P->Ramas->ObtenerRama(K-1)->cuenta > 5) //Tiene mas claves que el minimo y por tanto puede desplazarse una clave
        {
            MoverDerecha(P,K);
        }
        else
        {
            Combina(P,K);
        }
    }
    else
    {//solo tiene hermano derecho
        if (P->Ramas->ObtenerRama(1)->cuenta > 5)
        {
            //Tiene mas claves que el minimo
            int int_temp = 1;
            MoverIzquierda(P, int_temp);
        }
        else{
            int int_temp = 1;
            Combina(P, int_temp);
        }
    }
}




//Mueve una clave del nodo antecedente(P) al nodo que se esta restaurando
//Asciende la clave mayor del hermano izquierdo al nodo antecedente
void ArbolClientes::MoverDerecha(ApuntadorPagina P, int& K)
//En este metodo se deja hueco en el nodo P.Ramas[K] que es el nodo que tiene menos claves que elminimo
//necesario, inserta la clave k del nodo antecedente y a su vez asciende la clave mayor ( la mas a la derecha)
//del hermano izquierdo
{
    int J;
    //with P.Ramas[K]
    {
        for (J= P->Ramas->ObtenerRama(K)->cuenta; J>=1; J--)
        {
            P->Ramas->ObtenerRama(K)->Claves[J+1]= P->Ramas->ObtenerRama(K)->Claves[J];
            P->Ramas->ObtenerRama(K)->Ramas[J+1]=P->Ramas->ObtenerRama(K)->Ramas[J];
        }
        P->Ramas->ObtenerRama(K)->cuenta=J= P->Ramas->ObtenerRama(K)->cuenta+1;
        P->Ramas->ObtenerRama(K)->Ramas[1] = P->Ramas->ObtenerRama(K)->Ramas[0];
        P->Ramas->ObtenerRama(K)->Claves[1] = P->Claves[K]; // baja la clave del nodo padre
    }
    //Ahora sube la clave desde el hermano izquierdo al nodo padre, para reemplazar la que bajo
    //with P.Ramas[K-1] // hermano izquierdo
    {
        P->Claves[K]=P->Ramas->ObtenerRama(K-1)->Claves[P->Ramas->ObtenerRama(K-1)->cuenta];
        P->Ramas->ObtenerRama(K)->Ramas[0] = P->Ramas->ObtenerRama(K-1)->Ramas[P->Ramas->ObtenerRama(K-1)->cuenta];
        P->Ramas->ObtenerRama(K-1)->cuenta = P->Ramas->ObtenerRama(K-1)->cuenta-1;
    }
}




//Ahora la clave que asciende al nodo antecedente es la clave menor(izquierda) del nodo a restaurar
void ArbolClientes::MoverIzquierda (ApuntadorPagina P, int& K)
{
    int J;
    //with P.Ramas[K-1]// es el nodo con menos claves que el minimo
    {
        P->Ramas->ObtenerRama(K-1)->cuenta=P->Ramas->ObtenerRama(K-1)->cuenta+1;
        P->Ramas->ObtenerRama(K-1)->Claves[P->Ramas->ObtenerRama(K-1)->cuenta]=P->Claves[K];
        P->Ramas->ObtenerRama(K-1)->Ramas[P->Ramas->ObtenerRama(K-1)->cuenta]=P->Ramas->ObtenerRama(K)->Ramas[0];
        // baja la clave del nodo padre
    }
    //with P.Ramas[K] // hermano derecho
    {
        P->Claves[K]=P->Ramas->ObtenerRama(K)->Claves[1];   //sube al nodo padre de la clave 1 del hermano derecho, sustituye a la que bajo
        P->Ramas[0]=P->Ramas->ObtenerRama(K)->Ramas[1];
        P->Ramas->ObtenerRama(K)->cuenta=P->Ramas->ObtenerRama(K)->cuenta-1;

        for (J=1; J<=P->Ramas->ObtenerRama(K)->cuenta; J++)
        {
            P->Ramas->ObtenerRama(K)->Claves[J]= P->Ramas->ObtenerRama(K)->Claves[J+1];
            P->Ramas->ObtenerRama(K)->Ramas[J] = P->Ramas->ObtenerRama(K)->Ramas[J+1];
        }
    }
}



//Este metodo forma un solo nodo
//Combina el nodo que esta en la rama K con el que esta en la rama k-1 y la clave mediana de ambos
// que se encuentra en el nodo ascendente.
void ArbolClientes::Combina(ApuntadorPagina P, int& K)
//forma un nuevo nodo con el hermano izquierdo la mediana ente el nodo problema y el hermano izquierdo
//situado en el nodo padre y las claves del nodo problema.
{
    int J;
    ApuntadorPagina Q;
    Q = P->Ramas->ObtenerRama(K);

    //with P.Ramas[K-1]//hermano izquierdo
    {
        P->Ramas->ObtenerRama(K-1)->cuenta = P->Ramas->ObtenerRama(K-1)->cuenta+1;
        P->Ramas->ObtenerRama(K-1)->Claves[P->Ramas->ObtenerRama(K-1)->cuenta]=P->Claves[K];// baja clave mediana desde el nodo padre
        P->Ramas->ObtenerRama(K-1)->Ramas[P->Ramas->ObtenerRama(K-1)->cuenta] = Q->Ramas[0];

        for (J=1; J<= Q->cuenta; J++)
        {
            P->Ramas->ObtenerRama(K-1)->cuenta = P->Ramas->ObtenerRama(K-1)->cuenta+1;
            P->Ramas->ObtenerRama(K-1)->Claves[P->Ramas->ObtenerRama(K-1)->cuenta] = Q->Claves[J];
            P->Ramas->ObtenerRama(K-1)->Ramas[P->Ramas->ObtenerRama(K-1)->cuenta] = Q->Ramas[J];
        }
    }
    //Reajustadas las claves y ramas del nodo padre debido a que antes ascendio la clave K
    //with P

    for (J=K; J<= P->Ramas->ObtenerRama(K-1)->cuenta-1; J++)
    {
        P->Claves[J]=P->Claves[J+1];
        P->Ramas[J]=P->Ramas[J+1];
    }
    P->cuenta=P->cuenta-1;

    delete(Q);
}
