#include "socketclient.h"




SocketClient::SocketClient(int _listenFd, char* host, int portNo)    {



    //portNo = 8888;
    //create client skt

    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    _listenFd = listenFd;
    if(listenFd < 0)
    {
        cerr << "Cannot open socket" << endl;
        //return 0;
    }
    server = gethostbyname(host);
    if(server == NULL)
    {
        cerr << "Host does not exist" << endl;
        //return 0;
    }

    bzero((char *) &svrAdd, sizeof(svrAdd));
    svrAdd.sin_family = AF_INET;

    bcopy((char *) server -> h_addr, (char *) &svrAdd.sin_addr.s_addr, server -> h_length);

    svrAdd.sin_port = htons(portNo);

    checker = connect(listenFd,(struct sockaddr *) &svrAdd, sizeof(svrAdd));

    if (checker < 0)
    {
        cerr << "Cannot connect!" << endl;
        //return 0;
    }

    //send stuff to server
    /*
    for(;;)
    {

        //cin.clear();
        //cin.ignore(256, '\n');
        cout << "Enter stuff: ";
        bzero(buffer, TAMANHO_BUFFER);
        fgets(buffer,TAMANHO_BUFFER,stdin);

        //cin.getline(buffer, TAMANHO_BUFFER);

        write(listenFd, buffer, strlen(buffer));

        bzero(buffer, TAMANHO_BUFFER);
        read(listenFd,buffer,TAMANHO_BUFFER-1);
    }
    */
    writeSocket("CLIENTE_1");
    readSocket();

}

void SocketClient::writeSocket(std::string _message) {



    //std::vector<char> v(_message.begin(), _message.end());
    //v.push_back('\0'); // Make sure we are null-terminated
    //char* msg = &v[0];
    write(listenFd,_message.c_str() , strlen(_message.c_str()));
}

void SocketClient::readSocket() {

    //emptyBuffer();
    bzero(buffer,TAMANO_BUFFER);
    int n = read(listenFd, buffer, TAMANO_BUFFER - 1);


}

void SocketClient::emptyBuffer() {
    bzero(buffer,TAMANO_BUFFER);
}

void SocketClient::fillBuffer(string _message) {
    //fgets(buffer,TAMANHO_BUFFER,_message);

}
