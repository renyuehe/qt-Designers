#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QResizeEvent>
#include <QDebug>

/*!
 * \brief Widget::Widget
 * 在事件循环分发事件给接收者之前，接收者被删除
 * \param parent
 */
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建小窗口
    m_label = new QLabel(this);
    m_label->setStyleSheet(QString("border:1px solid red;"));
    m_label->setGeometry(QRect(0,0,200,100));

    //在qApp发送事件之前销毁小窗口
    QTimer::singleShot(1000, this, SLOT(deleteLabel()));
    //qApp发送事件给小窗口
    QTimer::singleShot(2000, this, SLOT(slotSendEvent()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotSendEvent()
{
    QResizeEvent re(QSize(300,200), QSize(200,100));

    qDebug() << "qApp发送了一个事件给小窗口！";
    qApp->sendEvent(m_label, &re);
}

void Widget::deleteLabel()
{
    qDebug() << "小窗口被销毁了！";
    delete m_label;
    m_label = NULL;
}
