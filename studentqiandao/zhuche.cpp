#include "zhuche.h"
#include "ui_zhuche.h"
#include<QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QSqlQuery>
#include <QString>
#include "login.h"

zhuche::zhuche(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::zhuche)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("用户注册");
    this->setWindowIcon(QIcon(":/chenxu.jpg"));
    //取消
    connect(ui->cancelbtn,QPushButton::clicked,[=](){
        login *l=new login();
        l->show();
        this->close();
    });

    //添加班级
    QSqlQuery q;
    q.exec("select distinct clas from student");
    while(q.next())
    {
        ui->comboBoxclass->addItem(q.value(0).toString());
    }
    zhucheren();
}

zhuche::~zhuche()
{
    delete ui;
}


//注册
void zhuche::zhucheren()
{
    connect(ui->zhuchebtn,QPushButton::clicked,[=](){
        if(ui->lineEdituser->text().isEmpty()||ui->lineEditname->text().isEmpty()||ui->lineEditpassword->text().isEmpty())
        {
            QMessageBox::warning(this,"wrninig","姓名，学号，密码不能为空!!");
        }
        else
        {
            if(ui->lineEditpassword->text()!=ui->lineEditensurepassword->text())
            {
                QMessageBox::warning(this,"wrning","请确认两次密码一致");
                       ui->lineEditensurepassword->setText("");
            }
            else
            {
                QSqlQuery q;
                q.exec(QString("select * from student where sno='%1'").arg(ui->lineEdituser->text()));
                if(q.size())
                {
                    QMessageBox::warning(this,"wrning","该学号已经注册!");
                }
                else
                {
                  bool a=  q.exec(QString("insert into student values"
                                   "('%1','%2','%3','%4')").arg(ui->lineEdituser->text()).arg(ui->lineEditname->text()).arg(ui->comboBoxclass->currentText()).arg(ui->lineEditpassword->text()));
                    if(a)
                    {
                        QMessageBox::information(this,"注册提示","注册成功");
                        login *l=new login();
                        l->show();
                        this->close();
                    }
                    else
                    {
                        QMessageBox::warning(this,"wrning","注册失败");
                    }
                }
            }
        }
    });
}
