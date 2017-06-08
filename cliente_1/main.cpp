#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <cstdlib>
#include <pthread.h>

int const NUM_THREADS = 1;
//int const TAMANHO_BUFFER = 301;
static int listenFd;
static std::string message_to_server;
SocketClient* client;

/*
struct thread_data{
    int thread_id;
    char *message;
}

void* qtAppTest(void *ptr) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}
*/
//TEST for threads
void* test(void *ptr) {

    for (int i = 0; i < 10 ;i++) {
        std::cout << std::to_string(i) << std::endl;

    }
}

/*
void * respondingServer(void *ptr) {
    for(;;)
    {
        //cin.clear();
        //cin.ignore(256, '\n');
        cout << "Enter stuff: ";

       // bzero(buffer, TAMANHO_BUFFER);
        client->emptyBuffer();
        //fgets(buffer,TAMANHO_BUFFER,stdin);
        //fgets(buffer,TAMANHO_BUFFER,message_to_server);
        client->fillBuffer(message_to_server);

        if(( memcmp( client->buffer, "END", strlen( "END"))) == 0 )
                {break;}

        //cin.getline(buffer, TAMANHO_BUFFER);

        //write(listenFd, buffer, strlen(buffer));
        client->writeSocket();

        //bzero(buffer, TAMANHO_BUFFER);
        client->emptyBuffer();

        //read(listenFd,buffer,TAMANHO_BUFFER-1);
        client->readSocket();

    }
}
*/



int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    //struct thread_data td[NUM_THREADS];
    int rc,i;

    char host[] = "127.0.0.1";
    int portNo = 8889;
    SocketClient* client = new SocketClient(listenFd,host,portNo);

    QApplication a(argc, argv);
    MainWindow* w = new MainWindow(client);
    w->show();

    //rc = pthread_create(&threads[0],NULL,test,NULL);
    //i = pthread_create(&threads[1],NULL,qtAppTest,NULL);
    //rc = pthread_create(&threads[0],NULL,respondingServer,NULL);

    return a.exec();


/*
 *
 *         int neverUsedVariable;
        pthread_create(&threadA[noThread], NULL, task1, NULL);

        noThread++;
    }

    for(int i = 0; i < 3; i++) {
        pthread_join(threadA[i], NULL);
 *
 *
*/


}


