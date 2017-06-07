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

    client->readSocket();

    std::string infoInSocket (client->buffer);

    QString str = QString::fromUtf8(infoInSocket.c_str());

    ui->plainTextEdit->insertPlainText(str);
    ui->plainTextEdit->setReadOnly(true);


}
