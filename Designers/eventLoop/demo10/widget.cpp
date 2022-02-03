#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTime>

int count = 0;

/*!
 * \brief Widget::Widget
 * 通过QEventLoop开启一个新的事件循环分发事件
 * \param parent
 */
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "事件循环正常！" << ++count;
    QWidget::mousePressEvent(event);
}

void Widget::on_pushButton_clicked()
{
    //延时30秒模拟耗时操作
    Delay(1000*30);
}

void Widget::Delay(unsigned int msec)
{
    QTime start = QTime::currentTime();

    QTime end;
    do{
        end = QTime::currentTime();
        //处理过程中手动分发事件
        QEventLoop loop;
        loop.exec();
    } while(start.msecsTo(end) <= msec);
}
