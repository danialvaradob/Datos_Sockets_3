#include "dialogclientenuevo.h"
#include "ui_dialogclientenuevo.h"

DialogClienteNuevo::DialogClienteNuevo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogClienteNuevo)
{
    ui->setupUi(this);
}

DialogClienteNuevo::~DialogClienteNuevo()
{
    delete ui;
}

void DialogClienteNuevo::on_buttonBox_accepted()
{
    buff = "";
    std::string nombre,direccion,telefono;
    nombre = ui->lineEdit->text().toStdString();
    direccion = ui->lineEdit_2->text().toStdString();
    telefono = ui->lineEdit_3->text().toStdString();

    buff += nombre + ";" + direccion + ";" + telefono;

}
