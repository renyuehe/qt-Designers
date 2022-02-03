#include "widget.h"
#include "ui_widget.h"
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

bool Filter::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        qDebug() << "sorry everybody, I gonna filter all the mouse event!";
        return true;
    }
    return QObject::eventFilter(obj,event);
}

/*!
 * \brief Widget::Widget
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
    qDebug() << "mouse press!";

    QWidget::mousePressEvent(event);
}
