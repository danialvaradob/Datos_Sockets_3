#include "dialoggrafos.h"
#include "ui_dialoggrafos.h"

DialogGrafos::DialogGrafos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGrafos)
{
    ui->setupUi(this);
}

DialogGrafos::~DialogGrafos()
{
    delete ui;
}
