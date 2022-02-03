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

void Widget::on_buttondeadloop_clicked()
{
    while(1) //死循环!!!
    {
        //do something
        qApp->processEvents();
    }
}
