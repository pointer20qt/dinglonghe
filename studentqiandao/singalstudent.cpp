#include "singalstudent.h"
#include "ui_singalstudent.h"
#include <QSqlQuery>
#include <QTextCharFormat>
#include <QDebug>
#include <QCalendarWidget>

singalstudent::singalstudent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::singalstudent)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("个人详细签到信息");
    this->setWindowIcon(QIcon(":/chenxu.jpg"));
}

singalstudent::~singalstudent()
{
    delete ui;
}


//初始化每个学生签到的具体信息
 void singalstudent::init(QString sno,QString sname)
 {
     ui->labelname->setText("姓名："+sname);
     ui->labesno->setText("学号："+sno);
     QTextCharFormat qtext;
     qtext.setForeground(Qt::blue);
     qtext.setBackground(Qt::yellow);
     QSqlQuery q;
     q.exec(QString("select qiandaotmie from qiandao where sno='%1'").arg(sno));
     while(q.next())
     {
         ui->calendarWidget->setDateTextFormat(q.value(0).toDate(),qtext);
     }
     QSqlQuery q1;
          q1.exec(QString("select qiandaotmie from qiandao where "
                         "date_format(qiandaotmie,'%Y-%m')=date_format(curdate(),'%Y-%m') "
                         "and sno='%1'").arg(sno));
     ui->labelqiandao->setText("签到次数："+QString::number(q1.size()));
     ui->progressBar->setMaximum(31);
     ui->progressBar->setMinimum(0);
     ui->progressBar->setValue(q1.size());

     //显示每个月的签到信息
     connect(ui->calendarWidget,QCalendarWidget::currentPageChanged,[=](){
         QString year=QString::number(ui->calendarWidget->yearShown());
         QString month=QString::number(ui->calendarWidget->monthShown());
         QString curdate=year+"-"+month;
         QSqlQuery q2;
            q2.exec(QString("select qiandaotmie from  "
                                        "qiandao where date_format(qiandaotmie,'%Y-%m')="
                                        "date_format(str_to_date('%1','%Y-%m-%d'),'%Y-%m') "
                                           "and sno='%2'").arg(curdate).arg(sno));
         ui->labelqiandao->setText("签到次数："+QString::number(q2.size()));
         ui->progressBar->setValue(q2.size());
     });
 }
