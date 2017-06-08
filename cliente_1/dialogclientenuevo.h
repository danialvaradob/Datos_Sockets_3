#ifndef DIALOGCLIENTENUEVO_H
#define DIALOGCLIENTENUEVO_H

#include <QDialog>

namespace Ui {
class DialogClienteNuevo;
}

class DialogClienteNuevo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogClienteNuevo(QWidget *parent = 0);
    ~DialogClienteNuevo();
    std::string buff;
    std::string getInfo() {return buff;}

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogClienteNuevo *ui;
};

#endif // DIALOGCLIENTENUEVO_H
