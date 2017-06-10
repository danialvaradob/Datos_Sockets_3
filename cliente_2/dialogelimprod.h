#ifndef DIALOGELIMPROD_H
#define DIALOGELIMPROD_H
#include "socketclient.h"
#include <QDialog>

namespace Ui {
class DialogElimProd;
}

class DialogElimProd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogElimProd(QWidget *parent = 0);
    ~DialogElimProd();

    SocketClient *client;
    void setClient(SocketClient* _cliente) {client = _cliente;}


private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogElimProd *ui;
};

#endif // DIALOGELIMPROD_H
