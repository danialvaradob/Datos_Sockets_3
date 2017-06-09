#include "dialoggrafos.h"
#include "ui_dialoggrafos.h"

DialogGrafos::DialogGrafos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGrafos)
{
    ui->setupUi(this);
}

DialogGrafos::~DialogGrafos()
{
    delete ui;
}

void DialogGrafos::on_buttonBox_accepted()
{
    this->close();
    /*
    std::string lineaCombo = ui->comboBox->currentText().toStdString() +
            ";" + ui->lineEdit->text().toStdString();
    
    client->writeSocket(lineaCombo);
    client->readSocket();


    std::string infoInSocket (client->buffer);

    QString str = QString::fromUtf8(infoInSocket.c_str());

    ui->plainTextEdit->insertPlainText(str);
    ui->plainTextEdit->setReadOnly(true);
    */

}

void DialogGrafos::on_pushButton_clicked()
{
    std::string lineaCombo = ui->comboBox->currentText().toStdString() +
            ";" + ui->lineEdit->text().toStdString();

    client->writeSocket(lineaCombo);
    client->readSocket();


    std::string infoInSocket (client->buffer);

    QString str = QString::fromUtf8(infoInSocket.c_str());

    ui->plainTextEdit->insertPlainText(str);
    ui->plainTextEdit->setReadOnly(true);

}
