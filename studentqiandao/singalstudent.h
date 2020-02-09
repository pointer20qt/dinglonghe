#ifndef SINGALSTUDENT_H
#define SINGALSTUDENT_H

#include <QWidget>
#include <QString>

namespace Ui {
class singalstudent;
}

class singalstudent : public QWidget
{
    Q_OBJECT

public:
    explicit singalstudent(QWidget *parent = 0);
    void init(QString sno,QString sname);
    ~singalstudent();

private:
    Ui::singalstudent *ui;
};

#endif // SINGALSTUDENT_H
