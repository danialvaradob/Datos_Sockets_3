#include "dialogcompra.h"
#include "ui_dialogcompra.h"
#include "dialogclientenuevo.h"
#include <QMessageBox>

dialogCompra::dialogCompra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogCompra)
{

    ui->setupUi(this);
    ui->lugarLine->setDisabled(true);
    ui->catLine->setDisabled(true);
    ui->productoLine->setDisabled(true);
    ui->superLine->setDisabled(true);

}

dialogCompra::~dialogCompra()
{
    delete ui;
}

void dialogCompra::on_buttonBox_accepted()
{
    buff = "";
    std::string codL,codS,codC,codP;
    buff += "v;";
    codL = ui->lugarLine->text().toStdString();
    codS = ui->superLine->text().toStdString();
    codC = ui->catLine->text().toStdString();
    codP = ui->productoLine->text().toStdString();
    buff += codCliente + ";" + codL + ";" + codS + ";" + codC + ";" + codP;


}


void dialogCompra::setCliente(SocketClient *_client){
    client = _client;

}


void dialogCompra::on_OkClient_clicked()
{

    buff = "";
    std::string _codCliente;
    _codCliente= ui->lineEditClient->text().toStdString();

    client->writeSocket("CLIENTE");
    client->readSocket();

    //Envia la propuesta al servidor, donde este esta esperando esto
    client->writeSocket(codCliente);
    client->readSocket();


    std::string lecturaBuffer (client->buffer);
    std::string infoclientenuevo;

   codCliente = _codCliente;

    if (lecturaBuffer == "CLIENTE_EXISTE") {
        char message[] = "CLIENTE EXISTE";
        QMessageBox::about(this,tr("Compra"),tr(message));
    } else {

        DialogClienteNuevo clienteNuevoDialog;
        clienteNuevoDialog.setModal(true);
        clienteNuevoDialog.exec();

        std::string infoclientenuevo = codCliente + ";" + clienteNuevoDialog.getInfo();


        client->writeSocket(infoclientenuevo);
        client->readSocket();
        char message[] = "CLIENTE CREADO";
        QMessageBox::about(this,tr("Compra"),tr(message));


    }

    ui->lugarLine->setDisabled(false);
    ui->catLine->setDisabled(false);
    ui->productoLine->setDisabled(false);
    ui->superLine->setDisabled(false);
}

