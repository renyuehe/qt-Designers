#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QTime>

int count = 0;

/*!
 * \brief Widget::Widget 使用postEvent异步分发事件
 * 连续分发10个事件，在事件处理函数中逐个处理
 * \param parent
 */
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    int i = 1;
    while(i <= 10)
    {
        //postEvent传递的事件必须是通过new创建的
        qDebug() << "分发第" << i << "个事件";
        QApplication::postEvent(this, new QEvent(NewType));
        i++;
    }
}

//使用延时模拟来处理过程
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
