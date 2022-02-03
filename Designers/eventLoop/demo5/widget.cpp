#include "widget.h"
#include "ui_widget.h"
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

/*!
 * \brief Filter::eventFilter 用于监听qApp的监听器
 * \return
 */
bool Filter::eventFilter(QObject *obj, QEvent *event)
{
    //阻止所有的鼠标点击事件
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
