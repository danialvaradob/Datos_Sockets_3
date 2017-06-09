#include "dialogimparboles.h"
#include "ui_dialogimparboles.h"

DialogImpArboles::DialogImpArboles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImpArboles)
{
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);
}

DialogImpArboles::~DialogImpArboles()
{
    delete ui;
}
