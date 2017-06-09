#include "dialogconsulta.h"
#include "ui_dialogconsulta.h"

DialogConsulta::DialogConsulta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConsulta)
{
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);
}

DialogConsulta::~DialogConsulta()
{
    delete ui;
}


void DialogConsulta::on_buttonBox_accepted()
{

    this->close();

    /*
    std::string itemCombo = ui->comboBox->currentText().toStdString();
    if (itemCombo == "PMV") {
        client->writeSocket("PMV");
        client->readSocket();
        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);


    }else if (itemCombo == "PQMV") {
        client->writeSocket("PQMV");
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
        client->writeSocket("PCSS");
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

    }else if (itemCombo == "CMC") {
        client->writeSocket("CMC");
        client->readSocket();
        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);

    }else if (itemCombo == "LQMV") {
        client->writeSocket("LQMV");
        client->readSocket();
        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);

    } else if (itemCombo == "CMV") {
        client->writeSocket("CMV");
        client->readSocket();

        std::string res = "";

        string codL,codS;
        codL = ui->lineEdit->text().toStdString();
        codS = ui->lineEdit_3->text().toStdString();

        res += codL + ";" + codS;

        client->writeSocket(res);
        client->readSocket();

        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);

    }else if (itemCombo == "SMV") {
        client->writeSocket("SMV");
        client->readSocket();

        std::string res = "";

        string codL;
        codL = ui->lineEdit->text().toStdString();

        res += codL;

        client->writeSocket(res);
        client->readSocket();

        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);

    }
    */
}

void DialogConsulta::on_pushButton_clicked()
{

    std::string itemCombo = ui->comboBox->currentText().toStdString();
    if (itemCombo == "PMV") {
        client->writeSocket("PMV");
        client->readSocket();
        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);


    }else if (itemCombo == "PQMV") {
        client->writeSocket("PQMV");
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
        client->writeSocket("PCSS");
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

    }else if (itemCombo == "CMC") {
        client->writeSocket("CMC");
        client->readSocket();
        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);

    }else if (itemCombo == "LQMV") {
        client->writeSocket("LQMV");
        client->readSocket();
        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);

    } else if (itemCombo == "CMV") {
        client->writeSocket("CMV");
        client->readSocket();

        std::string res = "";

        string codL,codS;
        codL = ui->lineEdit->text().toStdString();
        codS = ui->lineEdit_3->text().toStdString();

        res += codL + ";" + codS;

        client->writeSocket(res);
        client->readSocket();

        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);

    }else if (itemCombo == "SMV") {
        client->writeSocket("SMV");
        client->readSocket();

        std::string res = "";

        string codL;
        codL = ui->lineEdit->text().toStdString();

        res += codL;

        client->writeSocket(res);
        client->readSocket();

        std::string infoInSocket (client->buffer);
        QString str = QString::fromUtf8(infoInSocket.c_str());
        ui->plainTextEdit->insertPlainText(str);
        ui->plainTextEdit->setReadOnly(true);

    }
}
