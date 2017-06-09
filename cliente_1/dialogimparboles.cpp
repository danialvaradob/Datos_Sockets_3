#include "dialogimparboles.h"
#include "ui_dialogimparboles.h"

DialogImpArboles::DialogImpArboles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImpArboles)
{
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);
}

DialogImpArboles::~DialogImpArboles()
{
    delete ui;
}

void DialogImpArboles::on_comboBox_activated(const QString &arg1)
{

}

void DialogImpArboles::on_buttonBox_accepted()
{
    std::string itemCombo = ui->comboBox->currentText().toStdString();
    if (itemCombo == "Proveedores") {
        client->writeSocket("Proveedores");
        client->readSocket();
        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);
    }

    else if (itemCombo == "Categorias"){
        client->writeSocket("Categorias");
        client->readSocket();

        std::string res = "";

        string codL,codC,codS;
        codL = ui->lineEdit_4->text().toStdString();
        //codC = ui->lineEdit_2->text().toStdString();
        codS = ui->lineEdit_3->text().toStdString();

        res += codL + ";" + codS;

        client->writeSocket(res);
        client->readSocket();

        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);
    }

    else if (itemCombo == "Productos"){
            client->writeSocket("Productos");
            client->readSocket();

            std::string res = "";

            string codL,codC,codS;
            codL = ui->lineEdit_4->text().toStdString();
            codC = ui->lineEdit_2->text().toStdString();
            codS = ui->lineEdit_3->text().toStdString();

            res += codL + ";" + codS + ";" + codC;

            client->writeSocket(res);
            client->readSocket();

            std::string infoInSocket (client->buffer);
            QString str = QString::fromUtf8(infoInSocket.c_str());
            ui->plainTextEdit->insertPlainText(str);
            ui->plainTextEdit->setReadOnly(true);
        }

    else if (itemCombo == "Clientes"){
            client->writeSocket("Clientes");
            client->readSocket();

            //std::string res = "";

           // string codL,codC,codS;
            //codL = ui->lineEdit_4->text().toStdString();
           // codC = ui->lineEdit_2->text().toStdString();
            //codS = ui->lineEdit_3->text().toStdString();

            res += codL + ";" + codS + ";" + codC; //No habria que mandar codigos
            //pero no se si aca hace falta mandarle algo para que funciones el server

            client->writeSocket(res);///////
            client->readSocket();

            std::string infoInSocket (client->buffer);
            QString str = QString::fromUtf8(infoInSocket.c_str());
            ui->plainTextEdit->insertPlainText(str);
            ui->plainTextEdit->setReadOnly(true);
        }

    else if (itemCombo == "Supermercados"){
            client->writeSocket("Supermercados");
            client->readSocket();

            std::string res = "";

            string codL,codC,codS;
            codL = ui->lineEdit_4->text().toStdString();
           // codC = ui->lineEdit_2->text().toStdString();
            //codS = ui->lineEdit_3->text().toStdString();

            res += codL;

            client->writeSocket(res);///////
            client->readSocket();

            std::string infoInSocket (client->buffer);
            QString str = QString::fromUtf8(infoInSocket.c_str());
            ui->plainTextEdit->insertPlainText(str);
            ui->plainTextEdit->setReadOnly(true);
        }

}
