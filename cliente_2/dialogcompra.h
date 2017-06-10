#ifndef DIALOGCOMPRA_H
#define DIALOGCOMPRA_H
#include <QDialog>
#include "socketclient.h"
namespace Ui {
class dialogCompra;
}

class dialogCompra : public QDialog
{
    Q_OBJECT

public:
    explicit dialogCompra(QWidget *parent = 0);
    ~dialogCompra();

    std::string buff;
    std::string codCliente;


    SocketClient* client;

    std::string getInfo() {return buff;}

    void setCliente(SocketClient* _client);
    Ui::dialogCompra *ui;
private slots:
    void on_buttonBox_accepted();
    void on_OkClient_clicked();
};

#endif // DIALOGCOMPRA_H
