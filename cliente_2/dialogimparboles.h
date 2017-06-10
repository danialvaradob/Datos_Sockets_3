#ifndef DIALOGIMPARBOLES_H
#define DIALOGIMPARBOLES_H

#include <QDialog>
#include "socketclient.h"

namespace Ui {
class DialogImpArboles;
}

class DialogImpArboles : public QDialog
{
    Q_OBJECT

public:
    explicit DialogImpArboles(QWidget *parent = 0);
    ~DialogImpArboles();

    SocketClient *client;
    void setClient(SocketClient* _cliente) {client = _cliente;}

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogImpArboles *ui;
};

#endif // DIALOGIMPARBOLES_H
