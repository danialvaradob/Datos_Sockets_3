#ifndef DIALOGCONSULTA_H
#define DIALOGCONSULTA_H

#include <QDialog>
#include "socketclient.h"

namespace Ui {
class DialogConsulta;
}

class DialogConsulta : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConsulta(QWidget *parent = 0);
    ~DialogConsulta();

    SocketClient *client;
    void setClient(SocketClient* _cliente) {client = _cliente;}

private slots:



    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::DialogConsulta *ui;
};

#endif // DIALOGCONSULTA_H
