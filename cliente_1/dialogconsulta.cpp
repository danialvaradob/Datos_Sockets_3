#include "dialogconsulta.h"
#include "ui_dialogconsulta.h"

DialogConsulta::DialogConsulta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConsulta)
{
    ui->setupUi(this);
}

DialogConsulta::~DialogConsulta()
{
    delete ui;
}



void DialogConsulta::on_buttonBox_clicked(QAbstractButton *button)
{

    std::string itemCombo = ui->comboBox->itemText();
    if (itemCombo == "PMV") {
        client->writeSocket("PMV");
        client->readSocket();
        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);


    }else if (itemCombo == "PQMV") {
        client->writeSocket("CMC");
        client->readSocket();

        std::string res = "";

        string codL,codC,codS;
        codL = ui->lineEdit->text().toStdString();
        codC = ui->lineEdit_2->text().toStdString();
        codS = ui->lineEdit_3->text().toStdString();

        res += codL + ";" + codS + ";" + codC;

        client->writeSocket(res);
        client->readSocket();

        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);


    }else if (itemCombo == "PCSS") {

    }else if (itemCombo == "CMC") {
        client->writeSocket("CMC");
        client->readSocket();
        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);

    }else if (itemCombo == "LQMV") {

    } else if (itemCombo == "CMC") {

    }

}
