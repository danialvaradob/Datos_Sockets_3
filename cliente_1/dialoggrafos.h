#ifndef DIALOGGRAFOS_H
#define DIALOGGRAFOS_H

#include <QDialog>
#include "socketclient.h"
namespace Ui {
class DialogGrafos;
}

class DialogGrafos : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGrafos(QWidget *parent = 0);
    ~DialogGrafos();

    SocketClient* client;
    void setClient(SocketClient* _client) {client = _client;}

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogGrafos *ui;
};

#endif // DIALOGGRAFOS_H
