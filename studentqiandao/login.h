#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QString>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:

    explicit login(QWidget *parent = 0);
    ~login();
    void loginbtn();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
