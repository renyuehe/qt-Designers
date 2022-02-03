#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTime>

int count = 0;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    int i = 10;
    while(i > 0)
    {
        //postEvent传递的事件必须是通过new创建的
        QApplication::postEvent(this, new QEvent(NewType));
        i--;
    }
}

void Widget::customEvent(QEvent *event)
{
    if(event->type() == NewType)
    {
        qDebug() << "现在时间:" <<
                    QTime::currentTime().toString("hh::mm:ss.zzz");
        qDebug() << "第" << ++count << "次收到了事件！处理事件需要一点时间！";
        Delay(1000*2);
    }

    QWidget::customEvent(event);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Delay(unsigned int msec)
{
    QTime start = QTime::currentTime();

    QTime end;
    do{
        end = QTime::currentTime();
    } while(start.msecsTo(end) <= msec);
}
