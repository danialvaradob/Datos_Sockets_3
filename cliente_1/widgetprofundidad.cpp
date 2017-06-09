#include "widgetprofundidad.h"
#include "ui_widgetprofundidad.h"

WidgetProfundidad::WidgetProfundidad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WidgetProfundidad)
{
    ui->setupUi(this);

}

WidgetProfundidad::~WidgetProfundidad()
{
    delete ui;
}

void WidgetProfundidad::setCliente(SocketClient *_client) {
    client = _client;

    /*
    client->readSocket();

    std::string infoInSocket (client->buffer);

    QString str = QString::fromUtf8(infoInSocket.c_str());

    ui->plainTextEdit->insertPlainText(str);
    ui->plainTextEdit->setReadOnly(true);
    */


}

void WidgetProfundidad::on_buttonBox_accepted()
{
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

void WidgetProfundidad::on_pushButton_clicked()
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
