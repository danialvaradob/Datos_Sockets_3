#ifndef WIDGETPROFUNDIDAD_H
#define WIDGETPROFUNDIDAD_H
#include "socketclient.h"
#include <QDialog>

namespace Ui {
class WidgetProfundidad;
}

class WidgetProfundidad : public QDialog
{
    Q_OBJECT

public:
    explicit WidgetProfundidad(QWidget *parent = 0);
    ~WidgetProfundidad();

    SocketClient* client;
    void setCliente(SocketClient *_client);



private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::WidgetProfundidad *ui;
};

#endif // WIDGETPROFUNDIDAD_H
