#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogcompra.h"
#include "widgetprofundidad.h"
#include <QMessageBox>



MainWindow::MainWindow( SocketClient* _server ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    //_server = SocketUtility{Server, Port}
    client = _server;
    //client->readSocket();
    //printf(client->buffer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    dialogCompra compraDialog;
    compraDialog.setModal(true);
    compraDialog.exec(); //show the dialog when button is pressed

    //std::cout << compraDialog.getInfo() << std::endl;

    //SocketUtility.sendToServer()


    //O PUEDE HACERSE ASI
    //... se pone un atributo en MainWindow, en el header, que se llama comprarDialog compra;
    client->writeSocket(compraDialog.getInfo());
    client->readSocket();


    string lecturaSocket (client->buffer);
    if (lecturaSocket == "V_REALIZADA") {
        char message[] = "VENTA REALIZADA";
        QMessageBox::about(this,tr("Compra"),tr(message));
    } else {
        char message[] = "VENTA NO REALIZADA, por favor verifique los codigos";
        QMessageBox::about(this,tr("Compra"),tr(message));
    }





}
//BOTON DE PROFUNDIDAD
void MainWindow::on_pushButton_2_clicked()
{

    client->writeSocket("PROFUNDIDAD");

    WidgetProfundidad widgetProfundidad;
    widgetProfundidad.setModal(true);
    widgetProfundidad.setCliente(client);
    widgetProfundidad.exec(); //show the dialog when button is pressed




}
