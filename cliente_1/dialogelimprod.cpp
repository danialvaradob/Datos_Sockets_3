#include "dialogelimprod.h"
#include "ui_dialogelimprod.h"

DialogElimProd::DialogElimProd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogElimProd)
{
    ui->setupUi(this);
}

DialogElimProd::~DialogElimProd()
{
    delete ui;
}
