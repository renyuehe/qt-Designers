#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

int count = 0;

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
    while(1) //死循环模拟耗时操作
    {
        QEventLoop loop;
        loop.exec();
    }
}
