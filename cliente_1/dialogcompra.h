#ifndef DIALOGCOMPRA_H
#define DIALOGCOMPRA_H
#include <iostream>
#include <QDialog>

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

    std::string getInfo() {return buff;}

    Ui::dialogCompra *ui;
private slots:
    void on_buttonBox_accepted();
};

#endif // DIALOGCOMPRA_H
