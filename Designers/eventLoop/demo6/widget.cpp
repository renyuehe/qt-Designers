#include "widget.h"
#include "ui_widget.h"
#include "newmouseevent.h"
#include <QMouseEvent>
#include <QTimer>

/*!
 * \brief Widget::Widget
 * 创建并分发一种新的事件：鼠标连续点击10次
 * \param parent
 */
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->label->installEventFilter(this);

    ui->label->setText(tr("请连续点击屏幕以唤醒屏幕校准功能!"));
    ui->label->adjustSize();

    m_timer = new QTimer;
    m_timer->setInterval(1000);
    m_timer->start();
    connect(m_timer, SIGNAL(timeout()), SLOT(clearCount()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;

    if(m_timer->isActive())
        m_timer->stop(); //如果计时器在运行，则停止然后重新开始
    m_timer->start();

    count++;

    if(10 == count)
    {
        count = 0;

        NewMouseEvent event;
        qApp->sendEvent(ui->label, &event);
    }

    QWidget::mouseReleaseEvent(event);
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->label && event->type()== NewMouseEvent::MouseTenClick)
    {
        ui->label->setText(tr("你连续点击了10次屏幕，校准程序正在启动！"));
        ui->label->adjustSize();
        return true;
    }

    return QWidget::eventFilter(obj,event);
}

void Widget::clearCount()
{
    count = 0;
}
