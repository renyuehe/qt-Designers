#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

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
#if 0
    if(!m_dialog)
        m_dialog = new Dialog(this);

    m_dialog->show();
    m_dialog->exec();
#else
    Dialog dlg;
    dlg.show();
    QEventLoop loop;
    loop.exec();
#endif
}
