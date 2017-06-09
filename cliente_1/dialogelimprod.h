#ifndef DIALOGELIMPROD_H
#define DIALOGELIMPROD_H

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

private:
    Ui::DialogElimProd *ui;
};

#endif // DIALOGELIMPROD_H
