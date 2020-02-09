#include "widget.h"
#include "ui_widget.h"
#include  <QSqlDataBase>
#include <QDebug>
#include<QSqlQuery>
#include<QString>
#include <QCheckBox>
#include <QDatetime>
#include <QComboBox>
#include <QTableWidget>
#include <QPushButton>
#include <singalstudent.h>
#include "login.h"
#include <QMessageBox>
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowIcon(QIcon(":/chenxu.jpg"));
    this->setWindowTitle("签到系统主界面");
    ui->labeluser->setText("登陆用户："+strsno);
    ui->cancelbtn->setIcon(QIcon(":/exit.jpg"));
    ui->cancelbtn->setStyleSheet("border:0");
    ui->pushButtonselect->setIcon(QIcon(":/select.jpg"));
    ui->pushButtonselect->setIconSize(QSize(50,50));
    ui->cancelbtn->setIconSize(QSize(60,60));
    ui->pushButtonselect->setStyleSheet("border:0");
    QSqlQuery q0;
    q0.exec("select * from student");
     addstundet(q0);
     addclass();
     classselecgt();
     snoselecgt();
     displaystudent();
     //退出
     connect(ui->cancelbtn,QPushButton::clicked,[=](){
         login *l=new login();
         l->show();
         this->close();
     });
}


Widget::~Widget()
{
    delete ui;
}

//添加班级
void Widget::addclass()
{
      QSqlQuery q;
      q.exec("select distinct clas from student");
      while(q.next())
      {
          ui->comboBox->addItem(q.value(0).toString());
      }
}

//按班级查看学生信息
void Widget::classselecgt()
{
    connect(ui->comboBox,QComboBox::currentTextChanged,[=](QString str){
         QSqlQuery q1;
         if(str=="all")
         {
             q1.exec("select * from student");
         }
         else
         {
             q1.exec(QString("select * from student where clas='%1'").arg(str));
         }
         ui->tableWidget->clearContents();
         addstundet(q1);
    });
}

//按学号查看学生信息
void Widget::snoselecgt()
{

        connect(ui->pushButtonselect,QPushButton::clicked,[=](){
            if(!ui->lineEdit_2->text().isEmpty())
            {
                QSqlQuery q1;
               q1.exec(QString("select * from student where sno=%1").arg(ui->lineEdit_2->text()));
                ui->tableWidget->clearContents();
                addstundet(q1);
            }
        });
}

//添加学生信息
void Widget::addstundet(QSqlQuery q)
{
    int i=0;
    ui->tableWidget->setRowCount(q.size());
    while(q.next())
    {
        QCheckBox *check=new QCheckBox("未签到");
        QString sno1=q.value(0).toString();
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(sno1));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(q.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(q.value(2).toString()));
        ui->tableWidget->setCellWidget(i,3,check);

        //检查是否已经签到
           QSqlQuery q1;
            q1.exec(QString("select qiandaotmie from qiandao where sno=%1 and"
                            " date(qiandaotmie)=curdate() "
                            "order by qiandaotmie desc").arg(sno1));
            q1.next();
             if(q1.size())
             {
                 check->setChecked(true);
                 check->setText("已签到");
                 check->setDisabled(true);
                 ui->tableWidget->setItem(i,4,new QTableWidgetItem(q1.value(0).toString()));
             }

        //添加签到学生
        connect(check,QCheckBox::clicked,[=](){
            if(sno1==strsno)
            {
                check->setText("已签到");
                check->setDisabled(true);
                ui->tableWidget->setItem(i,4,new QTableWidgetItem(QDateTime::currentDateTime().toString()));
                QSqlQuery q2;
                q2.exec(QString("insert into qiandao values(%1,now())").arg(sno1));
            }
            else
            {
                check->setChecked(false);
                QMessageBox::warning(this,"worning","请签到自己的!");
            }
        });
        i++;
    }
}

//显示学生出勤情况
 void  Widget::displaystudent()
 {
     connect(ui->tableWidget,QTableWidget::cellDoubleClicked,[=](int r,int c){
         singalstudent *dispaly=new singalstudent();
         dispaly->show();
         dispaly->init(ui->tableWidget->item(r,0)->text(),ui->tableWidget->item(r,1)->text());
     });
 }

  void Widget::logininfo()
  {
      ui->labeluser->setText("登陆用户:"+this->strsno);
      ui->labellogintime->setText("时间:"+QDateTime::currentDateTime().toString());
      QTimer *timer=new QTimer();
      timer->start(1000);
      connect(timer,QTimer::timeout,[=](){
          ui->labellogintime->setText("时间:"+QDateTime::currentDateTime().toString());
      });
  }
