#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QSqlQuery>
#include <QString>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    QString strsno;
    explicit Widget(QWidget *parent = 0);
    void addstundet(QSqlQuery q);
    void addclass();
     void classselecgt();
    void  snoselecgt();
    void  displaystudent();
    void logininfo();
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
