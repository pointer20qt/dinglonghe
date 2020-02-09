#ifndef ZHUCHE_H
#define ZHUCHE_H

#include <QWidget>

namespace Ui {
class zhuche;
}

class zhuche : public QWidget
{
    Q_OBJECT

public:
    explicit zhuche(QWidget *parent = 0);
    ~zhuche();
    void zhucheren();

private:
    Ui::zhuche *ui;
};

#endif // ZHUCHE_H
