#include "dialogcompra.h"
#include "ui_dialogcompra.h"

dialogCompra::dialogCompra(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogCompra)
{
    ui->setupUi(this);

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
    buff += codL + ";" + codS + ";" + codC + ";" + codP;


}

