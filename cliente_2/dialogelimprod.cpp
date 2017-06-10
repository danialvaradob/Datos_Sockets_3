#include "dialogelimprod.h"
#include "ui_dialogelimprod.h"
#include <QMessageBox>

DialogElimProd::DialogElimProd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogElimProd)
{
    ui->setupUi(this);
}

DialogElimProd::~DialogElimProd()
{
    delete ui;
}

void DialogElimProd::on_pushButton_clicked()
{
    std::string buff = "";
    std::string codL,codS,codC,codP,codProveedor,cantidad;


    codL = ui->lineEditLugar->text().toStdString();
    codS = ui->lineEditSuper->text().toStdString();
    codC = ui->lineEditCat->text().toStdString();
    codP = ui->lineEdit_3->text().toStdString();

    buff += "ELIMINAR_ARTICULO";
    buff += ";" + codL + ";" + codS + ";" + codC + ";" + codP + ";" + cantidad + ";" + codProveedor;


    client->writeSocket(buff);
    client->readSocket();

    std::string tester(client->buffer);
    if (tester == "REALIZADA") {

        char message[] = "PRODUCTO ELIMINADO";
        QMessageBox::about(this,tr(message),tr(message));
        ui->lineEditLugar->setText("");
        ui->lineEditSuper->setText("");
        ui->lineEditCat->setText("");
        ui->lineEdit_3->setText("");

    } else {
        char message[] = "PRODUCTO NO FUE ELIMINADO";
        QMessageBox::about(this,tr(message),tr(message));
    }

}
