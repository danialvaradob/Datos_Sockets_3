#ifndef DIALOGGRAFOS_H
#define DIALOGGRAFOS_H

#include <QDialog>

namespace Ui {
class DialogGrafos;
}

class DialogGrafos : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGrafos(QWidget *parent = 0);
    ~DialogGrafos();

private:
    Ui::DialogGrafos *ui;
};

#endif // DIALOGGRAFOS_H
