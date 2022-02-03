#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

/*!
 * \brief Widget::Widget 界面控件开启事件循环会否影响主界面的事件循环
 * \param parent
 */
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
    , m_dialog(NULL)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::event(QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
        qDebug() << "mainwindow mouse event!";
    return QWidget::event(event);
}

void Widget::on_pushButton_clicked()
{
    if(!m_dialog)
        m_dialog = new Dialog(this);

    m_dialog->show();
    m_dialog->exec();
}
