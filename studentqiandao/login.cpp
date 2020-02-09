#include "login.h"
#include "ui_login.h"
#include  <QSqlQuery>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <QSqlDatabase>
#include <widget.h>
#include<QDebug>
#include "zhuche.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
    {

    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowIcon(QIcon(":/chenxu.jpg"));
    this->setWindowTitle("签到登陆");
    loginbtn();
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("22qi");
    db.setUserName("root");
    db.setPassword("123456");
    if(db.open())
    {
        qDebug()<<"连接成功";
    }
    else
        {
           qDebug()<<"连接失败";
        }

    //取消
    connect(ui->quxiaobtn,QPushButton::clicked,[=](){
        ui->lineEditsno->clear();
        ui->lineEdit_password->clear();
    });

    //注册
    connect(ui->zhuchebtn,QPushButton::clicked,[=](){
        zhuche *zhu=new zhuche();
        zhu->show();
        this->close();
    });
}

login::~login()
{
    delete ui;
}

//登陆
void login::loginbtn()
{
    connect(ui->loginbtn,QPushButton::clicked,[=](){
        if(ui->lineEditsno->text()==NULL||ui->lineEdit_password->text()==NULL)
        {
            QMessageBox::warning(this,"登陆提示！","用户名或密码不能为空！");
        }
        else
        {
           QSqlQuery q;
           q.exec(QString("select loginuser('%1','%2')").arg(ui->lineEditsno->text()).arg(ui->lineEdit_password->text()));
           q.next();
           if(q.value(0).toString()=="登陆成功")
           {
               Widget *w=new Widget();
               w->strsno=ui->lineEditsno->text();
               w->logininfo();
               w->show();
               this->close();
           }
           else
           {
               QMessageBox::warning(this,"登陆提示！",q.value(0).toString());
           }
        }
    });
}
