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
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mouse press!" << ++count;
    QString string = ui->label->text();
    string.append(QString(" "));
    string.append(QString::number(count));
    ui->label->setText(string);
    QWidget::mousePressEvent(event);
}

void Widget::on_pushButton_clicked()
{
    Delay(1000*20); //延时10秒
}

void Widget::Delay(unsigned int msec)
{
    QTime start = QTime::currentTime();

    QTime end;
    do{
        end = QTime::currentTime();
    } while(start.msecsTo(end) <= msec);

}
